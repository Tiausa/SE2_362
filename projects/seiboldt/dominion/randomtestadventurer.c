//
// Created by Tia on 20/02/18.
//

//
// Created by Tia on 06/02/18.
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
#define TESTCARD "Adventurer"

//randomize the kingdom cards
int* randomize (int arr[] );
//swap helper for randomize()
void swap(int *a, int *b);


/********************************************************
 * Name: randomtestadventurer.c
 * Author: Tia Seibold
 * Description: This is a random test for adventurer.
 * It allows the players to pick up up to two treasure
 * cards. Please see my documentation for full explanation.
*********************************************************/
int main (int argc, char** argv) {

    //initiate counters and variables
    int i, j, l, round, currentHand, thisPlayer, choice1, choice2, choice3, *bonus, cardEffectReturn, preCount, aftercount;
    int newCards = 3;
    int discarded = 1;
    int gameSetup = 2;
    int countPasses = 0;
    long seedN = 200;

    int arr[20];
    arr[0] = adventurer; arr[1] = council_room; arr[2] = feast; arr[3] = gardens; arr[4] = mine; arr[5] = remodel; arr[6] = smithy; arr[7] = village; arr[8] = baron; arr[9] = great_hall;
    arr[10] = minion; arr[11] = steward; arr[12] = tribute; arr[13] = ambassador; arr[14] = cutpurse; arr[15] = embargo; arr[16] = outpost; arr[17] = salvager; arr[18] = sea_hag; arr[19] = treasure_map;
    randomize (arr);

    //create two different game states, such that one is the original before function is called,
    //and the other is after the function has been called.
    struct gameState G, testG;

    //plant a seed and select a stream for Random() - these numbers are random, however,
    //they are hard coded, so that the test can be rerun with the exact same random
    //numbers so that failing tests can be observed.
    SelectStream(50);

    printf("\n--------------- Randomly Testing Card: %s --------------\n", TESTCARD);


    //run through random tests 200 times. The more, the better, however
    //in order to keep the results manageable, we'll run through it 200 times.
    for (round = 0; round < 200; round++) {


        //plant a seed and select a stream for Random() - these numbers are random, however,
        //they are hard coded, so that the test can be rerun with the exact same random
        //numbers so that failing tests can be observed.
        seedN++;
        PlantSeeds(seedN);

        //for flip, explicitly allocate space for g and testG.
        //on my computer, this is not necessary. 
        memset(&G, 0, sizeof(struct gameState));
        memset(&testG, 0, sizeof(struct gameState));

        //set the number of players to be between 2 and 4
        G.numPlayers = (int) (2 + floor(Random() * 2));

        //figure out randomly whose turn it will be and place it in variable thisPlayer
        G.whoseTurn = (int) floor(Random() * G.numPlayers);
        thisPlayer = G.whoseTurn;

        //initialize the game. Put a random seed into the game.
        initializeGame(G.numPlayers, arr, (int)(1 + floor(Random()*500)) , &G);

        //Go through each player
        int p = 0;
        for (p = 0; p < G.numPlayers; p++) {
            //set the discard pile for this player to be a random number at most
            // proportionate to the max of that player's deck
            G.discardCount[p] = (int) floor(Random() * 50);

            //set the hand pile for this player to be a random number at most
            // proportionate to the max of that player's hand
            G.handCount[p] = (int) floor(Random() * 50);

            //set the deck to be deck to be between 0 and 8, such that about
            //every eight rounds, the deck is zero and we can test this boundary case.
            G.deckCount[p] = (int) floor(Random() * 8);

        }

        //for each card in the player's hand pile, set it to a random valid card.
        for (i = 0; i < 50; i++) {
            if (!i%10){
                //the treasure cards are cards 4, 5 and 6.
                G.hand[thisPlayer][i] = (int) (4 + floor(Random() * 3));
            } else {
                //else, choose one of the other 27 cards
                G.hand[thisPlayer][i] = (int) floor(Random() * 27);
            }
        }
        //for each card in the player's deck, set it to a random valid card.
        for (i = 0; i < 50; i++) {
            if (!i%10){
                //the treasure cards are cards 4, 5 and 6.
                G.deck[thisPlayer][i] = (int) (4 + floor(Random() * 3));
            } else {
                //else, choose one of the other 27 cards
                G.deck[thisPlayer][i] = (int) floor(Random() * 27);
            }
        }
        //for each card in the player's discard pile, set it to a random valid card.
        for (i = 0; i < 50; i++) {
            if (!i%10){
                //the treasure cards are cards 4, 5 and 6.
                G.discard[thisPlayer][i] = (int) (4 + floor(Random() * 3));
            } else {
                //else, choose one of the other 27 cards
                G.discard[thisPlayer][i] = (int) floor(Random() * 27);
            }
        }


        //randomly assign all coin cards to once about every ten times
        // be either gold, silver or copper. This will test the function in the face of
        //having all of one type of coin.
        int playerTurn = 0;
        int specialCoin = (int) floor(Random() * 10);
        for(playerTurn = 0; playerTurn < G.numPlayers; playerTurn++) {
            if (specialCoin == 1) {
                for (j = 0; j < G.handCount[playerTurn]; j++) {
                    if (G.hand[playerTurn][j] == silver || G.hand[playerTurn][j] == gold) {
                        G.hand[playerTurn][j] = copper;
                    }
                }
                for (j = 0; j < G.deckCount[playerTurn]; j++) {
                    if (G.deck[playerTurn][j] == silver || G.deck[playerTurn][j] == gold) {
                        G.deck[playerTurn][j] = copper;
                    }
                }

                for (j = 0; j < G.discardCount[playerTurn]; j++) {
                    if (G.discard[playerTurn][j] == silver || G.discard[playerTurn][j] == gold) {
                        G.discard[playerTurn][j] = copper;
                    }
                }
            }

            if (specialCoin == 2) {
                for (j = 0; j < G.handCount[playerTurn]; j++) {
                    if (G.hand[playerTurn][j] == copper || G.hand[playerTurn][j] == gold) {
                        G.hand[playerTurn][j] = silver;
                    }
                }
                for (j = 0; j < G.deckCount[playerTurn]; j++) {
                    if (G.deck[playerTurn][j] == copper || G.deck[playerTurn][j] == gold) {
                        G.deck[playerTurn][j] = silver;
                    }
                }

                for (j = 0; j < G.discardCount[playerTurn]; j++) {
                    if (G.discard[playerTurn][j] == copper || G.discard[playerTurn][j] == gold) {
                        G.discard[playerTurn][j] = silver;
                    }
                }
            }
            if (specialCoin == 3) {
                for (j = 0; j < G.handCount[playerTurn]; j++) {
                    if (G.hand[playerTurn][j] == copper || G.hand[playerTurn][j] == silver) {
                        G.hand[playerTurn][j] = gold;
                    }
                }
                for (j = 0; j < G.deckCount[playerTurn]; j++) {
                    if (G.deck[playerTurn][j] == copper || G.deck[playerTurn][j] == silver) {
                        G.deck[playerTurn][j] = gold;
                    }
                }
                for (j = 0; j < G.discardCount[playerTurn]; j++) {
                    if (G.discard[playerTurn][j] == copper || G.discard[playerTurn][j] == silver) {
                        G.discard[playerTurn][j] = gold;
                    }
                }
            }
        }

        //put the person whose turn it is back in playerTurn.
        playerTurn = whoseTurn(&G);


        //put the adventurer card into a random place in the player's hand
        G.hand[thisPlayer][(int) floor(Random() * 50)] = adventurer;

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
        thisPlayer = playerTurn;
        int nextPlayer = (thisPlayer + 1) % G.numPlayers;
        //set the number of buys to be 1 at the start of the turn.
        G.numBuys = 1;
        //set the played card count to be a random, reasonable number.
        //since the max deck, is the max for the number of cards in the deck,
        //the played card count should be no more than this.
        G.playedCardCount = (int) floor(Random() * (MAX_DECK));



        //make a copy of the current state of the game
        memcpy (&testG, &G, sizeof(struct gameState));

        cardEffectReturn = cardEffect(adventurer, choice1, choice2, choice3, &testG, currentHand, bonus);


        //go through and see if there were any failures. If so, print them and the other
        //variables out, so that the combinations of variables that cause that failure
        //can be noted. The success statements are not printed out.
        int copperCount = 0;
        int silverCount = 0;
        int goldCount = 0;
        preCount = 0;
        for(i = 0; i < G.handCount[playerTurn]; i++){
            if(G.hand[playerTurn][i] == copper){preCount++; copperCount++;}
            else if(G.hand[playerTurn][i] == silver){preCount++; silverCount++;}
            else if(G.hand[playerTurn][i] == gold){preCount++; goldCount++; }
        }

        copperCount = 0;
        silverCount = 0;
        goldCount = 0;
        aftercount = 0;
        for(i = 0; i < testG.handCount[playerTurn]; i++){
            if(testG.hand[playerTurn][i] == copper){aftercount++; copperCount++; }
            else if(testG.hand[playerTurn][i] == silver){aftercount++; silverCount++; }
            else if(testG.hand[playerTurn][i] == gold){aftercount++; goldCount++;}
        }

        char cardEffectSuccess[] = "cardEffect successful";

        countPasses += assertTrue1( cardEffectReturn == 0, cardEffectSuccess, 1, thisPlayer, 2);

        char coinCountAmount[] = "coin count total";

        countPasses += assertTrue1( preCount + 2 ==  aftercount, coinCountAmount, 1, thisPlayer, 2);

        //expect the testG's current player to have the same amount of cards in their hand as the before cardEffect was run, plus three.
        char handcount[] = "hand count";

        countPasses += assertTrue1( testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded, handcount, 1, thisPlayer, 2);

        //expect the testG's next player to have at least one more adventurer discarded after it has been played.
        char discardAdv[] = "discard adventurer";
        int countA = 0;
        int origDiscarded = 0;
        for(origDiscarded = 0; origDiscarded < G.discardCount[thisPlayer]; origDiscarded++)
        {
            if( G.discard[thisPlayer][origDiscarded] == adventurer){ countA++;}
        }
        int testDiscarded = 0;
        int countB = 0;
        for(testDiscarded = 0; testDiscarded < testG.discardCount[thisPlayer]; testDiscarded++)
        {
            if( testG.discard[thisPlayer][testDiscarded] == adventurer){ countB++;}
        }
        //expect the testG's next player to have at least one more adventurer discarded after it has been played.
        countPasses += assertTrue1(countA < countB, discardAdv, 1, thisPlayer, 2);

        char discardcount[] = "discard count";

        countPasses += assertTrue1(testG.discardCount[thisPlayer] < G.discardCount[thisPlayer], discardcount, 5, thisPlayer, 2);

        //check that shuffle works.
        //copied from lesson 11: Random Testing, https://oregonstate.instructure.com/courses/1662160/pages/lesson-11-random-testing-1?module_item_id=17735019
        //shuffle the discard pile back into a deck
        int shuffleCount = 0;
        for (shuffleCount = 0; shuffleCount < testG.discardCount[thisPlayer]; shuffleCount++){
            testG.deck[thisPlayer][shuffleCount] = testG.discard[thisPlayer][shuffleCount];
            testG.discard[thisPlayer][shuffleCount] = -1;
        }
        testG.deckCount[thisPlayer] = testG.discardCount[thisPlayer];
        testG.discardCount[thisPlayer] = 0;

        //shuffle the deck
        int shuffleReturn = shuffle(thisPlayer, &testG);
        testG.discardCount[thisPlayer] = 0;

        char shuffleC [] = "shuffle";
        countPasses += assertTrue1(shuffleReturn != 0, shuffleC, 0, thisPlayer, 2);

        //expect the testG's game setup to have the same amount of estate cards as the before cardEffect was run.
        char estatecount [] = "estate count";

        countPasses += assertTrue1(testG.supplyCount[estate] == G.supplyCount[estate], estatecount, 0, gameSetup, 2);

        //expect the testG's game setup to have the same amount of douchy cards as the before cardEffect was run.
        char douchycount [] = "douchy count";

        countPasses += assertTrue1(testG.supplyCount[duchy] == G.supplyCount[duchy], douchycount, 0, gameSetup, 2);

        //expect the testG's game setup to have the same amount of province cards as the before cardEffect was run.
        char provincecount [] = "province count";

        countPasses += assertTrue1(testG.supplyCount[province] == G.supplyCount[province], provincecount, 0, gameSetup, 2);

        //expect the testG's current player to have one more action than before cardEffect was run.
        char numOfActions[] = "number of actions";

        countPasses += assertTrue1(testG.numActions == G.numActions, numOfActions, 0, thisPlayer, 2);

        char numberOfCoppers[] = "supply of coppers";

        //expect the testG's next player to have the same amount of coppers in their supply as the before cardEffect was run.
        countPasses += assertTrue1(testG.supplyCount[copper] == G.supplyCount[copper], numberOfCoppers, 0, thisPlayer, 2);

        char numberOfSilvers[] = "supply of silvers";
        //expect the testG's next player to have the same amount of silvers in their supply as the before cardEffect was run.

        countPasses += assertTrue1(testG.supplyCount[silver] == G.supplyCount[silver], numberOfSilvers, 0, thisPlayer, 2);

        char numberOfGolds[] = "supply of golds";
        //expect the testG's next player to have the same amount of golds in their supply as the before cardEffect was run.

        countPasses += assertTrue1(testG.supplyCount[gold] == G.supplyCount[gold], numberOfGolds, 0, thisPlayer, 2);

        //expect the testG's next player to have the same amount of cards in their hand as the before cardEffect was run.
        countPasses += assertTrue1(testG.handCount[nextPlayer] == G.handCount[nextPlayer], handcount, 0, nextPlayer, 2);

        char deckcount[] = "deck count";
        //expect the testG's next player to have the same amount of cards in their deck as the before cardEffect was run.

        countPasses += assertTrue1(testG.deckCount[nextPlayer] == G.deckCount[nextPlayer], deckcount, 0, nextPlayer, 2);

        char numberOfBuys[] = "number of buys";
        //expect the testG's next player to have the same amount of cards in their deck as the before cardEffect was run.

        countPasses += assertTrue1(testG.numBuys == G.numBuys, numberOfBuys, 0, nextPlayer, 2);

        //print the failures and the other variables monitored, such that interactions
        //between them become evident.
        if(countPasses != 16){
            printf("\n---------------Failures were found in: %s --------------\n", TESTCARD);

            printf("Coins in hand before cardEffect. Number of coppers: %d. Number of silvers: %d. Number of gold: %d. \n", copperCount, silverCount, goldCount);

            countPasses += assertTrue( cardEffectReturn == 0, cardEffectSuccess, 1, thisPlayer, 2);

            printf("Coins after cardEffect. Number of coppers: %d. Number of silvers: %d. Number of gold: %d. \n", copperCount, silverCount, goldCount);
            countPasses += assertTrue( preCount + 2 ==  aftercount, coinCountAmount, 1, thisPlayer, 2);


            printf("discard count original = %d, after cardEffect = %d\n",G.discardCount[thisPlayer], testG.discardCount[thisPlayer]);
            countPasses += assertTrue(testG.discardCount[thisPlayer] < G.discardCount[thisPlayer], discardcount, 5, thisPlayer, 2);

            printf("Number of original discarded Adventurers = %d, after cardEffect = %d \n",countA, countB);
            countPasses += assertTrue(countA < countB, discardAdv, 1, thisPlayer, 2);

            printf("cardEffect return = %d, expected = %d\n", cardEffectReturn, 0);

            //check that shuffle works.
            //copied from lesson 11: Random Testing, https://oregonstate.instructure.com/courses/1662160/pages/lesson-11-random-testing-1?module_item_id=17735019
            //shuffle the discard pile back into a deckshuffleCount = 0;
            for (shuffleCount = 0; shuffleCount < testG.discardCount[thisPlayer]; shuffleCount++){
                testG.deck[thisPlayer][shuffleCount] = testG.discard[thisPlayer][shuffleCount];
                testG.discard[thisPlayer][shuffleCount] = -1;
            }
            testG.deckCount[thisPlayer] = testG.discardCount[thisPlayer];
            testG.discardCount[thisPlayer] = 0;

            //shuffle the deck
            shuffleReturn = shuffle(thisPlayer, &testG);
            testG.discardCount[thisPlayer] = 0;

            //char shuffle [] = "shuffle";
            countPasses += assertTrue1(shuffleReturn != 0, shuffleC, 0, thisPlayer, 2);

            printf("coin value total original = %d, after cardEffect = %d, expected = %d\n", preCount, aftercount, preCount + 2);
            printf("hand count original = %d, after cardEffect = %d, expected with coins added = %d\n", G.handCount[thisPlayer], testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
            countPasses += assertTrue( testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded, handcount, 1, thisPlayer, 2);


            printf("province count = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]);
            countPasses += assertTrue(testG.supplyCount[province] == G.supplyCount[province], provincecount, 0, gameSetup, 2);

            printf("estate count = %d, expected = %d\n", testG.supplyCount[estate], G.supplyCount[estate]);

            countPasses += assertTrue(testG.supplyCount[estate] == G.supplyCount[estate], estatecount, 0, gameSetup, 2);

            printf("province count = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]);

            printf("douchy count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);
            countPasses += assertTrue(testG.supplyCount[duchy] == G.supplyCount[duchy], douchycount, 0, gameSetup, 2);

            printf("original number of actions = %d, after cardEffect = %d, expected = %d\n", G.numActions, testG.numActions, G.numActions);
            countPasses += assertTrue(testG.numActions == G.numActions, numOfActions, 0, thisPlayer, 2);

            printf("number of silvers = %d, expected = %d\n", testG.supplyCount[silver], G.supplyCount[silver]);
            countPasses += assertTrue(testG.supplyCount[silver] == G.supplyCount[silver], numberOfSilvers, 0, thisPlayer, 2);

            printf("number of coppers = %d, expected = %d\n", testG.supplyCount[copper], G.supplyCount[copper]);
            countPasses += assertTrue(testG.supplyCount[copper] == G.supplyCount[copper], numberOfCoppers, 0, thisPlayer, 2);

            printf("number of golds = %d, expected = %d\n", testG.supplyCount[gold], G.supplyCount[gold]);
            countPasses += assertTrue(testG.supplyCount[gold] == G.supplyCount[gold], numberOfGolds, 0, thisPlayer, 2);

            printf("hand count next player = %d, expected = %d\n", testG.handCount[nextPlayer], G.handCount[nextPlayer]);
            countPasses += assertTrue(testG.handCount[nextPlayer] == G.handCount[nextPlayer], handcount, 0, nextPlayer, 2);

            printf("deck count next player = %d, expected = %d\n", testG.deckCount[nextPlayer], G.deckCount[nextPlayer]);
            countPasses += assertTrue(testG.deckCount[nextPlayer] == G.deckCount[nextPlayer], deckcount, 0, nextPlayer, 2);
            printf("number of buys = %d, expected = %d\n", testG.numBuys, G.numBuys);
            countPasses += assertTrue(testG.numBuys == G.numBuys, numberOfBuys, 0, nextPlayer, 2);
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
