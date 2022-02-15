#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


int dictionary(char* userInput) {
    FILE* file;
    int buffer = strlen(userInput)+1;
    char dictionaryWord[buffer];
    char wordCheck[buffer];
    int boolean = 0;

    strcpy(wordCheck, userInput);

    file = fopen("dictionary.txt", "r");

    while (fgets(dictionaryWord, buffer, file) != NULL){
        if (strcmp(wordCheck, dictionaryWord)==0) {
            boolean = 1;
            break;
        }
    }

    fclose(file);
    return boolean;

}
