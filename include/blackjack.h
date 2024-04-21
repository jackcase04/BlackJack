#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <iostream>
#include <string>

using namespace std;

struct Card {
	string suit;
	string name_value;
	int num_value;

    // This operator == is overloaded for the struct Card to check if cards are the same.
    // Pre: Two structs Card.
    // Post: A true or false value.
    bool operator==(const Card& card) const {
        return (name_value == card.name_value) && (suit == card.suit);
    }

    // This operator << is overloaded to print a Card more easily.
    // Pre: A struct Card.
    // Post: A printed statement of the Card.
    friend ostream& operator<<(ostream& os, const Card& card) {
        os << card.name_value << " of " << card.suit;
        return os;
    }
    
    // This operator > is overloaded to check which card is greater in the sorting algorithm.
    // The order goes as such: Diamonds, Hearts, Clubs, then Spades, and if they are the same,
    // then goes Ace, 2-10, Jack, Queen, King.
    bool operator>(const Card& card) const {
        if ((suit == "Diamonds") && (card.suit != "Diamonds")) {
            return true;
        } else if ((suit == "Hearts") && ((card.suit == "Clubs") || (card.suit == "Spades"))) {
            return true;
        } else if ((suit == "Clubs") && (card.suit == "Spades")) {
            return true;
        } else if (suit == card.suit) {
            if (name_value == "Ace") {
                return true;
            } else if ((name_value == "Jack") && ((card.name_value == "Queen") || (card.name_value == "King"))) {
                return true;
            } else if ((name_value == "Queen") && (card.name_value == "King")) {
                return true;
            } else if (((name_value != "Ace") && (num_value != 10)) && num_value < card.num_value) {
                return true;
            } 
        } 
        return false;
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

// This function generates a random card value within an acceptable range,
// making sure that it has not been drawn before. 
// Pre: Struct Deck, integer min, integer max
// Post: Returns a randomly generated structure Card.
Card generateRandomCard(Deck& deck, const int min, const int max);

// This special version not only generates a random card value but also incorporates a “luck factor”
// that occasionally increases the likelihood of drawing a 10-valued card.
// Pre: Struct Deck, integer min, integer max, integer probability
// Post: Returns a randomly generated structure Card that has a higher chance of being a face card.
Card generateRandomCard(Deck& deck, const int min, const int max, const int probability);

// This function checks if a card has already been drawn.
// Pre: Struct Deck, Struct Card
// Post: Returns true or false based on if it has been drawn yet or not.
bool isCardAlreadyUsed(Deck deck, Card card);

// Determines whether a function is blackjack
// Pre: Struct Hand.
// Post: Returns true if the hand provided is Blackjack, returns false otherwise.
bool isBlackjack(Hand hand);

// This function takes a hand and returns the score of that hand.
// Pre: Struct Hand.
// Post: Returns an integer that is the score of that hand.
int getTotal(Hand hand);

// This function sorts the players hand and then prints it.
// Pre: Struct Hand, string name.
// Post: Prints the players hand along with thier name.
void printHand(Hand& hand, string name);

// This function updates the player’s balance after each round.
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

// This function clears the provided hand.
// Pre: Struct Hand
// Post: Via passing by refrence, clears the hand.
void clearHand(Hand& hand);

// This function clears the deck.
// Pre: Struct Hand
// Post: Via passing by refrence, clears the deck.
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

// This function adds a card to an array.
// Pre: type T array, Struct Card.
// Post: Via passing by refrence, adds a card to the passed array.
template <typename T> 
void addCard(T& cardArray, Card card)
{
    cardArray.cards[cardArray.index].name_value = card.name_value;
    cardArray.cards[cardArray.index].num_value = card.num_value;
    cardArray.cards[cardArray.index].suit = card.suit;
    cardArray.index++;
}

// This function prints an array (used for testing).
// Pre: type T array.
// Post: Prints an array.
template <typename T> 
void printArray(T& cardArray)
{
    cout << "Printing Array" << endl;
    for (int i = 0; i < cardArray.index; i++) {
        cout << cardArray.cards[i] << endl;
    }
}

#endif
