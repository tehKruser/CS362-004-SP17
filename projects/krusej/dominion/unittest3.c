/*
 * unittest3.c
 *

 */

/*
 * Include the following lines in your makefile:
 *
 * unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define UNITTEST "unittest3"
#define FUNCTEST "isGameOver()"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int assertEqual(int v1, int v2);

    int i, p, p_next, numPlayers;
    int seed = 1000;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

    struct gameState G;
    int testFailures = 0;

    printf("----------------- %s Testing: %s ----------------", UNITTEST, FUNCTEST);

    for (numPlayers = 2; numPlayers <= MAX_PLAYERS; numPlayers++) {
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        initializeGame(numPlayers, k, seed, &G); // initialize a new game
        for (p = 0; p < numPlayers; p++) {
            G.whoseTurn = p;
            endTurn(&G);

            for(i = 0; i < 5 ; i++){
#if (NOISY_TEST == 1)
                printf("\nTest that player whose turn ended has discarded hand.");
                printf("\nG.hand[%d][%d]: %d, expected: -1", p, i, G.hand[p][i]);
#endif
                testFailures += assertEqual(G.hand[p][i], -1);
            }

#if (NOISY_TEST == 1)
            printf("\nTest that player whose turn ended 0 cards in hand.");
            printf("\nG.handCount[%d]: %d, expected: 0", p, G.handCount[p]);
#endif
            testFailures += assertEqual(G.handCount[p], 0);

            //Determine whose turn it is
            if(p < numPlayers - 1) {
                p_next = p + 1;
            } else {
                p_next = 0;
            }

#if (NOISY_TEST == 1)
            printf("\nTest next player and game values.");
            printf("\nG.whoseTurn: %d, expected: %d", G.whoseTurn, p_next);
#endif
            testFailures += assertEqual(G.whoseTurn, p_next);

            int expected_outpostPlayed = 0;
            int expected_phase = 0;
            int expected_numActions = 1;
            int expected_numBuys = 1;
            int expected_playedCardCount = 0;
            int expected_handCount = 5;

#if (NOISY_TEST == 1)
            printf("\nG.outpostPlayed: %d, expected: %d", G.outpostPlayed, expected_outpostPlayed);
#endif
            testFailures += assertEqual(G.outpostPlayed, expected_outpostPlayed);

#if (NOISY_TEST == 1)
            printf("\nG.phase: %d, expected: %d", G.phase, expected_phase);
#endif
            testFailures += assertEqual(G.phase, expected_phase);

#if (NOISY_TEST == 1)
            printf("\nG.numActions: %d, expected: %d", G.numActions, expected_numActions);
#endif
            testFailures += assertEqual(G.numActions, expected_numActions);
/*
#if (NOISY_TEST == 1)
            printf("\nG.coins: %d, expected: %d", G.coins, expected_coins);
#endif
            testFailures += assertEqual(G.coins, expected_coins);
*/

#if (NOISY_TEST == 1)
            printf("\nG.numBuys: %d, expected: %d", G.numBuys, expected_numBuys);
#endif
            testFailures += assertEqual(G.numBuys, expected_numBuys);

#if (NOISY_TEST == 1)
            printf("\nG.playedCardCount: %d, expected: %d", G.playedCardCount, expected_playedCardCount);
#endif
            testFailures += assertEqual(G.playedCardCount, expected_playedCardCount);

#if (NOISY_TEST == 1)
            printf("\nG.handCount[G.whoseTurn]: %d, expected: %d", G.handCount[G.whoseTurn], expected_handCount);
#endif
            testFailures += assertEqual(G.handCount[G.whoseTurn], expected_handCount);

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
