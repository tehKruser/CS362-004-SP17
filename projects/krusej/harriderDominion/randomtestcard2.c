/*
 * randomtestcard2.c
 *

 */

/*
 * Include the following lines in your makefile:
 *
 * randomtestcard2: randomtestcard2.c dominion.o rngs.o
 *      gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>

#define UNITTEST "randomtestcard2"
#define FUNCTEST "SmithyFunc()"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

// prototype functions
int checkCard(int p, struct gameState *post, int handPos);
int assertEqual(int v1, int v2);
int assertMemEqual(int *m1, int *m2, int size);


int main(){
    int i, n, p, handPos, totalCards, cardsOK;

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

        G.handCount[p] = floor(Random() * (MAX_HAND - 4)) + 1; // game state requires smithy in hand
        handPos = floor(Random() * (G.handCount[p] - 1));

        G.hand[p][handPos] = smithy;   // set smithy position in hand

        cardsOK = 0;
        while(!cardsOK) {
            G.discardCount[p] = floor(Random() * (MAX_DECK - 1)); // will discard, so can't have full deck
            G.deckCount[p] = floor(Random() * (MAX_DECK - 1)); // will discard, so can't have full deck
            totalCards = G.discardCount[p] + G.deckCount[p];
            if(totalCards >= 3){
                cardsOK = 1;
            }
        }

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
    int i, failures, testAll, fromDiscard;

    struct gameState pre;
    memcpy(&pre, post, sizeof(struct gameState));

    SmithyFunc(post, p, handPos);

    if(pre.deckCount[p] >= 3){
        testAll = 1;
        //--------------------------------------------------------
        // Set expected cards in hand
        for(i = 0; i < 3; i++){
            pre.hand[p][pre.handCount[p]] = pre.deck[p][pre.deckCount[p] - 1 ];
            pre.handCount[p]++;
            pre.deckCount[p]--;
        }

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
        pre.discard[p][pre.discardCount[p]] = smithy;
        pre.discardCount[p]++;

    } else {
        testAll = 0;

        // we can only verify the handCount, deckCount and discardCount b/c a shuffle happened
        pre.handCount[p] += 2;

        fromDiscard = 3 - pre.deckCount[p];
        pre.deckCount[p] = pre.discardCount[p] - fromDiscard;

        //--------------------------------------------------------
        // Set expected cards in discard
        pre.discardCount[p] = 1;    // should only be 1 card in discard if shuffle happened
        pre.discard[p][pre.discardCount[p] - 1] = smithy;
    }

    // tests
    failures = 0;


    //--------------------------------------------------------
    // Number of cards in hand
#if (NOISY_TEST == 1)
    printf("\npost.handCount[%d]: %d, expected: %d", p, post->handCount[p], pre.handCount[p]);
#endif
    failures += assertEqual(post->handCount[p], pre.handCount[p]);

    if(testAll){
#if (NOISY_TEST == 1)
        printf("\nComparing memory of post->hand[%d] to expected", p);
#endif
        failures += assertMemEqual(post->hand[p], (int*)&pre.hand[p], sizeof(int) * pre.handCount[p]);
    }

    //--------------------------------------------------------
    // Number of cards in deck
#if (NOISY_TEST == 1)
    printf("\npost.deckCount[%d]: %d, expected: %d", p, post->deckCount[p], pre.deckCount[p]);
#endif
    failures += assertEqual(post->deckCount[p], pre.deckCount[p]);

    if(testAll && pre.deckCount[p] != 0){
#if (NOISY_TEST == 1)
        printf("\nComparing memory of post->deck[%d] to expected", p);
#endif
        failures += assertMemEqual(post->deck[p], (int*)&pre.deck[p], sizeof(int) * pre.deckCount[p]);
    }

    //--------------------------------------------------------
    // Number of cards in discard
#if (NOISY_TEST == 1)
    printf("\npost.discardCount[%d]: %d, expected: %d", p, post->discardCount[p], pre.discardCount[p]);
#endif
    failures += assertEqual(post->discardCount[p], pre.discardCount[p]);

    if(testAll && pre.discardCount[p] != 0){
#if (NOISY_TEST == 1)
        printf("\nComparing memory of post->discard[%d] to expected", p);
#endif
        failures += assertMemEqual(post->discard[p], (int*)&pre.discard[p], sizeof(int) * pre.discardCount[p]);
    }

    return failures;
}
