//
// Created by Tia on 07/02/18.
//


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"
#include "assertTester.c"
#define TESTCARD "Smithy"

//randomize the kingdom cards
int* randomize (int arr[] );
//swap helper for randomize()
void swap(int *a, int *b);


/********************************************************
 * Name: randomtestcard1.c
 * Author: Tia Seibold
 * Description: This is a random test for smithy.
 * It allows the players to pick up up three more cards
 * cards. Please see my documentation for full explanation.
*********************************************************/

int main (int argc, char** argv) {

    //initiate counters and variables
    int i, l, round, currentHand, thisPlayer, choice1, choice2, choice3, *bonus, cardEffectReturn;
    int newCards = 3;
    int discarded = 1;
    int gameSetup = 2;
    int countPasses = 0;
    long seedN = 200;

    int arr[20];
    arr[0] = adventurer; arr[1] = council_room; arr[2] = feast; arr[3] = gardens; arr[4] = mine; arr[5] = remodel; arr[6] = smithy; arr[7] = village; arr[8] = baron; arr[9] = great_hall;
    arr[10] = minion; arr[11] = steward; arr[12] = tribute; arr[13] = ambassador; arr[14] = cutpurse; arr[15] = embargo; arr[16] = outpost; arr[17] = salvager; arr[18] = sea_hag; arr[19] = treasure_map;
    randomize (arr);

    printf("\n--------------- Randomly Testing Card: %s --------------\n", TESTCARD);


    //run through random tests 200 times. The more, the better, however
    //in order to keep the results manageable, we'll run through it 200 times.
    for (round = 0; round < 200; round++) {


        //plant a seed and select a stream for Random() - these numbers are random, however,
        //they are hard coded, so that the test can be rerun with the exact same random
        //numbers so that failing tests can be observed.
        SelectStream(50);
        seedN++;
        PlantSeeds(seedN);

        //create two different game states, such that one is the original before function is called,
        //and the other is after the function has been called.
        struct gameState G, testG;


        //randomly create the bytes for the game struct
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char *) &G)[i] = (char) floor(Random() * sizeof(struct gameState) - 1);
        }


        //set the number of players to be between 2 and 4
        G.numPlayers = (int) (2 + floor(Random() * 2));

        //figure out randomly whose turn it will be and place it in variable thisPlayer
        G.whoseTurn = (int) floor(Random() * G.numPlayers);
        thisPlayer = G.whoseTurn;

        //initialize the game. Put a random seed into the game.
        initializeGame(G.numPlayers, arr, (int) (1 + floor(Random() * 500)), &G);

        //Go through each player
        int p = 0;
        for (p = 0; p < G.numPlayers; p++) {

            //set the deck to be deck to be between 0 and 5, such that about
            //every five rounds, the deck is zero or 1 and we can test this boundary case.
            G.deckCount[p] = (int) floor(Random() * 8);

            //set the discard pile for this player to be a random number at most
            // proportionate to the max of that player's deck
            G.discardCount[p] = (int) floor(Random() * (MAX_DECK / G.numPlayers));

            //set the hand pile for this player to be a random number at most
            // proportionate to the max of that player's hand
            G.handCount[p] = (int) floor(Random() * (MAX_HAND / G.numPlayers));

        }

        //for each card in the player's hand pile, set it to a random valid card.
        for (i = 0; i < MAX_HAND; i++) {
            // choose one of the other 27 cards
            G.hand[thisPlayer][i] = (int) floor(Random() * 27);
        }
        //for each card in the player's deck, set it to a random valid card.
        for (i = 0; i < MAX_DECK; i++) {
            //choose one of the other 27 cards
            G.deck[thisPlayer][i] = (int) floor(Random() * 27);
        }
        //for each card in the player's discard pile, set it to a random valid card.
        for (i = 0; i < MAX_DECK; i++) {
            // choose one of the other 27 cards
            G.discard[thisPlayer][i] = (int) floor(Random() * 27);

        }


        //put the person whose turn it is back in playerTurn.
        int playerTurn = whoseTurn(&G);


        //put the smithy card into a random place in the player's hand
        G.hand[thisPlayer][(int) floor(Random() * MAX_HAND)] = smithy;

        //put random cards into the different choices.
        //There are 500 cards in the base dominion game total, so
        //any number up to 500 is reasonable.
        choice1 = (int) floor(Random() * 500);
        choice2 = (int) floor(Random() * 500);
        choice3 = (int) floor(Random() * 500);
        l = (int) floor(Random() * 500);
        bonus = &l;

        //set the current hand to a reasonable number in the current player's hand card range.
        currentHand = (int) floor(Random() * (G.handCount[thisPlayer]));
        //get the current player's turn and set the next player's turn.
        int thisPlayer = playerTurn;
        int nextPlayer = (thisPlayer + 1) % G.numPlayers;
        //set the number of buys to be 1 at the start of the turn.
        G.numBuys = 1;
        //set the played card count to be a random, reasonable number.
        //since the max deck, is the max for the number of cards in the deck,
        //the played card count should be no more than this.
        G.playedCardCount = (int) floor(Random() * (MAX_DECK));

        //make a copy of the current state of the game
        memcpy (&testG, &G, sizeof(struct gameState));

        cardEffectReturn = cardEffect(smithy, choice1, choice2, choice3, &testG, currentHand, bonus);



        //go through and see if there were any failures. If so, print them and the other
        //variables out, so that the combinations of variables that cause that failure
        //can be noted. The success statements are not printed out.
        char cardEffectSuccess[] = "cardEffect successful";


        countPasses += assertTrue1(cardEffectReturn == 0, cardEffectSuccess, 1, thisPlayer, 1);

//expect the testG's current player to have the same amount of cards in their hand as the before cardEffect was run, plus three.
        char handcount[] = "hand count";


        //testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);

        countPasses += assertTrue1(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded,
                                  handcount, 1, thisPlayer, 1);

//expect the testG's current player to have the same amount of cards in their hand as the before cardEffect was run, plus three.
        char deckcount[] = "deck count";

        int three = 3;
        int *threeP = &three;
        if (G.deckCount >= threeP) {
            //testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 3);

            countPasses += assertTrue1(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 3,
                                      handcount, 1, thisPlayer, 1);
        }
        int two = 2;
        int *twoP = &two;
        if (G.deckCount == twoP) {
           // testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 2);

            countPasses += assertTrue1(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 2,
                                      handcount, 1, thisPlayer, 1);
        }
        int one = 1;
        int *oneP = &one;
        if (G.deckCount == oneP) {
          //  testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 1);

            countPasses += assertTrue1(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 1,
                                      handcount, 1, thisPlayer, 1);
        }
        int zero = 0;
        int *zeroP = &zero;
        if (G.deckCount == zeroP) {
           // testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);

            countPasses += assertTrue1(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer],
                                      handcount, 1, thisPlayer, 1);
        }

//expect the testG's next player to have at least one more smithy discarded after it has been played.
        char discardAdv[] = "discard smithy";
        int countA = 0;
        int origDiscarded = 0;
        for (origDiscarded = 0; origDiscarded < G.discardCount[thisPlayer]; origDiscarded++) {
            if (G.discard[thisPlayer][origDiscarded] == smithy) { countA++; }
        }
        int testDiscarded = 0;
        int countB = 0;
        for (testDiscarded = 0; testDiscarded < testG.discardCount[thisPlayer]; testDiscarded++) {
            if (testG.discard[thisPlayer][testDiscarded] == smithy) { countB++; }
        }
//expect the testG's next player to have at least one more smithy discarded after it has been played.
        countPasses += assertTrue1(countA < countB, discardAdv, 5, thisPlayer, 1);

        char discardcount[] = "discard count";

        //testG.discardCount[thisPlayer]);

        countPasses += assertTrue1(testG.discardCount[thisPlayer] > G.discardCount[thisPlayer], discardcount, 1,
                                  thisPlayer, 1);


//expect the testG's game setup to have the same amount of estate cards as the before cardEffect was run.
        char estatecount[] = "estate count";


        countPasses += assertTrue1(testG.supplyCount[estate] == G.supplyCount[estate], estatecount, 0, gameSetup, 1);

//expect the testG's game setup to have the same amount of douchy cards as the before cardEffect was run.
        char douchycount[] = "douchy count";


        countPasses += assertTrue1(testG.supplyCount[duchy] == G.supplyCount[duchy], douchycount, 0, gameSetup, 1);

//expect the testG's game setup to have the same amount of province cards as the before cardEffect was run.
        char provincecount[] = "province count";


        countPasses += assertTrue1(testG.supplyCount[province] == G.supplyCount[province], provincecount, 0,
                                  gameSetup, 1);

//expect the testG's current player to have one more action than before cardEffect was run.
        char numOfActions[] = "number of actions";

       // testG.numActions, G.numActions);

        countPasses += assertTrue1(testG.numActions == G.numActions, numOfActions, 0, thisPlayer, 1);


        char numberOfCoppers[] = "supply of coppers";
//expect the testG's next player to have the same amount of coppers in their supply as the before cardEffect was run.

        countPasses += assertTrue1(testG.supplyCount[copper] == G.supplyCount[copper], numberOfCoppers, 0,
                                  thisPlayer, 1);


        char numberOfSilvers[] = "supply of silvers";
//expect the testG's next player to have the same amount of silvers in their supply as the before cardEffect was run.

        countPasses += assertTrue1(testG.supplyCount[silver] == G.supplyCount[silver], numberOfSilvers, 0,
                                  thisPlayer, 1);

        char numberOfGolds[] = "supply of golds";
//expect the testG's next player to have the same amount of golds in their supply as the before cardEffect was run.

        countPasses += assertTrue1(testG.supplyCount[gold] == G.supplyCount[gold], numberOfGolds, 0, thisPlayer, 1);

//expect the testG's next player to have the same amount of cards in their hand as the before cardEffect was run.
       // G.handCount[nextPlayer]);

        countPasses += assertTrue1(testG.handCount[nextPlayer] == G.handCount[nextPlayer], handcount, 0, nextPlayer,
                                  1);

//expect the testG's next player to have the same amount of cards in their deck as the before cardEffect was run.
       // G.deckCount[nextPlayer]);

        countPasses += assertTrue1(testG.deckCount[nextPlayer] == G.deckCount[nextPlayer], deckcount, 0, nextPlayer,
                                  1);

        char numberOfBuys[] = "number of buys";
//expect the testG's next player to have the same amount of cards in their deck as the before cardEffect was run.

        countPasses += assertTrue1(testG.numBuys == G.numBuys, numberOfBuys, 0, nextPlayer, 1);



        //print the failures and the other variables monitored, such that interactions
        //between them become evident.
        if (countPasses != 28) {
            printf("\n---------------Failures were found in: %s --------------\n", TESTCARD);


            //char cardEffectSuccess[] = "cardEffect successful";

            printf("cardEffect return = %d, expected = %d\n", cardEffectReturn, 0);

            countPasses += assertTrue(cardEffectReturn == 0, cardEffectSuccess, 1, thisPlayer, 1);

            //expect the testG's current player to have the same amount of cards in their hand as the before cardEffect was run, plus three.
            //char handcount[] = "hand count";

            printf("hand count original = %d, after cardEffect = %d, expected = %d\n", G.handCount[thisPlayer],
                   testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);

            countPasses += assertTrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded,
                                      handcount, 1, thisPlayer, 1);

            //expect the testG's current player to have the same amount of cards in their hand as the before cardEffect was run, plus three.
            //char deckcount[] = "deck count";

           // int three = 3;
            //int *threeP = &three;
            if (G.deckCount >= threeP) {
                printf("deck count original = %d, after cardEffect = %d, expected = %d\n", G.deckCount[thisPlayer],
                       testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 3);

                countPasses += assertTrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 3,
                                          handcount, 1, thisPlayer, 1);
            }
            //int two = 2;
           // int *twoP = &two;
            if (G.deckCount == twoP) {
                printf("deck count original = %d, after cardEffect = %d, expected = %d\n", G.deckCount[thisPlayer],
                       testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 2);

                countPasses += assertTrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 2,
                                          handcount, 1, thisPlayer, 1);
            }
           // int one = 1;
           // int *oneP = &one;
            if (G.deckCount == oneP) {
                printf("deck count original = %d, after cardEffect = %d, expected = %d\n", G.deckCount[thisPlayer],
                       testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 1);

                countPasses += assertTrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 1,
                                          handcount, 1, thisPlayer, 1);
            }
            //int zero = 0;
           // int *zeroP = &zero;
            if (G.deckCount == zeroP) {
                printf("deck count original = %d, after cardEffect = %d, expected = %d\n", G.deckCount[thisPlayer],
                       testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);

                countPasses += assertTrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer],
                                          handcount, 1, thisPlayer, 1);
            }

            //expect the testG's next player to have at least one more smithy discarded after it has been played.
           // char discardAdv[] = "discard smithy";
             countA = 0;
           origDiscarded = 0;
            for (origDiscarded = 0; origDiscarded < G.discardCount[thisPlayer]; origDiscarded++) {
                if (G.discard[thisPlayer][origDiscarded] == smithy) { countA++; }
            }
            testDiscarded = 0;
            countB = 0;
            for (testDiscarded = 0; testDiscarded < testG.discardCount[thisPlayer]; testDiscarded++) {
                if (testG.discard[thisPlayer][testDiscarded] == smithy) { countB++; }
            }
            printf("Number of original discarded Smithies = %d, after cardEffect = %d \n", countA, countB);
            //expect the testG's next player to have at least one more smithy discarded after it has been played.
            countPasses += assertTrue(countA < countB, discardAdv, 5, thisPlayer, 1);

            //char discardcount[] = "discard count";

            printf("discard count original = %d, after cardEffect = %d\n", G.discardCount[thisPlayer],
                   testG.discardCount[thisPlayer]);

            countPasses += assertTrue(testG.discardCount[thisPlayer] > G.discardCount[thisPlayer], discardcount, 1,
                                      thisPlayer, 1);


            //expect the testG's game setup to have the same amount of estate cards as the before cardEffect was run.
           // char estatecount[] = "estate count";

            printf("estate = %d, expected = %d, duchy = %d, expected = %d, province = %d, expected = %d\n",
                   testG.supplyCount[estate], \
           G.supplyCount[estate], testG.supplyCount[duchy], G.supplyCount[duchy], testG.supplyCount[province], \
           G.supplyCount[province]);

            countPasses += assertTrue(testG.supplyCount[estate] == G.supplyCount[estate], estatecount, 0, gameSetup, 1);

            //expect the testG's game setup to have the same amount of douchy cards as the before cardEffect was run.
           // char douchycount[] = "douchy count";

            printf("douchy count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);

            countPasses += assertTrue(testG.supplyCount[duchy] == G.supplyCount[duchy], douchycount, 0, gameSetup, 1);

            //expect the testG's game setup to have the same amount of province cards as the before cardEffect was run.
            //char provincecount[] = "province count";

            printf("province count = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]);

            countPasses += assertTrue(testG.supplyCount[province] == G.supplyCount[province], provincecount, 0,
                                      gameSetup, 1);

            //expect the testG's current player to have one more action than before cardEffect was run.
            //char numOfActions[] = "number of actions";

            printf("original number of actions = %d, after cardEffect = %d, expected = %d\n", G.numActions,
                   testG.numActions, G.numActions);

            countPasses += assertTrue(testG.numActions == G.numActions, numOfActions, 0, thisPlayer, 1);


            //char numberOfCoppers[] = "supply of coppers";
            //expect the testG's next player to have the same amount of coppers in their supply as the before cardEffect was run.
            printf("number of coppers = %d, expected = %d\n", testG.supplyCount[copper], G.supplyCount[copper]);

            countPasses += assertTrue(testG.supplyCount[copper] == G.supplyCount[copper], numberOfCoppers, 0,
                                      thisPlayer, 1);


           // char numberOfSilvers[] = "supply of silvers";
            //expect the testG's next player to have the same amount of silvers in their supply as the before cardEffect was run.
            printf("number of silvers = %d, expected = %d\n", testG.supplyCount[silver], G.supplyCount[silver]);

            countPasses += assertTrue(testG.supplyCount[silver] == G.supplyCount[silver], numberOfSilvers, 0,
                                      thisPlayer, 1);

           // char numberOfGolds[] = "supply of golds";
            //expect the testG's next player to have the same amount of golds in their supply as the before cardEffect was run.
            printf("number of golds = %d, expected = %d\n", testG.supplyCount[gold], G.supplyCount[gold]);

            countPasses += assertTrue(testG.supplyCount[gold] == G.supplyCount[gold], numberOfGolds, 0, thisPlayer, 1);

            //expect the testG's next player to have the same amount of cards in their hand as the before cardEffect was run.
            printf("hand count next player = %d, expected = %d\n", testG.handCount[nextPlayer],
                   G.handCount[nextPlayer]);

            countPasses += assertTrue(testG.handCount[nextPlayer] == G.handCount[nextPlayer], handcount, 0, nextPlayer,
                                      1);

            //expect the testG's next player to have the same amount of cards in their deck as the before cardEffect was run.
            printf("deck count next player = %d, expected = %d\n", testG.deckCount[nextPlayer],
                   G.deckCount[nextPlayer]);

            countPasses += assertTrue(testG.deckCount[nextPlayer] == G.deckCount[nextPlayer], deckcount, 0, nextPlayer,
                                      1);

           // char numberOfBuys[] = "number of buys";
            //expect the testG's next player to have the same amount of cards in their deck as the before cardEffect was run.
            printf("number of buys = %d, expected = %d\n", testG.numBuys, G.numBuys);

            countPasses += assertTrue(testG.numBuys == G.numBuys, numberOfBuys, 0, nextPlayer, 1);

        }
        countPasses = 0;
    }

    printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTCARD);

    return 0;
}

/********************************************************
 * Name: randomize
 * Description: This function randomizes the kingdom cards,
 * such that each game starts with a new combination of
 * kingdom cards
 * Source: https://www.geeksforgeeks.org/shuffle-a-given-array/
*********************************************************/
int* randomize (int arr[] )
{

    int n = 20;
    //plant a seed and select a stream for Random() - these numbers are random, however,
    //they are hard coded, so that the test can be rerun with the exact same random
    //numbers so that failing tests can be observed.
    long seedN = 200;
    SelectStream(50);
    seedN++;
    PlantSeeds(seedN);


    // Start from the last element and swap one by one. We don't
    // need to run for the first element that's why i > 0
    for (int i = n-1; i > 0; i--)
    {
        // Pick a random index from 0 to i
        int j = (int) Random() * (i+1);

        // Swap arr[i] with the element at random index
        swap(&arr[i], &arr[j]);
    }
    return arr;
}
/********************************************************
 * Name: swap
 * Description: A utility function to swap to integers
 * Source: https://www.geeksforgeeks.org/shuffle-a-given-array/
*********************************************************/
void swap (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}