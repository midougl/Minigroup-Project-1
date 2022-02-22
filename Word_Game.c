#include "main.h"
#include "randomFile.h"
#include "dictionary_Check.h"
#include "score.h"
#include "scoreBoard.h"
#include "gameRules.h"







int main() {

    //readScore();  // for testing

    // calls menu function
    menu();

    //gets word from txt file
    getWordFromTxt();

    if(menuOp==1){
        // starts game
        MainGameLoopSingle();
    }
    if(menuOp==2){ // for multiplayer
        MainGameLoop();
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
        printf("Penalized 1 point");
        score[playerTacker] = score[playerTacker] -1;
        return false;
        }
    else {
        return true;

    }
return false;
}

// checks if word is in dict
bool check_dict(){
    bool contToDict=false;
    foundInDic = false;

    contToDict = wordInTextFileCheck();

    if(contToDict){
        if (dictionary(newInput) == 0) {
            printf("%s is not accepted in the given dictionary\n", newInput);
            printf("Penalized 1 point\n");
            score[playerTacker] = score[playerTacker] -1;
            return false;

        }
        else{
            foundInDic = true;
            addWordTotxt();
            return true;
        }
    }


    if(!contToDict){
        return true;
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
/*  reused some where else
    if(count == strlen(userInput)){
        printf("You can't use the same word\n");
        printf("Penalized 1 point\n");
        score[playerTacker] = score[playerTacker] -1;
        sameWord = true;
    }
*/
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
    printf("Penalized 1 point\n");
    score[playerTacker] = score[playerTacker] -1;
return false;
}

