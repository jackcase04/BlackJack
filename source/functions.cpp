#include <iostream>
#include "blackjack.h"
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

bool isBlackjack(vector<Card> hand)
{
    if (hand.size() != 2)
    {
        return false;
    }
    else if (((hand[0].num_value == 10) && (hand[1].num_value == 11)) || 
        ((hand[0].num_value == 11) && (hand[1].num_value == 10))) 
    {
        return true;
    }
    else 
    {
        return false;
    }
}

Card generateRandomCard(const int min, const int max) 
{
    Card card = {};
    int num = 0;
    //card.num_value = min + rand() % max;
    card.num_value = rand() % (max - min + 1) + min;

    if (card.num_value == 1)
    {
        card.num_value = 11;
        card.name_value = "Ace";
    } 
    else if ((card.num_value > 1) && (card.num_value <= 10))
    {
        card.name_value = std::to_string(card.num_value);
    }
    else if (card.num_value == 11)
    {
        card.num_value = 10;
        card.name_value = "Jack";
    }
    else if (card.num_value == 12)
    {
        card.num_value = 10;
        card.name_value = "Queen";
    }
    else if (card.num_value == 13)
    {
        card.num_value = 10;
        card.name_value = "King";
    }

    num = 1 + rand() % 4;
    switch(num)
    {
        case 1:
            card.suit = "Hearts";
            break;
        case 2:
            card.suit = "Diamonds";
            break;
        case 3:
            card.suit = "Clubs";
            break;
        case 4:
            card.suit = "Spades";
            break;
    }

    return card;
}

Card generateRandomCard(const int min, const int max, const int probability) 
{
    Card card = {};
    int num = 0;
    card.num_value = min + rand() % max;
    int random = (rand() % 101);
    if (random <= probability)
    {
        card.num_value = 11 + rand() % 3;
    }

    if (card.num_value == 1)
    {
        card.num_value = 11;
        card.name_value = "Ace";
    } 
    else if ((card.num_value > 1) && (card.num_value <= 10))
    {
        card.name_value = std::to_string(card.num_value);
    }
    else if (card.num_value == 11)
    {
        card.num_value = 10;
        card.name_value = "Jack";
    }
    else if (card.num_value == 12)
    {
        card.num_value = 10;
        card.name_value = "Queen";
    }
    else if (card.num_value == 13)
    {
        card.num_value = 10;
        card.name_value = "King";
    }

    num = 1 + rand() % 4;
    switch(num)
    {
        case 1:
            card.suit = "Hearts";
            break;
        case 2:
            card.suit = "Diamonds";
            break;
        case 3:
            card.suit = "Clubs";
            break;
        case 4:
            card.suit = "Spades";
            break;
    }

    return card;
}

void outputPlayerHand(Player player)
{
    cout << player.name << "'s Hand: ";
    for (unsigned int i = 0; i <= (player.current_hand.size() - 1); i++)
    {
        cout << player.current_hand[i].name_value << " of " << player.current_hand[i].suit;
        if (i != (player.current_hand.size() - 1))
        {
            cout << ", ";
        }
    }
    cout << endl;
}

void outputDealerHand(vector<Card> hand)
{
    cout << "Dealer's Hand: ";
    for (unsigned int i = 0; i <= (hand.size() - 1); i++)
    {
        cout << hand[i].name_value << " of " << hand[i].suit;
        if (i != (hand.size() - 1))
        {
            cout << ", ";
        }
    }
    cout << endl;
}

int getTotal(vector<Card> hand)
{
    int aces_in_hand = 0;
    int sum = 0;
    for (unsigned int i = 0; i <= (hand.size() - 1); i++)
    {
        sum += hand[i].num_value;
        if (hand[i].num_value == 11)
        {
            aces_in_hand++;
        }
    }
    for (int i = 0; i < aces_in_hand; ++i)
    {
        if (sum > 21)
        {
            sum = sum - 10;
        }
    }
    return sum;
}

void updatePlayerBalance(float*balance, float wager, bool player_win)
{
    if (player_win)
    {
        wager = wager * 1.5;
        *balance += wager;
    }
    else if (!player_win)
    {
        *balance -= wager;
    }
}

void updatePlayerBalance(float*balance, float wager, string adviceGiven, string choice, bool player_win)
{
    if (player_win && (adviceGiven == choice))
    {
        *balance += wager;
    }
    else if (!player_win && (adviceGiven == choice))
    {
        *balance -= wager * 0.8;
    }
    else if (player_win && (adviceGiven != choice))
    {
        *balance += wager + (0.8 * wager);
    }
    else if (!player_win && (adviceGiven != choice))
    {
        *balance -= (wager + (0.2 * wager));
    }
}

void displayOutcome(string outcome, float balance, float temp_balance)
{
    cout << "=== Round Results === " << endl;
    if (outcome == "playerblackjack")
    {
        cout << "Congratulations! You hit Blackjack!" << endl;
    }
    else if (outcome == "dealerblackjack")
    {
        cout << "Dealer hit Blackjack." << endl;
    }
    else if (outcome == "tie")
    {
        cout << "It's a tie!" << endl;
    }
    else if (outcome == "playerwin")
    {
        cout << "Congratulations! You win!" << endl;
    }
    else if (outcome == "dealerwin")
    {
        cout << "Dealer wins." << endl;
    }

    if (balance > temp_balance)
    {
        cout << "Balance Update: +" << (balance - temp_balance) << endl;
        cout << "Your New Balance is: " << balance << endl;
    }
    else if (balance < temp_balance)
    {
        cout << "Balance Update: -" << (temp_balance - balance) << endl;
        cout << "Your New Balance is: " << balance << endl;
    }
}

void displayGameSummary(int rounds, int wins_reg, int wins_black, 
int losses_reg, int losses_black, int ties_reg, int ties_black, 
float balance, float diff)
{
    cout << "=== Game Summary === " << endl;
    cout << "Total Rounds Played: " << rounds << endl;
    cout << "Total Wins (Regular): " << wins_reg << endl;
    cout << "Total Wins (Blackjack): " << wins_black << endl;
    cout << "Total Losses (Regular): " << losses_reg << endl;
    cout << "Total Losses (Blackjack): " << losses_black << endl;
    cout << "Total Ties (Regular): " << ties_reg << endl;
    cout << "Total Ties (Blackjack): " << ties_black << endl;
    cout << "Final Balance: $" << balance << endl;
    cout << "Net Gain/Loss: " << diff << endl << endl;
    cout << "Thank you for playing CodeJack: The Blackjack Simulator!" << endl << "We hope to see you again soon." << endl;
}