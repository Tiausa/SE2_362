#define MUCHTEXT 1

/****************************************************************************
 * Name: assertTester.c
 * Author: Tia Seibold
 * Description: Asserts whether the function passed or failed without
 * crashing the program and by providing helpful feedback.
*****************************************************************************/

int assertTrue(int PF, char* test, int PNtest, int player, int card)
{
    char cardA[20];
    memset(&cardA[0], 0, sizeof(cardA));
    if(card == 1) {strncpy(cardA, "smithy", (sizeof cardA)-1);}
    if(card == 2) {strncpy(cardA, "adventurer", (sizeof cardA)-1);}
    if(card == 3) {strncpy(cardA, "cutpurse", (sizeof cardA)-1);}
    if(card == 4) {strncpy(cardA, "great hall", (sizeof cardA)-1);}
    if(card == 5) {strncpy(cardA, "full deck count", (sizeof cardA)-1);}
    if(card == 6) {strncpy(cardA, "update coins", (sizeof cardA)-1);}
    if(card == 7) {strncpy(cardA, "whose turn", (sizeof cardA)-1);}
    if(card == 8) {strncpy(cardA, "discard card", (sizeof cardA)-1);}


    char PF_L[5];
    memset(&PF_L[0], 0, sizeof(PF_L));
    if(PF != 0){
        strncpy(PF_L, "PASS", (sizeof PF_L)-1);
    }
    else{

        strncpy(PF_L, "FAIL", (sizeof PF_L)-1);
    }

    char PNtest_L[20];
    memset(&PNtest_L[0], 0, sizeof(PNtest_L));
    if(PNtest == 1){
        strncpy(PNtest_L, "does", (sizeof PNtest_L)-1);
    }
    else{
        strncpy(PNtest_L, "does not", (sizeof PNtest_L)-1);
    }

    char PlayerN[20];
    memset(&PlayerN[0], 0, sizeof(PlayerN));
    if(player == 0){
        strncpy(PlayerN, " on current player", (sizeof PlayerN)-1);
    }
    else if (player == 1){
        strncpy(PlayerN, " on next player", (sizeof PlayerN)-1);
    }
    else{
        strncpy(PlayerN, "", (sizeof PlayerN)-1);
    }

    char str[800];
    strcpy(str, cardA);
    strcat(str, ": ");
    strcat(str, PF_L);
    strcat(str, " on ");
    strcat(str, test);
    strcat(str, " ");
    strcat(str, PNtest_L);
    strcat(str, " change");
    strcat(str, PlayerN);
    strcat(str, ".\n");
#if (MUCHTEXT)
    printf("%s", str);
#endif

    if (PF == 0)
    {   char strFail[80];
        char F1[80];
        memset(&F1[0], 0, sizeof(F1));
        strncpy(F1, "\n >>>>> FAILURE: Testing found bug in ", (sizeof F1)-1);
        strcpy(strFail, F1);
        strcat(strFail, cardA);
        char F2[10];
        memset(&F2[0], 0, sizeof(F2));
        strncpy(F2, " <<<<<\n\n", (sizeof F2)-1);
        strcat(strFail, F2);
        #if (MUCHTEXT)
        printf("%s", strFail);
#endif
        return 0;
    }
    else
        return 1;
}