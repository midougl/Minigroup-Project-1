#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "server_main.h"

int TotalScore = 0;
int player1 = 0;
int num_players =5;
int score[3];
int playerTacker=0;

int Calcscore(int wordSize){


    if(wordSize<5)         score[playerTacker] = score[playerTacker] + 1;
    else if(wordSize == 5) score[playerTacker] = score[playerTacker] + 2;
    else if(wordSize == 6) score[playerTacker] = score[playerTacker] + 3;
    else if(wordSize == 7) score[playerTacker] = score[playerTacker] + 5;
    else if(wordSize >= 8) score[playerTacker] = score[playerTacker] + 11;

    if(foundInDic==true) score[playerTacker] = score[playerTacker] +5;


    //FOR SERVER////////////////////////////////////////////////////////////////////
    snprintf(scoreTracker, 64, "score for player %d: \n", playerTacker);
    strcat(test, scoreTracker);
    bzero(scoreTracker, 64);
    
    snprintf(scoreTracker, 64, "score= %d\n", score[playerTacker]);
    strcat(test, scoreTracker);
    strcat(test, newLine);
    bzero(scoreTracker, 64);
    ///////////////////////////////////////////////////////////////////////////////


    printf("\nscore for player: %d\n", playerTacker);
    printf("score= %d\n", score[playerTacker]);
    printf("\n");

    //number of words in the dict added

    if(playerTacker==1 ){
        if(foundInDic==true){
            wordsAddPlayer1++;
            wordsFoundPlayer1++;
        }
        else{
            wordsFoundPlayer1++;
        }
    }


    if(playerTacker==2 ){
        if(foundInDic==true){
            wordsAddPlayer2++;
            wordsFoundPlayer2++;
        }
        else{
            wordsFoundPlayer2++;
        }
    }

    return 0;
}