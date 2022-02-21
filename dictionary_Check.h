#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "main.h"
#include <time.h>
#include <unistd.h>




int dictionary(char* userInput) {
    FILE* file;
    int buffer = strlen(userInput)+1;
    char dictionaryWord[buffer];
    char wordCheck[buffer];
    int dictCount =0;


    strcpy(wordCheck, userInput);

    file = fopen("dictionary.txt", "r");


    while (fgets(dictionaryWord, buffer, file) != NULL){
    dictCount=0;
        for(int i=0; i<strlen(wordCheck); i++){
            if(wordCheck[i]==dictionaryWord[i]){
                dictCount++;
            }

        }
        if(dictCount== strlen(wordCheck)){
            foundInDic= true;
            fclose(file);
            return true;
        }
    }




  /*
        if (strcmp(wordCheck, dictionaryWord)==0) {
            boolean = 1;
            foundInDic= true;
            return true;
        }
    }
    */

    fclose(file);
    return false;

}
