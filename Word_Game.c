#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "randomFile.h"
#include "dictionary_Check.h"
#include "score.h"

bool availableLetters(char *userInput, char *playText);
bool endOfWord(char *userInput, char *newInput);

    /****************************************************************************************************************************************
     * Need part to check for single and multiplayer (probably use for loop for how ever many players with array for score)
     * Probably need to fix scoring system (inprogress)
     * NEEDS TO COMPARE TO DICTIONAIRY (done)
     * need to make array to keep list of words previously used
     * etc
    ****************************************************************************************************************************************/

int main() {
    bool cont = true;
    int lengthOfWord =0;
    bool foundInDic = false;
    //******************************************** Might turn this into it's own function? *************************************************
    //11111111111111111111111111111111111111111111111 Gets first word from user 1111111111111111111111111111111111111111111111111111111111111
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

    //for first created word
    printf("Make a word from %s\n", playText);
    char userInput[32];
    scanf("%s", userInput);
     //1111111111111111111111111111111111111111111111111111111111111 end of  Gets first word from user 1111111111111111111111111111111111111111111111111111111111111

    while (cont){ //////////////////////////////////main game loop//////////////////////////////////////////////////

    //2222222222222222222222222222222222222222222--makes sure the users input is in the the word--22222222222222222222222222222222222222222222222222222
    cont = availableLetters(userInput, playText);
    //222222222222222222222222222222222222222222--end of makes sure the users input is in the the word--22222222222222222222222222222222222222222222222222222

    //333333333333333333333333333333333333333333--end of checks if userInput is in dictionary.txt--3333333333333333333333333333333333333333333333333333333333333
    if (dictionary(userInput) == 0) {    //checks if userInput is in dictionary.txt
        printf("%s is not accepted in the given dictionary\n", userInput);
        printf("Game Over\n", userInput);
        cont = false;
        foundInDic = true;
        break;
    }
    //33333333333333333333333333333333333333333333333--end of checks if userInput is in dictionary.txt--3333333333333333333333333333333333333333333333333333333333333333333333

    // 444444444444444444444444444444444444444444444--Score stuff--4444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444
    lengthOfWord = strlen(userInput);
    Calcscore(lengthOfWord , foundInDic);
    foundInDic = false;
// 44444444444444444444444444444444444444444444444444--End of Score stuff--44444444444444444444444444444444444444444444444444444444444444444444444444444444444444444

    // 5555555555555555555555555555555555555555555555--continuing off the ending of the previous word--555555555555555555555555555555555555555555555555555555555555555
        printf("Make a word using the ending character(s) of %s\n", userInput);
        char newInput[32];
        scanf("%s", newInput);
        if(strlen(newInput)<3){
            printf("word to small needs to be atleast 3 chars");
            break;
        }
        endOfWord(userInput, newInput);
        strcpy(userInput, newInput);
    // 55555555555555555555555555555555555555555555555--end of  continuing off the ending of the previous word--55555555555555555555555555555555555555555555555555555555555
    }

}


bool availableLetters(char *userInput, char *playText){
    bool cont = true;
    int score=0;
    int check;

    for (int i = 0; i < strlen(userInput); ++i) {
        check = 0;
        for (int j = 0; j < strlen(playText); ++j) {
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

        }
    }
    return cont;
}


bool endOfWord(char *userInput, char *newInput){  // ill clean this up later
    int j =0;
    char one[10];
    char two[20];
    int count = 0;
    char hold[1];
    char hold2[1];
    bool end = false;

    int lentgh = strlen(userInput);
    for(int i=0; i<strlen(userInput); i++){
        if(end) return true;
        j--;
        hold2[0] = userInput[strlen(userInput)+j];
        one[i] = userInput[strlen(userInput)+j];
        two[i] = (newInput[i]);
        hold[0] = two[0];
        count ++;
        if(hold[0] == hold2[0]) {
        printf("here");
            for(int k =0; k<count; k++){
                end = true;
                if(two[k]!= one[count-k-1]){
                    return false;
                }
            }
        }

    }
    return false;

}

