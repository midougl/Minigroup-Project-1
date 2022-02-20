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
bool passCheck();
bool randCharPassChecker();


char userInput[32];
int playTextLength = 255;
char playText[255];
char newInput[32];
FILE* inputFile;
int lengthOfWord =0;
int menuOp;
char startingChar;
int twoPasses =0;
int bothPassCount=0;
char charHolder;

int main() {

    menu();  // calls menu function
    getWordFromTxt();  //gets word from txt file

    if(menuOp==1){
        gameCheckers();    // starts game
    }
    if(menuOp==2){ // for multiplayer
        printf("not setup yet");
    }

}

void randCharPicker(){  // pick random char at start of the game and random player
    int ranChar =0;
    int lengthOfWord =0;
    bool pass = false;

    //char test[32];
    bool one = true;
    srand(time(0));
    lengthOfWord = strlen(userInput);
    ranChar = (rand() % (lengthOfWord-2)) ;//random cahr
    charHolder = userInput[ranChar];
    ranChar = (rand() % 2)+1 ; // random player
    playerTacker = ranChar;



    printf("starting player is %d \n", playerTacker);
    printf("Make a word from %c\n", charHolder);

    //starting the game here
    //printf("Make a word from %c\n", charHolder);
    one = true;
    while(one){

        scanf("%s", newInput);
        printf("\n");


        pass = randCharPassChecker();
        if(!pass){
            twoPasses =0;
            one = availableLetters();   // makes sure letter user inputed are in the word
            if(one) check_dict();   //checks if userInput is in dictionary.txt
        }
    }
    strcpy(userInput, newInput);   //sets up for next round
    lengthOfWord = strlen(userInput);  //score
    Calcscore(lengthOfWord , foundInDic);
    foundInDic = false;


}

bool randCharPassChecker(){
    int count = 0;
    char pass[4]= {'p','a','s','s'};
    for(int i=0; i <4; i++){// for passing
        if(newInput[i]==pass[i]){
            count++;
            if(count==4){
                printf("passing to other player\n");
                i = 10;
                twoPasses++;


            if(twoPasses==2){
                bothPassCount++;
                twoPasses =0;
            }

            if(bothPassCount ==2){
                printf("game over both players pasted two times");
                exit(0);
            }

            if(playerTacker==1)playerTacker=2;
            else playerTacker=1;
            printf("It is now player %d turn\n", playerTacker);
            //printf("Make a word from %s\n", userInput);
            printf("Make a word from %c\n", charHolder);



            return true;
        }
        }
    }
    return false;

}

void gameCheckers(){
    bool cont = true;
    bool one = true;
    bool two = true;
    bool three = true;
    bool twopass = false;

    printf("Your set of alphabets is %s\n", userInput);
    randCharPicker(); //starts game

    while(cont){
        twopass==false;

        if(playerTacker==1)playerTacker=2;
        else playerTacker=1;
        printf("It is now player %d turn\n", playerTacker);

        printf("Make a word from %s\n", userInput);
        scanf("%s", newInput);
        printf("\n");


        twopass = passCheck();// player pass handler

        if(twopass==false){

        if(twoPasses<2){//if no one passes

            two = check_dict();             //checks if userInput is in dictionary.txt
            if(two) three = endOfWord();        //makes sure its the end of the previous word

            if(one && two && three){//if both are true
                strcpy(userInput, newInput);   //sets up for next round
                lengthOfWord = strlen(userInput);  //score
                Calcscore(lengthOfWord , foundInDic);
                foundInDic = false;
                bothPassCount=0;
                twoPasses =0;

            }
        }
        }
        else if (twoPasses!=1){
            bothPassCount=0;
            twoPasses =0;
        }

    }
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

bool passCheck(){
    int count = 0;
    char pass[4]= {'p','a','s','s'};
    for(int i=0; i <4; i++){// for passing
        if(newInput[i]==pass[i]){
            count++;
            if(count ==4){
                printf("passing to other player\n");
                i = 10;
                twoPasses++;

                if(twoPasses==2){// if both players pass
                    printf("both players have passed reseting\n");
                    bothPassCount++;
                    twoPasses=0;
                    randCharPicker();
                    return true;
                }
                return true;
            }
        }
    }

    return false;
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
            for(int j=0; j<strlen(userInput)-1; j++){
                if( (word1[  i-j ])   ==  (newInput[j]) ){
                    count++;
                }
                if(count == i+1){

                    return true;

                }
            }
        }
    }
    printf("word didnt start with ending of last\n");
return false;
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






















