
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "assertTester.c"


#define UNITTEST "Full Deck Count"
#define MUCHTEXTE 1

/****************************************************************************
 * Name: unittest1.c
 * Function Tested: fullDeckCount
 * Author: Tia Seibold
 * Description: Verified that the function returned the correct combined deck card
 * count, hand card count and discard card count of one card from these pile.
*****************************************************************************/

int main(void) {

    int player = 0;
    int cardNumber = 0;
    int removeCard = 0;
    int handNum = 0;
    int cardNum = 0;
    int countPasses = 0;
    int numPlayers = 2;
    struct gameState G;
    int i = 0;
    int j = 0;
    int seed = 1000;
    int counter = 0;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    struct gameState testG;

    printf("----------------- Testing unittest1: %s ----------------\n", UNITTEST);


    for (player = 0; player < 2; player++) {

        printf("TEST %d: player %d's deck and hand\n", player+1, player);

        //fill the hand
        for (cardNumber = 0; cardNumber < 5; cardNumber++) {

            //remove a card
            for (removeCard = 0; removeCard < 5; removeCard++) {

                //for each card in hand
                for (handNum = 0; handNum < 5; handNum++) {

                    //go through each type of card
                    for (cardNum = 1; cardNum < 10; cardNum++) {

                        j = 0;
                        i = 0;
                        counter = 0;

                        //empty the struct - make valgrind happy
                        memset(&testG, 0, sizeof(struct gameState));

                        // initialize a game state and player cards
                        initializeGame(numPlayers, k, seed, &testG);

                        //set the current player to have a turn
                        testG.whoseTurn = player;


                        //set the player's hand count to a number between 0 and 5.
                        testG.handCount[player] = handNum;

                        if(handNum >= 1 )
                        {testG.hand[player][cardNum] = cardNum;}


                        //set the player's discard count
                        testG.discardCount[player] = removeCard;

                        if(removeCard >= 1 )
                        {testG.discard[player][cardNum] = cardNumber;}

                        //put the card into player's deck
                        testG.deckCount[player] = cardNumber;

                        if(cardNum >= 1 )
                        {testG.deck[player][cardNum] = cardNum;}

                        //make both of the games the same
                        memcpy (&G, &testG, sizeof(struct gameState));

                        //get the number of cards in the test deck using testG
                        j = fullDeckCount(player, cardNum, &testG);


                        char deckCount[] = "deck count";
                        
                        printf("deck count original = %d, from fullDeckCount = %d, expected = %d\n", G.deckCount[player],
                               testG.deckCount[player], G.deckCount[player]);

                        countPasses += assertTrue(G.deckCount[player] == testG.deckCount[player], deckCount, 0, 0, 5);

                        char handCount[] = "hand count";
                        
                        printf("hand count original = %d, from fullDeckCount = %d, expected = %d\n", G.handCount[player],
                               testG.handCount[player], G.handCount[player]);

                        countPasses += assertTrue(G.handCount[player] == testG.handCount[player], handCount, 0, 0, 5);

                        char discardCount[] = "discard count";
                        
                        printf("discard count original = %d, from fullDeckCount = %d, expected = %d\n", G.discardCount[player],
                               testG.discardCount[player], G.discardCount[player]);

                        countPasses += assertTrue(G.discardCount[player] == testG.discardCount[player], discardCount, 0, 0, 5);

                        //count cards in G
                        for (i = 0;i < G.handCount[player]; i++) {if (G.hand[player][i] == cardNum) {counter++;}}

                        for (i = 0; i < G.deckCount[player]; i++) {if (G.deck[player][i] == cardNum) {counter++;}}

                        for (i = 0; i < G.discardCount[player]; i++) {if (G.discard[player][i] == cardNum) {counter++;}}

                        char sameNumberOfCards[] = "same number of cards";
                        
                        printf ("full deck count original = %d, from fullDeckCount = %d, expected = %d\n", j, counter, j);

                        countPasses += assertTrue(counter == j, sameNumberOfCards, 0, 0, 5);
                        
                        //expect the testG's game setup to have the same amount of douchy cards as the before cardEffect was run.
                        char douchycount[] = "douchy count";
                        
                        printf("douchy count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);

                        countPasses += assertTrue(testG.supplyCount[duchy] == G.supplyCount[duchy], douchycount, 0, 0, 5);

                        //expect the testG's game setup to have the same amount of province cards as the before cardEffect was run.
                        char provincecount[] = "province count";
                        
                        printf("province count = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]);

                        countPasses += assertTrue(testG.supplyCount[province] == G.supplyCount[province], provincecount, 0, 0,
                                                  5);

                        //expect the testG's game setup to have the same amount of estate cards as the before cardEffect was run.
                        char estatecount[] = "estate count";
                        
                        printf("estate count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);

                        countPasses += assertTrue(testG.supplyCount[duchy] == G.supplyCount[duchy], estatecount, 0, 0, 5);

                        //expect the testG's current player to have one more action than before cardEffect was run.
                        char numOfActions[] = "number of actions";
                        
                        printf("original number of actions = %d, after cardEffect = %d, expected = %d\n", G.numActions,
                               testG.numActions, G.numActions);

                        countPasses += assertTrue(testG.numActions == G.numActions, numOfActions, 0, player, 5);
                        
                        
                        char fullDeckCount[] = "full deck count struct";
                        countPasses += assertTrue(memcmp(&G, &testG, sizeof(struct gameState)) == 0, fullDeckCount, 0, 0, 5);

                        break;
                    }
                }
            }
        }
    }


     // printf("\n\n%d\n\n", countPasses);
    if (countPasses == 2250){printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", UNITTEST);}
    else {printf("\n >>>>> FOUND BUGS: Testing complete.  %s <<<<<\n\n", UNITTEST);}


    return 0;
}
