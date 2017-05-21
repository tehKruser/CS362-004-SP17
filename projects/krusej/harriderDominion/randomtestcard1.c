/*
 * randomtestcard1.c
 *

 */

/*
 * Include the following lines in your makefile:
 *
 * randomtestcard1: randomtestcard1.c dominion.o rngs.o
 *      gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>

#define UNITTEST "randomtestcard1"
#define FUNCTEST "OutpostFunc()"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

// prototype functions
int checkCard(int p, struct gameState *post, int handPos);
int assertEqual(int v1, int v2);
int assertMemEqual(int *m1, int *m2, int size);


int main(){
    int i, n, p, handPos;

    struct gameState G;

    printf("Testing %s.\n RANDOM TESTS.\n", FUNCTEST);

    SelectStream(2);
    PutSeed(3);

    int testFailures = 0;

    for(n = 0; n < 2000; n++){
        for(i = 0; i < sizeof(struct gameState); i++){
            ((char*)&G)[i] = floor(Random() * 256);
        }
        p = floor(Random() * 4);
        G.whoseTurn = p;
        G.outpostPlayed = 0;
        G.playedCardCount = 0;

        G.handCount[p] = floor(Random() * (MAX_HAND - 1)) + 1; // game state requires outpost in hand
        handPos = floor(Random() * (G.handCount[p] - 1));

        G.hand[p][handPos] = outpost;   // set outpost position in hand

        G.discardCount[p] = floor(Random() * (MAX_DECK - 1)); // will discard, so can't have full deck

        testFailures += checkCard(p, &G, handPos);
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

int assertMemEqual(int *m1, int *m2, int size){
    if(memcmp(m1, m2, size) == 0){
        return 0;
    } else {
        printf("\t<------------------- TEST FAILED");
        return 1;
    }
}

int checkCard(int p, struct gameState *post, int handPos){
    int failures;

    struct gameState pre;
    memcpy(&pre, post, sizeof(struct gameState));

    OutpostFunc(post, p, handPos);

    //--------------------------------------------------------
    // Set expected outpost value
    pre.outpostPlayed++;

    //--------------------------------------------------------
    // Set expected cards in hand
    pre.hand[p][handPos] = -1;

    if(handPos == pre.handCount[p] - 1){
        pre.handCount[p]--;
    } else {
        pre.hand[p][handPos] = pre.hand[p][pre.handCount[p] - 1];
        pre.hand[p][pre.handCount[p] - 1] = -1;
        pre.handCount[p]--;
    }

    //--------------------------------------------------------
    // Set expected cards in discard
    pre.discard[p][pre.discardCount[p]] = outpost;
    pre.discardCount[p]++;

    // tests
    failures = 0;


    //--------------------------------------------------------
    // Check outpost flag
#if (NOISY_TEST == 1)
    printf("\npost.outpostPlayed: %d, expected: %d", post->outpostPlayed, pre.outpostPlayed);
#endif
    failures += assertEqual(post->outpostPlayed, pre.outpostPlayed);

    //--------------------------------------------------------
    // Number of cards in hand
#if (NOISY_TEST == 1)
    printf("\npost.handCount[%d]: %d, expected: %d", p, post->handCount[p], pre.handCount[p]);
#endif
    failures += assertEqual(post->handCount[p], pre.handCount[p]);


#if (NOISY_TEST == 1)
    printf("\nComparing memory of post->hand[%d] to expected", p);
#endif
    failures += assertMemEqual(post->hand[p], (int*)&pre.hand[p], sizeof(int) * pre.handCount[p]);

    //--------------------------------------------------------
    // Number of cards in discard
#if (NOISY_TEST == 1)
    printf("\npost.discardCount[%d]: %d, expected: %d", p, post->discardCount[p], pre.discardCount[p]);
#endif
    failures += assertEqual(post->discardCount[p], pre.discardCount[p]);

#if (NOISY_TEST == 1)
    printf("\nComparing memory of post->discard[%d] to expected", p);
#endif
    failures += assertMemEqual(post->discard[p], (int*)&pre.discard[p], sizeof(int) * pre.discardCount[p]);

    return failures;
}
