#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "randomFile.h"
#include "dictionary_Check.h"
#include "score.h"

bool availableLetters();
bool endOfWord();
bool check_dict();
void gameCheckers();
void getWordFromTxt();
void menu();
void randCharPicker();


char userInput[32];
int playTextLength = 255;
char playText[255];
char newInput[32];
FILE* inputFile;
int lengthOfWord =0;
int menuOp;
char startingChar;

int main() {

    menu();  // calls menu function
    getWordFromTxt();  //gets word from txt file

    if(menuOp==1){
        gameCheckers();    // starts game
    }
    if(menuOp==2){
        printf("not setup yet");
    }

}

void menu(){
    printf("\n1.    Single Player Mode\n");
    printf("2.    Multi-Player Mode\n");
    printf("3.    Exit\n \n");
    scanf("%d", &menuOp);

    if(menuOp == 1) printf("Starting Single Player Mode\n \n");
    if(menuOp == 2) printf("Starting Multi-Player Mode\n \n");
    if(menuOp == 3) printf("Exiting");

    if(menuOp==3){
        exit(0);
    }
}

void getWordFromTxt(){
    //gets random input file in form "input_xx.txt"
    char *file = randomInputFile();
    printf("Using game file: %s\n", file);
    inputFile = fopen(file, "r");

    //gets word to play from input file and inputs it into playText
    fgets(userInput, playTextLength, inputFile);
    fclose(inputFile);
}

void randCharPicker(){  // pick ranndom char at start of the game and random player
    int ranChar =0;
    char charHolder;
    int lengthOfWord =0;
    //char test[32];
    bool one = true;
    srand(time(0));
    lengthOfWord = strlen(userInput);
    ranChar = (rand() % lengthOfWord-1) ;//random cahr
    charHolder = userInput[ranChar];
    ranChar = (rand() % 2)+1 ; // random player
    playerTacker = ranChar;
    printf("starting player is %d \n", playerTacker);

    //starting the game here
    printf("Make a word from %c\n", charHolder);
    while(one){
        scanf("%s", newInput);
        one = availableLetters();   // makes sure letter user inputed are in the word
        if(one) check_dict();   //checks if userInput is in dictionary.txt
    }
    strcpy(userInput, newInput);   //sets up for next round
    lengthOfWord = strlen(userInput);  //score
    Calcscore(lengthOfWord , foundInDic);
    foundInDic = false;
}

void gameCheckers(){
    bool cont = true;
    bool one = true;
    bool two = true;
    bool three = true;
    int twoPasses =0;
    char pass[4]= {'p','a','s','s'};

    printf("Your set of alphabets is %s\n", userInput);
    randCharPicker(); //starts game

    while(cont){

        if(playerTacker==1)playerTacker=2;
        else playerTacker=1;
        printf("It is now player %d turn\n", playerTacker);

        printf("Make a word from %s\n", userInput);
        scanf("%s", newInput);

        for(int i=0; i <4; i++){// for passing
            if(newInput[i]==pass[i])
            printf("passing to other player\n");
            i = 10;
            twoPasses++;
        }

        if(twoPasses==2){// if both players pass
            printf("both players have passed reseting\n");
            randCharPicker();
        }

        if(twoPasses==0){//if no one passes

            two = check_dict();             //checks if userInput is in dictionary.txt
            if(two) three = endOfWord();        //makes sure its the end of the previous word


            if(one && two && three){
                strcpy(userInput, newInput);   //sets up for next round

                lengthOfWord = strlen(userInput);  //score
                Calcscore(lengthOfWord , foundInDic);
                foundInDic = false;

            }
        }
        else if (twoPasses!=1)twoPasses =0;
    }
}

bool check_dict(){
    if (dictionary(newInput) == 0) {
        printf("%s is not accepted in the given dictionary\n", newInput);
    }
    else{
        foundInDic = true;
        return true;
    }
return false;
}

bool availableLetters(){
    int check;

    check = 0;

    for (int j = 0; j < strlen(userInput); ++j) {
        if (tolower(newInput[0]) == tolower(userInput[j])) {
            check = 1;
        }
    }
    if (check == 0) {
        printf("Word does not count because you used '%c' which is not in the list of letters\n", newInput[0]);
        return true;
        }
    else {
        return false;

    }

return true;
}

bool endOfWord(){
    int count = 0;
    char word1[100];
    bool sameWord = false;
    count = 0;
    sameWord=false;

    for(int i=0; i<strlen(userInput); i++){
        if(newInput[i]== userInput[i] ){
            count++;
        }
    }

    if(count == strlen(userInput)){
        printf("You can't use the same word\n");
        sameWord = true;
    }

    if(sameWord==false){
        for(int i=0; i < strlen(userInput); i++){
            word1[i] = userInput[strlen(userInput)-i-1];
            count =0;
            for(int j=0; j<strlen(userInput)+1; j++){
                if( (word1[  i-j ])   ==  (newInput[j]) ){
                    count++;
                }
                if(count == i+1){
                    return true;
                }
            }
        }
    }
return false;
}































