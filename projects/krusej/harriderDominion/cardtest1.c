/****************************
* Author: Derek Harris
* Course: CS362
* Assignment: Assignment 3
* File: cardtest1.c
*****************************/
 
/*
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define TESTCARD "smithy"

//Function prototypes
void myAssert(int, int, int*);

/****************
* Main function
****************/
int main() 
{
  int passCount = 0;					//variable to store # of tests passed
  int numTests = 2;					//variable to store # of tests
  int newCards = 0;					//variable to store # of new cards
  int discarded = 0;					//variable to store # of discarded cards
  int shuffledCards = 0;				//variable to store # of cards shuffled into deck
  int handpos = 0;					//variable to store hand position
  int choice1=0, choice2=0, choice3=0, bonus=0;		//variables to initialize choice and bonus
  int seed = 1000;					//seed for initialize game function
  int numPlayers = 2;					//variable to store # of players
  int thisPlayer = 0;					//variable to identify current player
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
  struct gameState G; 					//struct to store gamestate values
  struct gameState testG;				//struct to store test gamestate values

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);

  printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

  // ----------- TEST 1: +3 cards --------------
  printf("TEST 1: +3 cards\n");

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));

  printf("\ntestG.handCount[thisPlayer] = %d, G.handCount[thisPlayer] = %d\n\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);

  cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);			//call the card's function

  newCards = 3;											//declare # of new cards
  discarded = 1;										//declare # of cards to discard

  printf("hand count = %d, expected = %d : ", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded); 
  myAssert(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded, &passCount);

  printf("deck count = %d, expected = %d : ", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
  myAssert(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards, &passCount);

  printf("---------------------------------------------------\n");

  //------------- Check other player states ------------------
  printf("\nChecking other player states...\n\n");

  for(int i = 1; i < numPlayers; i++)
  {
    printf("player[%d] hand count = %d, expected = %d : ", i, testG.handCount[i], G.handCount[i]);
    myAssert(testG.handCount[i], G.handCount[i], &passCount);

    printf("player[%d] deck count = %d, expected = %d : ", i, testG.deckCount[i], G.deckCount[i]);
    myAssert(testG.deckCount[i], G.deckCount[i], &passCount);
  
    numTests = numTests + 2;
  }

  //------------- Check kingdom and victory card ------------------
  printf("\nTesting Kingdom Card and Victory Card states...\n\n");

  for(int j = 0; j < 10; j++)
  {
    printf("kingdom card k[%d] supply count = %d, expected = %d : ", j, testG.supplyCount[k[j]], G.supplyCount[k[j]]);
    myAssert(testG.supplyCount[k[j]], G.supplyCount[k[j]], &passCount);

    numTests = numTests + 1;
  }

  printf("\n");

  printf("victory card [estate] supply count = %d, expected = %d : ", testG.supplyCount[estate], G.supplyCount[estate]);
  myAssert(testG.supplyCount[estate], G.supplyCount[estate], &passCount);

  numTests = numTests + 1;

  printf("victory card [duchy] supply count = %d, expected = %d : ", testG.supplyCount[duchy], G.supplyCount[duchy]);
  myAssert(testG.supplyCount[duchy], G.supplyCount[duchy], &passCount);

  numTests = numTests + 1;

  printf("victory card [province] supply count = %d, expected = %d : ", testG.supplyCount[province], G.supplyCount[province]);
  myAssert(testG.supplyCount[province], G.supplyCount[province], &passCount);

  numTests = numTests + 1;

  printf("---------------------------------------------------\n");

  //----------------------- print results -------------------------------
  printf("\n >>>>> SUCCESS: Testing card [%s] complete.  Passed [%d of %d] tests <<<<<\n\n", TESTCARD, passCount, numTests);


  return 0;
}

/*************************************************************************************/
/*************************************************************************************/


/**********************************
* Function: myAssert()
* Input: int left, int right
* Output: none
* Description: compares left value
*   to right and displays a message
**********************************/
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
