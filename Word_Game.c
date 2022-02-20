#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "randomFile.h"
#include "dictionary_Check.h"
#include "score.h"

bool availableLettersChecker();
bool endOfWord();
bool check_dict();
void MainGameLoop();
void getWordFromTxt();
void menu();
void randAlphabetPicker();
bool passCheck();
bool PassCheckerForRandalph();


char userInput[32];
char alphabets[32];
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
    // calls menu function
    menu();

    //gets word from txt file
    getWordFromTxt();

    if(menuOp==1){
        // starts game
        MainGameLoop();
    }
    if(menuOp==2){ // for multiplayer
        printf("not setup yet");
    }

}

void randAlphabetPicker(){  // pick random char at start of the game and random player
    int ranChar =0;
    int lengthOfWord =0;
    bool pass = false;
    bool one = true;

    srand(time(0));
    lengthOfWord = strlen(userInput);

    //random alph
    ranChar = (rand() % (lengthOfWord-2)) ;
    charHolder = alphabets[ranChar];

    // random player
    ranChar = (rand() % 2)+1 ;
    playerTacker = ranChar;

    printf("starting player is %d \n", playerTacker);
    printf("Make a word from %c\n", charHolder);

    //Changes userInput to alphabets holder
    for(int i=0; i<strlen(alphabets);i++){
        userInput[i]=alphabets[i];
    }

    //starting first word here
    while(one){

        scanf("%s", newInput);
        printf("\n");

        // checks if the input was "pass'
        pass = PassCheckerForRandalph();

        if(!pass){
            twoPasses =0;

            // makes sure letter user inputed are in the word
            one = availableLettersChecker();
            //checks if userInput is in dictionary.txt
            if(one) check_dict();
        }
    }

     //sets up for next round
    strcpy(userInput, newInput);

    //score stuff
    lengthOfWord = strlen(userInput);
    Calcscore(lengthOfWord , foundInDic);
    foundInDic = false;
}



void MainGameLoop(){
    bool cont = true;
    bool one = true;
    bool two = true;
    bool three = true;
    bool twopass = false;

    printf("Your set of alphabets is %s\n", userInput);
    randAlphabetPicker(); //starts game

    while(cont){

        //changes whos turn it is
        if(playerTacker==1)playerTacker=2;
        else playerTacker=1;

        printf("It is now player %d turn\n", playerTacker);
        printf("Make a word from %s\n", userInput);
        scanf("%s", newInput);
        printf("\n");

        // checks if the input was "pass'
        twopass = passCheck();

        // checks for two passes in a row becuase if there are then you need to pick another random alph
        if(twopass==false){

            //if no one passes
            if(twoPasses<2){

                two = check_dict();              //checks if userInput is in dictionary.txt
                if(two) three = endOfWord();    //makes sure its the end of the previous word

                 //if both previous statments are true
                if(one && two && three){

                    //sets up for next round
                    strcpy(userInput, newInput);

                     //score stuff
                    lengthOfWord = strlen(userInput);
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


//functions for making sure the letters used are in the given chars
bool availableLettersChecker(){
    int check=0;

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

// checks if word is in dict
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

// checks for passing in main loop
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
                    randAlphabetPicker();
                    return true;
                }
                return true;
            }
        }
    }

    return false;
}

//check if the user input starts with the ending of preivous input
bool endOfWord(){
    int count = 0;
    char word1[100];
    bool sameWord = false;

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


// menu display function
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

//gets aphlabet from txt
void getWordFromTxt(){
    //gets random input file in form "input_xx.txt"
    char *file = randomInputFile();
    printf("Using game file: %s\n", file);
    inputFile = fopen(file, "r");

    //gets word to play from input file and inputs it into playText
    fgets(userInput, playTextLength, inputFile);

    for(int i=0; i<strlen(userInput); i++){
        alphabets[i]=userInput[i];
    }

    fclose(inputFile);
}

//pass checker for rand alph.    this one is different becuase it has to check for 4 passes to end game
bool PassCheckerForRandalph(){
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
            printf("Make a word from %c\n", charHolder);
            return true;
            }
        }
    }
    return false;
}
