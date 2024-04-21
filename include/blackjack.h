#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <iostream>
#include <string>

using namespace std;

struct Card {
	string suit;
	string name_value;
	int num_value;

    bool operator==(const Card& card) const {
        return (name_value == card.name_value) && (suit == card.suit);
    }

    friend ostream& operator<<(ostream& os, const Card& card) {
        os << card.name_value << " of " << card.suit;
        return os;
    }
};

struct Hand {
    int index;
    Card cards[17];
};

struct Deck {
    int index;
    Card cards[52];
};

struct Player {
	float balance;
	Hand current_hand;
	int rounds;
	int wins_blackjack;
	int wins_normal;
	int losses_blackjack;
	int losses_regular;
	int ties_blackjack;
	int ties_regular;
	string name;
};

// This function generates a random card value within an acceptable range. 
// Pre: integer min, integer max
// Post: Returns a randomly generated structure Card.
Card generateRandomCard(Deck& deck, const int min, const int max);

// This special version not only generates a random card value but also incorporates a “luck factor”
// that occasionally increases the likelihood of drawing a 10-valued card.
// Pre: integer min, integer max, integer probability
// Post: Returns a randomly generated structure Card that has a higher chance of being a face card.
Card generateRandomCard(Deck& deck, const int min, const int max, const int probability);

bool isCardAlreadyUsed(Deck deck, Card card);

// Determines whether a function is blackjack
// Pre: vector of structures Cards.
// Post: Returns true if the hand provided is Blackjack, returns false otherwise.
bool isBlackjack(Hand hand);

// This function takes a hand and returns the score of that hand.
// Pre: vector of structures Cards.
// Post: Returns an integer that is the score of that hand.
int getTotal(Hand hand);

// This function prints the players hand.
// Pre: Structure Player.
// Post: Prints the players hand along with thier name.
void outputHand(Hand hand, string name);

// This fucntion updates the player’s balance after each round.
// Pre: float balance, float wager, and bool player_win
// Post: Via passing by refrence, the players balance is altered.
void updatePlayerBalance(float*balance, float wager, bool player_win);

// This function is overloaded to take into account the outcome of the game and whether they followed the strategic advice provided.
// Pre: float balance, float wager, string adviceGiven, string choice, and bool player_win.
// Post: Via passing by refrence, the players balance is altered.
void updatePlayerBalance(float*balance, float wager, string adviceGiven, string choice, bool player_win);

// This function displays a message indicating the game outcome of the current round and any changes to the player’s balance.
// Pre: string outcome, float balance, and float temp_balance
// Post: Prints the outcome of the round. 
void displayOutcome(string outcome, float balance, float temp_balance);

// This function Provides a detailed summary of the player’s entire game session upon exiting the program.
// Pre: int rounds, int wins_reg, int wins_black, int losses_reg, int losses_black, int ties_reg, int ties_black, float balance, and float diff.
// Post: Prints a summary of the game.
void displayGameSummary(int rounds, int wins_reg, int wins_black, 
int losses_reg, int losses_black, int ties_reg, int ties_black, 
float balance, float diff);

//
// Pre:
// Post:
void clearHand(Hand& hand);

//
// Pre:
// Post:
void clearDeck(Deck& deck);

//This function offers strategic recommendations to the player 
// if the probability threshold is met; otherwise, it suggests a random action.
// I had to implement this template function here in the header file otherwise I could not get my program to compile.
// Pre: T probability_threshold, int playerTotal, and int dealerUpCard.
// Post: Returns a string advising the player on what they should do.
template <typename T> 
string adviseOptimalOptionOnLuck(const T probability_threshold, const int playerTotal, const int dealerUpCard)
{
    string result = "";
    int chance = rand() % 101;
    if (chance > probability_threshold)
    {
        if (playerTotal >= 9 && playerTotal <= 11)
        {
            result = "Double-Down";
        }
        else if (playerTotal < 11)
        {
            result = "Hit";
        }
        else if (playerTotal >= 12 && playerTotal <= 16)
        {
            if (dealerUpCard >= 7)
            {
                result = "Hit";
            }
            else
            {
                result = "Stand";
            }
        }
        else if (playerTotal >= 17)
        {
            result = "Stand";
        }
    }
    else
    {
        int rec = rand() % 3;
        switch(rec)
        {
            case 0:
                result = "Stand";
                break;
            case 1:
                result = "Hit";
                break;
            case 2:
                result = "Double-Down";
                break;
        }
    }
    return result;
}  

template <typename T> 
void addCard(T& cardArray, Card card)
{
    cardArray.cards[cardArray.index].name_value = card.name_value;
    cardArray.cards[cardArray.index].num_value = card.num_value;
    cardArray.cards[cardArray.index].suit = card.suit;
    cardArray.index++;
}

template <typename T> 
void printArray(T& cardArray)
{
    cout << "Printing Array" << endl;
    for (int i = 0; i < cardArray.index; i++) {
        cout << cardArray.cards[i] << endl;
    }
}
#endif
