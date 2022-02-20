#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "main.h"

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

    printf("\nscore for player: %d\n", playerTacker);
    printf("score= %d\n", score[playerTacker]);
    printf("\n");

    return 0;
}
