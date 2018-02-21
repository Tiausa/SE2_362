//
// Created by Tia on 25/01/18.
//

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "assertTester.c"


#define TESTCARD "adventurer"
//#define MUCHTEXTB 1

/****************************************************************************
 * Name: cardtest2.c
 * Function Tested: adventurer
 * Author: Tia Seibold
 * Description: Tests adventurer card and functionality.
*****************************************************************************/


int main () {

    int i = 0, m = 0;
    int card = 0;
    int NumOfTreasures = 0;
    int NumOfOrigTreasures = 0;
    int newCards = 0;
    int discarded = 0;
    int countPasses = 0;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int nextPlayer = 1;
    int gameSetup = 2;
    int count = 0;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};
    struct gameState testG, G;




    initializeGame(numPlayers, k, seed, &G);



    printf("----------------- Testing cardtest2: %s ----------------\n", TESTCARD);

    for (count = 0;  count < 5; count++){



    // ----------- TEST 1: +2 cards --------------
    printf("TEST 1: Player gains 2 cards.  "
                   "\nPreconditions: treasure cards are copper.\n");





    for (i=1; i<G.deckCount[thisPlayer]; i++) {
        if(i % 5) {G.deck[thisPlayer][i] = great_hall;}
        if(i % 4) {G.deck[thisPlayer][i] = cutpurse;}
        if(i % 3) {G.deck[thisPlayer][i] = copper;}
        if(i % 2) {G.deck[thisPlayer][i] = copper;}
        if(i % 1) {G.deck[thisPlayer][i] = copper;}
    }



    G.hand[thisPlayer][0] = adventurer;
    G.hand[thisPlayer][1] = great_hall;
    G.hand[thisPlayer][2] = cutpurse;
    G.hand[thisPlayer][3] = estate;
    G.hand[thisPlayer][4] = feast;

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    printf("starting cards: ");
    for (m=0; m<testG.handCount[thisPlayer]; m++) {
        printf("(%d)", testG.hand[thisPlayer][m]);
    }
    printf("; ");

    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

    printf("ending cards: ");

    // tests that the removed cards are no longer in the player's hand
    for (m=0; m<testG.handCount[thisPlayer]; m++) {
        printf("(%d)", testG.hand[thisPlayer][m]);
    }
    printf("\n");





    //newCards are two since there are two new treasures added to the hand plus the adventurer card
    newCards = 3;

    //the player discards the adventurer card at the end of their turn
    discarded = 1;

    NumOfTreasures = 0;
    NumOfOrigTreasures = 0;


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
    
    printf("hand count original = %d, after cardEffect = %d, expected = %d\n", G.handCount[thisPlayer], testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    
    countPasses += assertTrue( testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded, handcount, 1, thisPlayer, 2);

    //expect the testG's current player to have two more treasure cards in their hand as the before cardEffect was run.
    char treasureCountArray[] = "treasure cards";
    
    printf("treasure card count original = %d, after cardEffect = %d, expected = %d\n", NumOfOrigTreasures, NumOfTreasures, NumOfOrigTreasures+2);
    
    countPasses += assertTrue( NumOfOrigTreasures+2 == NumOfTreasures, treasureCountArray, 1, thisPlayer, 2);

    char deckcount[] = "deck count";
    //expect the testG's next player to have the same amount of cards in their deck as the before cardEffect was run.
    
    printf("deck count original = %d, after cardEffect = %d, expected = %d\n",G.deckCount[thisPlayer], testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 2);
    
    countPasses += assertTrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 2, deckcount, 0, thisPlayer, 2);

    char discardcount[] = "discard count";
//expect the testG's next player to have a change in their discard count as before cardEffect was run.

    printf("discard count original = %d, after cardEffect = %d\n",G.discardCount[thisPlayer], testG.discardCount[thisPlayer]);

    countPasses += assertTrue(testG.discardCount[thisPlayer] != G.discardCount[thisPlayer], discardcount, 1, thisPlayer, 2);

    //expect the testG's game setup to have the same amount of estate cards as the before cardEffect was run.
    char estatecount [] = "estate count";
    
    printf("estate = %d, expected = %d, duchy = %d, expected = %d, province = %d, expected = %d\n",  testG.supplyCount[estate], \
           G.supplyCount[estate], testG.supplyCount[duchy], G.supplyCount[duchy], testG.supplyCount[province], \
           G.supplyCount[province]);
    
    countPasses += assertTrue(testG.supplyCount[estate] == G.supplyCount[estate], estatecount, 0, gameSetup, 2);

    //expect the testG's game setup to have the same amount of douchy cards as the before cardEffect was run.
    char douchycount [] = "douchy count";
    
    printf("douchy count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);

    countPasses += assertTrue(testG.supplyCount[duchy] == G.supplyCount[duchy], douchycount, 0, gameSetup, 2);

    //expect the testG's game setup to have the same amount of province cards as the before cardEffect was run.
    char provincecount [] = "province count";
    
    printf("province count = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]);
   
    countPasses += assertTrue(testG.supplyCount[province] == G.supplyCount[province], provincecount, 0, gameSetup, 2);

    //expect the testG's current player to have one more action than before cardEffect was run.
    char numOfActions[] = "number of actions";
    
    printf("original number of actions = %d, after cardEffect = %d, expected = %d\n", G.numActions, testG.numActions, G.numActions);
    
    countPasses += assertTrue(testG.numActions == G.numActions, numOfActions, 0, thisPlayer, 2);

    //expect the testG's current player to have the same amount of supply cards than before cardEffect was run.
    int j = 0;
    for(i = 0; i < 25; i++)
    { if(testG.supplyCount[i] != G.supplyCount[i]) { j = 1; }}
    char supplyCards[] = "supply cards";
    
    printf("original number of supply cards = %d, after cardEffect = %d, expected = %d\n", 0, j, 0);
    
    countPasses += assertTrue(j == 0, supplyCards, 0, thisPlayer, 2);



    //expect the testG's next player to have the same amount of cards in their hand as the before cardEffect was run.
    printf("hand count next player = %d, expected = %d\n", testG.handCount[nextPlayer], G.handCount[nextPlayer]);
    
    countPasses += assertTrue(testG.handCount[nextPlayer] == G.handCount[nextPlayer], handcount, 0, nextPlayer, 2);

    //expect the testG's next player to have the same amount of cards in their deck as the before cardEffect was run.
    printf("deck count next player = %d, expected = %d\n", testG.deckCount[nextPlayer], G.deckCount[nextPlayer]);
    
    countPasses += assertTrue(testG.deckCount[nextPlayer] == G.deckCount[nextPlayer], deckcount, 0, nextPlayer, 2);






    // ----------- TEST 1: +2 cards --------------
    printf("TEST 2: Player gains 2 cards.  "
                   "\nPreconditions: treasure cards are silver.\n");


    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);



    for (i=1; i<G.deckCount[thisPlayer]; i++) {
        if(i % 5) {G.deck[thisPlayer][i] = great_hall;}
        if(i % 4) {G.deck[thisPlayer][i] = cutpurse;}
        if(i % 3) {G.deck[thisPlayer][i] = silver;}
        if(i % 2) {G.deck[thisPlayer][i] = silver;}
        if(i % 1) {G.deck[thisPlayer][i] = silver;}
    }



    G.hand[thisPlayer][0] = adventurer;
    G.hand[thisPlayer][1] = great_hall;
    G.hand[thisPlayer][2] = cutpurse;
    G.hand[thisPlayer][3] = estate;
    G.hand[thisPlayer][4] = feast;

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    printf("starting cards: ");
    for (m=0; m<testG.handCount[thisPlayer]; m++) {
        printf("(%d)", testG.hand[thisPlayer][m]);
    }
    printf("; ");

    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

    printf("ending cards: ");

    // tests that the removed cards are no longer in the player's hand
    for (m=0; m<testG.handCount[thisPlayer]; m++) {
        printf("(%d)", testG.hand[thisPlayer][m]);
    }
    printf("\n");





    //newCards are two since there are two new treasures added to the hand plus the adventurer card
    newCards = 3;

    //the player discards the adventurer card at the end of their turn
    discarded = 1;



    NumOfTreasures = 0;
    NumOfOrigTreasures = 0;
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
    //char handcount[] = "hand count";
    
    printf("hand count original = %d, after cardEffect = %d, expected = %d\n", G.handCount[thisPlayer], testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    
    countPasses += assertTrue( testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded, handcount, 1, thisPlayer, 2);

    //expect the testG's current player to have two more treasure cards in their hand as the before cardEffect was run.
   // char treasureCountArray[] = "treasure cards";
   
    printf("treasure card count original = %d, after cardEffect = %d, expected = %d\n", NumOfOrigTreasures, NumOfTreasures, NumOfOrigTreasures+2);
    
    countPasses += assertTrue( NumOfOrigTreasures+2 == NumOfTreasures, treasureCountArray, 1, thisPlayer, 2);

    //char deckcount[] = "deck count";
    //expect the testG's next player to have the same amount of cards in their deck as the before cardEffect was run.
   
    printf("deck count original = %d, after cardEffect = %d, expected = %d\n",G.deckCount[thisPlayer], testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 2);
    
    countPasses += assertTrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 2, deckcount, 0, thisPlayer, 2);

//expect the testG's next player to have a change in their discard count as before cardEffect was run.

    printf("discard count original = %d, after cardEffect = %d\n",G.discardCount[thisPlayer], testG.discardCount[thisPlayer]);

    countPasses += assertTrue(testG.discardCount[thisPlayer] != G.discardCount[thisPlayer], discardcount, 1, thisPlayer, 2);

    //expect the testG's game setup to have the same amount of estate cards as the before cardEffect was run.
    //char estatecount [] = "estate count";
    
    printf("estate = %d, expected = %d, duchy = %d, expected = %d, province = %d, expected = %d\n",  testG.supplyCount[estate], \
           G.supplyCount[estate], testG.supplyCount[duchy], G.supplyCount[duchy], testG.supplyCount[province], \
           G.supplyCount[province]);
    
    countPasses += assertTrue(testG.supplyCount[estate] == G.supplyCount[estate], estatecount, 0, gameSetup, 2);

    //expect the testG's game setup to have the same amount of douchy cards as the before cardEffect was run.
   // char douchycount [] = "douchy count";
   
    printf("douchy count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);
    
    countPasses += assertTrue(testG.supplyCount[duchy] == G.supplyCount[duchy], douchycount, 0, gameSetup, 2);

    //expect the testG's game setup to have the same amount of province cards as the before cardEffect was run.
    //char provincecount [] = "province count";
    
    printf("province count = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]);
    
    countPasses += assertTrue(testG.supplyCount[province] == G.supplyCount[province], provincecount, 0, gameSetup, 2);

    //expect the testG's current player to have one more action than before cardEffect was run.
    //char numOfActions[] = "number of actions";
    
    printf("original number of actions = %d, after cardEffect = %d, expected = %d\n", G.numActions, testG.numActions, G.numActions);
    
    countPasses += assertTrue(testG.numActions == G.numActions, numOfActions, 0, thisPlayer, 2);

    //expect the testG's current player to have the same amount of supply cards than before cardEffect was run.
   // int j = 0;
    for(i = 0; i < 25; i++)
    { if(testG.supplyCount[i] != G.supplyCount[i]) { j = 1; }}
   // char supplyCards[] = "supply cards";
   
    printf("original number of supply cards = %d, after cardEffect = %d, expected = %d\n", 0, j, 0);
    
    countPasses += assertTrue(j == 0, supplyCards, 0, thisPlayer, 2);



    //expect the testG's next player to have the same amount of cards in their hand as the before cardEffect was run.
    printf("hand count next player = %d, expected = %d\n", testG.handCount[nextPlayer], G.handCount[nextPlayer]);
    
    countPasses += assertTrue(testG.handCount[nextPlayer] == G.handCount[nextPlayer], handcount, 0, nextPlayer, 2);


    //expect the testG's next player to have the same amount of cards in their deck as the before cardEffect was run.
    printf("deck count next player = %d, expected = %d\n", testG.deckCount[nextPlayer], G.deckCount[nextPlayer]);
   
    countPasses += assertTrue(testG.deckCount[nextPlayer] == G.deckCount[nextPlayer], deckcount, 0, nextPlayer, 2);



    // ----------- TEST 1: +2 cards --------------
    printf("TEST 3: Player gains 2 cards.  "
                   "\nPreconditions: treasure cards are gold.\n");



    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);



    for (i=1; i<G.deckCount[thisPlayer]; i++) {
        if(i % 5) {G.deck[thisPlayer][i] = great_hall;}
        if(i % 4) {G.deck[thisPlayer][i] = cutpurse;}
        if(i % 3) {G.deck[thisPlayer][i] = gold;}
        if(i % 2) {G.deck[thisPlayer][i] = gold;}
        if(i % 1) {G.deck[thisPlayer][i] = gold;}
    }

 /*   gainCard(gold,&G, 2, 0);
    gainCard(gold,&G, 2, 0);
    gainCard(gold,&G, 2, 0);*/


    G.hand[thisPlayer][0] = adventurer;
    G.hand[thisPlayer][1] = great_hall;
    G.hand[thisPlayer][2] = cutpurse;
    G.hand[thisPlayer][3] = estate;
    G.hand[thisPlayer][4] = feast;



    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));


    printf("starting cards: ");
    for (m=0; m<testG.handCount[thisPlayer]; m++) {
        printf("(%d)", testG.hand[thisPlayer][m]);
    }
    printf("; ");

    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);


    printf("ending cards: ");

    // tests that the removed cards are no longer in the player's hand
    for (m=0; m<testG.handCount[thisPlayer]; m++) {
        printf("(%d)", testG.hand[thisPlayer][m]);
    }
    printf("\n");





    //newCards are two since there are two new treasures added to the hand plus the adventurer card
    newCards = 3;

    //the player discards the adventurer card at the end of their turn
    discarded = 1;


    NumOfTreasures = 0;
    NumOfOrigTreasures = 0;

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
   // char handcount[] = "hand count";
   
    printf("hand count original = %d, after cardEffect = %d, expected = %d\n", G.handCount[thisPlayer], testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    
    countPasses += assertTrue( testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded, handcount, 1, thisPlayer, 2);

    //expect the testG's current player to have two more treasure cards in their hand as the before cardEffect was run.
   // char treasureCountArray[] = "treasure cards";
   
    printf("treasure card count original = %d, after cardEffect = %d, expected = %d\n", NumOfOrigTreasures, NumOfTreasures, NumOfOrigTreasures+2);
    
    countPasses += assertTrue( NumOfOrigTreasures+2 == NumOfTreasures, treasureCountArray, 1, thisPlayer, 2);

   // char deckcount[] = "deck count";
    //expect the testG's next player to have the same amount of cards in their deck as the before cardEffect was run.
    
    printf("deck count original = %d, after cardEffect = %d, expected = %d\n",G.deckCount[thisPlayer], testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 2);
    
    countPasses += assertTrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 2, deckcount, 0, thisPlayer, 2);

//expect the testG's next player to have a change in their discard count as before cardEffect was run.

    printf("discard count original = %d, after cardEffect = %d\n",G.discardCount[thisPlayer], testG.discardCount[thisPlayer]);

    countPasses += assertTrue(testG.discardCount[thisPlayer] != G.discardCount[thisPlayer], discardcount, 1, thisPlayer, 2);

    //expect the testG's game setup to have the same amount of estate cards as the before cardEffect was run.
   // char estatecount [] = "estate count";
   
    printf("estate = %d, expected = %d, duchy = %d, expected = %d, province = %d, expected = %d\n",  testG.supplyCount[estate], \
           G.supplyCount[estate], testG.supplyCount[duchy], G.supplyCount[duchy], testG.supplyCount[province], \
           G.supplyCount[province]);
   
    countPasses += assertTrue(testG.supplyCount[estate] == G.supplyCount[estate], estatecount, 0, gameSetup, 2);

    //expect the testG's game setup to have the same amount of douchy cards as the before cardEffect was run.
   // char douchycount [] = "douchy count";
   
    printf("douchy count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);
    
    countPasses += assertTrue(testG.supplyCount[duchy] == G.supplyCount[duchy], douchycount, 0, gameSetup, 2);

    //expect the testG's game setup to have the same amount of province cards as the before cardEffect was run.
    //char provincecount [] = "province count";
    
    printf("province count = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]);
    
    countPasses += assertTrue(testG.supplyCount[province] == G.supplyCount[province], provincecount, 0, gameSetup, 2);

    //expect the testG's current player to have one more action than before cardEffect was run.
  //  char numOfActions[] = "number of actions";
  
    printf("original number of actions = %d, after cardEffect = %d, expected = %d\n", G.numActions, testG.numActions, G.numActions);
    
    countPasses += assertTrue(testG.numActions == G.numActions, numOfActions, 0, thisPlayer, 2);

    //expect the testG's current player to have the same amount of supply cards than before cardEffect was run.
  //  int j = 0;
    for(i = 0; i < 25; i++)
    { if(testG.supplyCount[i] != G.supplyCount[i]) { j = 1; }}
  //  char supplyCards[] = "supply cards";
  
    printf("original number of supply cards = %d, after cardEffect = %d, expected = %d\n", 0, j, 0);
    
    countPasses += assertTrue(j == 0, supplyCards, 0, thisPlayer, 2);



    //expect the testG's next player to have the same amount of cards in their hand as the before cardEffect was run.
    printf("hand count next player = %d, expected = %d\n", testG.handCount[nextPlayer], G.handCount[nextPlayer]);
    
    countPasses += assertTrue(testG.handCount[nextPlayer] == G.handCount[nextPlayer], handcount, 0, nextPlayer, 2);


    //expect the testG's next player to have the same amount of cards in their deck as the before cardEffect was run.
    printf("deck count next player = %d, expected = %d\n", testG.deckCount[nextPlayer], G.deckCount[nextPlayer]);
    
    countPasses += assertTrue(testG.deckCount[nextPlayer] == G.deckCount[nextPlayer], deckcount, 0, nextPlayer, 2);







    // ----------- TEST 1: +2 cards --------------
    printf("TEST 4: Player gains 2 cards.  "
                   "\nPreconditions: 0 treasures cards in hand and 3 in deck.\n");



    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);


    for (i=1; i<G.deckCount[thisPlayer]; i++) {
        if(i % 5) {G.deck[thisPlayer][i] = great_hall;}
        if(i % 4) {G.deck[thisPlayer][i] = cutpurse;}
        if(i % 3) {G.deck[thisPlayer][i] = adventurer;}
        if(i % 2) {G.deck[thisPlayer][i] = duchy;}
        if(i % 1) {G.deck[thisPlayer][i] = feast;}
    }

    gainCard(silver,&G, 1, 0);
    gainCard(silver,&G, 1, 0);
    gainCard(silver,&G, 1, 0);

    G.hand[thisPlayer][0] = great_hall;
    G.hand[thisPlayer][1] = cutpurse;
    G.hand[thisPlayer][2] = duchy;
    G.hand[thisPlayer][3] = estate;
    G.hand[thisPlayer][4] = feast;

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    printf("starting cards: ");
    for (m=0; m<testG.handCount[thisPlayer]; m++) {
        printf("(%d)", testG.hand[thisPlayer][m]);
    }
    printf("; ");

    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

    printf("ending cards: ");

    // tests that the removed cards are no longer in the player's hand
    for (m=0; m<testG.handCount[thisPlayer]; m++) {
        printf("(%d)", testG.hand[thisPlayer][m]);
    }
    printf("\n");




    //newCards are two since there are two new treasures added to the hand plus the adventurer card
    newCards = 3;

    //the player discards the adventurer card at the end of their turn
    discarded = 1;



    NumOfTreasures = 0;
    NumOfOrigTreasures = 0;


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
  //  char handcount[] = "hand count";
    printf("hand count original = %d, after cardEffect = %d, expected = %d\n", G.handCount[thisPlayer], testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
   
    countPasses += assertTrue( testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded, handcount, 1, thisPlayer, 2);


    //expect the testG's current player to have two more treasure cards in their hand as the before cardEffect was run.
  //  char treasureCountArray[] = "treasure cards";
    printf("treasure card count original = %d, after cardEffect = %d, expected = %d\n", NumOfOrigTreasures, NumOfTreasures, NumOfOrigTreasures+2);
   
    countPasses += assertTrue( NumOfOrigTreasures+2 == NumOfTreasures, treasureCountArray, 1, thisPlayer, 2);


   // char deckcount[] = "deck count";
    //expect the testG's next player to have the same amount of cards in their deck as the before cardEffect was run.
    printf("deck count original = %d, after cardEffect = %d, expected = %d\n",G.deckCount[thisPlayer], testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 2);
    
    countPasses += assertTrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 2, deckcount, 0, thisPlayer, 2);

//expect the testG's next player to have a change in their discard count as before cardEffect was run.

    printf("discard count original = %d, after cardEffect = %d\n",G.discardCount[thisPlayer], testG.discardCount[thisPlayer]);

    countPasses += assertTrue(testG.discardCount[thisPlayer] != G.discardCount[thisPlayer], discardcount, 1, thisPlayer, 2);


    //expect the testG's game setup to have the same amount of estate cards as the before cardEffect was run.
   // char estatecount [] = "estate count";
    printf("estate = %d, expected = %d, duchy = %d, expected = %d, province = %d, expected = %d\n",  testG.supplyCount[estate], \
           G.supplyCount[estate], testG.supplyCount[duchy], G.supplyCount[duchy], testG.supplyCount[province], \
           G.supplyCount[province]);
    
    countPasses += assertTrue(testG.supplyCount[estate] == G.supplyCount[estate], estatecount, 0, gameSetup, 2);

    //expect the testG's game setup to have the same amount of douchy cards as the before cardEffect was run.
 //   char douchycount [] = "douchy count";
    printf("douchy count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);
   
    countPasses += assertTrue(testG.supplyCount[duchy] == G.supplyCount[duchy], douchycount, 0, gameSetup, 2);

    //expect the testG's game setup to have the same amount of province cards as the before cardEffect was run.
  //  char provincecount [] = "province count";
    printf("province count = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]);
    
    countPasses += assertTrue(testG.supplyCount[province] == G.supplyCount[province], provincecount, 0, gameSetup, 2);

    //expect the testG's current player to have one more action than before cardEffect was run.
  //  char numOfActions[] = "number of actions";
    printf("original number of actions = %d, after cardEffect = %d, expected = %d\n", G.numActions, testG.numActions, G.numActions);
   
    countPasses += assertTrue(testG.numActions == G.numActions, numOfActions, 0, thisPlayer, 2);

    //expect the testG's current player to have the same amount of supply cards than before cardEffect was run.
  //  int j = 0;
    for(i = 0; i < 25; i++)
    { if(testG.supplyCount[i] != G.supplyCount[i]) { j = 1; }}
  //  char supplyCards[] = "supply cards";
  
    printf("original number of supply cards = %d, after cardEffect = %d, expected = %d\n", 0, j, 0);
   
    countPasses += assertTrue(j == 0, supplyCards, 0, thisPlayer, 2);



    //expect the testG's next player to have the same amount of cards in their hand as the before cardEffect was run.
    printf("hand count next player = %d, expected = %d\n", testG.handCount[nextPlayer], G.handCount[nextPlayer]);
   
    countPasses += assertTrue(testG.handCount[nextPlayer] == G.handCount[nextPlayer], handcount, 0, nextPlayer, 2);

    //expect the testG's next player to have the same amount of cards in their deck as the before cardEffect was run.
    printf("deck count next player = %d, expected = %d\n", testG.deckCount[nextPlayer], G.deckCount[nextPlayer]);
    
    countPasses += assertTrue(testG.deckCount[nextPlayer] == G.deckCount[nextPlayer], deckcount, 0, nextPlayer, 2);



    // ----------- TEST 2: +2 cards --------------
    printf("TEST 5: Player gains 2 treasure cards"
                   "\nPreconditions: 0 treasures cards in hand and 2 in deck. \n");






    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);


    for (i=1; i<G.deckCount[thisPlayer]; i++) {
        if(i % 5) {G.deck[thisPlayer][i] = great_hall;}
        if(i % 4) {G.deck[thisPlayer][i] = cutpurse;}
        if(i % 3) {G.deck[thisPlayer][i] = duchy;}
        if(i % 2) {G.deck[thisPlayer][i] = estate;}
        if(i % 1) {G.deck[thisPlayer][i] = feast;}
    }

    gainCard(silver,&G, 1, 0);
    gainCard(silver,&G, 1, 0);

    G.hand[thisPlayer][0] = great_hall;
    G.hand[thisPlayer][1] = cutpurse;
    G.hand[thisPlayer][2] = duchy;
    G.hand[thisPlayer][3] = estate;
    G.hand[thisPlayer][4] = feast;

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    printf("starting cards: ");
    for (m=0; m<testG.handCount[thisPlayer]; m++) {
        printf("(%d)", testG.hand[thisPlayer][m]);
    }
    printf("; ");

    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

    printf("ending cards: ");

    // tests that the removed cards are no longer in the player's hand
    for (m=0; m<testG.handCount[thisPlayer]; m++) {
        printf("(%d)", testG.hand[thisPlayer][m]);
    }
    printf("\n");


    NumOfTreasures = 0;
    NumOfOrigTreasures = 0;

    // checks default treasure count
    NumOfOrigTreasures = 0;
    for (i = 0; i < G.handCount[thisPlayer]; i++) {
        card = G.hand[thisPlayer][i];
        if (card == copper || card == silver || card == gold) {
            NumOfOrigTreasures++;
        }
    }

    // checks how much treasure is gained
    NumOfTreasures = 0;
    for (i = 0; i < testG.handCount[thisPlayer]; i++) {
        card = testG.hand[thisPlayer][i];
        if (card == copper || card == silver || card == gold) {
            NumOfTreasures++;
        }
    }

    //expect the testG's current player to have two more treasure cards in their hand as the before cardEffect was run.
    //char treasureCountArray[] = "treasure cards";
    printf("treasure card count original = %d, after cardEffect = %d, expected = %d\n", NumOfOrigTreasures, NumOfTreasures, NumOfOrigTreasures+2);
    
    countPasses += assertTrue( NumOfOrigTreasures+2 == NumOfTreasures, treasureCountArray, 1, thisPlayer, 2);

    //expect the testG's current player to have the same amount of cards in their hand as the before cardEffect was run, plus three.
    //char handcount[] = "hand count";
    printf("hand count original = %d, after cardEffect = %d, expected = %d\n", G.handCount[thisPlayer], testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
   
    countPasses += assertTrue( testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded, handcount, 1, thisPlayer, 2);


    //expect the testG's next player to have the same amount of cards in their deck as the before cardEffect was run.
    printf("deck count this player = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + discarded);
    
    countPasses += assertTrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + discarded, deckcount, 0, thisPlayer, 2);

//expect the testG's next player to have a change in their discard count as before cardEffect was run.

    printf("discard count original = %d, after cardEffect = %d\n",G.discardCount[thisPlayer], testG.discardCount[thisPlayer]);

    countPasses += assertTrue(testG.discardCount[thisPlayer] != G.discardCount[thisPlayer], discardcount, 1, thisPlayer, 2);


    // ----------- TEST 3: +0 cards --------------
    printf("TEST 6: Player gains 0 treasure cards"
                   "\nPreconditions: 2 treasures cards in hand and 0 in deck. \n");




    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);



    for (i=1; i<G.deckCount[thisPlayer]; i++) {
        if(i % 5) {G.deck[thisPlayer][i] = great_hall;}
        if(i % 4) {G.deck[thisPlayer][i] = cutpurse;}
        if(i % 3) {G.deck[thisPlayer][i] = duchy;}
        if(i % 2) {G.deck[thisPlayer][i] = estate;}
        if(i % 1) {G.deck[thisPlayer][i] = feast;}
    }

    gainCard(copper,&G, 2, 0);
    gainCard(copper,&G, 2, 0);


    G.hand[thisPlayer][0] = great_hall;
    G.hand[thisPlayer][1] = cutpurse;
    G.hand[thisPlayer][2] = duchy;
    G.hand[thisPlayer][3] = estate;
    G.hand[thisPlayer][4] = feast;

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    printf("starting cards: ");
    for (m=0; m<testG.handCount[thisPlayer]; m++) {
        printf("(%d)", testG.hand[thisPlayer][m]);
    }
    printf("; ");

    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

    printf("ending cards: ");

    // tests that the removed cards are no longer in the player's hand
    for (m=0; m<testG.handCount[thisPlayer]; m++) {
        printf("(%d)", testG.hand[thisPlayer][m]);
    }
    printf("\n");


    NumOfTreasures = 0;
    NumOfOrigTreasures = 0;

    // checks default treasure count
    NumOfOrigTreasures = 0;
    for (i = 0; i < G.handCount[thisPlayer]; i++) {
        card = G.hand[thisPlayer][i];
        if (card == copper || card == silver || card == gold) {
            NumOfOrigTreasures++;
        }
    }

    // checks how much treasure is gained
    NumOfTreasures = 0;
    for (i = 0; i < testG.handCount[thisPlayer]; i++) {
        card = testG.hand[thisPlayer][i];
        if (card == copper || card == silver || card == gold) {
            NumOfTreasures++;
        }
    }

    //expect the testG's current player to have two more treasure cards in their hand as the before cardEffect was run.
    //char treasureCountArray[] = "treasure cards";
    printf("treasure card count original = %d, after cardEffect = %d, expected = %d\n", NumOfOrigTreasures, NumOfTreasures, NumOfOrigTreasures);
   
    countPasses += assertTrue( NumOfOrigTreasures == NumOfTreasures, treasureCountArray, 1, thisPlayer, 2);

    //expect the testG's current player to have the same amount of cards in their hand as the before cardEffect was run, plus three.
    //char handcount[] = "hand count";
    printf("hand count original = %d, after cardEffect = %d, expected = %d\n", G.handCount[thisPlayer], testG.handCount[thisPlayer], G.handCount[thisPlayer] );
    
    countPasses += assertTrue( testG.handCount[thisPlayer] == G.handCount[thisPlayer], handcount, 0, thisPlayer, 2);


    //expect the testG's next player to have the same amount of cards in their deck as the before cardEffect was run.
    printf("deck count this player = %d, expected = %d\n", testG.deckCount[thisPlayer], 0);
    
    countPasses += assertTrue(testG.deckCount[thisPlayer] == 0, deckcount, 0, thisPlayer, 2);

//expect the testG's next player to have a change in their discard count as before cardEffect was run.

    printf("discard count original = %d, after cardEffect = %d\n",G.discardCount[thisPlayer], testG.discardCount[thisPlayer]);

    countPasses += assertTrue(testG.discardCount[thisPlayer] != G.discardCount[thisPlayer], discardcount, 1, thisPlayer, 2);


    // ----------- TEST 3: +0 cards --------------
    printf("TEST 7: Player gains 1 treasure cards"
                   "\nPreconditions: 1 treasures cards in hand and 1 in deck. \n");

int OnlyOneTreasureCard = 1;

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);



    for (i=1; i<G.deckCount[thisPlayer]; i++) {
        if(i % 5) {G.deck[thisPlayer][i] = great_hall;}
        if(i % 4) {G.deck[thisPlayer][i] = cutpurse;}
        if(i % 3) {G.deck[thisPlayer][i] = duchy;}
        if(i % 2) {G.deck[thisPlayer][i] = estate;}
        if(i % 1) {G.deck[thisPlayer][i] = feast;}
    }

    gainCard(silver,&G, 1, 0);
    gainCard(silver,&G, 2, 0);

    G.hand[thisPlayer][0] = great_hall;
    G.hand[thisPlayer][1] = cutpurse;
    G.hand[thisPlayer][2] = duchy;
    G.hand[thisPlayer][3] = estate;
    G.hand[thisPlayer][4] = feast;

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    printf("starting cards: ");
    for (m=0; m<testG.handCount[thisPlayer]; m++) {
        printf("(%d)", testG.hand[thisPlayer][m]);
    }
    printf("; ");

    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

    printf("ending cards: ");

    // tests that the removed cards are no longer in the player's hand
    for (m=0; m<testG.handCount[thisPlayer]; m++) {
        printf("(%d)", testG.hand[thisPlayer][m]);
    }
    printf("\n");



    // checks default treasure count
    NumOfOrigTreasures = 0;
    for (i = 0; i < G.handCount[thisPlayer]; i++) {
        card = G.hand[thisPlayer][i];
        if (card == copper || card == silver || card == gold) {
            NumOfOrigTreasures++;
        }
    }

    // checks how much treasure is gained
    NumOfTreasures = 0;
    for (i = 0; i < testG.handCount[thisPlayer]; i++) {
        card = testG.hand[thisPlayer][i];
        if (card == copper || card == silver || card == gold) {
            NumOfTreasures++;
        }
    }

    //expect the testG's current player to have two more treasure cards in their hand as the before cardEffect was run.
    //char treasureCountArray[] = "treasure cards";
    printf("treasure card count original = %d, after cardEffect = %d, expected = %d\n", NumOfOrigTreasures, NumOfTreasures, NumOfOrigTreasures+1);
    
    countPasses += assertTrue( NumOfOrigTreasures+1 == NumOfTreasures, treasureCountArray, 1, thisPlayer, 2);

    //expect the testG's current player to have the same amount of cards in their hand as the before cardEffect was run, plus three.
    //char handcount[] = "hand count";
    printf("hand count original = %d, after cardEffect = %d, expected = %d\n", G.handCount[thisPlayer], testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded - OnlyOneTreasureCard);
    
    countPasses += assertTrue( testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded-OnlyOneTreasureCard, handcount, 1, thisPlayer, 2);


    //expect the testG's next player to have the same amount of cards in their deck as the before cardEffect was run.
    printf("deck count this player = %d, expected = %d\n", testG.deckCount[thisPlayer],0);
    
    countPasses += assertTrue(testG.deckCount[thisPlayer] == 0, deckcount, 0, thisPlayer, 2);
//expect the testG's next player to have a change in their discard count as before cardEffect was run.

    printf("discard count original = %d, after cardEffect = %d\n",G.discardCount[thisPlayer], testG.discardCount[thisPlayer]);

    countPasses += assertTrue(testG.discardCount[thisPlayer] != G.discardCount[thisPlayer], discardcount, 1, thisPlayer, 2);





    // ----------- TEST 1: +2 cards --------------
    printf("TEST 8: Player gains 1 treasure cards"
                   "\nPreconditions: 0 treasures cards in hand and 1 in deck. \n");



    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);


   for (i=1; i<G.deckCount[thisPlayer]; i++) {
        if(i % 5) {G.deck[thisPlayer][i] = great_hall;}
        if(i % 4) {G.deck[thisPlayer][i] = cutpurse;}
        if(i % 3) {G.deck[thisPlayer][i] = duchy;}
        if(i % 2) {G.deck[thisPlayer][i] = estate;}
        if(i % 1) {G.deck[thisPlayer][i] = feast;}
    }

    gainCard(silver,&G, 1, 0);

            G.hand[thisPlayer][0] = great_hall;
            G.hand[thisPlayer][1] = cutpurse;
            G.hand[thisPlayer][2] = duchy;
            G.hand[thisPlayer][3] = estate;
            G.hand[thisPlayer][4] = feast;

            // copy the game state to a test case
            memcpy(&testG, &G, sizeof(struct gameState));

            printf("starting cards: ");
            for (m=0; m<testG.handCount[thisPlayer]; m++) {
                printf("(%d)", testG.hand[thisPlayer][m]);
            }
            printf("; ");

            cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

            printf("ending cards: ");

            // tests that the removed cards are no longer in the player's hand
            for (m=0; m<testG.handCount[thisPlayer]; m++) {
                printf("(%d)", testG.hand[thisPlayer][m]);
            }
            printf("\n");

            // checks default treasure count
            NumOfOrigTreasures = 0;
            for (i = 0; i < G.handCount[thisPlayer]; i++) {
                card = G.hand[thisPlayer][i];
                if (card == copper || card == silver || card == gold) {
                    NumOfOrigTreasures++;
                }
            }

            // checks how much treasure is gained
            NumOfTreasures = 0;
            for (i = 0; i < testG.handCount[thisPlayer]; i++) {
                card = testG.hand[thisPlayer][i];
                if (card == copper || card == silver || card == gold) {
                    NumOfTreasures++;
                }
            }

            //expect the testG's current player to have two more treasure cards in their hand as the before cardEffect was run.
            //char treasureCountArray[] = "treasure cards";
            printf("treasure card count original = %d, after cardEffect = %d, expected = %d\n", NumOfOrigTreasures, NumOfTreasures, NumOfOrigTreasures+1);
            
            countPasses += assertTrue( NumOfOrigTreasures+1 == NumOfTreasures, treasureCountArray, 1, thisPlayer, 2);

            //expect the testG's current player to have the same amount of cards in their hand as the before cardEffect was run, plus three.
            //char handcount[] = "hand count";
            printf("hand count original = %d, after cardEffect = %d, expected = %d\n", G.handCount[thisPlayer], testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded - OnlyOneTreasureCard);
            
            countPasses += assertTrue( testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded-OnlyOneTreasureCard, handcount, 1, thisPlayer, 2);


            //expect the testG's next player to have the same amount of cards in their deck as the before cardEffect was run.
            printf("deck count this player = %d, expected = %d\n", testG.deckCount[thisPlayer], 0);
            
            countPasses += assertTrue(testG.deckCount[thisPlayer] == 0, deckcount, 0, thisPlayer, 2);
//expect the testG's next player to have a change in their discard count as before cardEffect was run.

    printf("discard count original = %d, after cardEffect = %d\n",G.discardCount[thisPlayer], testG.discardCount[thisPlayer]);

    countPasses += assertTrue(testG.discardCount[thisPlayer] != G.discardCount[thisPlayer], discardcount, 1, thisPlayer, 2);

//        }

   // }


    // ----------- TEST 1: +2 cards --------------
    printf("TEST 9: Player gains 1 treasure card. "
                   "\nPreconditions: 1 treasures cards in hand and 0 in deck. \n");


    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);


    for (i=1; i<G.deckCount[thisPlayer]; i++) {
        if (i % 5) { G.deck[thisPlayer][i] = gold; }
        if (i % 4) { G.deck[thisPlayer][i] = cutpurse; }
        if (i % 3) { G.deck[thisPlayer][i] = duchy; }
        if (i % 2) { G.deck[thisPlayer][i] = estate; }
        if (i % 1) { G.deck[thisPlayer][i] = feast; }
    }
    //G.deck[thisPlayer][2] = gold;
    //G.deck[thisPlayer][3] = gold;

    //gainCard(gold,&G, 1, 0);
    //gainCard(gold,&G, 2, 0);
    G.hand[thisPlayer][0] = silver;
    G.hand[thisPlayer][1] = adventurer;
    G.hand[thisPlayer][2] = duchy;
    G.hand[thisPlayer][3] = estate;
    G.hand[thisPlayer][4] = feast;

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    printf("starting cards: ");
    for (m=0; m<testG.handCount[thisPlayer]; m++) {
        printf("(%d)", testG.hand[thisPlayer][m]);
    }
    printf("; ");

    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

    printf("ending cards: ");

    // tests that the removed cards are no longer in the player's hand
    for (m=0; m<testG.handCount[thisPlayer]; m++) {
        printf("(%d)", testG.hand[thisPlayer][m]);
    }
    printf("\n");

    // checks default treasure count
    NumOfOrigTreasures = 0;
    for (i = 0; i < G.handCount[thisPlayer]; i++) {
        card = G.hand[thisPlayer][i];
        if (card == copper || card == silver || card == gold) {
            NumOfOrigTreasures++;
        }
    }

    // checks how much treasure is gained
    NumOfTreasures = 0;
    for (i = 0; i < testG.handCount[thisPlayer]; i++) {
        card = testG.hand[thisPlayer][i];
        if (card == copper || card == silver || card == gold) {
            NumOfTreasures++;
        }
    }

    //expect the testG's current player to have two more treasure cards in their hand as the before cardEffect was run.
    //char treasureCountArray[] = "treasure cards";
    printf("treasure card count original = %d, after cardEffect = %d, expected = %d\n", NumOfOrigTreasures, NumOfTreasures, NumOfOrigTreasures);
    
    countPasses += assertTrue( NumOfOrigTreasures == NumOfTreasures, treasureCountArray, 1, thisPlayer, 2);

    //expect the testG's current player to have the same amount of cards in their hand as the before cardEffect was run, plus three.
    // char handcount[] = "hand count";
    printf("hand count original = %d, after cardEffect = %d, expected = %d\n", G.handCount[thisPlayer], testG.handCount[thisPlayer], 0);
    
    countPasses += assertTrue( G.handCount[thisPlayer] == testG.handCount[thisPlayer], handcount, 1, thisPlayer, 2);


    //expect the testG's next player to have the same amount of cards in their deck as the before cardEffect was run.
    printf("deck count this player = %d, expected = %d\n", testG.deckCount[thisPlayer], 0);
    
    countPasses += assertTrue(testG.deckCount[thisPlayer] == 0, deckcount, 0, thisPlayer, 2);
//expect the testG's next player to have a change in their discard count as before cardEffect was run.

    printf("discard count original = %d, after cardEffect = %d\n",G.discardCount[thisPlayer], testG.discardCount[thisPlayer]);

    countPasses += assertTrue(testG.discardCount[thisPlayer] != G.discardCount[thisPlayer], discardcount, 1, thisPlayer, 2);



    // ----------- TEST 1: +2 cards --------------
     printf("TEST 10: Player gains 0 treasure cards. "
                   "\nPreconditions: 0 treasures cards in hand and 0 in deck\n");


    for (i=1; i<G.deckCount[thisPlayer]; i++) {
        if (i % 5) { G.deck[thisPlayer][i] = gold; }
        if (i % 4) { G.deck[thisPlayer][i] = cutpurse; }
        if (i % 3) { G.deck[thisPlayer][i] = duchy; }
        if (i % 2) { G.deck[thisPlayer][i] = estate; }
        if (i % 1) { G.deck[thisPlayer][i] = feast; }
    }
    //G.deck[thisPlayer][2] = gold;
    //G.deck[thisPlayer][3] = gold;

    //gainCard(gold,&G, 1, 0);
    //gainCard(gold,&G, 1, 0);
    G.hand[thisPlayer][0] = adventurer;
    G.hand[thisPlayer][1] = adventurer;
    G.hand[thisPlayer][2] = duchy;
    G.hand[thisPlayer][3] = estate;
    G.hand[thisPlayer][4] = feast;

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    printf("starting cards: ");
    for (m=0; m<testG.handCount[thisPlayer]; m++) {
        printf("(%d)", testG.hand[thisPlayer][m]);
    }
    printf("; ");

    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

    printf("ending cards: ");

    // tests that the removed cards are no longer in the player's hand
    for (m=0; m<testG.handCount[thisPlayer]; m++) {
        printf("(%d)", testG.hand[thisPlayer][m]);
    }
    printf("\n");

    // checks default treasure count
    NumOfOrigTreasures = 0;
    for (i = 0; i < G.handCount[thisPlayer]; i++) {
        card = G.hand[thisPlayer][i];
        if (card == copper || card == silver || card == gold) {
            NumOfOrigTreasures++;
        }
    }

    // checks how much treasure is gained
    NumOfTreasures = 0;
    for (i = 0; i < testG.handCount[thisPlayer]; i++) {
        card = testG.hand[thisPlayer][i];
        if (card == copper || card == silver || card == gold) {
            NumOfTreasures++;
        }
    }

    //expect the testG's current player to have two more treasure cards in their hand as the before cardEffect was run.
    //char treasureCountArray[] = "treasure cards";
    printf("treasure card count original = %d, after cardEffect = %d, expected = %d\n", NumOfOrigTreasures, NumOfTreasures, NumOfOrigTreasures);
    
    countPasses += assertTrue( NumOfOrigTreasures == NumOfTreasures, treasureCountArray, 1, thisPlayer, 2);

    //expect the testG's current player to have the same amount of cards in their hand as the before cardEffect was run, plus three.
    // char handcount[] = "hand count";
    printf("hand count original = %d, after cardEffect = %d, expected = %d\n", G.handCount[thisPlayer], testG.handCount[thisPlayer], -1);
    
    countPasses += assertTrue( testG.handCount[thisPlayer] == -1, handcount, 1, thisPlayer, 2);


    //expect the testG's next player to have the same amount of cards in their deck as the before cardEffect was run.
    printf("deck count this player = %d, expected = %d\n", testG.deckCount[thisPlayer], 0);
    
    countPasses += assertTrue(testG.deckCount[thisPlayer] == 0, deckcount, 0, thisPlayer, 2);

//expect the testG's next player to have a change in their discard count as before cardEffect was run.

    printf("discard count original = %d, after cardEffect = %d\n",G.discardCount[thisPlayer], testG.discardCount[thisPlayer]);

    countPasses += assertTrue(testG.discardCount[thisPlayer] != G.discardCount[thisPlayer], discardcount, 1, thisPlayer, 2);
    }

   //printf("\n\n%d\n\n", countPasses);
    if (countPasses == 136){printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);}
    else {printf("\n >>>>> FOUND BUGS: Testing complete. %s <<<<<\n\n", TESTCARD);}


    return 0;
}