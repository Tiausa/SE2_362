
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include "assertTester.c"

#define UNITTEST "discard card"
#define MUCHTEXTH 2

/****************************************************************************
 * Name: unittest4.c
 * Function Tested: discardCard
 * Author: Tia Seibold
 * Description: Checks that card is discarded according to flag and hand.
*****************************************************************************/

int main(int argc, char const *argv[]) {
    int seed = 1000;
    int NumberOfPlayers = 2;
    int cardCount = 0;
    int trashFlag = 0;
    int numOfCardsInHand;
    int readyToBeDiscarded = 0;
    int maxHandCount = 5;
    int countPasses = 0;
    int i = 0;
    int l = 0;
    int discardedCards = 0;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};
    struct gameState testG, G;



    printf("----------------- Testing unittest4: %s ----------------\n", UNITTEST);

    for (i = 0; i < NumberOfPlayers; i++) {

        printf("TEST %d: player %d\n", i+1, i);

        for(numOfCardsInHand = 1; numOfCardsInHand <= maxHandCount; numOfCardsInHand++) {

            for(readyToBeDiscarded = 0; readyToBeDiscarded < 3; readyToBeDiscarded++) {

                for(trashFlag = 0; trashFlag <= 2; trashFlag++) {

                    for(discardedCards = 0; discardedCards < 3; discardedCards++) {

                        memset(&testG, 0, sizeof(struct gameState));

                        initializeGame(NumberOfPlayers, k, seed, &testG);

                        testG.playedCardCount = readyToBeDiscarded;
                        testG.handCount[i] = numOfCardsInHand;

                        //prepare cards to be discarded
                        for (l = 0; l < readyToBeDiscarded; l++) { testG.playedCards[l] = k[l]; }

                        //prepare cards in hand
                        for (l = 0; l < numOfCardsInHand; l++) { testG.hand[i][l] = k[l]; }

                        //make both of the games the same
                        memcpy (&G, &testG, sizeof(struct gameState));

                        int cardN = 0;

                        if (numOfCardsInHand != 1) {
                            //discard card
                            discardCard(numOfCardsInHand / 2, i, &testG, trashFlag);
                            cardN = testG.hand[i][numOfCardsInHand/2];
                        } else {
                            discardCard(numOfCardsInHand, i, &testG, trashFlag);
                            cardN = testG.hand[i][numOfCardsInHand];
                        }

                        //check flag
                        if (trashFlag < 1) { cardCount = readyToBeDiscarded + 1; }
                        else { cardCount = readyToBeDiscarded; }

                        //expect the G's current player to have one less card in hand as before discardCard was run.
                        char handCount[] = "hand count";

                        printf("card in hand = %d, expected = %d\n", testG.handCount[i], numOfCardsInHand - 1);

                        countPasses += assertTrue(testG.handCount[i] == numOfCardsInHand - 1, handCount, 1, 1, 8);

                        //expect the G's current player to have the same number of cards discarded as before discardCard was run.
                        char discardCount[] = "discard count";

                        printf("discard card count original = %d, after discardCard = %d, expected = %d\n", G.discardCount[i], testG.discardCount[i], cardCount);

                        countPasses += assertTrue(G.discardCount[i] != testG.discardCount[i], discardCount, 1, 0, 8);

                        //expect the G's current player to have more cards discarded as before discardCard was run.
                        char discardPile[] = "discard pile";
                        int counterG = 0;
                        int counterTestG = 0;
                        int counterHandG = 0;
                        for (i = 0; i < G.handCount[i]; i++) {if (G.hand[i][i] == cardN) {counterHandG++;}}
                        for (i = 0; i < G.discardCount[i]; i++) {if (G.discard[i][i] == cardN) {counterG++;}}
                        for (i = 0; i < testG.discardCount[i]; i++) {if (testG.discard[i][i] == cardN) {counterTestG++;}}

                        int expectedD = counterG + counterHandG;
                        printf("number of card %d discarded card original = %d, after discardCard = %d, expected = %d \n",  cardN, counterG, counterTestG, expectedD);

                        countPasses += assertTrue( (counterG + counterHandG) == counterTestG, discardPile, 1, 0, 8);


                        //expect the G's current player to have one more card played as before discardCard was run.
                        char playedCount[] = "played card count";

                        printf("cards played original = %d, after discardCard = %d, expected = %d\n", G.playedCardCount, testG.playedCardCount,G.playedCardCount);

                        countPasses += assertTrue(testG.playedCardCount ==  G.playedCardCount, playedCount, 1, 1, 8);

                        //expect the G's current player to have the same number of cards playeded as before playedCard was run.
                        char playedPile[] = "played pile";
                        int counterGP = 0;
                        int counterTestGP = 0;
                        int counterHandGP = 0;
                        for (i = 0; i < G.handCount[i]; i++) {if (G.hand[i][i] == cardN) {counterHandGP++;}}
                        for (i = 0; i < G.playedCardCount; i++) {if (G.playedCards[i] == cardN) {counterGP++;}}
                        for (i = 0; i < testG.playedCardCount; i++) {if (testG.playedCards[i] == cardN) {counterTestGP++;}}

                        printf("number of card %d played card original = %d, after playedCard = %d, expected = %d \n",  cardN, counterGP, counterTestGP, counterGP);

                        countPasses += assertTrue( counterGP == counterTestG, playedPile, 1, 1, 8);

                        //expect the G's game setup to have the same amount of douchy cards as the before cardEffect was run.
                        char douchycount[] = "douchy count";

                        printf("douchy count = %d, expected = %d\n", G.supplyCount[duchy], testG.supplyCount[duchy]);

                        countPasses += assertTrue(G.supplyCount[duchy] == testG.supplyCount[duchy], douchycount, 0, 0,
                                                  8);

                        //expect the G's game setup to have the same amount of province cards as the before cardEffect was run.
                        char provincecount[] = "province count";

                        printf("province count = %d, expected = %d\n", G.supplyCount[province],
                               testG.supplyCount[province]);

                        countPasses += assertTrue(G.supplyCount[province] == testG.supplyCount[province], provincecount,
                                                  0, 0, 8);

                        //expect the G's game setup to have the same amount of estate cards as the before cardEffect was run.
                        char estatecount[] = "estate count";

                        printf("estate count = %d, expected = %d\n", G.supplyCount[duchy], testG.supplyCount[duchy]);

                        countPasses += assertTrue(G.supplyCount[duchy] == testG.supplyCount[duchy], estatecount, 0, 0,
                                                  8);

                        //expect the G's current player to have the same number action than before cardEffect was run.
                        char numOfActions[] = "number of actions";

                        printf("original number of actions = %d, after cardEffect = %d, expected = %d\n",
                               testG.numActions,
                               G.numActions, testG.numActions);

                        countPasses += assertTrue(G.numActions == testG.numActions, numOfActions, 0, 0, 8);
                    }

                }
            }
        }

    }
   // printf("\n\n%d\n\n", countPasses);
    if (countPasses == 1890){printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", UNITTEST);}
    else {printf("\n >>>>> FOUND BUGS: Testing complete.  %s <<<<<\n\n", UNITTEST);}


    return 0;
}