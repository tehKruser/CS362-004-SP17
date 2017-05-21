/*
 * cardtest4.c
 *

 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define UNITTEST "cardtest4"
#define FUNCTEST "salvager"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1


int main() {
    int assertEqual(int v1, int v2);
    int run_test(int handPos, int trashPos, int* test_hand);
    int handPos, trashPos;

    printf("----------------- %s Testing: %s ----------------", UNITTEST, FUNCTEST);

    int testFailures = 0;

    for(handPos = 0; handPos < 5; handPos++){
        for(trashPos = 0; trashPos < 5; trashPos++){
            int test_hand[5] = {adventurer, council_room, feast, gardens, mine};
            test_hand[handPos] = salvager;
            testFailures += run_test(handPos, trashPos, test_hand);
        }
    }

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


int run_test(int handPos, int trashPos, int* test_hand){

    int seed = 1000;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int numPlayers = 2;
    int i, trashCard, xtraCoins, x2discard, xinHand;
    int p = 0;
    struct gameState G;

    //int failcount;
    int failures = 0;

    // initialize game
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayers, k, seed, &G); // initialize a new game

    // set player's hand
    G.handCount[p] = 5;
    for(i = 0; i < 5; i++){
        G.hand[p][i] = test_hand[i];
    }

    G.whoseTurn = p;
    G.discardCount[p] = 0;                  // set player's discard
    G.numBuys = 1;
    G.coins = 0;
    trashCard = test_hand[trashPos];        // card to be trashed
    xtraCoins = getCost(trashCard);

    if (trashPos == handPos){
        x2discard = 0;
        xinHand = 4;
    } else {
        x2discard = 1;
        xinHand = 3;
    }


    int bonus  = 0;
    // run card
    cardEffect(salvager, trashPos, 0, 0, &G, handPos, &bonus);

    //--------------------------------------------------------
    // test for correct results
    printf("\nTEST %d: SALVAGER CARD AT HANDPOS %d, TRASHING HANDPOS %d", handPos+1, handPos, trashPos);


    //--------------------------------------------------------
    // Check number of buys
#if (NOISY_TEST == 1)
    printf("\nG.numBuys: %d, expected: %d", G.numBuys, 2);
#endif
    failures += assertEqual(G.numBuys, 2);

    //--------------------------------------------------------
    // Check extra coins
#if (NOISY_TEST == 1)
    printf("\nG.coins: %d, expected: %d", G.coins, xtraCoins);
#endif
    failures += assertEqual(G.coins, xtraCoins);


    //--------------------------------------------------------
    // Number of cards in hand
#if (NOISY_TEST == 1)
    printf("\nG.handCount[%d]: %d, expected: %d", p, G.handCount[p], xinHand);
#endif
    failures += assertEqual(G.handCount[p], xinHand);

    //--------------------------------------------------------
    // Correct cards in hand
    int card;
    for(i = 0; i < xinHand; i++){
        if(i == trashPos){
            card = test_hand[4];
        } else if(i == handPos){
            if(trashPos == 3){
                card = test_hand[4];
            } else {
                card = test_hand[3];
            }
        } else {
            card = test_hand[i];
        }

#if (NOISY_TEST == 1)
        printf("\nG.hand[%d][%d]: %d, expected: %d", p, i, G.hand[p][i], card);
#endif
        failures += assertEqual(G.hand[p][i], card);
    }

    //--------------------------------------------------------
    // Number of cards in discard
#if (NOISY_TEST == 1)
    printf("\nG.discardCount[%d]: %d, expected: %d", p, G.discardCount[p], x2discard);
#endif
    failures += assertEqual(G.discardCount[p], x2discard);

    //--------------------------------------------------------
    // Check cards in discard pile
    if(x2discard == 1){
#if (NOISY_TEST == 1)
        printf("\nG.discard[%d][0]: %d, expected: %d", p, G.discard[p][0], salvager);
#endif
        failures += assertEqual(G.discard[p][0], salvager);
    }

    return failures;
}
