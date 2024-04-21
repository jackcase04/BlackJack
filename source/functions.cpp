#include <iostream>
#include <string>
#include <cstdlib>
#include "blackjack.h"

using namespace std;

bool isBlackjack(Hand hand)
{
    if (hand.index != 2)
    {
        return false;
    }
    else if (((hand.cards[0].num_value == 10) && (hand.cards[1].num_value == 11)) || 
        ((hand.cards[0].num_value == 11) && (hand.cards[1].num_value == 10))) 
    {
        return true;
    }
    else 
    {
        return false;
    }
}

Card generateRandomCard(Deck& deck, const int min, const int max) 
{
    Card card = {};
    int num = 0;
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

    if (isCardAlreadyUsed(deck, card)) {
        //cout << "Card already used, generating new card" << endl;
        //cout << "Card is: " << card << endl;
        return generateRandomCard(deck, min, max);
    } else {
        addCard(deck, card);
        //printArray(deck);
        return card;
    }
}

Card generateRandomCard(Deck& deck, const int min, const int max, const int probability) 
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

    if (isCardAlreadyUsed(deck, card)) {
        //cout << "Card already used, generating new card" << endl;
        //cout << "Card is: " << card << endl;
        return generateRandomCard(deck, min, max, probability);
    } else {
        addCard(deck, card);
        //printArray(deck);
        return card;
    }
}

bool isCardAlreadyUsed(Deck deck, Card card) {
    bool result = false;
    for (int i = 0; i < deck.index; i++) {
        if (deck.cards[i] == card) {
            result = true;
        }
    }
    return result;
}

void clearHand(Hand& hand) {
    for(int i = 0; i < 17; ++i) {
        hand.cards[i].num_value = 0;
        hand.cards[i].name_value = "";
        hand.cards[i].suit = "";
    }
    hand.index = 0;
}

void clearDeck(Deck& deck) {
    for(int i = 0; i < 52; ++i) {
        deck.cards[i].num_value = 0;
        deck.cards[i].name_value = "";
        deck.cards[i].suit = "";
    }
    deck.index = 0;
}

void printHand(Hand& hand, string name)
{
    for (int i = 0; i < hand.index; i++) {
        for (int j = 0; j < hand.index - i - 1; j++) {
            if (hand.cards[j+1] > hand.cards[j]) {
				swap(hand.cards[j], hand.cards[j+1]);
            }
        }
    }

    cout << name << "'s Hand: ";
    for (int i = 0; i < hand.index; i++)
    {
        cout << hand.cards[i];
        if (i != (hand.index - 1))
        {
            cout << ", ";
        }
    }
    cout << endl;
}

int getTotal(Hand hand)
{
    int aces_in_hand = 0;
    int sum = 0;
    for (int i = 0; i < hand.index; i++)
    {
        sum += hand.cards[i].num_value;
        if (hand.cards[i].num_value == 11)
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