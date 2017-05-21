/*******************************
* Author: Derek Harris
* Course: CS362 
* Assignment: Assignment #3
* File: unittest2.c
*******************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>

#define FUNC_NAME "buyCard()"

/****************************************
* Dominion function to test: buyCard() 
* Conditions:
*   buy card if: 
*     -player has "buys" left
*     -there are enough of the card type left
*     -player has enough money
****************************************/

//Function prototypes
void myAssert(int, int, int*);
void myAssertNoCounter(int, int);

/***************
* Main function
***************/
int main(int argc, char ** argv)
{
  int additional = 0;						//variable to store # of additional cards to add to hand
  int passCount = 0;						//variable to store number of test conditions passed
  int numTests = 4;						//variable to store number of test conditions for unit test
  int numPlayers = 2;						//variable to store number of players
  int card = -1;						//variable to store card # of selected card
  int result = 0; 						//variable to store function call result value
  int seed = 1000;						//variable to store value for randomSeed
  int k[10] = {adventurer, gardens, embargo, village, minion, 
		mine, cutpurse, sea_hag, tribute, smithy};	//array to store selecte kingdom cards
  struct gameState G;						//struct to store gameState values
  struct gameState testG;


  result = initializeGame(numPlayers, k, seed, &G);		//initialize a game and set initial state	
 
  printf("***************\n");
  printf("* Unittest 2: *\n");
  printf("***************\n");
  printf("\n----------Testing function: %s----------\n", FUNC_NAME);

  //------------- generate random supply counts and ensure none are equal to zero --------------

  for(int i = 0; i < 26; i++)
  {
	G.supplyCount[i] = (rand() % 9) + 1;			//give each card a random supply count
	//printf("    G.supplyCount[%d] = %d\n", i, G.supplyCount[i]);
  }
  printf("\n");


  //-------------- Test 1 cardBuy with numBuys > 0, supply > 0 and money = 10 ------------------
  printf("  Test 1 - Player has numBuys and coins, supply > 0: ");

  card = rand() % 26;						//randomly choose a card to buy
  G.numBuys = 1;						//set numBuys to 1
  G.coins = 10;							//set # of coins to 10

  memcpy(&testG, &G, sizeof(struct gameState));			//create a test copy of current gamestate

  result = buyCard(card, &testG);				//test isGameover when no supplies are at zero
  myAssert(result, 0, &passCount);				//expected result is 0

  printf("    test buying card # %d:\n", card);
  printf("      -numBuys for player = %d\n", G.numBuys);
  printf("      -# of coins for player = %d and card cost = %d\n", G.coins, getCardCost(card));
  printf("      -supply for card #%d = %d\n", card, G.supplyCount[card]);
  printf("\n    buyCard() return val is: %d and expected return val is: 0\n", result);

  printf("----------------------------------------------------\n");

  //-------------- Test2 cardBuy with numBuys > 0, supply == 0 and money = 10 --------------------
  printf("  Test 2 - Player has numBuys and coins, supply == 0: ");

  card = rand() % 26;						//randomly choose a card to buy
  G.numBuys = 1;						//set numBuys to 1
  G.coins = 10;							//set # of coins to 10

  memcpy(&testG, &G, sizeof(struct gameState));			//create a test copy of current gamestate

  testG.supplyCount[card] = 0;					//set supplyCount for selected card to 0 in teststate
 
  result = buyCard(card, &testG);				//test isGameover when no supplies are at zero
  myAssert(result, -1, &passCount);				//expected result is 0

  printf("    test buying card # %d:\n", card);
  printf("      -numBuys for player = %d\n", G.numBuys);
  printf("      -# of coins for player = %d and card cost = %d\n", G.coins, getCardCost(card));
  printf("      -supply for card #%d = %d\n", card, testG.supplyCount[card]);
  printf("\n    buyCard() return val is: %d and expected return val is: -1\n", result);

  printf("----------------------------------------------------\n");

  //---------------- Test3 cardBuy with numBuys == 0, supply > 0 and money = 10 -------------------
  printf("  Test 3 - Player has no buys but coins > cost, supply > 0: ");

  card = rand() % 26;						//randomly choose a card to buy
  G.numBuys = 1;						//set numBuys to 1
  G.coins = 10;							//set # of coins to 10

  memcpy(&testG, &G, sizeof(struct gameState));			//create a test copy of current gamestate

  testG.numBuys = 0;						//set numBuys to 0 in test gamestate
 
  result = buyCard(card, &testG);				//test isGameover when no supplies are at zero
  myAssert(result, -1, &passCount);				//expected result is 0

  printf("    test buying card # %d:\n", card);
  printf("      -numBuys for player = %d\n", testG.numBuys);
  printf("      -# of coins for player = %d and card cost = %d\n", G.coins, getCardCost(card));
  printf("      -supply for card #%d = %d\n", card, G.supplyCount[card]);
  printf("\n    buyCard() return val is: %d and expected return val is: -1\n", result);

  printf("----------------------------------------------------\n");

  //--------------- Test4 cardBuy with numBuys == 1, supply > 0 and money = 0 -------------------
  printf("  Test 4 - Player has no coins but numBuys > 0, supply > 0: ");

  card = rand() % 26;						//randomly choose a card to buy
  G.numBuys = 1;						//set numBuys to 1
  G.coins = 10;							//set # coins to 10

  memcpy(&testG, &G, sizeof(struct gameState));			//create a test copy of current gamestate

  testG.coins = 0;						//set # coins to 0 in test gamestate
 
  result = buyCard(card, &testG);				//test isGameover when no supplies are at zero
  myAssert(result, -1, &passCount);				//expected result is 0

  printf("    test buying card # %d:\n", card);
  printf("      -numBuys for player = %d\n", G.numBuys);
  printf("      -# of coins for player = %d and card cost = %d\n", testG.coins, getCardCost(card));
  printf("      -supply for card #%d = %d\n", card, G.supplyCount[card]);
  printf("\n    buyCard() return val is: %d and expected return val is: -1\n", result);

  printf("----------------------------------------------------\n");

  //--------------- Test5 cardBuy with numBuys == 0, supply > 0 and money = 10 --------------------
  printf("  Test 5 - Check for gamestate change between test & actual state: \n");

  card = rand() % 26;						//randomly choose a card to buy
  G.numBuys = 1;						//set numBuys to 1
  G.coins = 10;							//set # of coins to 10

  memcpy(&testG, &G, sizeof(struct gameState));			//create a test copy of current gamestate
 
  result = buyCard(card, &testG);				//test isGameover when no supplies are at zero
  //myAssert(result, 0, &passCount);				//expected result is 0

  printf("    test buying card # %d:\n", card);
  printf("      -numBuys for player = %d\n", G.numBuys);
  printf("      -# of coins for player = %d and card cost = %d\n", testG.coins, getCardCost(card));
  printf("      -supply for card #%d = %d\n", card, G.supplyCount[card]);
  printf("\n    buyCard() return val is: %d and expected return val is: 0\n", result);

  if(result == 0)
	additional = 1;

  printf("\n    current # of cards = %d and expected # of cards = %d: ", testG.handCount[0], G.handCount[0]+additional);
  myAssert(testG.handCount[0], G.handCount[0]+additional, &passCount);
  numTests += 1;
  
  printf("    current # of buys = %d and expected # of buys = %d: ", testG.numBuys, G.numBuys-1);
  myAssert(testG.numBuys, G.numBuys-1, &passCount);
  numTests += 1;
  
  printf("    current # of coins = %d and expected # of coins = %d: ", testG.coins, G.coins - getCost(card));
  myAssert(testG.coins, G.coins-getCost(card), &passCount);
  numTests +=1;

  printf("----------------------------------------------------\n");

  // ---------------------- Print test results ---------------------------
  printf(">>>>> Unittest 2 complete. Function %s Passed [%d of %d] tests. <<<<<\n\n", FUNC_NAME, passCount, numTests);
	
  return 0;
}

/*--------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------*/

/*******************************************
* Function: myAssert
* Input: int left, int right, int* count
* Output: none
* Description: prints result message based on
* the condition test between left value and 
* right value
********************************************/
void myAssert(int left, int right, int* count)
{
  if(left == right)
  {
	printf("test passed!\n");
	*count+=1;
  }
  else
  {
	printf("test failed!\n");
  }
}

/*******************************************
* Function: myAssertNoCounter
* Input: int res
* Output: none
* Description: prints result message based on
* the condition test between left value and 
* right value
********************************************/
void myAssertNoCounter(int left, int right)
{
  if(left == right)
  {
	printf("test passed!\n");
  }
  else
  {
	printf("test failed!\n");
  }
}
