
/************************************************************
 * File: testme.c
 * Name: Tia Seibold
 * Description: Fixes a test function by writing out two
 * of its dependencies.
 *************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include <unistd.h>


//global char array to keep the current random chars in.
char charArray[6];

/************************************************************
 * Name: char inputChar()
 * Description: returns a random letter from the string "reset"
 *************************************************************/
char inputChar()
{
    // TODO: rewrite this function
    //chose a random char of the following chars [({ ax})] from the inputChars array.
    char inputChars[] = "[({ ax})]";
    return inputChars[rand() % 9];

}

/************************************************************
 * Name: char *inputString()
 * Description: returns a random letter from the string "reset"
 *************************************************************/
/*
 * char *inputString()
 * returns a string composed of concatenating randomly chosen characters
 * from a predefined string
 */
char *inputString()
{
    // TODO: rewrite this function

    //the array to hold the letters of the input string
    char inputString[] = "reset";

    //go through each memory space and put a random letter into it
    int eachLetter = 0;
    for (eachLetter = 0; eachLetter < 5; eachLetter++)
    { charArray[eachLetter] = inputString[rand() % 5];}

    //mark end of array
    charArray[eachLetter] = '\0';

    //return the array
    return charArray;
}

void testme()
{
    int tcCount = 0;
    char *s;
    char c;
    int state = 0;
    while (1)
    {
        tcCount++;
        c = inputChar();
        s = inputString();
        printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

        if (c == '[' && state == 0) state = 1;
        if (c == '(' && state == 1) state = 2;
        if (c == '{' && state == 2) state = 3;
        if (c == ' ' && state == 3) state = 4;
        if (c == 'a' && state == 4) state = 5;
        if (c == 'x' && state == 5) state = 6;
        if (c == '}' && state == 6) state = 7;
        if (c == ')' && state == 7) state = 8;
        if (c == ']' && state == 8) state = 9;
        if (s[0] == 'r' && s[1] == 'e'
            && s[2] == 's' && s[3] == 'e'
            && s[4] == 't' && s[5] == '\0'
            && state == 9)
        {
            printf("error ");
            exit(200);
        }
    }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}