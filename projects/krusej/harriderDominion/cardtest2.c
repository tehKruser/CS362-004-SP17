/*
 * cardtest2.c
 *

 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define UNITTEST "cardtest2"
#define FUNCTEST "SmithyFunc()"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

struct card_test{
    int deck[6];
    int deckCount;      // post count
    int newCards[3];
};

int main() {
    int assertEqual(int v1, int v2);
    int run_test(int handPos, int* test_hand, struct card_test* ct);
    int handPos;

    // last two cards are treasure
    struct card_test test1 = {
        {copper, silver, remodel, gold, village, baron},
        3,
        {baron, village, gold}
        };

    printf("----------------- %s Testing: %s ----------------", UNITTEST, FUNCTEST);

    int testFailures = 0;

    for(handPos = 0; handPos < 5; handPos++){
        int test_hand[5] = {adventurer, council_room, feast, gardens, mine};
        test_hand[handPos] = smithy;
        testFailures += run_test(handPos, test_hand, &test1);
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


int run_test(int handPos, int* test_hand, struct card_test* ct){

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
    //set player's deck
    G.deckCount[p] = 6;
    for(i = 0; i < 6; i++){
        G.deck[p][i] = ct->deck[i];
    }
    // set player's discard
    G.discardCount[p] = 0;

    // run card
    SmithyFunc(&G, p, handPos);

    //--------------------------------------------------------
    // test for correct results
    printf("\nTEST %d: SMITHY CARD AT HANDPOS %d", handPos+1, handPos);

    //--------------------------------------------------------
    // Number of cards in hand
    failcount = failures;
#if (NOISY_TEST == 1)
    printf("\nG.handCount[%d]: %d, expected: %d", p, G.handCount[p], 7);
#endif
    failures += assertEqual(G.handCount[p], 7);

    //--------------------------------------------------------
    // Correct cards in hand
    if(failures - failcount == 0){
        int card;
        for(i = 0; i < 5; i++){
            if(i == handPos){
                card = ct->newCards[2];
            } else {
                card = test_hand[i];
            }

#if (NOISY_TEST == 1)
            printf("\nG.hand[%d][%d]: %d, expected: %d", p, i, G.hand[p][i], card);
#endif
            failures += assertEqual(G.hand[p][i], card);
        }
        for(i = 5; i < 7; i++){
#if (NOISY_TEST == 1)
            printf("\nG.hand[%d][%d]: %d, expected: %d", p, i, G.hand[p][i], ct->newCards[i-5]);
#endif
            failures += assertEqual(G.hand[p][i], ct->newCards[i-5]);
        }
    }

    //--------------------------------------------------------
    // Number of cards in deck
    failcount = failures;
#if (NOISY_TEST == 1)
    printf("\nG.deckCount[%d]: %d, expected: %d", p, G.deckCount[p], ct->deckCount);
#endif
    failures += assertEqual(G.deckCount[p], ct->deckCount);

    //--------------------------------------------------------
    // Check that remainder of cards in deck is okay
    if(failcount - failures == 0 && ct->deckCount != 0 ){
        for(i = 0; i < ct->deckCount; i++){
#if (NOISY_TEST == 1)
            printf("\nG.deck[%d][%d]: %d, expected: %d", p, i, G.deck[p][i], ct->deck[i]);
#endif
            failures += assertEqual(G.deck[p][i], ct->deck[i]);
        }
    }

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
        printf("\nG.discard[%d][0]: %d, expected: %d", p, G.discard[p][0], smithy);
#endif
        failures += assertEqual(G.discard[p][0], smithy);
    }

    return failures;
}
