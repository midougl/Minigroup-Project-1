#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>



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

#endif // MAIN_H
