#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


int TotalScore = 0;
int player1 = 0;
int num_players =5;
int score[3];
int playerTacker=0;

int Calcscore(int wordSize, bool FoundInDic){

    if(wordSize<5)         score[playerTacker] = score[playerTacker] + 1;
    else if(wordSize == 5) score[playerTacker] = score[playerTacker] + 2;
    else if(wordSize == 6) score[playerTacker] = score[playerTacker] + 3;
    else if(wordSize == 7) score[playerTacker] = score[playerTacker] + 5;
    else if(wordSize >= 8) score[playerTacker] = score[playerTacker] + 11;

    if(FoundInDic) score[playerTacker] = score[playerTacker] +5;

    return 0;
}
