
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "assertTester.c"


#define UNITTEST "update coins"
#define MUCHTEXTF 1

/****************************************************************************
 * Name: unittest2.c
 * Function Tested: updateCoins
 * Author: Tia Seibold
 * Description: Exchanges the player's treasure cards for coins. If there are
 * bonuses, it adds these as well.
*****************************************************************************/


int main () {

    int i = 0;
    int j = 0;
    int player = 0;
    int seed = 2000;
    int numPlayer = 4;
    int bonusPoints = 0;
    int countPasses = 0;
    int maxBonus = 10;
    int numOfCardsCInHand = 0;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    struct gameState G, testG;


    int copperCoins[500];
    int silverCoins[500];
    int goldCoins[500];
    for (i = 0; i < 500; i++)
    {   copperCoins[i] = copper;
        silverCoins[i] = silver;
        goldCoins[i] = gold; }


    printf("----------------- Testing unittest2: %s ----------------\n", UNITTEST);


    for (player = 0; player < numPlayer; player++)
    {
        #if (MUCHTEXTF)
        printf("TEST %d: player %d's deck and hand\n", player+1, player);
#endif
        for (numOfCardsCInHand = 1; numOfCardsCInHand <= 5; numOfCardsCInHand++)
        {
            for (bonusPoints = 0; bonusPoints <= maxBonus; bonusPoints++)
            {
                #if (MUCHTEXTF)
                printf("TEST %d: player %d's bonus points and %d treasure cards.\n", player+1, bonusPoints, numOfCardsCInHand);
#endif
                //prepare the game
                memset(&G, 0, sizeof(struct gameState));

                initializeGame(numPlayer, k, seed, &G);

                // copy the game state to a test case
                memcpy(&testG, &G, sizeof(struct gameState));

                //put the num of cards in current hand
                G.handCount[player] = numOfCardsCInHand;

                //set cards to copper
                memcpy(G.hand[player], copperCoins, sizeof(int) * numOfCardsCInHand);

               //run update coins
                j = updateCoins(player, &G, bonusPoints);

                //verify no coins were updated
                char NoCoinsUpdated[] = "no coins were updated";
                countPasses += assertTrue(j == 0, NoCoinsUpdated, 0, 0, 6);

                char NumberOfCCoins[] = "number of copper coins";
#if (MUCHTEXTF)
                printf ("Coins = %d, expected = %d\n", G.coins, numOfCardsCInHand * 1 + bonusPoints);
#endif
                countPasses += assertTrue(G.coins == numOfCardsCInHand * 1 + bonusPoints, NumberOfCCoins, 0, 2, 6);


                //set cards to silver
                memcpy(G.hand[player], silverCoins, sizeof(int) * numOfCardsCInHand);

                //run update coins
                j = updateCoins(player, &G, bonusPoints);

                //verify no coins were updated
                //char NoCoinsUpdated[] = "no coins were updated";
                countPasses += assertTrue(j == 0, NoCoinsUpdated, 0, 0, 6);

                char NumberOfSCoins[] = "number of silver coins";
                #if (MUCHTEXTF)
                printf ("Coins = %d, expected = %d\n", G.coins, numOfCardsCInHand * 2 + bonusPoints);
#endif
                countPasses += assertTrue(G.coins == numOfCardsCInHand * 2 + bonusPoints, NumberOfSCoins, 0, 2, 6);

                //set cards to gold
                memcpy(G.hand[player], goldCoins, sizeof(int) * numOfCardsCInHand);

                //run update coins
                j = updateCoins(player, &G, bonusPoints);

                //verify no coins were updated
                countPasses += assertTrue(j == 0, NoCoinsUpdated, 0, 0, 6);

                char NumberOfGCoins[] = "number of gold coins";
                #if (MUCHTEXTF)
                printf ("Coins = %d, expected = %d\n", G.coins, numOfCardsCInHand * 3 + bonusPoints);
#endif
                countPasses += assertTrue(G.coins == numOfCardsCInHand * 3 + bonusPoints, NumberOfGCoins, 0, 2, 6);



                //expect the testG's game setup to have the same amount of douchy cards as the before function was run.
                char douchycount[] = "douchy count";
                #if (MUCHTEXTF)
                printf("douchy count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);
#endif
                countPasses += assertTrue(testG.supplyCount[duchy] == G.supplyCount[duchy], douchycount, 0, 0, 6);

                //expect the testG's game setup to have the same amount of province cards as the before function was run.
                char provincecount[] = "province count";
                #if (MUCHTEXTF)
                printf("province count = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]);
#endif
                countPasses += assertTrue(testG.supplyCount[province] == G.supplyCount[province], provincecount, 0, 0,
                                          6);

                //expect the testG's game setup to have the same amount of estate cards as the before function was run.
                char estatecount[] = "estate count";
                #if (MUCHTEXTF)
                printf("estate count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);
#endif
                countPasses += assertTrue(testG.supplyCount[duchy] == G.supplyCount[duchy], estatecount, 0, 0, 6);

                //expect the testG's current player to have one more action than before function was run.
                char numOfActions[] = "number of actions";
                #if (MUCHTEXTF)
                printf("original number of actions = %d, after cardEffect = %d, expected = %d\n", G.numActions,
                       testG.numActions, G.numActions);
#endif
                countPasses += assertTrue(testG.numActions == G.numActions, numOfActions, 0, player, 6);

            }
        }
    }


    //printf("\n\n%d\n\n", countPasses);
    if (countPasses == 2200){printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", UNITTEST);}
    else {printf("\n >>>>> FOUND BUGS: Testing complete.  %s <<<<<\n\n", UNITTEST);}

    return 0;
}


