#include "gtest/gtest.h"
#include "blackjack.h" // Include header file where functions are declared

using namespace std;

class IsBlackjackTest : public ::testing::Test {
protected:
    vector<Card> testHand;
    Card tempHand;

    // Setup function
    void SetUp() override {
        // Any setup tasks that need to be performed before each test case
        testHand.clear();
        tempHand = {};
    }

    // Teardown function
    void TearDown() override {
        // Any cleanup tasks that need to be performed after each test case
    }
};

TEST_F(IsBlackjackTest, blackjackIsTrue1)
{
    tempHand.num_value = 10;
    testHand.push_back(tempHand);
    tempHand.num_value = 11;
    testHand.push_back(tempHand);
    EXPECT_EQ(isBlackjack(testHand), true);
}

TEST_F(IsBlackjackTest, blackjackIsTrue2)
{
    tempHand.num_value = 11;
    testHand.push_back(tempHand);
    tempHand.num_value = 10;
    testHand.push_back(tempHand);
    EXPECT_EQ(isBlackjack(testHand), true);
}

TEST_F(IsBlackjackTest, blackjackIsFalseSizeZero)
{
    EXPECT_EQ(isBlackjack(testHand), false);
}

TEST_F(IsBlackjackTest, blackjackIsFalseSizeTooSmall)
{
    tempHand.num_value = 11;
    testHand.push_back(tempHand);
    EXPECT_EQ(isBlackjack(testHand), false);
}

TEST_F(IsBlackjackTest, blackjackIsFalseSizeTooBig)
{
    tempHand.num_value = 11;
    testHand.push_back(tempHand);
    tempHand.num_value = 10;
    testHand.push_back(tempHand);
    tempHand.num_value = 10;
    testHand.push_back(tempHand);
    EXPECT_EQ(isBlackjack(testHand), false);
}

TEST_F(IsBlackjackTest, blackjackIsFalse)
{
    tempHand.num_value = 1;
    testHand.push_back(tempHand);
    tempHand.num_value = 2;
    testHand.push_back(tempHand);
    EXPECT_EQ(isBlackjack(testHand), false);
}
