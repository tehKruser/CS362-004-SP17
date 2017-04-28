/*
 * cardtest1.c
 *

 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define UNITTEST "cardtest1"
#define FUNCTEST "adventurerCard()"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int assertEqual(int v1, int v2);
    int run_test(int* test_hand, int* test_deck, int* test_discard, int test_discardCount, char* test_desc);


    int test_hand[5] = {adventurer, council_room, feast, gardens, mine};

    // first two cards are treasure
    int test1_deck[6] = {copper, silver, remodel, smithy, village, baron};
    int test1_discard[0];
    int test1_discardCount = 0;

    // last two cards are treasure
    int test2_deck[6] = {remodel, smithy, village, baron, copper, gold};
    int test2_discard[4] = {remodel, smithy, village, baron};
    int test2_discardCount = 4;

    // treasure cards are first and last
    int test3_deck[6] = {silver, remodel, smithy, village, baron, gold};
    int test3_discard[4] = {remodel, smithy, village, baron};
    int test3_discardCount = 4;

    // treasure cards are in the middle
    int test4_deck[6] = {remodel, silver, smithy, village, silver, baron};
    int test4_discard[3] = {remodel, smithy, village};
    int test4_discardCount = 3;

    int testFailures = 0;

    printf("----------------- %s Testing: %s ----------------", UNITTEST, FUNCTEST);

    //--------------------- TEST 1:
    char* test1_desc = "\nTEST 1: FIRST 2 CARDS ARE TREASURE";

    testFailures = run_test(test_hand, test1_deck, test1_discard, test1_discardCount, &test1_desc);

    printf("\n\nUNIT TEST %s COMPLETED: ", UNITTEST);

    if(testFailures == 0){
        printf("All tests passed!\n\n");
    } else {
        printf("%d failures!\n\n", testFailures);
    }

    return 0;
}


int assertEqual(int v1, int v2){
    if(v1 == v2){
        //printf("RESULT: PASS\n");
        return 0;
    } else {
        printf("\t<------------------- TEST FAILED");
        return 1;
    }
}

int run_test(int* test_hand, int* test_deck, int* test_discard, int test_discardCount, char* test_desc){

    int seed = 1000;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int numPlayers = 2;
    int i;
    int p = 0;
    struct gameState G;

    int failures = 0;

    // initialize game
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayers, k, seed, &G); // initialize a new game

    // set player's hand
    G.handCount[p] = 5;
    for(i = 0; i < 5; i++){
        G.hand[p][i] = test_hand[i];
    }
    //set player's deck
    G.deckCount[p] = 6;
    for(i = 0; i < 6; i++){
        G.deck[p][i] = test_deck[i];
    }
    // set player's discard
    G.discardCount[p] = 0;

    // run card
    adventurerCard(&G);

    // test for correct results

    // Number of cards in hand
#if (NOISY_TEST == 1)
    printf("\nG.handCount[%d]: %d, expected: %d", p, G.handCount[p], 7);
#endif
    failures += assertEqual(G.handCount[p], 7);


    return failures;
}
