/*
 * cardtest3.c
 *

 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest3: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define UNITTEST "cardtest3"
#define FUNCTEST "outpost"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int assertEqual(int v1, int v2);
    int run_test(int handPos, int* test_hand);
    int handPos;

    printf("----------------- %s Testing: %s ----------------", UNITTEST, FUNCTEST);

    int testFailures = 0;

    for(handPos = 0; handPos < 5; handPos++){
        int test_hand[5] = {adventurer, council_room, feast, gardens, mine};
        test_hand[handPos] = outpost;
        testFailures += run_test(handPos, test_hand);
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


int run_test(int handPos, int* test_hand){

    int seed = 1000;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int numPlayers = 2;
    int i;
    int p = 0;
    struct gameState G;

    int failcount;
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

    // set player's discard
    G.discardCount[p] = 0;

    // set outpost flag
    G.outpostPlayed = 0;

    int bonus  = 0;
    // run card
    cardEffect(outpost, 0, 0, 0, &G, handPos, &bonus);

    //--------------------------------------------------------
    // test for correct results
    printf("\nTEST %d: OUTPOST CARD AT HANDPOS %d", handPos+1, handPos);

    //--------------------------------------------------------
    // Number of cards in hand
    failcount = failures;
#if (NOISY_TEST == 1)
    printf("\nG.handCount[%d]: %d, expected: %d", p, G.handCount[p], 4);
#endif
    failures += assertEqual(G.handCount[p], 4);

    //--------------------------------------------------------
    // Correct cards in hand
    if(failures - failcount == 0){
        int card;
        for(i = 0; i < G.handCount[p]; i++){
            if(i == handPos){
                card = test_hand[4];
            } else {
                card = test_hand[i];
            }

#if (NOISY_TEST == 1)
            printf("\nG.hand[%d][%d]: %d, expected: %d", p, i, G.hand[p][i], card);
#endif
            failures += assertEqual(G.hand[p][i], card);
        }
    }

    //--------------------------------------------------------
    // Check outpost flag
#if (NOISY_TEST == 1)
    printf("\nG.outpostPlayed: %d, expected: %d", G.outpostPlayed, 1);
#endif
    failures += assertEqual(G.outpostPlayed, 1);


    //--------------------------------------------------------
    // Number of cards in discard
    failcount = failures;
#if (NOISY_TEST == 1)
    printf("\nG.discardCount[%d]: %d, expected: %d", p, G.discardCount[p], 1);
#endif
    failures += assertEqual(G.discardCount[p], 1);

    //--------------------------------------------------------
    // Check cards in discard pile
    if(failcount - failures == 0){
#if (NOISY_TEST == 1)
        printf("\nG.discard[%d][0]: %d, expected: %d", p, G.discard[p][0], outpost);
#endif
        failures += assertEqual(G.discard[p][0], outpost);
    }

    return failures;
}
