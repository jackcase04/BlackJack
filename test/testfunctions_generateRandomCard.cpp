#include "gtest/gtest.h"
#include "blackjack.h" // Include header file where functions are declared

using namespace std;

class GenerateRandomCardTest : public ::testing::Test {
protected:
    Card card = {};
    int num = 0;

    // Setup function
    void SetUp() override {
        // Any setup tasks that need to be performed before each test case
        srand(12345);
    }

    // Teardown function
    void TearDown() override {
        // Any cleanup tasks that need to be performed after each test case
    }
};

TEST_F(GenerateRandomCardTest, numWithinRange)
{
    const int min = 1;
    const int max = 13;
    Card card = generateRandomCard(min, max);
    EXPECT_GE(card.num_value, min);
    EXPECT_LE(card.num_value, max);
}

TEST_F(GenerateRandomCardTest, returnsNum)
{
    const int min = 5;
    const int max = 5;
    Card card = generateRandomCard(min, max);

    EXPECT_EQ(card.name_value, "5");

}

TEST_F(GenerateRandomCardTest, returnsAce)
{
    const int min = 1;
    const int max = 1;
    Card card = generateRandomCard(min, max);

    EXPECT_EQ(card.name_value, "Ace");
}

TEST_F(GenerateRandomCardTest, returnsJack)
{
    const int min = 1;
    const int max = 13;
    Card card = generateRandomCard(min, max);

    if (card.num_value == 11) 
    {
    EXPECT_EQ(card.name_value, "Jack");
    }
}

TEST_F(GenerateRandomCardTest, returnsQueen)
{
    const int min = 1;
    const int max = 13;
    Card card = generateRandomCard(min, max);

    if (card.num_value == 12) 
    {
    EXPECT_EQ(card.name_value, "Queen");
    }
}

TEST_F(GenerateRandomCardTest, returnsKing)
{
    const int min = 1;
    const int max = 13;
    Card card = generateRandomCard(min, max);

    if (card.num_value == 13) 
    {
    EXPECT_EQ(card.name_value, "King");
    }
}


// Not working
// TEST_F(GenerateRandomCardTest, returnsCorrectSuit)
// {
//     map<int, string> suit_map = {
//         {1, "Hearts"},
//         {2, "Diamonds"},
//         {3, "Clubs"},
//         {4, "Spades"}
//     };

//     for (int num = 1; num <= 4; ++num) {
//         Card card = generateRandomCard(1, 13);

//         EXPECT_EQ(card.suit, suit_map[num]);
//     }
// }
// Not working
// TEST_F(GenerateRandomCardTest, suitWithinRange)
// {
//     const int min = 1;
//     const int max = 4;

//     EXPECT_GE(num, min);
//     EXPECT_LE(num, max);
// }