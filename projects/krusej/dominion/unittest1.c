/*
 * unittest1.c
 *

 */

/*
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define UNITTEST "unittest1"
#define FUNCTEST "buyCard()"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    //int i;
    int seed = 1000;
    int numPlayer;
    int p, r, cardNumber, cardCost, playerCoins, playerBuys, supplyPos, supplyCount;
    int expectedCoins, expectedBuys, expectedSupplyCount, expectedPhase;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

    struct gameState G;
    //int maxHandCount = 5;

    printf("----------------- %s Testing: %s ----------------\n", UNITTEST, FUNCTEST);
    for (numPlayer = 2; numPlayer <= MAX_PLAYERS; numPlayer++) {
         for (p = 0; p < numPlayer; p++) {
            for(cardNumber = curse; cardNumber <= treasure_map; cardNumber++){
                cardCost = getCost(cardNumber);
                for(playerCoins = cardCost - 1; playerCoins <= cardCost; playerCoins++){
                    for(playerBuys = 0; playerBuys <= 1; playerBuys++){
                        for(supplyPos = 0; supplyPos <= treasure_map; supplyPos++){
                            for(supplyCount = 0; supplyCount <= 1; supplyCount++){
                                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                                initializeGame(numPlayer, k, seed, &G); // initialize a new game
                                G.whoseTurn = p;
                                G.coins = playerCoins;
                                G.supplyCount[supplyPos] = supplyCount;
                                G.numBuys = playerBuys;

                                if(playerBuys == 0 || playerCoins < cardCost || supplyCount < 0) {
                                    expectedCoins = G.coins;
                                    expectedBuys = G.numBuys;
                                    //expectedSupplyCount = G.supplyCount[supplyPos];
                                    expectedPhase = G.phase;
                                } else {
                                    expectedCoins = G.coins - cardCost;
                                    expectedBuys = G.numBuys - 1;
                                    //expectedSupplyCount = G.supplyCount[supplyPos] - 1;
                                    expectedPhase = 1;
                                }

                                printf("Test player %d with %d coin(s) and %d buy(s) in a %d player game.\n", p, playerCoins, playerBuys, numPlayer);

                                r = buyCard(supplyPos, &G);
#if (NOISY_TEST == 1)
                                printf("G.coins = %d, expected = %d\n", G.coins, expectedCoins);
                                printf("G.numBuys = %d, expected = %d\n", G.numBuys, expectedBuys);
                                //printf("G.supplyCount[%d] = %d, expected = %d\n", supplyPos, G.supplyCount[supplyPos], expectedSupplyCount);
                                printf("G.phase = %d, expected = %d\n", G.phase, expectedPhase);
#endif
                                assert(G.coins == expectedCoins);
                                assert(G.numBuys == expectedBuys);
                                //assert(G.supplyCount[supplyPos] == expectedSupplyCount);
                                assert(G.phase == expectedPhase);
                            }
                        }
                    }
                }
            }
         }
    }

    printf("All tests passed!\n");

    return 0;
}
