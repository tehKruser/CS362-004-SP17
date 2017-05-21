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
    int assertTrue(int v1, int v2);

    int i;
    int seed = 1000;
    int numPlayer;
    int p, cardNumber, cardCost, playerCoins, playerBuys, supplyCount;
    int expectedCoins, expectedBuys, expectedPhase;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

    struct gameState G;
    int testFailures = 0;
    //int maxHandCount = 5;

    printf("----------------- %s Testing: %s ----------------", UNITTEST, FUNCTEST);
    for (numPlayer = 2; numPlayer <= MAX_PLAYERS; numPlayer++) {
         for (p = 0; p < numPlayer; p++) {
            for(playerBuys = 0; playerBuys <= 1; playerBuys++){

                // iterate through normal cards
                for(cardNumber = curse; cardNumber <= gold; cardNumber++){
                    cardCost = getCost(cardNumber);
                    for(supplyCount = 0; supplyCount <= 1; supplyCount++){
                        for(playerCoins = cardCost - 1; playerCoins <= cardCost; playerCoins++){

                            memset(&G, 23, sizeof(struct gameState));   // clear the game state
                            initializeGame(numPlayer, k, seed, &G); // initialize a new game
                            G.whoseTurn = p;
                            G.numBuys = playerBuys;
                            G.supplyCount[cardNumber] = supplyCount;
                            G.coins = playerCoins;

                            if(playerBuys == 0 || playerCoins < cardCost || supplyCount == 0) {
                                expectedCoins = G.coins;
                                expectedBuys = G.numBuys;
                                expectedPhase = G.phase;
                            } else {
                                expectedCoins = G.coins - cardCost;
                                expectedBuys = G.numBuys - 1;
                                expectedPhase = 1;
                            }
#if (NOISY_TEST == 1)
                            printf("\nTest player %d with %d coin(s) and %d buy(s) in a %d player game,", p, playerCoins, playerBuys, numPlayer);
                            printf(" attempt to buy card %d for %d coins when there is %d card(s) left.", cardNumber, cardCost, supplyCount);
#endif
                            buyCard(cardNumber, &G);
#if (NOISY_TEST == 1)
                            printf("\nG.coins = %d, expected = %d", G.coins, expectedCoins);
#endif
                            testFailures += assertTrue(G.coins, expectedCoins);
#if (NOISY_TEST == 1)
                            printf("\nG.numBuys = %d, expected = %d", G.numBuys, expectedBuys);
#endif
                            testFailures += assertTrue(G.numBuys, expectedBuys);
#if (NOISY_TEST == 1)
                            printf("\nG.phase = %d, expected = %d", G.phase, expectedPhase);
#endif
                            testFailures += assertTrue(G.phase, expectedPhase);
                        }
                    }
                }

                // iterate through kingdom cards
                for(i = 0; i < 10; i++){
                    cardNumber = k[i];
                    cardCost = getCost(cardNumber);
                    for(supplyCount = 0; supplyCount <= 1; supplyCount++){
                        for(playerCoins = cardCost - 1; playerCoins <= cardCost; playerCoins++){

                            memset(&G, 23, sizeof(struct gameState));   // clear the game state
                            initializeGame(numPlayer, k, seed, &G); // initialize a new game
                            G.whoseTurn = p;
                            G.numBuys = playerBuys;
                            G.supplyCount[cardNumber] = supplyCount;
                            G.coins = playerCoins;

                            if(playerBuys == 0 || playerCoins < cardCost || supplyCount == 0) {
                                expectedCoins = G.coins;
                                expectedBuys = G.numBuys;
                                expectedPhase = G.phase;
                            } else {
                                expectedCoins = G.coins - cardCost;
                                expectedBuys = G.numBuys - 1;
                                expectedPhase = 1;
                            }

                            //printf("\nTest player %d with %d coin(s) and %d buy(s) in a %d player game, attempt to buy card %d for %d coins when there is %d card left.", p, playerCoins, playerBuys, numPlayer, cardNumber, cardCost, supplyCount);
                            printf("\nTest player %d with %d coin(s) and %d buy(s) in a %d player game,", p, playerCoins, playerBuys, numPlayer);
                            printf(" attempt to buy card %d for %d coins when there is %d card(s) left.", cardNumber, cardCost, supplyCount);
                            buyCard(cardNumber, &G);
#if (NOISY_TEST == 1)
                            printf("\nG.coins = %d, expected = %d", G.coins, expectedCoins);
#endif
                            testFailures += assertTrue(G.coins, expectedCoins);
#if (NOISY_TEST == 1)
                            printf("\nG.numBuys = %d, expected = %d", G.numBuys, expectedBuys);
#endif
                            testFailures += assertTrue(G.numBuys, expectedBuys);
#if (NOISY_TEST == 1)
                            printf("\nG.phase = %d, expected = %d", G.phase, expectedPhase);
#endif
                            testFailures += assertTrue(G.phase, expectedPhase);
                        }
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


int assertTrue(int v1, int v2){
    if(v1 == v2){
        //printf("RESULT: PASS\n");
        return 0;
    } else {
        printf("\t<------------------- TEST FAILED");
        return 1;
    }
}

