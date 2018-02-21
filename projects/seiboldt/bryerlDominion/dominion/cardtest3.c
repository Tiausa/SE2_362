
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "assertTester.c"


#define TESTCARD "great_hall"
#define MUCHTEXTC 1

/****************************************************************************
 * Name: cardtest3.c
 * Function Tested: great hall
 * Author: Tia Seibold
 * Description: Verifies that the great hall function adds one action and one card.
*****************************************************************************/


// runs the tests
int main () {

    int i = 0;
    int card = 0;
    int NumOfTreasures = 0;
    int NumOfOrigTreasures = 0;
    int newCards = 1;
    int discarded = 1;
    //int shuffledCards = 0;
    int countPasses = 0;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 4;
    int thisPlayer = 0;
    int opponentPlayer = 1;
    int gameSetup = 2;
    int eachPlayer = 0;
    int cardNum = 0;
    int newActions = 1;
    int gamecount = 0;
    // struct gametestG G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};
    struct gameState testG, G;






    //print testing smithy
    printf("----------------- Testing cardtest3: %s ----------------\n", TESTCARD);

    for (gamecount = 0; gamecount < 5; gamecount++) {

        for (eachPlayer = 0; eachPlayer < numPlayers; eachPlayer++) {
#if (MUCHTEXTC)
            // ----------- TEST 1: +2 cards --------------
            printf("TEST %d: Player %d gains gains one card and one action\n", eachPlayer + 1, eachPlayer + 1);
#endif

            for (cardNum = 0; cardNum < 5; cardNum++) {
                // initialize a game state and player cards
                initializeGame(numPlayers, k, seed, &G);

                if (cardNum >= 1) { testG.hand[eachPlayer][cardNum] = cardNum; }

                // copy the game state to a test case
                memcpy(&testG, &G, sizeof(struct gameState));

                cardEffect(great_hall, choice1, choice2, choice3, &testG, handpos, &bonus);


                // checks how much treasure is gained
                for (i = 0; i < testG.handCount[thisPlayer]; i++) {
                    card = testG.hand[thisPlayer][i];
                    if (card == copper || card == silver || card == gold) {
                        NumOfTreasures++;
                    }
                }

                // checks default treasure count
                for (i = 0; i < G.handCount[thisPlayer]; i++) {
                    card = G.hand[thisPlayer][i];
                    if (card == copper || card == silver || card == gold) {
                        NumOfOrigTreasures++;
                    }
                }

                //expect the testG's current player to have the same amount of cards in their hand as the before cardEffect was run, plus three.
                char handcount[] = "hand count";
#if (MUCHTEXTC)
                printf("hand count original = %d, after cardEffect = %d, expected = %d\n", G.handCount[thisPlayer],
                       testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
#endif
                countPasses += assertTrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded,
                                          handcount, 1, thisPlayer, 4);

                //expect the testG's current player to have one more action than before cardEffect was run.
                char numOfActions[] = "number of actions";
#if (MUCHTEXTC)
                printf("original number of actions = %d, after cardEffect = %d, expected = %d\n", G.numActions,
                       testG.numActions, G.numActions + newActions);
#endif
                countPasses += assertTrue(testG.numActions == G.numActions + newActions, numOfActions, 1, thisPlayer,
                                          4);

                //expect the testG's current player to have one more action than before cardEffect was run.
                char whoseTurn[] = "whose turn";
#if (MUCHTEXTC)
                printf("original player's turn = %d, after cardEffect = %d, expected = %d\n", G.outpostTurn,
                       testG.outpostTurn,
                       G.outpostTurn);
#endif
                countPasses += assertTrue(testG.outpostTurn == G.outpostTurn, whoseTurn, 0, thisPlayer, 4);

                //expect the testG's opponent player to have the same amount of cards in their deck as the before cardEffect was run.
                char discardcount[] = "discard count";
#if (MUCHTEXTC)
                printf("discard count original = %d, after cardEffect = %d\n", G.discardCount[thisPlayer],
                       testG.discardCount[thisPlayer]);
#endif
                countPasses += assertTrue(testG.deckCount[opponentPlayer] != G.deckCount[opponentPlayer], discardcount,
                                          0,
                                          opponentPlayer, 4);

                //expect the testG's current player to have two more treasure cards in their hand as the before cardEffect was run.
                char treasureCountArray[] = "treasure cards";
#if (MUCHTEXTC)
                printf("treasure card count original = %d, after cardEffect = %d, expected = %d\n", NumOfOrigTreasures,
                       NumOfTreasures, NumOfOrigTreasures);
#endif
                countPasses += assertTrue(NumOfOrigTreasures == NumOfTreasures, treasureCountArray, 0, thisPlayer, 4);

                //expect the testG's game setup to have the same amount of estate cards as the before cardEffect was run.
                char estatecount[] = "estate count";
#if (MUCHTEXTC)
                printf("estate count = %d, expected = %d\n", testG.supplyCount[estate], G.supplyCount[estate]);
#endif
                countPasses += assertTrue(testG.supplyCount[estate] == G.supplyCount[estate], estatecount, 0, gameSetup,
                                          4);

                //expect the testG's game setup to have the same amount of douchy cards as the before cardEffect was run.
                char douchycount[] = "douchy count";
#if (MUCHTEXTC)
                printf("douchy count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);
#endif
                countPasses += assertTrue(testG.supplyCount[duchy] == G.supplyCount[duchy], douchycount, 0, gameSetup,
                                          4);

                //expect the testG's game setup to have the same amount of province cards as the before cardEffect was run.
                char provincecount[] = "province count";
#if (MUCHTEXTC)
                printf("province count = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]);
#endif
                countPasses += assertTrue(testG.supplyCount[province] == G.supplyCount[province], provincecount, 0,
                                          gameSetup,
                                          4);

                //expect the testG's current player to have the same amount of supply cards than before cardEffect was run.
                int j = 0;
                for (i = 0; i < 25; i++) { if (testG.supplyCount[i] != G.supplyCount[i]) { j = 1; }}
                char supplyCards[] = "supply cards";
#if (MUCHTEXTC)
                printf("original number of supply cards = %d, after cardEffect = %d, expected = %d\n", 0, j, 0);
#endif
                countPasses += assertTrue(j == 0, supplyCards, 0, thisPlayer, 4);


                //expect the testG's opponent player to have the same amount of cards in their deck as the before cardEffect was run.
                char deckcount[] = "deck count";
#if (MUCHTEXTC)
                printf("deck count opponent player = %d, expected = %d\n", testG.deckCount[opponentPlayer],
                       G.deckCount[opponentPlayer]);
#endif
                countPasses += assertTrue(testG.deckCount[opponentPlayer] == G.deckCount[opponentPlayer], deckcount, 0,
                                          opponentPlayer, 4);


            }
        }
    }

//printf("\n\n%d\n\n", countPasses);
    if (countPasses == 45){printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);}
    else {printf("\n >>>>> FOUND BUGS: Testing complete.  %s <<<<<\n\n", TESTCARD);}

    return 0;
}