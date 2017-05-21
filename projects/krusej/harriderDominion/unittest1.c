#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define FUNC_NAME "isGameOver()"

/****************************************
* Dominion function to test: isGameOver() 
* Conditions:
*   game is over if: 
*     -stack of province cards is empty
*     -3 supply piles are at 0
****************************************/

//Function prototypes
void myAssert(int, int, int*);

/***************
* Main function
***************/
int main(int argc, char ** argv)
{
  int passCount = 0;						//variable to store number of test conditions passed
  int numTests = 3;						//variable to store number of test conditions for unit test
  int numPlayers = 2;						//variable to store number of players
  int result = 0; 						//variable to store function call result value
  int seed = 1000;						//variable to store value for randomSeed
  int k[10] = {adventurer, gardens, embargo, village, minion, 
		mine, cutpurse, sea_hag, tribute, smithy};	//array to store selecte kingdom cards
  struct gameState G;						//struct to store gameState values


  result = initializeGame(numPlayers, k, seed, &G);		//initialize a game and set initial state	
 
  printf("***************\n");
  printf("* Unittest 1: *\n");
  printf("***************\n");
  printf("\n----------Testing function: %s----------\n", FUNC_NAME);

  //generate random supply counts and ensure none are equal to zero
  printf("\n  Randomly generated supply counts between 1 and 10:\n\n");

  for(int i = 0; i < 26; i++)
  {
	G.supplyCount[i] = (rand() % 9) + 1;			//give each card a random supply count
	printf("    G.supplyCount[%d] = %d\n", i, G.supplyCount[i]);
  }
  printf("\n");

  //test isGameOver with no supply counts at 0
  printf("  Test 1 - No supply counts at zero: ");
  
  result = isGameOver(&G);					//test isGameover when no supplies are at zero
  myAssert(result, 0, &passCount);				//expected result is 0

  printf("    isGameOver() return val is: %d and expected return val is: 0\n", result);

  //test isGameOver with province supply count at 0
  printf("\n  Test 2 - Province count at zero: ");
  G.supplyCount[province] = 0;					//set province supply count to 0
  
  result = isGameOver(&G);					//test isGameover when province count at zero
  myAssert(result, 1, &passCount);				//expected result is 1
  printf("    G.supplyCount[province] = %d\n", G.supplyCount[province]);
  printf("    isGameOver() return val is: %d and expected return val is: 1\n", result);

  G.supplyCount[province] = (rand() % 9) + 1;			//reset province supply count

  //test isGameOver with 3 supply pile counts at 0
  printf("\n  Test 3 - 3 supply piles at zero: ");
  G.supplyCount[feast] = 0;					//set supply count to 0
  G.supplyCount[minion] = 0;					//set supply count to 0
  G.supplyCount[cutpurse] = 0;					//set supply count to 0
  
  result = isGameOver(&G);					//test isGameover when 3 supply piles are at zero
  myAssert(result, 1, &passCount);				//expected result is 1
  printf("    G.supplyCount[feast] = %d\n", G.supplyCount[feast]);
  printf("    G.supplyCount[minion] = %d\n", G.supplyCount[minion]);
  printf("    G.supplyCount[cutpurse] = %d\n", G.supplyCount[cutpurse]);
  printf("    isGameOver() return val is: %d and expected return val is: 1\n", result);

  printf("\n>>>>> Unittest 1 complete. Function %s Passed [%d of %d] tests. <<<<<\n", FUNC_NAME, passCount, numTests);
	
  return 0;
}

/*--------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------*/

/*******************************************
* Function: myAssert
* Input: int res
* Output: none
* Description: prints result message based on
* the return value of a function (ie. 'res')
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
