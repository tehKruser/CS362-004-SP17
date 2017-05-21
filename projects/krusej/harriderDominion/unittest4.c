/*******************************
* Author: Derek Harris
* Course: CS362 
* Assignment: Assignment #3
* File: unittest4.c
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

#define FUNC_NAME "updateCoins()"

/****************************************
* Dominion function to test: updateCoins() 
* Conditions:
*   return cost if: 
*     -add coins for each treasure card in
*       player's hand
*     -add bonus if required
****************************************/

//Function prototypes
void myAssert(int, int, int*);
void myAssertNoCounter(int, int);

/***************
* Main function
***************/
int main(int argc, char ** argv)
{
  int bonus = 0;
  int passCount = 0;						//variable to store number of test conditions passed
  int numTests = 2;						//variable to store number of test conditions for unit test
  int numPlayers = 2;						//variable to store number of players
  int result = 0; 						//variable to store function call result value
  int seed = 1000;						//variable to store value for randomSeed
  int k[10] = {adventurer, gardens, embargo, village, minion, 
		mine, cutpurse, sea_hag, tribute, smithy};	//array to store selecte kingdom cards
  struct gameState G;						//struct to store gameState values
  struct gameState testG;

  result = initializeGame(numPlayers, k, seed, &G);		//initialize a game and set initial state	
 
  printf("***************\n");
  printf("* Unittest 4: *\n");
  printf("***************\n");
  printf("\n----------Testing function: %s----------\n", FUNC_NAME);

  //------------- generate random supply counts and ensure none are equal to zero --------------

  for(int i = 0; i < 26; i++)
  {
	G.supplyCount[i] = (rand() % 9) + 1;			//give each card a random supply count
	//printf("    G.supplyCount[%d] = %d\n", i, G.supplyCount[i]);
  }
  printf("\n");

  memcpy(&testG, &G, sizeof(struct gameState));			//create a copy of current gameState G

  //-------------- Test 1 - updateCoins() for current player ------------------
  printf("  Test 1 - updateCoins for current player: ");

  bonus = 0;

  result = updateCoins(0, &testG, bonus);			//get return value of function
  myAssert(result, 0, &passCount);				//expected result is 0

  printf("    comparing current gamestate to previous gamestate:\n");
  printf("      -bonus = %d\n", bonus);
  printf("      -current coins with bonus = %d and previous gamestate coins = %d\n", testG.coins, G.coins);
  printf("\n    updateCoin() return val is: %d and expected return val is: 0\n", result);

  printf("----------------------------------------------------\n");

  //-------------- Test 2 - updateCoins() for current player with bonus ------------------
  printf("  Test 2 - updateCoins with bonus > 0 for current player: ");

  bonus = 5;

  result = updateCoins(0, &testG, bonus);			//get return value of function
  myAssert(result, 0, &passCount);				//expected result is 0

  printf("    comparing current gamestate to previous gamestate:\n");
  printf("      -bonus = %d\n", bonus);
  printf("      -current coins with bonus = %d and previous gamestate coins = %d\n", testG.coins, G.coins);
  printf("\n    updateCoin() return val is: %d and expected return val is: 0\n", result);

  printf("----------------------------------------------------\n");

  // ---------------------- Print test results ---------------------------
  printf(">>>>> Unittest 4 complete. Function %s Passed [%d of %d] tests. <<<<<\n\n", FUNC_NAME, passCount, numTests);
	
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
  if(left >= right)
  {
	printf("test passed!\n");
	*count+=1;
  }
  else
  {
	printf("test failed! result is: %d and expected result is: %d\n", left, right);
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
