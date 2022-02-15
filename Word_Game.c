#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "randomFile.h"
#include "dictionary_Check.h"


int main() {


    //******************************************** Might turn this into it's own function? *************************************************
    //used to read input file
    FILE* inputFile;
    int playTextLength = 255;
    char playText[playTextLength];



    //gets random input file in form "input_xx.txt"
    char *file = randomInputFile();
    printf("%s\n", file);


    inputFile = fopen(file, "r");
    
    //gets word to play from input file and inputs it into playText
    fgets(playText, playTextLength, inputFile);
    printf("%s\n", playText);       //test to see if working
    

    fclose(inputFile);

    /****************************************************************************************************************************************
     * Need part to check for single and multiplayer 
     * maybe this part is just for single player?    
     * Probably need to fix scoring system
     * NEEDS TO COMPARE TO DICTIONAIRY
     * need to make array to keep list of words previously used
    **/
    //used to track score
    bool cont = true;
    int score;

    int i;
    int j;

    int result;
    int check;
    
    //for first created word
    printf("Make a word from %s\n", playText);
    char userInput[32];
    scanf("%s", userInput);


    //for loop to check first word to see if the letters used are in the available letters
    //NEEDS TO CHECK DICTIONARY AS WELL<-----------------------------------------------------
    for (i = 0; i < strlen(userInput); ++i) {
        //used to check if 
        check = 0;
        for (j = 0; j < strlen(playText); ++j) {
            //printf("%c%c\n", userInput[i], tolower(playText[j]));
            if (tolower(userInput[i]) == tolower(playText[j])) {
                check = 1;
            }
        }
        if (check == 0) {
            printf("Word does not count because you used %c which is not in the list of letters\n", userInput[i]);
            score = 0;
            cont = false;
            break;
        }
        else {
            cont = true;
            score++;
        }
    }

    //checks if userInput is in dictionary.txt
    if (dictionary(userInput) == 0) {
        printf("%s is not accepted in the given dictionary\n", userInput);
        printf("Game Over\n", userInput);
        cont = false;
    }

    //prints score
    printf("Your score is %d\n", score);


    
    /****************************************************************************************************
     * Below is to continue game if the word they entered is valid 
     * Needs:
     * More Testing
     * Need to make array or list or words previously used.
     * Implement some sort of way to make it multiplayer?
     * **/
        
    //while loop that will run if first word is valid
    while (cont == true) {

        int roundScore = 0;     //used to keep score of round to add at the end
        int counter = 0;        //used in for loop to see if new input works with old
        printf("Make a word using the ending character(s) of %s\n", userInput);    
        char newInput[32];
        scanf("%s", newInput);

        for (i = 0; i < strlen(userInput); i++) {
            int letterCount = 0;    //resets letter count to check in inner for loop
            
            //if first letter in new input is in old word, start check
            if (tolower(userInput[i]) == tolower(newInput[0])) {
                for (j = i; j < strlen(userInput); ++j) {
                   
                    //if statement to check if beginning of new word is equal to ending of previous word
                    if (tolower(userInput[j]) == tolower(newInput[letterCount])) {
                        //printf("second if statement lettercount: %d\n", letterCount);
                        ++letterCount;
                        ++roundScore;
                        counter = letterCount;
                    }
                    //if letter in new input /= ending of previous word, breaks the while loop and game finishes
                    else {
                        printf("The letter %c is not in the word %s\n", newInput[letterCount], userInput);
                        counter = 0;
                    }
                }
            }
        }

        //counter used to keep track of if new input works with old
        //if not, breaks the for loop
        if (counter == 0) {
            printf("%s does not work with %s\n", newInput, userInput);
            printf("The game is over. Your total score is %d\n", score);
            roundScore = 0;
            break;
        }

        //checks if newInput is in dictionary.txt
        if (dictionary(newInput) == 0) {
            printf("%s is not accepted in the given dictionary\n", userInput);
            printf("Game Over\n", userInput);
            break;
        }



        //if game continues, for loop to add rest of score based on word and change value of userInput into new input
        for (i = counter; i < strlen(newInput); ++i) {
            ++roundScore;
        }

        printf("Your score for this round is %d\n", roundScore);

        score = score + roundScore;

        printf("New total score is %d\n", score);

    
        //changes userinput string into the new input
        strcpy(userInput, newInput);

    }

    return 0;


}
