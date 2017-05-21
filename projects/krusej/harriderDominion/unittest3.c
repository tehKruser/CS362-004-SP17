/*******************************
* Author: Derek Harris
* Course: CS362 
* Assignment: Assignment #3
* File: unittest3.c
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

#define FUNC_NAME "getCost()"

/****************************************
* Dominion function to test: getCost() 
* Conditions:
*   return cost if: 
*     -card is enumerated
*     -card has a cost
****************************************/

//Function prototypes
void myAssert(int, int, int*);
void myAssertNoCounter(int, int);

/***************
* Main function
***************/
int main(int argc, char ** argv)
{
  int passCount = 0;						//variable to store number of test conditions passed
  int numTests = 2;						//variable to store number of test conditions for unit test
  int numPlayers = 2;						//variable to store number of players
  int card = -1;						//variable to store card # of selected card
  int result = 0; 						//variable to store function call result value
  int seed = 1000;						//variable to store value for randomSeed
  int k[10] = {adventurer, gardens, embargo, village, minion, 
		mine, cutpurse, sea_hag, tribute, smithy};	//array to store selecte kingdom cards
  struct gameState G;						//struct to store gameState values

  result = initializeGame(numPlayers, k, seed, &G);		//initialize a game and set initial state	
 
  printf("***************\n");
  printf("* Unittest 3: *\n");
  printf("***************\n");
  printf("\n----------Testing function: %s----------\n", FUNC_NAME);

  //------------- generate random supply counts and ensure none are equal to zero --------------

  for(int i = 0; i < 26; i++)
  {
	G.supplyCount[i] = (rand() % 9) + 1;			//give each card a random supply count
	//printf("    G.supplyCount[%d] = %d\n", i, G.supplyCount[i]);
  }
  printf("\n");


  //-------------- Test 1 - getCost() for randomly selected card ------------------
  printf("  Test 1 - randomly select card and get cost: ");

  card = rand() % 26;						//randomly choose a card

  result = getCost(card);					//get return value of function
  myAssert(result, 0, &passCount);				//expected result is 0

  printf("    test buying card # %d:\n", card);
  printf("      -card cost = %d\n", getCost(card));
  printf("\n    getCost() return val is: %d and expected return val is: >= 0\n", result);

  printf("----------------------------------------------------\n");

  //-------------- Test 2 - getCost() for card not listed ------------------
  printf("  Test 2 - get cost for card #999 'swamp': ");

  card = 999;							//select an unimplemented card

  result = getCost(card);					//get return value of function
  myAssert(result, -1, &passCount);				//expected result is -1

  printf("    test buying card # %d:\n", card);
  printf("      -card cost = %d\n", getCost(card));
  printf("\n    getCost() return val is: %d and expected return val is: -1\n", result);

  printf("----------------------------------------------------\n");

  // ---------------------- Print test results ---------------------------
  printf(">>>>> Unittest 3 complete. Function %s Passed [%d of %d] tests. <<<<<\n\n", FUNC_NAME, passCount, numTests);
	
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
