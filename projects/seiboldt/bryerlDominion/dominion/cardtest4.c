

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "assertTester.c"


#define TESTCARD "cutpurse"
#define MUCHTEXTD 1

/****************************************************************************
 * Name: cardtest4.c
 * Function Tested: cutpurse
 * Author: Tia Seibold
 * Description: Verifies that the curpurse card takes on copper and adds two points.
*****************************************************************************/

// runs the tests
int main () {

    int i = 0, j = 0;
    int card = 0;
    int NumOfTreasures = 0;
    int NumOfOrigTreasures = 0;
    int newCards = 0;
    int discarded = 1;
    //int shuffledCards = 0;
    int countPasses = 0;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 4;
    int thisPlayer = 0;
    int numOfCardsCInHand = 0;
    int opponentPlayer = 1;
    int gameSetup = 2;
    int player = 0;
    int gamecount = 0;
    // struct gametestG G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};
    struct gameState testG, G;






    printf("----------------- Testing cardtest4: %s ----------------\n", TESTCARD);
    for (gamecount = 0; gamecount < 5; gamecount++) {


        // initialize a game state and player cards
        initializeGame(numPlayers, k, seed, &G);


#if (MUCHTEXTD)
        // ----------- TEST 1: +2 cards --------------
        printf("TEST 1: Player gains 2 points and others loose one cooper.\n"
                       "Preconditions: Opponent has one copper in the first position.\n");
#endif

        G.hand[opponentPlayer][0] = copper;
        G.hand[opponentPlayer][1] = cutpurse;
        G.hand[opponentPlayer][2] = great_hall;
        G.hand[opponentPlayer][3] = estate;
        G.hand[opponentPlayer][4] = duchy;


        int copperCoins[500];
        int silverCoins[500];
        int goldCoins[500];
        for (i = 0; i < 500; i++) {
            copperCoins[i] = copper;
            silverCoins[i] = silver;
            goldCoins[i] = gold;
        }


        player = 0;
        for (player = 0; player < numPlayers; player++) {
            for (numOfCardsCInHand = 1; numOfCardsCInHand <= 5; numOfCardsCInHand++) {
                G.handCount[player] = numOfCardsCInHand;
                memcpy(G.hand[player], goldCoins, sizeof(int) * numOfCardsCInHand);
                if (numOfCardsCInHand == 5) {
                    G.handCount[player] = numOfCardsCInHand;
                    memcpy(G.hand[player], silverCoins, sizeof(int) * numOfCardsCInHand);

                    G.hand[player][0] = copper;
                }
            }
        }





        // copy the game state to a test case
        memcpy(&testG, &G, sizeof(struct gameState));

        cardEffect(cutpurse, choice1, choice2, choice3, &testG, handpos, &bonus);

        //newCards are two since there are two new treasures added to the hand
        newCards = 0;




        // checks how much treasure is gained
        NumOfTreasures = 0;
        for (i = 0; i < testG.handCount[thisPlayer]; i++) {
            card = testG.hand[thisPlayer][i];
            if (card == copper || card == silver || card == gold) {
                NumOfTreasures++;
            }
        }


        // checks default treasure count
        NumOfOrigTreasures = 0;
        for (i = 0; i < G.handCount[thisPlayer]; i++) {
            card = G.hand[thisPlayer][i];
            if (card == copper || card == silver || card == gold) {
                NumOfOrigTreasures++;
            }
        }



        //expect the testG's current player to have the same amount of cards in their hand as the before cardEffect was run, plus three.
        char handcount[] = "hand count";
#if (MUCHTEXTD)
        printf("hand count original = %d, after cardEffect = %d, expected = %d\n", G.handCount[thisPlayer],
               testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
#endif
        countPasses += assertTrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded,
                                  handcount, 0, thisPlayer, 3);

        //expect the testG's current player to have two more treasure cards in their hand as the before cardEffect was run.
        char treasureCountArray[] = "treasure cards";
#if (MUCHTEXTD)
        printf("treasure card count original = %d, after cardEffect = %d, expected = %d\n", NumOfOrigTreasures,
               NumOfTreasures, NumOfOrigTreasures - 1);
#endif
        countPasses += assertTrue(NumOfOrigTreasures - 1 == NumOfTreasures, treasureCountArray, 0, thisPlayer, 3);

        char discardcount[] = "discard count";
        //expect the testG's next player to have one more card in their discard count as the before cardEffect was run.
#if (MUCHTEXTD)
        printf("discard count original = %d, after cardEffect = %d\n", G.discardCount[thisPlayer],
               testG.discardCount[thisPlayer]);
#endif
        countPasses += assertTrue(testG.discardCount[thisPlayer] != G.discardCount[thisPlayer], discardcount, 1,
                                  thisPlayer, 3);


        //expect the testG's game setup to have the same amount of estate cards as the before cardEffect was run.
        char estatecount[] = "estate count";
#if (MUCHTEXTD)
        printf("estate = %d, expected = %d, duchy = %d, expected = %d, province = %d, expected = %d\n",
               testG.supplyCount[estate], \
           G.supplyCount[estate], testG.supplyCount[duchy], G.supplyCount[duchy], testG.supplyCount[province], \
           G.supplyCount[province]);
#endif
        countPasses += assertTrue(testG.supplyCount[estate] == G.supplyCount[estate], estatecount, 0, gameSetup, 3);

        //expect the testG's game setup to have the same amount of douchy cards as the before cardEffect was run.
        char douchycount[] = "douchy count";
#if (MUCHTEXTD)
        printf("douchy count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);
#endif
        countPasses += assertTrue(testG.supplyCount[duchy] == G.supplyCount[duchy], douchycount, 0, gameSetup, 3);

        //expect the testG's game setup to have the same amount of province cards as the before cardEffect was run.
        char provincecount[] = "province count";
#if (MUCHTEXTD)
        printf("province count = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]);
#endif
        countPasses += assertTrue(testG.supplyCount[province] == G.supplyCount[province], provincecount, 0, gameSetup,
                                  3);

        //expect the testG's current player to have one more action than before cardEffect was run.
        char numOfActions[] = "number of actions";
#if (MUCHTEXTD)
        printf("original number of actions = %d, after cardEffect = %d, expected = %d\n", G.numActions,
               testG.numActions, G.numActions);
#endif
        countPasses += assertTrue(testG.numActions == G.numActions, numOfActions, 0, thisPlayer, 3);

        //expect the testG's current player to have the same amount of supply cards than before cardEffect was run.
        //int i = 0, j = 0;
        for (i = 0; i < 25; i++) { if (testG.supplyCount[i] != G.supplyCount[i]) { j = 1; }}
        char supplyCards[] = "supply cards";
#if (MUCHTEXTD)
        printf("original number of supply cards = %d, after cardEffect = %d, expected = %d\n", 0, j, 0);
#endif
        countPasses += assertTrue(j == 0, supplyCards, 0, thisPlayer, 4);


        int NumOfCoppers = 0;
        for (i = 0; i < G.handCount[opponentPlayer]; i++) {
            card = G.hand[opponentPlayer][i];
            if (card == copper || card == silver || card == gold) {
                NumOfCoppers++;
            }
        }
#if (MUCHTEXTD)
        printf("hand count opponent player original = %d, after cardEffect = %d, expected = %d\n",
               G.handCount[opponentPlayer], testG.handCount[opponentPlayer], G.handCount[opponentPlayer] - 1);
#endif
        countPasses += assertTrue(testG.handCount[opponentPlayer] == G.handCount[opponentPlayer] - 1, handcount, 1,
                                  opponentPlayer, 3);
        // }
        //expect the testG's opponent player to have the same amount of cards in their deck as the before cardEffect was run.
        char deckcount[] = "deck count";
#if (MUCHTEXTD)
        printf("deck count opponent player original  = %d, after cardEffect = %d, expected = %d\n",
               G.deckCount[opponentPlayer], testG.deckCount[opponentPlayer], G.deckCount[opponentPlayer]);
#endif
        countPasses += assertTrue(testG.deckCount[opponentPlayer] == G.deckCount[opponentPlayer], deckcount, 0,
                                  opponentPlayer, 3);


#if (MUCHTEXTD)
        // ----------- TEST 1: +2 cards --------------
        printf("TEST 2: Player gains 2 points and others loose one cooper.\n"
                       "Preconditions: Opponent has one copper in the second position.\n");
#endif

        // initialize a game state and player cards
        initializeGame(numPlayers, k, seed, &G);


        player = 0;
        for (player = 0; player < numPlayers; player++) {
            for (numOfCardsCInHand = 1; numOfCardsCInHand <= 5; numOfCardsCInHand++) {
                G.handCount[player] = numOfCardsCInHand;
                memcpy(G.hand[player], goldCoins, sizeof(int) * numOfCardsCInHand);
                if (numOfCardsCInHand == 5) {
                    G.handCount[player] = numOfCardsCInHand;
                    memcpy(G.hand[player], silverCoins, sizeof(int) * numOfCardsCInHand);

                    G.hand[player][1] = copper;
                }
            }






            // copy the game state to a test case
            memcpy(&testG, &G, sizeof(struct gameState));


            cardEffect(cutpurse, choice1, choice2, choice3, &testG, handpos, &bonus);

            //newCards are two since there are two new treasures added to the hand
            newCards = 0;



            // checks how much treasure is gained
            NumOfTreasures = 0;
            for (i = 0; i < testG.handCount[thisPlayer]; i++) {
                card = testG.hand[thisPlayer][i];
                if (card == copper || card == silver || card == gold) {
                    NumOfTreasures++;
                }
            }


            // checks default treasure count
            NumOfOrigTreasures = 0;
            for (i = 0; i < G.handCount[thisPlayer]; i++) {
                card = G.hand[thisPlayer][i];
                if (card == copper || card == silver || card == gold) {
                    NumOfOrigTreasures++;
                }
            }



            //expect the testG's current player to have the same amount of cards in their hand as the before cardEffect was run, plus three.
            // char handcount[] = "hand count";
#if (MUCHTEXTD)
            printf("hand count original = %d, after cardEffect = %d, expected = %d\n", G.handCount[thisPlayer],
                   testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
#endif
            countPasses += assertTrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded,
                                      handcount, 0, thisPlayer, 3);

            //expect the testG's current player to have two more treasure cards in their hand as the before cardEffect was run.
            //  char treasureCountArray[] = "treasure cards";
#if (MUCHTEXTD)
            printf("treasure card count original = %d, after cardEffect = %d, expected = %d\n", NumOfOrigTreasures,
                   NumOfTreasures, NumOfOrigTreasures - 1);
#endif
            countPasses += assertTrue(NumOfOrigTreasures - 1 == NumOfTreasures, treasureCountArray, 0, thisPlayer, 3);

            //expect the testG's game setup to have the same amount of estate cards as the before cardEffect was run.
            //  char estatecount [] = "estate count";
#if (MUCHTEXTD)
            printf("estate = %d, expected = %d, duchy = %d, expected = %d, province = %d, expected = %d\n",
                   testG.supplyCount[estate], \
           G.supplyCount[estate], testG.supplyCount[duchy], G.supplyCount[duchy], testG.supplyCount[province], \
           G.supplyCount[province]);
#endif
            countPasses += assertTrue(testG.supplyCount[estate] == G.supplyCount[estate], estatecount, 0, gameSetup, 3);

            //expect the testG's game setup to have the same amount of douchy cards as the before cardEffect was run.
            //char douchycount [] = "douchy count";
#if (MUCHTEXTD)
            printf("douchy count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);
#endif
            countPasses += assertTrue(testG.supplyCount[duchy] == G.supplyCount[duchy], douchycount, 0, gameSetup, 3);

            //expect the testG's game setup to have the same amount of province cards as the before cardEffect was run.
            // char provincecount [] = "province count";
#if (MUCHTEXTD)
            printf("province count = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]);
#endif
            countPasses += assertTrue(testG.supplyCount[province] == G.supplyCount[province], provincecount, 0,
                                      gameSetup,
                                      3);

            //expect the testG's current player to have one more action than before cardEffect was run.
            // char numOfActions[] = "number of actions";
#if (MUCHTEXTD)
            printf("original number of actions = %d, after cardEffect = %d, expected = %d\n", G.numActions,
                   testG.numActions, G.numActions);
#endif
            countPasses += assertTrue(testG.numActions == G.numActions, numOfActions, 0, thisPlayer, 3);

            //expect the testG's current player to have the same amount of supply cards than before cardEffect was run.
            //int i = 0, j = 0;
            for (i = 0; i < 25; i++) { if (testG.supplyCount[i] != G.supplyCount[i]) { j = 1; }}
            //char supplyCards[] = "supply cards";
#if (MUCHTEXTD)
            printf("original number of supply cards = %d, after cardEffect = %d, expected = %d\n", 0, j, 0);
#endif
            countPasses += assertTrue(j == 0, supplyCards, 0, thisPlayer, 4);


            NumOfCoppers = 0;
            for (i = 0; i < G.handCount[opponentPlayer]; i++) {
                card = G.hand[opponentPlayer][i];
                if (card == copper || card == silver || card == gold) {
                    NumOfCoppers++;
                }
            }
#if (MUCHTEXTD)
            printf("hand count opponent player original = %d, after cardEffect = %d, expected = %d\n",
                   G.handCount[opponentPlayer], testG.handCount[opponentPlayer], G.handCount[opponentPlayer] - 1);
#endif
            countPasses += assertTrue(testG.handCount[opponentPlayer] == G.handCount[opponentPlayer] - 1, handcount, 1,
                                      opponentPlayer, 3);
            // }
            //expect the testG's opponent player to have the same amount of cards in their deck as the before cardEffect was run.
            // char deckcount[] = "deck count";
#if (MUCHTEXTD)
            printf("deck count opponent player original  = %d, after cardEffect = %d, expected = %d\n",
                   G.deckCount[opponentPlayer], testG.deckCount[opponentPlayer], G.deckCount[opponentPlayer]);
#endif
            countPasses += assertTrue(testG.deckCount[opponentPlayer] == G.deckCount[opponentPlayer], deckcount, 0,
                                      opponentPlayer, 3);

        }
#if (MUCHTEXTD)
        // ----------- TEST 1: +2 cards --------------
        printf("TEST 3: Player gains 2 points and others loose one cooper.\n"
                       "Preconditions: Opponent has one copper in the third position.\n");
#endif

        // initialize a game state and player cards
        initializeGame(numPlayers, k, seed, &G);


        player = 0;
        for (player = 0; player < numPlayers; player++) {
            for (numOfCardsCInHand = 1; numOfCardsCInHand <= 5; numOfCardsCInHand++) {

                G.handCount[player] = numOfCardsCInHand;
                memcpy(G.hand[player], goldCoins, sizeof(int) * numOfCardsCInHand);
                if (numOfCardsCInHand == 5) {
                    G.handCount[player] = numOfCardsCInHand;
                    memcpy(G.hand[player], silverCoins, sizeof(int) * numOfCardsCInHand);

                    G.hand[player][2] = copper;
                }
            }






            // copy the game state to a test case
            memcpy(&testG, &G, sizeof(struct gameState));

            cardEffect(cutpurse, choice1, choice2, choice3, &testG, handpos, &bonus);

            //newCards are two since there are two new treasures added to the hand
            newCards = 0;


            // checks how much treasure is gained
            NumOfTreasures = 0;
            for (i = 0; i < testG.handCount[thisPlayer]; i++) {
                card = testG.hand[thisPlayer][i];
                if (card == copper || card == silver || card == gold) {
                    NumOfTreasures++;
                }
            }


            // checks default treasure count
            NumOfOrigTreasures = 0;
            for (i = 0; i < G.handCount[thisPlayer]; i++) {
                card = G.hand[thisPlayer][i];
                if (card == copper || card == silver || card == gold) {
                    NumOfOrigTreasures++;
                }
            }


            //expect the testG's current player to have the same amount of cards in their hand as the before cardEffect was run, plus three.
            // char handcount[] = "hand count";
#if (MUCHTEXTD)
            printf("hand count original = %d, after cardEffect = %d, expected = %d\n", G.handCount[thisPlayer],
                   testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
#endif
            countPasses += assertTrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded,
                                      handcount, 0, thisPlayer, 3);

            //expect the testG's current player to have two more treasure cards in their hand as the before cardEffect was run.
            //  char treasureCountArray[] = "treasure cards";
#if (MUCHTEXTD)
            printf("treasure card count original = %d, after cardEffect = %d, expected = %d\n", NumOfOrigTreasures,
                   NumOfTreasures, NumOfOrigTreasures - 1);
#endif
            countPasses += assertTrue(NumOfOrigTreasures - 1 == NumOfTreasures, treasureCountArray, 0, thisPlayer, 3);

            //expect the testG's game setup to have the same amount of estate cards as the before cardEffect was run.
            //  char estatecount [] = "estate count";
#if (MUCHTEXTD)
            printf("estate = %d, expected = %d, duchy = %d, expected = %d, province = %d, expected = %d\n",
                   testG.supplyCount[estate], \
           G.supplyCount[estate], testG.supplyCount[duchy], G.supplyCount[duchy], testG.supplyCount[province], \
           G.supplyCount[province]);
#endif
            countPasses += assertTrue(testG.supplyCount[estate] == G.supplyCount[estate], estatecount, 0, gameSetup, 3);

            //expect the testG's game setup to have the same amount of douchy cards as the before cardEffect was run.
            //char douchycount [] = "douchy count";
#if (MUCHTEXTD)
            printf("douchy count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);
#endif
            countPasses += assertTrue(testG.supplyCount[duchy] == G.supplyCount[duchy], douchycount, 0, gameSetup, 3);

            //expect the testG's game setup to have the same amount of province cards as the before cardEffect was run.
            // char provincecount [] = "province count";
#if (MUCHTEXTD)
            printf("province count = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]);
#endif
            countPasses += assertTrue(testG.supplyCount[province] == G.supplyCount[province], provincecount, 0,
                                      gameSetup,
                                      3);

            //expect the testG's current player to have one more action than before cardEffect was run.
            // char numOfActions[] = "number of actions";
#if (MUCHTEXTD)
            printf("original number of actions = %d, after cardEffect = %d, expected = %d\n", G.numActions,
                   testG.numActions, G.numActions);
#endif
            countPasses += assertTrue(testG.numActions == G.numActions, numOfActions, 0, thisPlayer, 3);

            //expect the testG's current player to have the same amount of supply cards than before cardEffect was run.
            //int i = 0, j = 0;
            for (i = 0; i < 25; i++) { if (testG.supplyCount[i] != G.supplyCount[i]) { j = 1; }}
            //char supplyCards[] = "supply cards";
#if (MUCHTEXTD)
            printf("original number of supply cards = %d, after cardEffect = %d, expected = %d\n", 0, j, 0);
#endif
            countPasses += assertTrue(j == 0, supplyCards, 0, thisPlayer, 4);


            NumOfCoppers = 0;
            for (i = 0; i < G.handCount[opponentPlayer]; i++) {
                card = G.hand[opponentPlayer][i];
                if (card == copper || card == silver || card == gold) {
                    NumOfCoppers++;
                }
            }
#if (MUCHTEXTD)
            printf("hand count opponent player original = %d, after cardEffect = %d, expected = %d\n",
                   G.handCount[opponentPlayer], testG.handCount[opponentPlayer], G.handCount[opponentPlayer] - 1);
#endif
            countPasses += assertTrue(testG.handCount[opponentPlayer] == G.handCount[opponentPlayer] - 1, handcount, 1,
                                      opponentPlayer, 3);
            // }
            //expect the testG's opponent player to have the same amount of cards in their deck as the before cardEffect was run.
            // char deckcount[] = "deck count";
#if (MUCHTEXTD)
            printf("deck count opponent player original  = %d, after cardEffect = %d, expected = %d\n",
                   G.deckCount[opponentPlayer], testG.deckCount[opponentPlayer], G.deckCount[opponentPlayer]);
#endif
            countPasses += assertTrue(testG.deckCount[opponentPlayer] == G.deckCount[opponentPlayer], deckcount, 0,
                                      opponentPlayer, 3);

        }
#if (MUCHTEXTD)
        // ----------- TEST 1: +2 cards --------------
        printf("TEST 4: Player gains 2 points and others loose one cooper.\n"
                       "Preconditions: Opponent has one copper in the fourth position.\n");
#endif


        // initialize a game state and player cards
        initializeGame(numPlayers, k, seed, &G);


        player = 0;
        for (player = 0; player < numPlayers; player++) {
            for (numOfCardsCInHand = 1; numOfCardsCInHand <= 5; numOfCardsCInHand++) {
                G.handCount[player] = numOfCardsCInHand;
                memcpy(G.hand[player], goldCoins, sizeof(int) * numOfCardsCInHand);
                if (numOfCardsCInHand == 5) {
                    G.handCount[player] = numOfCardsCInHand;
                    memcpy(G.hand[player], silverCoins, sizeof(int) * numOfCardsCInHand);

                    G.hand[player][3] = copper;
                }
            }






            // copy the game state to a test case
            memcpy(&testG, &G, sizeof(struct gameState));


            cardEffect(cutpurse, choice1, choice2, choice3, &testG, handpos, &bonus);

            //newCards are two since there are two new treasures added to the hand
            newCards = 0;

            // checks how much treasure is gained
            NumOfTreasures = 0;
            for (i = 0; i < testG.handCount[thisPlayer]; i++) {
                card = testG.hand[thisPlayer][i];
                if (card == copper || card == silver || card == gold) {
                    NumOfTreasures++;
                }
            }


            // checks default treasure count
            NumOfOrigTreasures = 0;
            for (i = 0; i < G.handCount[thisPlayer]; i++) {
                card = G.hand[thisPlayer][i];
                if (card == copper || card == silver || card == gold) {
                    NumOfOrigTreasures++;
                }
            }



            //expect the testG's current player to have the same amount of cards in their hand as the before cardEffect was run, plus three.
            // char handcount[] = "hand count";
#if (MUCHTEXTD)
            printf("hand count original = %d, after cardEffect = %d, expected = %d\n", G.handCount[thisPlayer],
                   testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
#endif
            countPasses += assertTrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded,
                                      handcount, 0, thisPlayer, 3);

            //expect the testG's current player to have two more treasure cards in their hand as the before cardEffect was run.
            //  char treasureCountArray[] = "treasure cards";
#if (MUCHTEXTD)
            printf("treasure card count original = %d, after cardEffect = %d, expected = %d\n", NumOfOrigTreasures,
                   NumOfTreasures, NumOfOrigTreasures - 1);
#endif
            countPasses += assertTrue(NumOfOrigTreasures - 1 == NumOfTreasures, treasureCountArray, 0, thisPlayer, 3);

            //expect the testG's game setup to have the same amount of estate cards as the before cardEffect was run.
            //  char estatecount [] = "estate count";
#if (MUCHTEXTD)
            printf("estate = %d, expected = %d, duchy = %d, expected = %d, province = %d, expected = %d\n",
                   testG.supplyCount[estate], \
           G.supplyCount[estate], testG.supplyCount[duchy], G.supplyCount[duchy], testG.supplyCount[province], \
           G.supplyCount[province]);
#endif
            countPasses += assertTrue(testG.supplyCount[estate] == G.supplyCount[estate], estatecount, 0, gameSetup, 3);

            //expect the testG's game setup to have the same amount of douchy cards as the before cardEffect was run.
            //char douchycount [] = "douchy count";
#if (MUCHTEXTD)
            printf("douchy count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);
#endif
            countPasses += assertTrue(testG.supplyCount[duchy] == G.supplyCount[duchy], douchycount, 0, gameSetup, 3);

            //expect the testG's game setup to have the same amount of province cards as the before cardEffect was run.
            // char provincecount [] = "province count";
#if (MUCHTEXTD)
            printf("province count = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]);
#endif
            countPasses += assertTrue(testG.supplyCount[province] == G.supplyCount[province], provincecount, 0,
                                      gameSetup,
                                      3);

            //expect the testG's current player to have one more action than before cardEffect was run.
            // char numOfActions[] = "number of actions";
#if (MUCHTEXTD)
            printf("original number of actions = %d, after cardEffect = %d, expected = %d\n", G.numActions,
                   testG.numActions, G.numActions);
#endif
            countPasses += assertTrue(testG.numActions == G.numActions, numOfActions, 0, thisPlayer, 3);

            //expect the testG's current player to have the same amount of supply cards than before cardEffect was run.
            //int i = 0, j = 0;
            for (i = 0; i < 25; i++) { if (testG.supplyCount[i] != G.supplyCount[i]) { j = 1; }}
            //char supplyCards[] = "supply cards";
#if (MUCHTEXTD)
            printf("original number of supply cards = %d, after cardEffect = %d, expected = %d\n", 0, j, 0);
#endif
            countPasses += assertTrue(j == 0, supplyCards, 0, thisPlayer, 4);


            NumOfCoppers = 0;
            for (i = 0; i < G.handCount[opponentPlayer]; i++) {
                card = G.hand[opponentPlayer][i];
                if (card == copper || card == silver || card == gold) {
                    NumOfCoppers++;
                }
            }
#if (MUCHTEXTD)
            printf("hand count opponent player original = %d, after cardEffect = %d, expected = %d\n",
                   G.handCount[opponentPlayer], testG.handCount[opponentPlayer], G.handCount[opponentPlayer] - 1);
#endif
            countPasses += assertTrue(testG.handCount[opponentPlayer] == G.handCount[opponentPlayer] - 1, handcount, 1,
                                      opponentPlayer, 3);
#if (MUCHTEXTD)
            printf("deck count opponent player original  = %d, after cardEffect = %d, expected = %d\n",
                   G.deckCount[opponentPlayer], testG.deckCount[opponentPlayer], G.deckCount[opponentPlayer]);
#endif
            countPasses += assertTrue(testG.deckCount[opponentPlayer] == G.deckCount[opponentPlayer], deckcount, 0,
                                      opponentPlayer, 3);


        }

#if (MUCHTEXTD)

        printf("TEST 5: Player gains 2 points and others looses one cooper.\n"
                       "Preconditions: Opponent has one copper in last position.\n");
#endif

        player = 0;
        numOfCardsCInHand = 0;


        for (player = 0; player < numPlayers; player++) {
            for (numOfCardsCInHand = 1; numOfCardsCInHand <= 5; numOfCardsCInHand++) {
                G.handCount[player] = numOfCardsCInHand;
                memcpy(G.hand[player], goldCoins, sizeof(int) * numOfCardsCInHand);
                if (numOfCardsCInHand == 5) {
                    G.handCount[player] = numOfCardsCInHand;
                    memcpy(G.hand[player], silverCoins, sizeof(int) * numOfCardsCInHand);

                    G.hand[player][numOfCardsCInHand - 1] = copper;
                }
            }




            // copy the game state to a test case
            memcpy(&testG, &G, sizeof(struct gameState));


            cardEffect(cutpurse, choice1, choice2, choice3, &testG, handpos, &bonus);

            //newCards are two since there are two new treasures added to the hand
            newCards = 0;



            // checks how much treasure is gained
            NumOfTreasures = 0;
            for (i = 0; i < testG.handCount[thisPlayer]; i++) {
                card = testG.hand[thisPlayer][i];
                if (card == copper || card == silver || card == gold) {
                    NumOfTreasures++;
                }
            }

            // checks default treasure count
            NumOfOrigTreasures = 0;
            for (i = 0; i < G.handCount[thisPlayer]; i++) {
                card = G.hand[thisPlayer][i];
                if (card == copper || card == silver || card == gold) {
                    NumOfOrigTreasures++;
                }
            }


            //expect the testG's current player to have the same amount of cards in their hand as the before cardEffect was run, plus three.
            //handcount[] = "hand count";
#if (MUCHTEXTD)
            printf("hand count original = %d, after cardEffect = %d, expected = %d\n", G.handCount[thisPlayer],
                   testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
#endif
            countPasses += assertTrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded,
                                      handcount, 0, thisPlayer, 3);

            //expect the testG's current player to have two more treasure cards in their hand as the before cardEffect was run.
            //treasureCountArray[] = "treasure cards";
#if (MUCHTEXTD)
            printf("treasure card count original = %d, after cardEffect = %d, expected = %d\n", NumOfOrigTreasures,
                   NumOfTreasures, NumOfOrigTreasures - 1);
#endif
            countPasses += assertTrue(NumOfOrigTreasures - 1 == NumOfTreasures, treasureCountArray, 0, thisPlayer, 3);

            //expect the testG's game setup to have the same amount of estate cards as the before cardEffect was run.
            // estatecount [] = "estate count";
#if (MUCHTEXTD)
            printf("estate = %d, expected = %d, duchy = %d, expected = %d, province = %d, expected = %d\n",
                   testG.supplyCount[estate], \
           G.supplyCount[estate], testG.supplyCount[duchy], G.supplyCount[duchy], testG.supplyCount[province], \
           G.supplyCount[province]);
#endif
            countPasses += assertTrue(testG.supplyCount[estate] == G.supplyCount[estate], estatecount, 0, gameSetup, 3);

            //expect the testG's game setup to have the same amount of douchy cards as the before cardEffect was run.
            //douchycount [] = "douchy count";
#if (MUCHTEXTD)
            printf("douchy count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);
#endif
            countPasses += assertTrue(testG.supplyCount[duchy] == G.supplyCount[duchy], douchycount, 0, gameSetup, 3);

            //expect the testG's game setup to have the same amount of province cards as the before cardEffect was run.
            //provincecount [] = "province count";
#if (MUCHTEXTD)
            printf("province count = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]);
#endif
            countPasses += assertTrue(testG.supplyCount[province] == G.supplyCount[province], provincecount, 0,
                                      gameSetup,
                                      3);

            //expect the testG's current player to have one more action than before cardEffect was run.
            //numOfActions[] = "number of actions";
#if (MUCHTEXTD)
            printf("original number of actions = %d, after cardEffect = %d, expected = %d\n", G.numActions,
                   testG.numActions, G.numActions);
#endif
            countPasses += assertTrue(testG.numActions == G.numActions, numOfActions, 0, thisPlayer, 3);

            //expect the testG's current player to have the same amount of supply cards than before cardEffect was run.
            // int i = 0, j = 0;
            for (i = 0; i < 25; i++) { if (testG.supplyCount[i] != G.supplyCount[i]) { j = 1; }}
            // char supplyCards[] = "supply cards";
#if (MUCHTEXTD)
            printf("original number of supply cards = %d, after cardEffect = %d, expected = %d\n", 0, j, 0);
#endif
            countPasses += assertTrue(j == 0, supplyCards, 0, thisPlayer, 4);


            NumOfCoppers = 0;
            for (i = 0; i < G.handCount[opponentPlayer]; i++) {
                card = G.hand[opponentPlayer][i];
                if (card == copper || card == silver || card == gold) {
                    NumOfCoppers++;
                }
            }
            // if (!NumOfCoppers) {

            int loseOneCopper = 1;
            //expect the testG's opponent player to have the same amount of cards in their hand as the before cardEffect was run.
#if (MUCHTEXTD)
            printf("Hand count opponent player = %d, expected = %d\n", testG.handCount[opponentPlayer],
                   G.handCount[opponentPlayer] - loseOneCopper);
#endif
            countPasses += assertTrue(testG.handCount[opponentPlayer] == G.handCount[opponentPlayer] - loseOneCopper,
                                      handcount, 1, opponentPlayer, 3);

#if (MUCHTEXTD)
            printf("deck count opponent player = %d, expected = %d\n", testG.deckCount[opponentPlayer],
                   G.deckCount[opponentPlayer]);
#endif
            countPasses += assertTrue(testG.deckCount[opponentPlayer] == G.deckCount[opponentPlayer], deckcount, 0,
                                      opponentPlayer, 3);

        }


#if (MUCHTEXTD)
        // ----------- TEST 2: +2 cards --------------
        printf("TEST 6: Player gains 2 points and others loose one cooper. "
                       "\nPreconditions: Opponent has 2 coopers.\n");
#endif

        player = 0;
        numOfCardsCInHand = 0;


        for (player = 0; player < numPlayers; player++) {
            for (numOfCardsCInHand = 1; numOfCardsCInHand <= 5; numOfCardsCInHand++) {
                G.handCount[player] = numOfCardsCInHand;
                memcpy(G.hand[player], goldCoins, sizeof(int) * numOfCardsCInHand);
                if (numOfCardsCInHand == 5) {
                    G.handCount[player] = numOfCardsCInHand;
                    memcpy(G.hand[player], silverCoins, sizeof(int) * numOfCardsCInHand);

                    G.hand[player][1] = copper;
                    G.hand[player][2] = copper;
                }
            }





            // copy the game state to a test case
            memcpy(&testG, &G, sizeof(struct gameState));


            cardEffect(cutpurse, choice1, choice2, choice3, &testG, handpos, &bonus);

            //newCards are two since there are two new treasures added to the hand
            newCards = 0;


            // checks how much treasure is gained
            NumOfTreasures = 0;
            for (i = 0; i < testG.handCount[thisPlayer]; i++) {
                card = testG.hand[thisPlayer][i];
                if (card == copper || card == silver || card == gold) {
                    NumOfTreasures++;
                }
            }

            // checks default treasure count
            NumOfOrigTreasures = 0;
            for (i = 0; i < G.handCount[thisPlayer]; i++) {
                card = G.hand[thisPlayer][i];
                if (card == copper || card == silver || card == gold) {
                    NumOfOrigTreasures++;
                }
            }



            //expect the testG's current player to have the same amount of cards in their hand as the before cardEffect was run, plus three.
            // char handcount[] = "hand count";
#if (MUCHTEXTD)
            printf("hand count original = %d, after cardEffect = %d, expected = %d\n", G.handCount[thisPlayer],
                   testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
#endif
            countPasses += assertTrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded,
                                      handcount, 0, thisPlayer, 3);

            //expect the testG's current player to have two more treasure cards in their hand as the before cardEffect was run.
            //char treasureCountArray[] = "treasure cards";
#if (MUCHTEXTD)
            printf("treasure card count original = %d, after cardEffect = %d, expected = %d\n", NumOfOrigTreasures,
                   NumOfTreasures, NumOfOrigTreasures - 1);
#endif
            countPasses += assertTrue(NumOfOrigTreasures - 1 == NumOfTreasures, treasureCountArray, 0, thisPlayer, 3);

            //expect the testG's game setup to have the same amount of estate cards as the before cardEffect was run.
            //  char estatecount [] = "estate count";
#if (MUCHTEXTD)
            printf("estate = %d, expected = %d, duchy = %d, expected = %d, province = %d, expected = %d\n",
                   testG.supplyCount[estate], \
           G.supplyCount[estate], testG.supplyCount[duchy], G.supplyCount[duchy], testG.supplyCount[province], \
           G.supplyCount[province]);
#endif
            countPasses += assertTrue(testG.supplyCount[estate] == G.supplyCount[estate], estatecount, 0, gameSetup, 3);

            //expect the testG's game setup to have the same amount of douchy cards as the before cardEffect was run.
            // char douchycount [] = "douchy count";
#if (MUCHTEXTD)
            printf("douchy count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);
#endif
            countPasses += assertTrue(testG.supplyCount[duchy] == G.supplyCount[duchy], douchycount, 0, gameSetup, 3);

            //expect the testG's game setup to have the same amount of province cards as the before cardEffect was run.
            // char provincecount [] = "province count";
#if (MUCHTEXTD)
            printf("province count = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]);
#endif
            countPasses += assertTrue(testG.supplyCount[province] == G.supplyCount[province], provincecount, 0,
                                      gameSetup,
                                      3);

            //expect the testG's current player to have one more action than before cardEffect was run.
            // char numOfActions[] = "number of actions";
#if (MUCHTEXTD)
            printf("original number of actions = %d, after cardEffect = %d, expected = %d\n", G.numActions,
                   testG.numActions, G.numActions);
#endif
            countPasses += assertTrue(testG.numActions == G.numActions, numOfActions, 0, thisPlayer, 3);

            //expect the testG's current player to have the same amount of supply cards than before cardEffect was run.
            //int i = 0, j = 0;
            for (i = 0; i < 25; i++) { if (testG.supplyCount[i] != G.supplyCount[i]) { j = 1; }}
            //char supplyCards[] = "supply cards";
#if (MUCHTEXTD)
            printf("original number of supply cards = %d, after cardEffect = %d, expected = %d\n", 0, j, 0);
#endif
            countPasses += assertTrue(j == 0, supplyCards, 0, thisPlayer, 4);



            //int NumOfCoppers = 0;
            for (i = 0; i < G.handCount[opponentPlayer]; i++) {
                card = G.hand[opponentPlayer][i];
                if (card == copper || card == silver || card == gold) {
                    NumOfCoppers++;
                }
            }

            //expect the testG's opponent player to have the same amount of cards in their hand as the before cardEffect was run.
#if (MUCHTEXTD)
            printf("Hand count opponent player = %d, expected = %d\n", testG.handCount[opponentPlayer],
                   G.handCount[opponentPlayer] - 1);
#endif
            countPasses += assertTrue(testG.handCount[opponentPlayer] == G.handCount[opponentPlayer] - 1, handcount, 1,
                                      opponentPlayer, 3);
            // }
            //expect the testG's opponent player to have the same amount of cards in their deck as the before cardEffect was run.
            //char deckcount[] = "deck count";
#if (MUCHTEXTD)
            printf("deck count opponent player = %d, expected = %d\n", testG.deckCount[opponentPlayer],
                   G.deckCount[opponentPlayer]);
#endif
            countPasses += assertTrue(testG.deckCount[opponentPlayer] == G.deckCount[opponentPlayer], deckcount, 0,
                                      opponentPlayer, 3);

        }


#if (MUCHTEXTD)
        printf("TEST 7: Player gains 2 points and others looses one cooper.\n"
                       "Preconditions: Opponent has all coppers.\n");
#endif


        for (player = 0; player < numPlayers; player++) {
            for (numOfCardsCInHand = 1; numOfCardsCInHand <= 5; numOfCardsCInHand++) {
                G.handCount[player] = numOfCardsCInHand;
                memcpy(G.hand[player], copperCoins, sizeof(int) * numOfCardsCInHand);
            }
        }



        // copy the game state to a test case
        memcpy(&testG, &G, sizeof(struct gameState));


        cardEffect(cutpurse, choice1, choice2, choice3, &testG, handpos, &bonus);

        //newCards are two since there are two new treasures added to the hand
        newCards = 0;


        // checks how much treasure is gained
        NumOfTreasures = 0;
        for (i = 0; i < testG.handCount[thisPlayer]; i++) {
            card = testG.hand[thisPlayer][i];
            if (card == copper || card == silver || card == gold) {
                NumOfTreasures++;
            }
        }

        // checks default treasure count
        NumOfOrigTreasures = 0;
        for (i = 0; i < G.handCount[thisPlayer]; i++) {
            card = G.hand[thisPlayer][i];
            if (card == copper || card == silver || card == gold) {
                NumOfOrigTreasures++;
            }
        }


        //expect the testG's current player to have the same amount of cards in their hand as the before cardEffect was run, plus three.
        //handcount[] = "hand count";
#if (MUCHTEXTD)
        printf("hand count original = %d, after cardEffect = %d, expected = %d\n", G.handCount[thisPlayer],
               testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
#endif
        countPasses += assertTrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded,
                                  handcount, 0, thisPlayer, 3);

        //expect the testG's current player to have two more treasure cards in their hand as the before cardEffect was run.
        //treasureCountArray[] = "treasure cards";
#if (MUCHTEXTD)
        printf("treasure card count original = %d, after cardEffect = %d, expected = %d\n", NumOfOrigTreasures,
               NumOfTreasures, NumOfOrigTreasures - 1);
#endif
        countPasses += assertTrue(NumOfOrigTreasures - 1 == NumOfTreasures, treasureCountArray, 0, thisPlayer, 3);

        //expect the testG's game setup to have the same amount of estate cards as the before cardEffect was run.
        // estatecount [] = "estate count";
#if (MUCHTEXTD)
        printf("estate = %d, expected = %d, duchy = %d, expected = %d, province = %d, expected = %d\n",
               testG.supplyCount[estate], \
           G.supplyCount[estate], testG.supplyCount[duchy], G.supplyCount[duchy], testG.supplyCount[province], \
           G.supplyCount[province]);
#endif
        countPasses += assertTrue(testG.supplyCount[estate] == G.supplyCount[estate], estatecount, 0, gameSetup, 3);

        //expect the testG's game setup to have the same amount of douchy cards as the before cardEffect was run.
        //douchycount [] = "douchy count";
#if (MUCHTEXTD)
        printf("douchy count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);
#endif
        countPasses += assertTrue(testG.supplyCount[duchy] == G.supplyCount[duchy], douchycount, 0, gameSetup, 3);

        //expect the testG's game setup to have the same amount of province cards as the before cardEffect was run.
        //provincecount [] = "province count";
#if (MUCHTEXTD)
        printf("province count = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]);
#endif
        countPasses += assertTrue(testG.supplyCount[province] == G.supplyCount[province], provincecount, 0, gameSetup,
                                  3);

        //expect the testG's current player to have one more action than before cardEffect was run.
        //numOfActions[] = "number of actions";
#if (MUCHTEXTD)
        printf("original number of actions = %d, after cardEffect = %d, expected = %d\n", G.numActions,
               testG.numActions, G.numActions);
#endif
        countPasses += assertTrue(testG.numActions == G.numActions, numOfActions, 0, thisPlayer, 3);

        //expect the testG's current player to have the same amount of supply cards than before cardEffect was run.
        // int i = 0, j = 0;
        for (i = 0; i < 25; i++) { if (testG.supplyCount[i] != G.supplyCount[i]) { j = 1; }}
        // char supplyCards[] = "supply cards";
#if (MUCHTEXTD)
        printf("original number of supply cards = %d, after cardEffect = %d, expected = %d\n", 0, j, 0);
#endif
        countPasses += assertTrue(j == 0, supplyCards, 0, thisPlayer, 4);


        NumOfCoppers = 0;
        for (i = 0; i < G.handCount[opponentPlayer]; i++) {
            card = G.hand[opponentPlayer][i];
            if (card == copper || card == silver || card == gold) {
                NumOfCoppers++;
            }
        }
        int OneCopperLost = 1;
        // if (!NumOfCoppers) {
        //expect the testG's opponent player to have the same amount of cards in their hand as the before cardEffect was run.
#if (MUCHTEXTD)
        printf("Hand count opponent player = %d, expected = %d\n", testG.handCount[opponentPlayer],
               G.handCount[opponentPlayer] - OneCopperLost);
#endif
        countPasses += assertTrue(testG.handCount[opponentPlayer] == G.handCount[opponentPlayer] - OneCopperLost,
                                  handcount, 0, opponentPlayer, 3);

#if (MUCHTEXTD)
        printf("deck count opponent player = %d, expected = %d\n", testG.deckCount[opponentPlayer],
               G.deckCount[opponentPlayer]);
#endif
        countPasses += assertTrue(testG.deckCount[opponentPlayer] == G.deckCount[opponentPlayer], deckcount, 0,
                                  opponentPlayer, 3);


#if (MUCHTEXTD)

        printf("TEST 8: Player gains 2 points and others looses no cooper.\n"
                       "Preconditions: Opponent has zero coppers.\n");
#endif


        player = 0;
        numOfCardsCInHand = 0;

        for (player = 0; player < numPlayers; player++) {
            for (numOfCardsCInHand = 1; numOfCardsCInHand <= 5; numOfCardsCInHand++) {
                G.handCount[player] = numOfCardsCInHand;
                memcpy(G.hand[player], goldCoins, sizeof(int) * numOfCardsCInHand);
            }
        }



        // copy the game state to a test case
        memcpy(&testG, &G, sizeof(struct gameState));



        //turn on DEBUG 1 in dominion.h for this to work. In the current version of dominion this
        //shows an error in the dominion.h's cutpurse function.
        //This came from: https://ubuntuforums.org/showthread.php?t=31512
        FILE *uname;
        char os[80];
        memset(os, '\0', sizeof(os));
        int lastchar;
        cardEffect(cutpurse, choice1, choice2, choice3, &testG, handpos, &bonus);
        uname = popen("uname -r", "r");
        lastchar = fread(os, 1, 80, uname);
        os[lastchar - 1] = '\0';
        //printf("Your OS is %s", os);
        pclose(uname);

        char consoleEO[] = "console error output";
        int incorrectOutput = 25;
#if (MUCHTEXTD)
        printf("console error output = %s, expected = \"Player # reveals card number...\"\n", os);
#endif
        countPasses += assertTrue(lastchar > incorrectOutput, consoleEO, 1, gameSetup, 3);
        newCards = 0;


        // checks how much treasure is gained
        NumOfTreasures = 0;
        for (i = 0; i < testG.handCount[thisPlayer]; i++) {
            card = testG.hand[thisPlayer][i];
            if (card == copper || card == silver || card == gold) {
                NumOfTreasures++;
            }
        }

        // checks default treasure count
        NumOfOrigTreasures = 0;
        for (i = 0; i < G.handCount[thisPlayer]; i++) {
            card = G.hand[thisPlayer][i];
            if (card == copper || card == silver || card == gold) {
                NumOfOrigTreasures++;
            }
        }


        //expect the testG's current player to have the same amount of cards in their hand as the before cardEffect was run, plus three.
        //handcount[] = "hand count";
#if (MUCHTEXTD)
        printf("hand count original = %d, after cardEffect = %d, expected = %d\n", G.handCount[thisPlayer],
               testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
#endif
        countPasses += assertTrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded,
                                  handcount, 0, thisPlayer, 3);

        //expect the testG's current player to have two more treasure cards in their hand as the before cardEffect was run.
        //treasureCountArray[] = "treasure cards";
#if (MUCHTEXTD)
        printf("treasure card count original = %d, after cardEffect = %d, expected = %d\n", NumOfOrigTreasures,
               NumOfTreasures, NumOfOrigTreasures - 1);
#endif
        countPasses += assertTrue(NumOfOrigTreasures - 1 == NumOfTreasures, treasureCountArray, 0, thisPlayer, 3);

        //expect the testG's game setup to have the same amount of estate cards as the before cardEffect was run.
        // estatecount [] = "estate count";
#if (MUCHTEXTD)
        printf("estate = %d, expected = %d, duchy = %d, expected = %d, province = %d, expected = %d\n",
               testG.supplyCount[estate], \
           G.supplyCount[estate], testG.supplyCount[duchy], G.supplyCount[duchy], testG.supplyCount[province], \
           G.supplyCount[province]);
#endif
        countPasses += assertTrue(testG.supplyCount[estate] == G.supplyCount[estate], estatecount, 0, gameSetup, 3);

        //expect the testG's game setup to have the same amount of douchy cards as the before cardEffect was run.
        //douchycount [] = "douchy count";
#if (MUCHTEXTD)
        printf("douchy count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);
#endif
        countPasses += assertTrue(testG.supplyCount[duchy] == G.supplyCount[duchy], douchycount, 0, gameSetup, 3);

        //expect the testG's game setup to have the same amount of province cards as the before cardEffect was run.
        //provincecount [] = "province count";
#if (MUCHTEXTD)
        printf("province count = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]);

#endif
        countPasses += assertTrue(testG.supplyCount[province] == G.supplyCount[province], provincecount, 0, gameSetup,
                                  3);

        //expect the testG's current player to have one more action than before cardEffect was run.
        //numOfActions[] = "number of actions";
#if (MUCHTEXTD)
        printf("original number of actions = %d, after cardEffect = %d, expected = %d\n", G.numActions,
               testG.numActions, G.numActions);
#endif
        countPasses += assertTrue(testG.numActions == G.numActions, numOfActions, 0, thisPlayer, 3);

        //expect the testG's current player to have the same amount of supply cards than before cardEffect was run.
        // int i = 0, j = 0;
        for (i = 0; i < 25; i++) { if (testG.supplyCount[i] != G.supplyCount[i]) { j = 1; }}
        // char supplyCards[] = "supply cards";
#if (MUCHTEXTD)
        printf("original number of supply cards = %d, after cardEffect = %d, expected = %d\n", 0, j, 0);
#endif
        countPasses += assertTrue(j == 0, supplyCards, 0, thisPlayer, 4);


        NumOfCoppers = 0;
        for (i = 0; i < G.handCount[opponentPlayer]; i++) {
            card = G.hand[opponentPlayer][i];
            if (card == copper || card == silver || card == gold) {
                NumOfCoppers++;
            }
        }
        // if (!NumOfCoppers) {
        //expect the testG's opponent player to have the same amount of cards in their hand as the before cardEffect was run.
#if (MUCHTEXTD)
        printf("Hand count opponent player = %d, expected = %d\n", testG.handCount[opponentPlayer],
               G.handCount[opponentPlayer]);
#endif
        countPasses += assertTrue(testG.handCount[opponentPlayer] == G.handCount[opponentPlayer], handcount, 0,
                                  opponentPlayer, 3);

#if (MUCHTEXTD)
        printf("deck count opponent player = %d, expected = %d\n", testG.deckCount[opponentPlayer],
               G.deckCount[opponentPlayer]);
#endif
        countPasses += assertTrue(testG.deckCount[opponentPlayer] == G.deckCount[opponentPlayer], deckcount, 0,
                                  opponentPlayer, 3);


        //  printf("\n\n%d\n\n", countPasses);
    }
    if (countPasses == 73){printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);}
    else {printf("\n >>>>> FOUND BUGS: Testing complete. %s <<<<<\n\n", TESTCARD);}

    return 0;
}

