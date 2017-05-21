/*
 * cardtest1.c
 *

 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define UNITTEST "cardtest1"
#define FUNCTEST "adventurerCard()"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

struct card_test{
    char* description;
    int handCount;
    int treasureCards[2];
    int deck[6];
    int deckCount;      // post count
    int discard[4];
    int discardCount;   // post count
};

int main() {
    int assertEqual(int v1, int v2);
    int run_test(int* test_hand, struct card_test* ct);

    int test_hand[5] = {adventurer, council_room, feast, gardens, mine};

    // last two cards are treasure
    struct card_test test1 = {
        "\nTEST 1: LAST 2 CARDS ARE TREASURE",
        7,
        {silver, copper},
        {copper, silver, remodel, smithy, village, baron},
        0,
        {remodel, smithy, village, baron},
        4 };

    // first two cards are treasure
    struct card_test test2 = {
        "\nTEST 2: FIRST 2 CARDS ARE TREASURE",
        7,
        {gold, copper},
        {remodel, smithy, village, baron, copper, gold},
        4,
        {-1, -1, -1, -1},
        0 };

    // treasure cards are first and last
    struct card_test test3 = {
        "\nTEST 3: FIRST AND LAST CARDS ARE TREASURE",
        7,
        {gold, silver},
        {silver, remodel, smithy, village, baron, gold},
        0,
        {remodel, smithy, village, baron},
        4 };

    // treasure cards are in the middle
    struct card_test test4 = {
        "\nTEST 4: TREASURE CARDS ARE IN THE MIDDLE",
        7,
        {silver, silver},
        {remodel, silver, smithy, village, silver, baron},
        1,
        {smithy, village, baron, -1},
        3 };

    printf("----------------- %s Testing: %s ----------------", UNITTEST, FUNCTEST);

    int testFailures = 0;
    testFailures += run_test(test_hand, &test1);
    testFailures += run_test(test_hand, &test2);
    testFailures += run_test(test_hand, &test3);
    testFailures += run_test(test_hand, &test4);


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


int run_test(int* test_hand, struct card_test* ct){

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
    adventurerCard(&G);

    //--------------------------------------------------------
    // test for correct results
    printf(ct->description);

    //--------------------------------------------------------
    // Number of cards in hand
#if (NOISY_TEST == 1)
    printf("\nG.handCount[%d]: %d, expected: %d", p, G.handCount[p], 7);
#endif
    failures += assertEqual(G.handCount[p], 7);

    //--------------------------------------------------------
    // Correct treasure cards in hand
#if (NOISY_TEST == 1)
    printf("\nG.hand[%d][%d]: %d, expected: %d", p, 5, G.hand[p][5], ct->treasureCards[0]);
#endif
    failures += assertEqual(G.hand[p][5], ct->treasureCards[0]);
#if (NOISY_TEST == 1)
    printf("\nG.hand[%d][%d]: %d, expected: %d", p, 6, G.hand[p][6], ct->treasureCards[1]);
#endif
    failures += assertEqual(G.hand[p][6], ct->treasureCards[1]);

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
    printf("\nG.discardCount[%d]: %d, expected: %d", p, G.discardCount[p], ct->discardCount);
#endif
    failures += assertEqual(G.discardCount[p], ct->discardCount);

    //--------------------------------------------------------
    // Check cards in discard pile
    if(failcount - failures == 0 && ct->discardCount != 0){
        for(i = 0; i < ct->discardCount; i++){
#if (NOISY_TEST == 1)
            printf("\nG.discard[%d][%d]: %d, expected: %d", p, i, G.discard[p][i], ct->discard[i]);
#endif
            failures += assertEqual(G.discard[p][i], ct->discard[i]);
        }
    }

    return failures;
}
