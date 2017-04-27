/*
 * unittest2.c
 *

 */

/*
 * Include the following lines in your makefile:
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define UNITTEST "unittest2"
#define FUNCTEST "isGameOver()"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int assertTrue(int v1, int v2);

    int i, r, expected_r;
    int seed = 1000;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int supplyCards[4] = {province, estate, duchy, gold};
    int initialCount;

    struct gameState G;
    int testFailures = 0;
    //int maxHandCount = 5;

    printf("----------------- %s Testing: %s ----------------", UNITTEST, FUNCTEST);

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(2, k, seed, &G); // initialize a new game

    // Initial state
    r = isGameOver(&G);
#if (NOISY_TEST == 1)
    printf("\nTest when game starts.");
    printf("\nisGameOver return value: %d, expected: 0", r);
#endif
    testFailures += assertTrue(r, 0);

    // No province cards
    initialCount = G.supplyCount[province];
    G.supplyCount[province] = 0;
    r = isGameOver(&G);
#if (NOISY_TEST == 1)
    printf("\nTest when no province cards (card %d) in supply.", province);
    printf("\nisGameOver return value: %d, expected: 1", r);
#endif
    testFailures += assertTrue(r, 1);
    G.supplyCount[province] = initialCount;

    for(i=1; i<4; i++){
        G.supplyCount[supplyCards[i]] = 0;

        expected_r = 0;
        if(i == 3) {
            expected_r = 1;
        }

        r = isGameOver(&G);
#if (NOISY_TEST == 1)
        printf("\nTest when %d supply cards are empty.", i);
        printf(" Setting card %d to 0.", supplyCards[i]);
        printf("\nisGameOver return value: %d, expected: %d", r, expected_r);
#endif
        testFailures += assertTrue(r, expected_r);
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

