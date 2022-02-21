#include "main.h"
#include "randomFile.h"
#include "dictionary_Check.h"
#include "score.h"


bool availableLettersChecker();
bool endOfWord();
bool check_dict();
void MainGameLoop();
void getWordFromTxt();
void menu();
void randAlphabetPicker();
bool passCheck();
bool PassCheckerForRandalph();
bool wordInTextFileCheck();
bool checkIfWordUsed();
void addWordTotxt();
void MainGameLoopSingle();
void serverPlayer();

char usedWords[500][30];
int wordCount=0;


int main() {
    // calls menu function
    menu();

    //gets word from txt file
    getWordFromTxt();

    if(menuOp==1){
        // starts game
        MainGameLoopSingle();
    }
    if(menuOp==2){ // for multiplayer
        MainGameLoop();
    }

}


void randAlphabetPickerSinglePlayer(){  // for single player
    int ranChar =0;
    int lengthOfWord =0;
    bool pass = false;
    bool one = false;
    bool two = false;
    bool three = false;

    srand(time(0));
    lengthOfWord = strlen(userInput);

    //random alph
    ranChar = (rand() % (lengthOfWord-2)) ;
    charHolder = alphabets[ranChar];
/*  // random plyer pick for single player had problems with it working ///////////////////////
    // random player
    ranChar = (rand() % 2)+1 ;
    playerTacker = ranChar;
*/
    playerTacker=1;
    printf("starting player is %d \n", playerTacker);
    printf("Make a word from %c\n", charHolder);

    //Changes userInput to alphabets holder
    for(int i=0; i<strlen(alphabets);i++){
        userInput[i]=alphabets[i];
    }
    if(playerTacker==2){
        getWordFromtxtServerPlayer();

    }
    else{

        //starting first word here
        while(!one){

            if(playerTacker==2){
                getWordFromtxtServerPlayer();
            }

            scanf("%s", newInput);
            printf("\n");

            // checks if the input was "pass'
            pass = PassCheckerForRandalph();

            if(!pass){
                twoPasses =0;

                two = checkIfWordUsed();
                // makes sure letter user inputed are in the word
                if(!two) one = availableLettersChecker();

                //checks if userInput is in dictionary.txt
                if(one) three = check_dict();
                if(!three) one = false;
            }
        }
    }

     //sets up for next round
    strcpy(userInput, newInput);

    //score stuff
    lengthOfWord = strlen(userInput);
    Calcscore(lengthOfWord);
    foundInDic = false;
}


//single player stuff  /////////////////////////////////////////////server
void MainGameLoopSingle(){

    bool cont = true;
    bool one = false;
    bool two = true;
    bool three = true;
    bool twopass = false;

    printf("Your set of alphabets is %s\n", userInput);
    randAlphabetPickerSinglePlayer(); //starts game

    while(cont){

        //changes whos turn it is
        if(playerTacker==1)playerTacker=2;
        else playerTacker=1;

        // if its the servers turn
        if(playerTacker==2){
            printf("It is now the servers turn\n");
            getWordFromtxtServerPlayer();
        }
        else{

            printf("It is now player %d turn\n", playerTacker);
            printf("Make a word from %s\n", userInput);
            scanf("%s", newInput);
            printf("\n");


        // checks if the input was "pass'
        twopass = passCheck();

        // checks for two passes in a row becuase if there are then you need to pick another random alph
        if(twopass==false){

            //if no one passes
            if(twoPasses<2){
                one = checkIfWordUsed();

                if(!one)two = check_dict();      //checks if userInput is in dictionary.txt

                if(two) three = endOfWord();    //makes sure its the end of the previous word

                 //if both previous statments are true
                if(!one && two && three){

                    //sets up for next round
                    strcpy(userInput, newInput);

                     //score stuff
                    lengthOfWord = strlen(userInput);
                    Calcscore(lengthOfWord);
                    foundInDic = false;
                    bothPassCount=0;
                    twoPasses =0;

                }
            }
        }
        // resets passes if it makes it in the loop
        else if (twoPasses!=1){
            bothPassCount=0;
            twoPasses =0;
        }
        }

    }
}

//allows the server player to get a word /////////////////////////////////////////////server
void getWordFromtxtServerPlayer(){
    bool foundWord = false;
    char possWordLineCheck[15] = {'P','o','s','s','i','b','l','e',' ','W','o','r','d','s',':'};
    char check[32];
    int count=0;
    char pass[4]= {'p','a','s','s'};
    int len =0;
    char found[32];
    int counting=0;
    int found2 = 0;
    // reads txt for file input
    // and looks for start of list
    inputFile = fopen(file, "r");
    while(fgets(check, playTextLength, inputFile)){
        count=0;
        for(int i=0; i < strlen(check); i++){
            if(check[i] == possWordLineCheck[i] ){
                count++;
            }
        }
        if(count==15){
            break;
        }
    }
    // while loops for finding words
    while(fgets(check, playTextLength, inputFile)){
        count=0;

        if(foundWord==true){
            break;
        }
        // if it starts with the ending char
        if(check[0]== newInput[strlen(newInput)-1]){

        //to get rid of extra symbols in the string from the memory
        check[strcspn(check, "\r")]= 0;
        check[strcspn(check, "n")]=0;
        strtok(check, "\n");

        strcpy(newInput,check);

            // checks if its in the used words array
            len = sizeof(usedWords)/sizeof(usedWords[0]);
            for(int i =0; i<len; i++){
                if(!strcmp(usedWords[i], newInput)){
                    foundWord=true;
                    strcpy(found, check);
                    break;
                }
            }
            if(foundWord==false){
                found2=1;
                break;
            }
        }
    }

    // this if loop if for if it found a word that works
    if(foundWord==false && found2 ==1){
        counting++;
        printf("Servers word is: %s\n", newInput);
        strcpy(userInput, newInput);
        strcpy(usedWords[wordCount],newInput);
        wordCount++;
    }
    // if the server cant find a word
    else{
    printf("Server had to pass\n");
        strcpy(newInput,pass);
        twoPasses++;

    }
    // if player passes and server has to pass
    if(twoPasses==2){
        bothPassCount++;
        if(bothPassCount==2){// if the server and player hav both passed 2 times in a row
            printf("Both players have passed 2 time in a row. Game over");
            exit(0);
        }
        else{// resets if 2 passes and its not 2 times in a row
            twoPasses=0;
            randAlphabetPickerSinglePlayer();
        }
    }
    // gets rid of bad memory stuff
    newInput[strcspn(newInput, "\r")]= 0;
    newInput[strcspn(newInput, "n")]=0;
    strtok(newInput, "\n");
    newInput[strcspn(userInput, "\r")]= 0;
    newInput[strcspn(userInput, "n")]=0;
    strtok(userInput, "\n");
      fclose(inputFile);
      //return true;
}


void randAlphabetPicker(){  // pick random char at start of the game and random player multiplayer only
    int ranChar =0;
    int lengthOfWord =0;
    bool pass = false;
    bool one = false;
    bool two = false;
    bool three = false;

    srand(time(0));
    lengthOfWord = strlen(userInput);

    //random alph
    ranChar = (rand() % (lengthOfWord-2)) ;
    charHolder = alphabets[ranChar];

    // random player
    ranChar = (rand() % 2)+1 ;
    playerTacker = ranChar;

    printf("starting player is %d \n", playerTacker);
    printf("Make a word from %c\n", charHolder);

    //Changes userInput to alphabets holder
    for(int i=0; i<strlen(alphabets);i++){
        userInput[i]=alphabets[i];
    }

    //starting first word here
    while(!one){

        scanf("%s", newInput);
        printf("\n");

        // checks if the input was "pass'
        pass = PassCheckerForRandalph();

        if(!pass){
            twoPasses =0;

            two = checkIfWordUsed();
            // makes sure letter user inputed are in the word
            if(!two) one = availableLettersChecker();

            //checks if userInput is in dictionary.txt
            if(one) three = check_dict();
            if(!three) one = false;
        }
    }

     //sets up for next round
    strcpy(userInput, newInput);

    //score stuff
    lengthOfWord = strlen(userInput);
    Calcscore(lengthOfWord);
    foundInDic = false;
}


//multiplayer
void MainGameLoop(){
    bool cont = true;
    bool one = false;
    bool two = true;
    bool three = true;
    bool twopass = false;

    printf("Your set of alphabets is %s\n", userInput);
    randAlphabetPicker(); //starts game

    while(cont){

        //changes whos turn it is
        if(playerTacker==1)playerTacker=2;
        else playerTacker=1;

        printf("It is now player %d turn\n", playerTacker);
        printf("Make a word from %s\n", userInput);
        scanf("%s", newInput);
        printf("\n");

        // checks if the input was "pass'
        twopass = passCheck();

        // checks for two passes in a row becuase if there are then you need to pick another random alph
        if(twopass==false){

            //if no one passes
            if(twoPasses<2){
                one = checkIfWordUsed();

                if(!one)two = check_dict();              //checks if userInput is in dictionary.txt

                if(two) three = endOfWord();    //makes sure its the end of the previous word

                 //if both previous statments are true
                if(!one && two && three){

                    //sets up for next round
                    strcpy(userInput, newInput);

                     //score stuff
                    lengthOfWord = strlen(userInput);
                    Calcscore(lengthOfWord);
                    foundInDic = false;
                    bothPassCount=0;
                    twoPasses =0;

                }
            }
        }
        else if (twoPasses!=1){
            bothPassCount=0;
            twoPasses =0;
        }

    }
}

//checks if a word has been used before.
bool checkIfWordUsed(){
    int len =0;

    len = sizeof(usedWords)/sizeof(usedWords[0]);

    for(int i =0; i<len; i++){
        if(!strcmp(usedWords[i], newInput)){
            printf("This word has been used\n");
            score[playerTacker] = score[playerTacker] -2;
            printf("Minus 2 points\n");
            return true;
        }
    }

    strcpy(usedWords[wordCount],newInput);
    wordCount++;
    return false;


}
//functions for making sure the letters used are in the given chars
bool availableLettersChecker(){
    int check=0;

    for (int j = 0; j < strlen(userInput); ++j) {
        if (tolower(newInput[0]) == tolower(userInput[j])) {
            check = 1;
        }
    }
    if (check == 0) {
        printf("Word does not count because you used '%c' which is not in the list of letters\n", newInput[0]);
        printf("Penalized 1 point");
        score[playerTacker] = score[playerTacker] -1;
        return false;
        }
    else {
        return true;

    }
return false;
}

// checks if word is in dict
bool check_dict(){
    bool contToDict=false;
    foundInDic = false;

    contToDict = wordInTextFileCheck();

    if(contToDict){
        if (dictionary(newInput) == 0) {
            printf("%s is not accepted in the given dictionary\n", newInput);
            printf("Penalized 1 point\n");
            score[playerTacker] = score[playerTacker] -1;
            return false;

        }
        else{
            foundInDic = true;
            addWordTotxt();
            return true;
        }
    }


    if(!contToDict){
        return true;
    }

   return false;

}
//adds word to txt file
void addWordTotxt(){
    inputFile = fopen(file, "a");
    fprintf(inputFile, "%s\n", newInput);
    fclose(inputFile);
}

//checks if there word is already in the text file
bool wordInTextFileCheck(){
    //bool foundPossWords = false;
    char possWordLineCheck[15] = {'P','o','s','s','i','b','l','e',' ','W','o','r','d','s',':'};
    char check[32];
    int count=0;

    inputFile = fopen(file, "r");
    while(fgets(check, playTextLength, inputFile)){
        count=0;
        for(int i=0; i < strlen(check); i++){
            if(check[i] == possWordLineCheck[i] ){
                count++;
            }
        }
        if(count==15){
            break;
        }
    }

    while(fgets(check, playTextLength, inputFile)){
        count=0;
        for(int i=0; i<strlen(check);i++){
            if(check[i]== newInput[i]){
                count++;
            }
            if(count==strlen(newInput)){//found in txt file
                fclose(inputFile);
                return false;
            }
        }
    }

      fclose(inputFile);
      return true;
}

// checks for passing in main loop
bool passCheck(){
    int count = 0;
    char pass[4]= {'p','a','s','s'};
    for(int i=0; i <4; i++){// for passing
        if(newInput[i]==pass[i]){
            count++;
            if(count ==4){
                printf("passing to other player\n");
                i = 10;
                twoPasses++;

                if(twoPasses==2){// if both players pass
                    printf("both players have passed reseting\n");
                    bothPassCount++;
                    twoPasses=0;
                    // if your in single player moode menuOp = 1
                    if(menuOp==1){
                        randAlphabetPickerSinglePlayer();
                    }
                    else{
                        randAlphabetPicker();
                    }
                    return true;
                }
                return true;
            }
        }
    }

    return false;
}

//check if the user input starts with the ending of preivous input
bool endOfWord(){
    int count = 0;
    char word1[100];
    bool sameWord = false;

    for(int i=0; i<strlen(userInput); i++){
        if(newInput[i]== userInput[i] ){
            count++;
        }
    }
/*  reused some where else
    if(count == strlen(userInput)){
        printf("You can't use the same word\n");
        printf("Penalized 1 point\n");
        score[playerTacker] = score[playerTacker] -1;
        sameWord = true;
    }
*/
    if(sameWord==false){

        for(int i=0; i < strlen(userInput); i++){
            word1[i] = userInput[strlen(userInput)-i-1];
            count =0;
            for(int j=0; j<strlen(userInput)-1; j++){
                if( (word1[  i-j ])   ==  (newInput[j]) ){
                    count++;
                }
                if(count == i+1){

                    return true;

                }
            }
        }
    }
    printf("word didnt start with ending of last\n");
    printf("Penalized 1 point\n");
    score[playerTacker] = score[playerTacker] -1;
return false;
}


// menu display function
void menu(){
    printf("\n1.    Single Player Mode\n");
    printf("2.    Multi-Player Mode\n");
    printf("3.    Exit\n \n");
    scanf("%d", &menuOp);

    if(menuOp == 1) printf("Starting Single Player Mode\n \n");
    if(menuOp == 2) printf("Starting Multi-Player Mode\n \n");
    if(menuOp == 3) printf("Exiting");

    if(menuOp==3){
        exit(0);
    }
}

//gets aphlabet from txt
void getWordFromTxt(){
    //gets random input file in form "input_xx.txt"
    file = randomInputFile();
    printf("Using game file: %s\n", file);
    inputFile = fopen(file, "r");

    //gets word to play from input file and inputs it into playText
    fgets(userInput, playTextLength, inputFile);

    for(int i=0; i<strlen(userInput); i++){
        alphabets[i]=userInput[i];
    }
    fclose(inputFile);
}

//pass checker for rand alph.    this one is different becuase it has to check for 4 passes to end game
bool PassCheckerForRandalph(){
    int count = 0;
    char pass[4]= {'p','a','s','s'};

    for(int i=0; i <4; i++){// for passing
        if(newInput[i]==pass[i]){
            count++;
            if(count==4){
                printf("passing to other player\n");
                i = 10;
                twoPasses++;

            if(twoPasses==2){
                bothPassCount++;
                twoPasses =0;
            }

            if(bothPassCount ==2){
                printf("game over both players pasted two times");
                exit(0);
            }

            if(playerTacker==1)playerTacker=2;
            else playerTacker=1;
            printf("It is now player %d turn\n", playerTacker);
            printf("Make a word from %c\n", charHolder);
            return true;
            }
        }
    }
    return false;
}
