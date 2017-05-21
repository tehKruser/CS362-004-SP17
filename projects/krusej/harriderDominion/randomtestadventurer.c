/****************************
* Author: Derek Harris
* Course: CS362
* Assignment: Assignment 4
* File: randomtestadventurer.c
*****************************/
 
/*
 * Include the following lines in your makefile:
 *
 * randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
 *      gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define TESTCARD "adventurer"
#define NUM_TESTS 1000

//Function prototypes
void myAssert(int, int, int*);
void myAssertLessThan(int, int, int*);

/****************
* Main function
****************/
int main() 
{
  int x = 0;						//variable to store for loop counter
  int j = 0;						//variable to store # treasure cards in test gamestate hand
  int m = 0;						//variable to store # treasure cards in actual gamestate hand
  int passCount = 0;					//variable to store # of tests passed this iteration
  int numPass = 0;					//variable to store total # of tests passed
  int numFail = 0;					//variable to store total # of tests failed
  int totTests = 0;					//variable to store total # of tests run
  int numTests = 4;					//variable to store # of tests
  int newCards = 0;					//variable to store # of new cards
  int discarded = 0;					//variable to store # of discarded cards
  int shuffledCards = 0;				//variable to store # of cards shuffled into deck
  int handpos = 0;					//variable to store hand position
  int choice1=0, choice2=0, choice3=0, bonus=0;		//variables to initialize choice and bonus
  int seed = 1000;					//seed for initialize game function
  int status = -1;					//variable to store result of initializing game
  int numPlayers = 0;					//variable to store # of players
  int thisPlayer = 0;					//variable to identify current player
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

  struct gameState testG;				//struct to store test gamestate values
  struct gameState* randG;				//gameState struct ptr to help create new gameStates


  for(x = 0; x < NUM_TESTS; x++)			//iterate for test case number of games
  {
	  seed = rand();				//random seed to initialize gamestate
	  numPlayers = (rand() % MAX_PLAYERS);		//randomize number of players... chooses between 2-4 players
	  randG = malloc(sizeof(struct gameState));	//create new gameState struct
  

	  // initialize a game state and player cards
	  status = initializeGame(numPlayers, k, seed, randG);

	  // initialize player hand, deck and discard pile to random numbers
	  for(int a = 0; a < numPlayers; a++)
	  {
		  randG->deckCount[a] = rand() % MAX_DECK;
		  randG->discardCount[a] = rand() % MAX_DECK;
		  randG->handCount[a] = rand() % MAX_HAND;
	  }

	  printf("|***********************************************************************|\n");
	  printf("|***********************************************************************|\n\n");

	  printf("----------------- Test # %d for Card: %s ----------------\n", x+1, TESTCARD);

	  // ----------- TEST 1: +3 treasure cards --------------
	  printf("TEST 1: +3 treasure cards and smaller deck\n");
	  printf("\n");


	  //test game initiliazation status...failed test should return -1, otherwise should return 0
	  if(status < 0)
	  {
		printf("ERROR: Players < 2. Actual number of players: %d\n", numPlayers);

		printf("status of gameState initialization = %d, expected = %d : ", status, -1);
		myAssert(status, -1, &passCount);	//assert test conditions here

		printf("\n >>>>> SUCCESS: Test # %d for card [%s] complete.\nPassed [%d of %d] tests <<<<<\n\n", x+1, TESTCARD, passCount, 1);
		printf("Continuing to next test iteration \n\n");

		numPass = numPass + passCount;		//record number of tests passed
		numFail = numFail + (1 - passCount);	//record number of tests failed
		totTests = totTests + 1;		//record total number of tests

		passCount = 0;
		numTests = 4;
		free(randG);				//free dynamically allocated memory
		continue;
	  }
	  else
	  {
	  	printf("status of gameState initialization = %d, expected = %d : ", status, 0);
	  	myAssert(status, 0, &passCount);
	  }

	  // copy the game state to a test case
	  memcpy(&testG, randG, sizeof(struct gameState));

	  printf("\ntestG.handCount[thisPlayer] = %d, randG->handCount[thisPlayer] = %d\n\n", testG.handCount[thisPlayer], randG->handCount[thisPlayer]);

	  cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);			//call the card's function

	  newCards = 3;											//declare # of new cards
	  discarded = 1;										//declare # of cards to discard

	  for(int i = 0; i < testG.handCount[thisPlayer]; i++)  					//iterate through player's hand
	  {
	    if((testG.hand[thisPlayer][i] > province) && (testG.hand[thisPlayer][i] < adventurer))	//if current card is a treasure card
	    {
		j++;	//increment treasure card counter for test gamestate
	    }
	  }

	  for(int i = 0; i < randG->handCount[thisPlayer]; i++) 					//iterate through player's hand
	  {
	    if((randG->hand[thisPlayer][i] > province) && (randG->hand[thisPlayer][i] < adventurer))	//if current card is a treasure card
	    {
		m++;	//increment treasure card counter for actual gamestate
	    }
	  }

	  printf("treasure count = %d, expected = %d : ", j, m+3);				//test state should have 3 more treasure cards
	  myAssert(j - m, 3, &passCount);							//test that testG hand has 3 add't treas. cards

	  printf("hand count = %d, expected = %d : ", testG.handCount[thisPlayer], randG->handCount[thisPlayer] + newCards - discarded); 
	  myAssert(testG.handCount[thisPlayer], randG->handCount[thisPlayer] + newCards - discarded, &passCount);

	  printf("deck count = %d <= expected = %d : ", testG.deckCount[thisPlayer], randG->deckCount[thisPlayer] - newCards + shuffledCards);
	  myAssertLessThan(testG.deckCount[thisPlayer], randG->deckCount[thisPlayer] - newCards + shuffledCards, &passCount);

	  printf("---------------------------------------------------\n");

	  //------------- Check other player states ------------------
	  printf("\nChecking other player states...\n\n");

	  for(int i = 1; i < numPlayers; i++)
	  {
	    printf("player[%d] hand count = %d, expected = %d : ", i+1, testG.handCount[i], randG->handCount[i]);
	    myAssert(testG.handCount[i], randG->handCount[i], &passCount);

	    printf("player[%d] deck count = %d, expected = %d : ", i+1, testG.deckCount[i], randG->deckCount[i]);
	    myAssert(testG.deckCount[i], randG->deckCount[i], &passCount);
	  
	    numTests = numTests + 2;
	  }

	  //------------- Check kingdom and victory card ------------------
	  printf("\nTesting Kingdom Card and Victory Card states...\n\n");

	  for(int j = 0; j < 10; j++)
	  {
	    printf("kingdom card k[%d] supply count = %d, expected = %d : ", j, testG.supplyCount[k[j]], randG->supplyCount[k[j]]);
	    myAssert(testG.supplyCount[k[j]], randG->supplyCount[k[j]], &passCount);

	    numTests = numTests + 1;
	  }

	  printf("\n");

	  printf("victory card [estate] supply count = %d, expected = %d : ", testG.supplyCount[estate], randG->supplyCount[estate]);
	  myAssert(testG.supplyCount[estate], randG->supplyCount[estate], &passCount);

	  numTests = numTests + 1;

	  printf("victory card [duchy] supply count = %d, expected = %d : ", testG.supplyCount[duchy], randG->supplyCount[duchy]);
	  myAssert(testG.supplyCount[duchy], randG->supplyCount[duchy], &passCount);

	  numTests = numTests + 1;

	  printf("victory card [province] supply count = %d, expected = %d : ", testG.supplyCount[province], randG->supplyCount[province]);
	  myAssert(testG.supplyCount[province], randG->supplyCount[province], &passCount);

	  numTests = numTests + 1;

	  printf("---------------------------------------------------\n");

	  //----------------------- print results -------------------------------
	  printf("\n >>>>> SUCCESS: Test # %d for card [%s] complete.\nPassed [%d of %d] tests <<<<<\n\n", x+1, TESTCARD, passCount, numTests);

	  numPass = numPass + passCount;		//record number of tests passed for this game
	  numFail = numFail + (numTests - passCount);	//record number of tests failed for this game
	  totTests = totTests + numTests;		//record number of tests run
	
	  passCount = 0;				//reset passCount
	  numTests = 4;					//reset numTests

	  free(randG);					//free dynamically allocated memory
	  memset(&testG, 0, sizeof(struct gameState));	//clear testG struct

  }//end outer for loop


  printf("\n---------------------------------------------\n");
  printf("Final results of random testing:\n");
  printf("--------------------------------\n");
  printf("Total # of games run: %d\nTotal # of tests run: %d\nTotal # of tests passed: %d\nTotal # of tests failed: %d\n", NUM_TESTS,totTests, numPass, numFail);

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

/**********************************
* Function: myAssertLessThan()
* Input: int left, int right
* Output: none
* Description: compares left value
*   to right and displays a message
**********************************/
void myAssertLessThan(int left, int right, int* count)
{
  if(left <= right)
  {
    printf("test passed!\n");
    *count+=1;
  }
  else
  {
    printf("test failed!\n");
  }
}
