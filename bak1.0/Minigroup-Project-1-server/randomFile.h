#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


char* randomInputFile() {

    int fileNum;
    int i;
    char temp[32];
    char* fileName = malloc(32);

    //srand used so every time executed gets different number
    srand(time(0));

    //gets random number between 1 and 10
    fileNum = (rand() % 10) + 1;
    //printf("%d\n", fileNum);

    //makes string fileName become input txt file with 2 decimal digits
    snprintf(temp, 32, "input_%02d.txt", fileNum);

    //printf("%s\n", fileName);

    strcpy(fileName, temp);

    return fileName;

}


/**USED TO TEST RANDOMFILE.C
int main() {
    char *file = randomInputFile();


    printf("%s", file);
}
**/
