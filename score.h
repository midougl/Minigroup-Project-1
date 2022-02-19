#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct{
    int score;
}player_build;
player_build (**player);



int TotalScore = 0;
int player1 = 0;
int num_players =5;


int Calcscore(int wordSize, bool FoundInDic){

    player = (player_build **) malloc(num_players*sizeof(player_build*));
    for (int i =0; i<num_players; i++){
        player[i] = (player_build*) malloc(num_players * sizeof(player_build));
    }

    for(int i =0; i< num_players; i++){
        (player[i])->score=0;
    }


    if(wordSize<5)printf("1");
    else if(wordSize == 5) player1 = player1 + 2;
    else if(wordSize == 6) player1 = player1 + 3;
    else if(wordSize == 7) player1 = player1 + 5;
    else if(wordSize >= 8) player1 = player1 + 11;

    if(FoundInDic) player1= player1 +5;

    return 0;
}
