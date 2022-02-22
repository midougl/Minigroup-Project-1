#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int wordsFoundPlayer1=0;
int wordsFoundPlayer2=0;

int wordsAddPlayer1=0;
int wordsAddPlayer2=0;

char player1WonLoss=0;
char player2WonLoss=0;

char *file;
bool foundInDic = false;
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
int main();
char usedWords[500][30];
int wordCount=0;
bool availableLettersChecker();
bool endOfWord();
bool check_dict();


#endif // MAIN_H
