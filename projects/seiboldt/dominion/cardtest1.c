

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include "assertTester.c"

#define TESTCARD "smithy"
#define MUCHTEXTA 1

/****************************************************************************
 * Name: cardtest1.c
 * Function Tested: smithy
 * Author: Tia Seibold
 * Description: Tests Smithy card adds three cards to player's hand.
*****************************************************************************/

int main() {
    int count = 0;
    int newCards = 0;
    int discarded = 1;
    int shuffledCards = 0;
    int countPasses = 0;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 4;
    int thisPlayer = 0;
    int nextPlayer = 1;
    int cardNum = 0;
    int gameSetup = 2;
    int gamecount = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};



#if (MUCHTEXTA)
    //print testing smithy
    printf("----------------- Testing cardtest1: %s ----------------\n", TESTCARD);
#endif
#if (MUCHTEXTA)
    // ----------- TEST 1: +3 cards --------------
    printf("TEST 1: +3 cards\n");
#endif

for (gamecount = 0; gamecount < 5; gamecount++) {
    for (count = 0; count < numPlayers; count++) {

        for (cardNum = 0; cardNum < 5; cardNum++) {

            // initialize a game state and player cards
            initializeGame(numPlayers, k, seed, &G);

            if (cardNum >= 1) { testG.hand[count][cardNum] = cardNum; }

            // copy the game state to a test case
            memcpy(&testG, &G, sizeof(struct gameState));


            //call cardEffect with smithy
            int result = cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
            if (result != 0) {
#if (MUCHTEXTA)
                printf("\nReturn cardEffect: %d, Expected: %d. Exiting due to this error.", result, 0);
#endif
                return -1;
            }

            //three cards will be added
            newCards = 3;

            //expect the testG's current player to have the same amount of cards in their hand as the before cardEffect was run, plus three.
            char handcount[] = "hand count";
#if (MUCHTEXTA)
            printf("hand count original = %d, after cardEffect = %d, expected = %d\n", G.handCount[thisPlayer],
                   testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
#endif
            countPasses += assertTrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded,
                                      handcount, 1, thisPlayer, 1);

            //expect the testG's current player to have the same amount of cards in their deck as the before cardEffect was run, minus three.
            char deckcount[] = "deck count";
#if (MUCHTEXTA)
            printf("deck count original = %d, after cardEffect = %d, expected = %d\n", G.handCount[thisPlayer],
                   testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
#endif
            countPasses += assertTrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards,
                                      deckcount, 1, thisPlayer, 1);

            char discardcount[] = "discard count";
            //expect the testG's next player to have one more card in their discard count as the before cardEffect was run.
#if (MUCHTEXTA)
            printf("discard count original = %d, after cardEffect = %d\n", G.deckCount[thisPlayer],
                   testG.deckCount[thisPlayer]);
#endif
            countPasses += assertTrue(testG.deckCount[thisPlayer] != G.deckCount[thisPlayer], discardcount, 1,
                                      thisPlayer, 1);

#if (MUCHTEXTA)
            //expect the testG's next player to have the same amount of cards in their hand as the before cardEffect was run.
            printf("hand count next player = %d, expected = %d\n", testG.handCount[nextPlayer],
                   G.handCount[nextPlayer]);
#endif
            countPasses += assertTrue(testG.handCount[nextPlayer] == G.handCount[nextPlayer], handcount, 0, nextPlayer,
                                      1);
#if (MUCHTEXTA)
            //expect the testG's next player to have the same amount of cards in their deck as the before cardEffect was run.
            printf("deck count next player = %d, expected = %d\n", testG.deckCount[nextPlayer],
                   G.deckCount[nextPlayer]);
#endif
            countPasses += assertTrue(testG.deckCount[nextPlayer] == G.deckCount[nextPlayer], deckcount, 0, nextPlayer,
                                      1);

            //expect the testG's game setup to have the same amount of estate cards as the before cardEffect was run.
            char estatecount[] = "estate count";
#if (MUCHTEXTA)
            printf("estate = %d, expected = %d, duchy = %d, expected = %d, province = %d, expected = %d\n",
                   testG.supplyCount[estate], \
               G.supplyCount[estate], testG.supplyCount[duchy], G.supplyCount[duchy], testG.supplyCount[province], \
               G.supplyCount[province]);
#endif
            countPasses += assertTrue(testG.supplyCount[estate] == G.supplyCount[estate], estatecount, 0, gameSetup, 1);

            //expect the testG's game setup to have the same amount of douchy cards as the before cardEffect was run.
            char douchycount[] = "douchy count";
#if (MUCHTEXTA)
            printf("douchy count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);
#endif
            countPasses += assertTrue(testG.supplyCount[duchy] == G.supplyCount[duchy], douchycount, 0, gameSetup, 1);

            //expect the testG's game setup to have the same amount of province cards as the before cardEffect was run.
            char provincecount[] = "province count";
#if (MUCHTEXTA)
            printf("province count = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]);
#endif
            countPasses += assertTrue(testG.supplyCount[province] == G.supplyCount[province], provincecount, 0,
                                      gameSetup,
                                      1);

            //expect the testG's game setup to have the same amount of adventurer cards as the before cardEffect was run.
            char adventurercount[] = "adventurer count";
#if (MUCHTEXTA)
            printf("adventurer = %d, expected = %d\n", testG.supplyCount[adventurer], G.supplyCount[adventurer]);
#endif
            countPasses += assertTrue(testG.supplyCount[adventurer] == G.supplyCount[adventurer], adventurercount, 0,
                                      gameSetup, 1);

            //expect the testG's current player to have one more action than before cardEffect was run.
            char numOfActions[] = "number of actions";
#if (MUCHTEXTA)
            printf("original number of actions = %d, after cardEffect = %d, expected = %d\n", G.numActions,
                   testG.numActions, G.numActions);
#endif
            countPasses += assertTrue(testG.numActions == G.numActions, numOfActions, 0, thisPlayer, 1);
        }
    }
}
    //printf("\n\n%d\n\n", countPasses);
    if (countPasses == 180){printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);}
    else {printf("\n >>>>> FOUND BUGS: Testing complete.  %s <<<<<\n\n", TESTCARD);}

    return 0;
}
