// Programmer: Jack Case
// Student Id: 12601013
// Section: 301
// Date: 04/20/2024
// File: main.cpp
// Purpose: A program that allows users to play games of blackjack.

#include <iostream>
#include <string>
#include "blackjack.h"

using namespace std;

int main() {
	Player player1 = {};
	Hand dealer_hand = {};
	Deck deck = {};
	int og_bal = 0;
	float wager = 0;
	float temp_balance = 0;
	float balance = 0;
	bool player_turn_over = false;
	bool gameover = false;
	bool bust_or_black = false;
	bool first_time = true;
	string first_choice = "";
	string choice = "";
	string advice = "";
	string again = "y";
	

	cout << "Enter player name: ";
	cin >> player1.name;

	// Assign random balance to player between 100 and 1000
	srand(1570);
	player1.balance = 100.00 + rand() % 901 + (static_cast<float>(rand() % 101) / 100);
	cout << player1.name << "'s Balance: " << player1.balance << endl;
	og_bal = player1.balance;

	// Do While
	do {
		// Reset variables
		clearHand(player1.current_hand);
		clearHand(dealer_hand);
		clearDeck(deck);
		temp_balance = player1.balance;
		player_turn_over = false;
		gameover = false;
		bust_or_black = false;
		first_time = true;
		first_choice = "";
		choice = "";
		advice = "";

		// Prompt for wager
		cout << "How much would you like to wager?" << endl;
		while (!(cin >> wager) || wager <= 0 || wager > player1.balance) {

			cin.clear();
			cin.ignore(100000, '\n');

			if (wager <= 0) {
				cout << "Invalid wager. Please enter a positive integer." << endl;
			} else if (wager > player1.balance) {
				cout << "You don't have that kind of money!" << endl;
			}
		}	

		// Initialize hands
		// Check if player is lucky:
		if ((rand() % 101) <= 15)
		{
			addCard(player1.current_hand, generateRandomCard(deck, 1,13, rand() % 101));
			addCard(player1.current_hand, generateRandomCard(deck, 1,13, rand() % 101));
		}
		else
		{
			addCard(player1.current_hand, generateRandomCard(deck, 1,13));
			addCard(player1.current_hand, generateRandomCard(deck, 1,13));
		}
		addCard(dealer_hand, generateRandomCard(deck, 1,13));
		addCard(dealer_hand, generateRandomCard(deck, 1,13));

		// Print Hands
		cout << endl;
		printHand(player1.current_hand, player1.name);

		cout << "Dealers's Hand: " << dealer_hand.cards[0].name_value << " of " << dealer_hand.cards[0].suit 
		<< ", [Hidden Card]" << endl;
		cout << endl;
		// Check for blackjack
		if (isBlackjack(player1.current_hand) && !(isBlackjack(dealer_hand)))
		{
			// Game Over
			player1.wins_blackjack++;
			updatePlayerBalance(&player1.balance, wager, true);
			displayOutcome("playerblackjack", player1.balance, temp_balance);
			gameover = true;
			player_turn_over = true;
			bust_or_black = true;
		}
		else if (!(isBlackjack(player1.current_hand)) && (isBlackjack(dealer_hand)))
		{
			// Game Over
			player1.losses_blackjack++;
			updatePlayerBalance(&player1.balance, wager, false);
			cout << endl;
			displayOutcome("dealerblackjack", player1.balance, temp_balance);
			cout << endl;
			printHand(player1.current_hand, player1.name);
			printHand(dealer_hand, "Dealer");
			gameover = true;
			player_turn_over = true;
			bust_or_black = true;
		}
		else if ((isBlackjack(player1.current_hand)) && (isBlackjack(dealer_hand)))
		{
			// Game Over
			printHand(player1.current_hand, player1.name);
			printHand(dealer_hand, "Dealer");
			displayOutcome("tie", player1.balance, temp_balance);
			player1.ties_blackjack++;
			gameover = true;
			player_turn_over = true;
			bust_or_black = true;
		}

		// Players Turn

		if (!player_turn_over && !gameover)
		{
			cout << player1.name << "'s Turn." << endl;
		}

		first_time = true;
		while (!player_turn_over && !gameover)
		{
			if (getTotal(player1.current_hand) == 21)
			{
				player_turn_over = true;
				break;
			}
			else if (getTotal(player1.current_hand) > 21)
			{
				// Game Over, player bust
				updatePlayerBalance(&player1.balance, wager, advice, choice, false);
				cout << "Player Bust." << endl << endl;
				displayOutcome("dealerwin", player1.balance, temp_balance);
				gameover = true;
				player_turn_over = true;
				bust_or_black = true;
				player1.losses_regular++;
				break;
			}
			else
			{
				cout << "Choose (Hit), (Stand), or (Double-Down)" << endl;
				if (first_time)
				{
					// Advise Player
					advice = adviseOptimalOptionOnLuck<int>((rand() % 101), getTotal(player1.current_hand), dealer_hand.cards[0].num_value);
					cout << "Advise: " << advice << endl;
					first_time = false;
				}
				cin >> choice;
				// Make sure player chooses valid choice
				while ((choice != "Hit") && (choice != "Stand") && (choice != "Double-Down"))
				{
					cout << "Choose (Hit), (Stand), or (Double-Down)" << endl;
					cin >> choice;
				}

				if (choice == "Double-Down" && (wager * 2) > player1.balance)
				{
					cout << "You don't have that kind of money!" << endl;
					cin >> choice;
					while ((choice != "Hit") && (choice != "Stand"))
					{
						cout << "Choose (Hit), (Stand)" << endl;
						cin >> choice;
					}
				}

				first_choice = (first_time) ? choice : first_choice;

				if (choice == "Hit")
				{
					addCard(player1.current_hand, generateRandomCard(deck, 1,13));
					printHand(player1.current_hand, player1.name);

				}
				else if (choice == "Stand")
				{
					player_turn_over = true;
				}
				else if (choice == "Double-Down")
				{
					wager = wager * 2;
					addCard(player1.current_hand, generateRandomCard(deck, 1,13));
					printHand(player1.current_hand, player1.name);
					if (getTotal(player1.current_hand) > 21)
					{
						// Game Over
						updatePlayerBalance(&player1.balance, wager, advice, choice, false);
						displayOutcome("dealerwin", player1.balance, temp_balance);
						bust_or_black = true;
						player1.losses_regular++;
						gameover = true;
					}
					player_turn_over = true;
					
				}
			}
		}
		// Dealers Turn
		cout << endl;
		if (!gameover)
		{
			cout << "Dealer's Turn" << endl;
			printHand(dealer_hand, "Dealer");
			while (getTotal(dealer_hand) < 17)
			{
				addCard(dealer_hand, generateRandomCard(deck, 1,13));
				cout << "Dealer Hits." << endl;
				printHand(dealer_hand, "Dealer");
			}

			if (getTotal(dealer_hand) > 21)
			{
				// Game over
				updatePlayerBalance(&player1.balance, wager, advice, choice, true);
				cout << "Dealer Bust!" << endl << endl;
				displayOutcome("playerwin", player1.balance, temp_balance);
				bust_or_black = true;
				player1.wins_normal++;
			}
			else
			{
				cout << "Dealer Stands." << endl;
			}
			
		}
		cout << endl;
		// Determine Winner if not already determined

		if (!bust_or_black)
		{
			printHand(player1.current_hand, player1.name);
			printHand(dealer_hand, "Dealer");

			if (getTotal(player1.current_hand) > getTotal(dealer_hand))
			{
				updatePlayerBalance(&player1.balance, wager, advice, choice, true);
				displayOutcome("playerwin", player1.balance, temp_balance);
				player1.wins_normal++;
			}
			else if (getTotal(player1.current_hand) < getTotal(dealer_hand))
			{
				updatePlayerBalance(&player1.balance, wager, advice, choice, false);
				displayOutcome("dealerwin", player1.balance, temp_balance);
				player1.losses_regular++;
			}
			else if (getTotal(player1.current_hand) == getTotal(dealer_hand))
			{
				displayOutcome("tie", player1.balance, temp_balance);
				player1.ties_regular++;
			}
		}
		player1.rounds++;
		
		if (player1.balance <= 0)
		{
			cout << "Out of Money!" << endl << endl;
			again = 'n';
		}
		else
		{
			cout << "Play Again? (y/n)" << endl;
			cin >> again;
			while (again != "y" && again != "n")
			{
				cout << "Please Enter (y/n)" << endl;
				cin >> again;
			}
		}
		
	} while(again == "y");

	if (player1.balance > 0)
	{
		balance = player1.balance;
	}
	else
	{
		balance = 0;
	}

	displayGameSummary(player1.rounds, player1.wins_normal, player1.wins_blackjack, player1.losses_regular, player1.losses_blackjack, player1.ties_regular, player1.ties_blackjack, balance, player1.balance - og_bal);

	return 0;
}
