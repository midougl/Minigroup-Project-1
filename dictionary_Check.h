#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


int dictionary(char* userInput) {
    FILE* file;
    int buffer = 255;
    char dictionaryWord[buffer];
    char wordCheck[buffer];
    int boolean = 0;

    //makes word check = user input and appends new line to check with dictionary.txt
    strcpy(wordCheck, userInput);
    strcat(wordCheck, "\n");


    //printf("%s\n", wordCheck);


    file = fopen("dictionary.txt", "r");
    
    while (fgets(dictionaryWord, buffer, file) != NULL){
        
        if (strcmp(wordCheck, dictionaryWord) == 0) {
            //printf("boolean actually did equal 1\n");
            boolean = 1; 
            break;
        }
    }

    //printf("%d\n", boolean);

    fclose(file);

    return boolean;

}