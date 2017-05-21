/*
 * unittest4.c
 *

 */

/*
 * Include the following lines in your makefile:
 *
 * unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define UNITTEST "unittest4"
#define FUNCTEST "discardCard()"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int assertEqual(int v1, int v2);

    int i, p, numPlayers, trashFlag, handPos, cardsInHand, index
        , expected_discardCount, expected_discardedCard
        , expected_handCount, expected_cardInHandPos, expected_lastCardInHand;
    int seed = 1000;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

    struct gameState G;
    int testFailures = 0;

    printf("----------------- %s Testing: %s ----------------", UNITTEST, FUNCTEST);

    // Cycle through number of players that can be in a game
    for (numPlayers = 2; numPlayers <= MAX_PLAYERS; numPlayers++) {
#if (NOISY_TEST == 1)
        printf("\n***Switching to a %d player game.", numPlayers);
#endif
        // Cycle through each player
        for (p = 0; p < numPlayers; p++) {
#if (NOISY_TEST == 1)
            printf("\n***Switching to player %d.", p);
#endif

            for(trashFlag = 0; trashFlag <= 1; trashFlag++){
#if (NOISY_TEST == 1)
                printf("\n***trashFlag: %d.", trashFlag);
#endif
                for(cardsInHand = 1; cardsInHand <= 5; cardsInHand++){
#if (NOISY_TEST == 1)
                printf("\n***Cards in Hand: %d.", cardsInHand);
#endif
                    // Discard each card in a player's hand
                    for(handPos = 0; handPos < cardsInHand; handPos++){
#if (NOISY_TEST == 1)
                        printf("\n***Discarding card at position %d in hand.", handPos);
#endif

                        // initialize game
                        memset(&G, 23, sizeof(struct gameState));   // clear the game state
                        initializeGame(numPlayers, k, seed, &G); // initialize a new game

                        //Set player's hand
                        G.handCount[p] = cardsInHand;
                        for(i = 0; i < cardsInHand; i++){
                            G.hand[p][i] = k[i];
                        }
                        // Set the first played card to a value for testing against
                        G.discard[p][0] = -1;

                        // -------------- trashFlag:  Expected Values after discardCard() --------------
                        if(trashFlag == 0){
                            expected_discardedCard = G.hand[p][handPos];
                            expected_discardCount = G.discardCount[p] + 1;
                            index = G.discardCount[p];
                        } else {
                            if(G.discardCount[p] == 0){
                                expected_discardedCard = -1;
                                index = 0;
                            } else {
                                expected_discardedCard = G.discard[p][G.discardCount[p] - 1];
                                index = G.discardCount[p] - 1;
                            }
                            expected_discardCount = G.discardCount[p];
                        }

                        // -------------- player Hand: Expected Values after discardCard() --------------
                        expected_handCount = cardsInHand - 1;
                        if(handPos == (cardsInHand - 1)){               //if handPos is last card in hand
                            expected_cardInHandPos = -1;
                            expected_lastCardInHand = -1;
                        } else if ((cardsInHand == 1)){                 // if there is only 1 card in hand
                            expected_cardInHandPos = -1;
                            expected_lastCardInHand = -1;
                        } else {
                            expected_cardInHandPos = G.hand[p][cardsInHand - 1];
                            expected_lastCardInHand = -1;
                        }

                        // discard
                        discardCard(handPos, p, &G, trashFlag);

                        // test
#if (NOISY_TEST == 1)
                        printf("\nG.discard[%d][%d]: %d, expected: %d", p, index, G.discard[p][index], expected_discardedCard);
#endif
                        testFailures += assertEqual(G.discard[p][index], expected_discardedCard);

#if (NOISY_TEST == 1)
                        printf("\nG.discardCount[p]: %d, expected: %d", G.discardCount[p], expected_discardCount);
#endif
                        testFailures += assertEqual(G.discardCount[p], expected_discardCount);

#if (NOISY_TEST == 1)
                        printf("\nG.handCount[%d]: %d, expected: %d", p, G.handCount[p], expected_handCount);
#endif
                        testFailures += assertEqual(G.handCount[p], expected_handCount);

#if (NOISY_TEST == 1)
                        printf("\nG.hand[%d][%d]: %d, expected: %d", p, handPos, G.hand[p][handPos], expected_cardInHandPos);
#endif
                        testFailures += assertEqual(G.hand[p][handPos], expected_cardInHandPos);

#if (NOISY_TEST == 1)
                        printf("\nG.hand[%d][%d]: %d, expected: %d", p, cardsInHand -1, G.hand[p][cardsInHand -1], expected_lastCardInHand);
#endif
                        testFailures += assertEqual(G.hand[p][cardsInHand -1], expected_lastCardInHand);

                    }
                }
            }
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
