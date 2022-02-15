#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int TotalScore = 0;
int player1 = 0;
int Calcscore(int wordSize, bool FoundInDic){
    if(wordSize<5)printf("1");
    else if(wordSize == 5) player1 = player1 + 2;
    else if(wordSize == 6) player1 = player1 + 3;
    else if(wordSize == 7) player1 = player1 + 5;
    else if(wordSize >= 8) player1 = player1 + 11;

    if(FoundInDic) player1= player1 +5;
}
