/*
 * randomtestadventurer.c
 *

 */

/*
 * Include the following lines in your makefile:
 *
 * randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
 *      gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>

#define UNITTEST "randomtestadventurer"
#define FUNCTEST "AdventurerFunc()"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

// prototype functions
int checkAdventurerCard(int p, struct gameState *post);
int assertEqual(int v1, int v2);
int assertMemEqual(int *m1, int *m2, int size);


int main(){

    int i, j, n, c, p, treasureCount, worstCaseHand, cardsOK;
    int cards[13] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, copper, silver, gold};

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
        cardsOK = 0;

        // set up a sane game state where:
        // there is at least 2 treasure cards between the deck and discard pile
        // a the amount of held non treasure cards does not exceed 500
        while(!cardsOK){
            treasureCount = 0;

            G.deckCount[p] = floor(Random() * MAX_DECK);

            for(j = G.deckCount[p] - 1; j >= 0; j--){
                c = floor(Random() * 12.99);
                G.deck[p][j] = cards[c];
                if (cards[c] == copper || cards[c] == silver || cards[c] == gold){
                    treasureCount++;
                }
            }

            G.discardCount[p] = floor(Random() * MAX_DECK);
            for(j = G.discardCount[p] - 1; j >= 0; j--){
                c = floor(Random() * 12.49);
                G.discard[p][j] = cards[c];
                if (cards[c] == copper || cards[c] == silver || cards[c] == gold){
                    treasureCount++;
                }
            }

            worstCaseHand = G.deckCount[p] + G.discardCount[p] - treasureCount + 2;

            if(treasureCount >= 2 && worstCaseHand <= 500){
                cardsOK = 1;
            }
        }

        // need handCount to be able to hold all the cards in a worst case scenario
        G.handCount[p] = floor(Random() * (MAX_HAND - worstCaseHand));

        printf("\nplayer: %d, handCount: %d, deckCount: %d, discardCount: %d\n", p, G.handCount[p], G.deckCount[p], G.discardCount[p]);
        testFailures += checkAdventurerCard(p, &G);
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

int checkAdventurerCard(int p, struct gameState *post){
    struct gameState pre;
    memcpy(&pre, post, sizeof(struct gameState));

    int i, j, testAll;

    AdventurerFunc(post, p);

    int treasureCount = 0;
    int card1, card2, failures;
    int addDiscard = 0;

    // check if 2 treasure cards are in deck
    for(i = pre.deckCount[p] - 1; i >= 0; i --){
        if(pre.deck[p][i] == copper || pre.deck[p][i] == silver || pre.deck[p][i] == gold){
            if(treasureCount == 0){
                card1 = pre.deck[p][i];
            } else if (treasureCount == 1) {
                card2 = pre.deck[p][i];
                i = -1;
            }
            treasureCount++;
        } else if(treasureCount < 2) {
            addDiscard++;
        }
    }

    if(treasureCount >= 2){ // deck has enough treasure cards

        // can test for cards in deck and discard
        testAll = 1;

        // expected hand
        pre.hand[p][pre.handCount[p]] = card1;
        pre.handCount[p]++;
        pre.hand[p][pre.handCount[p]] = card2;
        pre.handCount[p]++;

        // expected discard and deck
        j = pre.deckCount[p] - addDiscard - 2;
        for (i = 0; i < addDiscard + 2; i++){
            if(pre.deck[p][j] == copper || pre.deck[p][j] == silver || pre.deck[p][j] == gold){
                // do nothing
            } else {
                pre.discard[p][pre.discardCount[p]] = pre.deck[p][j];
                pre.discardCount[p]++;
            }
            pre.deckCount[p]--;
            j++;
        }
    } else {
        // discard has been shuffled, can only test increase in handCount.
        // can not know what discardCount or deckCount will be
        testAll = 0;
        pre.handCount[p] += 2;
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

        //--------------------------------------------------------
        // Number of cards in deck
#if (NOISY_TEST == 1)
        printf("\npost.deckCount[%d]: %d, expected: %d", p, post->deckCount[p], pre.deckCount[p]);
#endif
        failures += assertEqual(post->deckCount[p], pre.deckCount[p]);

#if (NOISY_TEST == 1)
        printf("\nComparing memory of post->deck[%d] to expected", p);
#endif
        failures += assertMemEqual(post->deck[p], (int*)&pre.deck[p], sizeof(int) * pre.deckCount[p]);

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

    }

    return failures;
}
