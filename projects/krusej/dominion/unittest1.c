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
#define FUNCTEST "buyCard"

int main() {
    int i;
    int seed = 1000;
    int numPlayer;
    int maxBonus = 10;
    int p, r, handCount, cardNumber, cardCost, playerCoins, playerBuys;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

    struct gameState G;
    int maxHandCount = 5;

    printf("TESTING buyCard():\n");
    for (numPlayer = 2; numplayer <= MAX_PLAYERS; numPlayer++) {
         for (p = 0; p < numPlayer; p++) {
            for (handCount = 1; handCount <= maxHandCount; handCount++){
                for(cardNumber = curse; cardNumber <= treasure_map; cardNumber++){
                    cardCost = getCost(cardNumber);
                    for(playerCoins = cardCost - 1; playerCoins <= cardCost; playerCoins++){
                        for(playerBuys = 0; playerBuys <= 1; playerBuys++){

                        }
                    }
                }
            }
         }
    }




    return 0;
}
