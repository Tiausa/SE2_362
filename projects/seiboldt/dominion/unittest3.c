
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "assertTester.c"

#define UNITTEST "whose turn"
#define MUCHTEXTG 1

/****************************************************************************
 * Name: unittest3.c
 * Function Tested: whoseTurn
 * Author: Tia Seibold
 * Description: Checks that player's turn is correct according to whose
 * turn it was previously
*****************************************************************************/


int main(int argc, char const *argv[]) {
    int countPasses = 0;
    int seed = 1000;
    int thisPlayer;
    int NumberOfPlayers = 4;
    int i = 0;
    int whoseTurnDec = 0;
    int ActualTurn = 0;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};
    struct gameState G, testG;

    printf("----------------- Testing unittest3: %s ----------------\n", UNITTEST);


    for (i = 0; i < NumberOfPlayers; i++)	{


        for (thisPlayer = 0; thisPlayer <= NumberOfPlayers; thisPlayer++) {
#if (MUCHTEXT)
            printf("Testing player %d with %d turns\n",i, thisPlayer);
#endif


            memset(&G, 0, sizeof(struct gameState));


            initializeGame(i, k, seed, &G);

            // copy the game state to a test case
            memcpy(&testG, &G, sizeof(struct gameState));

            if (thisPlayer == NumberOfPlayers)
            { G.whoseTurn = 0; }
            else
            { G.whoseTurn = thisPlayer; }

            whoseTurnDec = whoseTurn(&G);

            if (thisPlayer == NumberOfPlayers) {
                ActualTurn = 0;
                //expect the testG's current player to have the same amount of turns before whoseTurn was run.
                char whoseTurnA[] = "whose turn";
                #if (MUCHTEXT)
                printf("after whoseTurn = %d, expected = %d\n", whoseTurnDec, ActualTurn);
                #endif
                countPasses += assertTrue(whoseTurnDec == ActualTurn, whoseTurnA, 1, thisPlayer, 7);

            }
            else {
                ActualTurn = thisPlayer;
                //expect the testG's current player to have the same amount of turns before whoseTurn was run.
                char whoseTurnA[] = "whose turn";
                #if (MUCHTEXT)
                printf("after whoseTurn = %d, expected = %d\n", whoseTurnDec, ActualTurn);
                #endif
                countPasses += assertTrue(thisPlayer == ActualTurn, whoseTurnA, 1, thisPlayer, 7);
            }

            //expect the testG's game setup to have the same amount of douchy cards as the before function was run.
            char douchycount[] = "douchy count";
            #if (MUCHTEXT)
            printf("douchy count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);
            #endif
            countPasses += assertTrue(testG.supplyCount[duchy] == G.supplyCount[duchy], douchycount, 0, 0, 7);

            //expect the testG's game setup to have the same amount of province cards as the before function was run.
            char provincecount[] = "province count";
            #if (MUCHTEXT)
            printf("province count = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]);
            #endif
            countPasses += assertTrue(testG.supplyCount[province] == G.supplyCount[province], provincecount, 0, 0, 7);

            //expect the testG's game setup to have the same amount of estate cards as the before function was run.
            char estatecount[] = "estate count";
            #if (MUCHTEXT)
            printf("estate count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);
            #endif
            countPasses += assertTrue(testG.supplyCount[duchy] == G.supplyCount[duchy], estatecount, 0, 0, 7);

            //expect the testG's current player to have one more action than before function was run.
            char numOfActions[] = "number of actions";
            #if (MUCHTEXT)
            printf("original number of actions = %d, after cardEffect = %d, expected = %d\n", G.numActions,
                   testG.numActions, G.numActions);
                   #endif
            countPasses += assertTrue(testG.numActions == G.numActions, numOfActions, 0, 0, 7);

        }


    }


  // printf("\n\n%d\n\n", countPasses);
    if (countPasses == 100){printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", UNITTEST);}
    else {printf("\n >>>>> FOUND BUGS: Testing complete. %s <<<<<\n\n", UNITTEST);}


    return 0;
}