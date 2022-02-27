#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>
#include "server_main.h"

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
void getWordFromtxtServerPlayer();
void winner();


void randAlphabetPickerSinglePlayer(int client_socket){  // for single player


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
  // random plyer pick for single player had problems with it working ///////////////////////
    // random player
    ranChar = (rand() % 2)+1 ;
    playerTacker = ranChar;


    //CHANGES TO COMMUNICATE WITH SERVER/////////////////////////////////////////////////////////////////////////
    char playerTurn[64];
    snprintf(playerTurn, 64, "Starting player is %d turn\nMake a word from: ", playerTacker);
    strncat(playerTurn, &charHolder, 1);
    strcat(test, playerTurn);
    strcat(test, newLine);
    bzero(playerTurn, 64);
    //read(client_socket, test, 1024);
    //strcpy(newInput, test);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////

   // playerTacker=1;
    printf("starting player is %d \n", playerTacker);
    printf("Make a word from %c\n", charHolder);

    //Changes userInput to alphabets holder
    for(int i=0; i<strlen(alphabets);i++){
        userInput[i]=alphabets[i];
    }
    if(playerTacker==2){
        getWordFromtxtServerPlayer(client_socket);



                if(serverPass==true){

                    if(playerTacker==1)playerTacker=2;
                    else playerTacker=1;
                    ////////////////////////////////////////////////////////////////////////////////////////////
                    snprintf(playerTurn, 64, "It is player %d turn\nMake a word from: ", playerTacker);
                    strncat(playerTurn, &charHolder, 1);
                    strcat(test, playerTurn);
                    strcat(test, newLine);
                    printf("%s", playerTurn);
                    bzero(playerTurn, 64);
                    ///////////////////////////////////////////////////////////////////////////////////////////
                    printf("It is now player %d turn\n", playerTacker);
                    printf("Make a word from %c\n", charHolder);
                }



    }
    if(playerTacker==1){

        //starting first word here
        while(!one){

            if(playerTacker==2){
                getWordFromtxtServerPlayer(client_socket);


                if(serverPass==true){

                    if(playerTacker==1)playerTacker=2;
                    else playerTacker=1;
                    ///////////////////////////////////////////////////////////////////////////////////////////
                    snprintf(playerTurn, 64, "It is player %d turn\nMake a word from: ", playerTacker);
                    strncat(playerTurn, &charHolder, 1);
                    strcat(test, playerTurn);
                    strcat(test, newLine);
                    printf("%s", playerTurn);
                    bzero(playerTurn, 64);
                    ///////////////////////////////////////////////////////////////////////////////////////////
                    printf("It is now player %d turn\n", playerTacker);
                    printf("Make a word from %c\n", charHolder);
                }

            }
            write(client_socket, test, strlen(test));
            printf("%s", test);
            //printf("It is now player %d turn\n", playerTacker);
            //printf("Make a word from %s\n", userInput);
            bzero(test, 1024);
            read(client_socket, test, 1024);
            strcpy(newInput, test);
            bzero(test, 1024);
            printf("%s", newInput);
            //scanf("%s", newInput);
            printf("\n");

            // checks if the input was "pass'
            pass = PassCheckerForRandalph(client_socket);



            if(!pass){

                twoPasses =0;

                two = checkIfWordUsed();
                // makes sure letter user inputed are in the word
                if(!two) one = availableLettersChecker();

                //checks if userInput is in dictionary.txt
                if(one) three = check_dict();
                if(!three) one = false;
            }
        if(!one &&! pass){
            //printf("hi");
            if(playerTacker==1)playerTacker=2;
            else playerTacker=1;
            //SERVER SPECIFIC//////////////////////////////////////////////////////////////////////////
            snprintf(playerTurn, 64, "It is player %d turn\nMake a word from: ", playerTacker);
            strncat(playerTurn, &charHolder, 1);
            strcat(test, playerTurn);
            strcat(test, newLine);
            printf("%s", playerTurn);
            bzero(playerTurn, 64);
            /////////////////////////////////////////////////////////////////////////////////////////
            printf("It is now player %d turn\n", playerTacker);
            printf("Make a word from %c\n", charHolder);

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
void MainGameLoopSingle(int client_socket){

    bool cont = true;
    bool one = false;
    bool two = true;
    bool three = true;
    bool twopass = false;


    //////////////////////////////////////////////////
    strcpy(test, "Your set of alphabets is: ");
    strcat(test, userInput);
    ////////////////////////////////////////////////

    printf("Your set of alphabets is %s\n", userInput);
    randAlphabetPickerSinglePlayer(client_socket); //starts game

    while(cont){

        //changes whos turn it is
        if(playerTacker==1)playerTacker=2;
        else playerTacker=1;

        // if its the servers turn
        if(playerTacker==2){
            // FOR SERVER///////////////////////////////////////////////////////////////
            char serverTurn[50] = "It is now the servers turn ";
            strcat(test, serverTurn);
            strcat(test, newLine);
            bzero(serverTurn, 50);
            ///////////////////////////////////////////////////////////////////////////
            printf("It is now the servers turn\n");
            getWordFromtxtServerPlayer(client_socket);
        }
        else{
            //FOR SERVER ////////////////////////////////////////////////////////////////
            char playerTurn[64];
            snprintf(playerTurn, 64, "It is now player %d turn\nMake a word from: ", playerTacker);
            strcat(playerTurn, userInput);
            strcat(test, playerTurn);
            strcat(test, newLine);
            write(client_socket, test, strlen(test));
            bzero(playerTurn, 64);
            //printf("%s", test);
            bzero(test, 1024);
            read(client_socket, test, 1024);
            bzero(newInput, 1024); 
            strcpy(newInput, test);
            bzero(test, 1024);
            ////////////////////////////////////////////////////////////////////////////
            printf("It is now player %d turn\n", playerTacker);
            printf("Make a word from %s\n", userInput);
            //scanf("%s", newInput);
            printf("\n");


        // checks if the input was "pass'
        twopass = passCheck(client_socket);

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
void getWordFromtxtServerPlayer(int client_socket){
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


    //used for server
    char serverWords[64];

    // this if loop if for if it found a word that works
    if(foundWord==false && found2 ==1){
        counting++;
        //server test/////////////////////////////////////
        strcpy(serverWords, "Servers word is: ");
        strcat(test, serverWords);
        strcat(test, newInput);
        strcat(test, newLine);
        bzero(serverWords, 64);
        /////////////////////////////////////////////////
        printf("Servers word is: %s\n", newInput);
        strcpy(userInput, newInput);
        strcpy(usedWords[wordCount],newInput);
        wordCount++;
    }
    // if the server cant find a word
    else{
    //server test/////////////////////////////////////
    strcpy(serverWords, "Server had to pass.");
    strcat(test, serverWords);
    strcat(test, newLine);
    bzero(serverWords, 64);
    /////////////////////////////////////////////////
    printf("Server had to pass\n");
        strcpy(newInput,pass);
        twoPasses++;
        serverPass=true;


    }
    // if player passes and server has to pass
    if(twoPasses==2){
        bothPassCount++;
        if(bothPassCount==2){// if the server and player hav both passed 2 times in a row
            //server test/////////////////////////////////////
            strcpy(serverWords, "Both Players have passed 2 times in a row. Game Over.");
            strcat(test, serverWords);
            strcat(test, newLine);
            bzero(serverWords, 64);
            /////////////////////////////////////////////////
            printf("Both players have passed 2 time in a row. Game over\n");

            winner(client_socket);
        }
        else{// resets if 2 passes and its not 2 times in a row
            twoPasses=0;
            randAlphabetPickerSinglePlayer(client_socket);
        }
    }

    if(!serverPass){
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
      fclose(inputFile);
}


void randAlphabetPicker(int client_socket){  // pick random char at start of the game and random player multiplayer only
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

    //CHANGES TO COMMUNICATE WITH SERVER/////////////////////////////////////////////////////////////////////////
    char playerTurn[64];
    snprintf(playerTurn, 64, "Starting player is %d turn\nMake a word from: ", playerTacker);
    strncat(playerTurn, &charHolder, 1);
    strcat(test, playerTurn);
    strcat(test, newLine);
    bzero(playerTurn, 64);
    //read(client_socket, test, 1024);
    //strcpy(newInput, test);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    printf("starting player is %d \n", playerTacker);
    printf("Make a word from %c\n", charHolder);

    //Changes userInput to alphabets holder
    for(int i=0; i<strlen(alphabets);i++){
        userInput[i]=alphabets[i];
    }

    //starting first word here
    while(!one){
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        bzero(test, 1024);
        read(client_socket, test, 1024);
        strcpy(newInput, test);
        bzero(test, 1024);
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        //scanf("%s", newInput);
        printf("\n");

        // checks if the input was "pass'
        pass = PassCheckerForRandalph(client_socket);

        if(!pass){
            twoPasses =0;

            two = checkIfWordUsed();
            // makes sure letter user inputed are in the word
            if(!two) one = availableLettersChecker();

            //checks if userInput is in dictionary.txt
            if(one) three = check_dict();
            if(!three) one = false;
        }
        if(!one &&! pass){
        //printf("hi");
            if(playerTacker==1)playerTacker=2;
            else playerTacker=1;
            //////////////////////////////////////////////////////////////////////////////////////////////
            snprintf(playerTurn, 64, "It is now player %d turn\nMake a word from: ", playerTacker);
            strcat(playerTurn, userInput);
            strcat(test, playerTurn);
            strcat(test, newLine);
            bzero(playerTurn, 64);
            ///////////////////////////////////////////////////////////////////////////////////////////////
            printf("It is now player %d turn\n", playerTacker);


            printf("Make a word from %c\n", charHolder);

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
    randAlphabetPicker(0); //starts game

    while(cont){
/* not done yet
        if(pid==0){
            while(playerTacker==1){
            //waiting
            }
        }
        if(pid!=0){
            while(playerTacker==2){
            //waiting
            }
        }
*/
        //changes whos turn it is
        if(playerTacker==1)playerTacker=2;
        else playerTacker=1;

        printf("It is now player %d turn\n", playerTacker);
        printf("Make a word from %s\n", userInput);
        scanf("%s", newInput);
        printf("\n");

        // checks if the input was "pass'
        twopass = passCheck(0);

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
    //used for server
    char serverWords[64];
    len = sizeof(usedWords)/sizeof(usedWords[0]);

    for(int i =0; i<len; i++){
        if(!strcmp(usedWords[i], newInput)){
            //server test/////////////////////////////////////
            strcpy(serverWords, "This word has been used. Minus 2 Points");
            strcat(test, serverWords);
            strcat(test, newLine);
            bzero(serverWords, 64);
            /////////////////////////////////////////////////
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

//adds word to txt file
void addWordTotxt(){

    // posix here **********************************************************************
    int pid = fork();
    int child_status;

    if(pid==0){
        inputFile = fopen(file, "a");
        fprintf(inputFile, "%s\n", newInput);
        fclose(inputFile);
        exit(0);
    }
    else{
        waitpid(pid,&child_status,0);
    }


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
bool passCheck(int client_socket){
    int count = 0;
    char serverWords[64];
    char pass[4]= {'p','a','s','s'};
    for(int i=0; i <4; i++){// for passing
        if(newInput[i]==pass[i]){
            count++;
            if(count ==4){
                 //server test/////////////////////////////////////
                strcpy(serverWords, "Passing to the other player.");
                strcat(test, serverWords);
                strcat(test, newLine);
                bzero(serverWords, 64);
                /////////////////////////////////////////////////
                printf("passing to other player\n");
                i = 10;
                twoPasses++;

                if(twoPasses==2){// if both players pass
                    //server test/////////////////////////////////////
                    strcpy(serverWords, "Both players have passed - resetting.");
                    strcat(test, serverWords);
                    strcat(test, newLine);
                    bzero(serverWords, 64);
                    /////////////////////////////////////////////////
                    printf("both players have passed reseting\n");
                    bothPassCount++;
                    twoPasses=0;
                    // if your in single player moode menuOp = 1
                    if(menuOp==1){
                        randAlphabetPickerSinglePlayer(client_socket);
                    }
                    else{
                        randAlphabetPicker(0);
                    }
                    return true;
                }
                return true;
            }
        }
    }

    return false;
}
// menu display function
void menu(){
    /////////////////////////////////////////////////////////////////////////////////////////
    char* mainMenu = "\n1.    Single Player Mode\n2.    Multi-Player Mode\n3.    Exit\n \n";
    strcpy(test, mainMenu);
    ////////////////////////////////////////////////////////////////////////////////////////
    printf("\n1.    Single Player Mode\n");
    printf("2.    Multi-Player Mode\n");
    printf("3.    Exit\n \n");
    //scanf("%d", &menuOp);

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
    ///////////////////////////////////////////////////////
    strcat(test, "Using game file: ");
    strcat(test, file);
    strcat(test, newLine);
    /////////////////////////////////////////////////////
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
bool PassCheckerForRandalph(int client_socket){
    int count = 0;
    char pass[4]= {'p','a','s','s'};
    //used for server
    char serverWords[64];

    for(int i=0; i <4; i++){// for passing
        if(newInput[i]==pass[i]){
            count++;
            if(count==4){
                //server test/////////////////////////////////////
                strcpy(serverWords, "Passing to other player");
                strcat(test, serverWords);
                strcat(test, newLine);
                bzero(serverWords, 64);
                /////////////////////////////////////////////////
                //prints to server side
                printf("passing to other player\n");
                i = 10;
                twoPasses++;

            if(twoPasses==2){
                bothPassCount++;
                twoPasses =0;
            }

            if(bothPassCount ==2){
                //server test/////////////////////////////////////
                strcpy(serverWords, "Both players passed twice - game over.");
                strcat(test, serverWords);
                strcat(test, newLine);
                bzero(serverWords, 64);
                /////////////////////////////////////////////////
                printf("game over both players pasted two times");
                winner();
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

void winner(int client_socket){

    char serverWords[64];

    if(menuOp==2){
        if(score[1]>score[2]){
            printf("Player1 Wins");
            player1WonLoss=1;
            player2WonLoss=0;
        }
        else if (score[2]>score[1]){
            printf("Player2 Wins");
            player1WonLoss=0;
            player2WonLoss=1;
        }
        else{
            printf("You tied");
        }
    }

    if(menuOp==1){
        if(score[1]>score[2]){
            //server test/////////////////////////////////////
            strcpy(serverWords, "You won.");
            strcat(test, serverWords);
            strcat(test, newLine);
            bzero(serverWords, 64);
            /////////////////////////////////////////////////
            printf("You Won");
            player1WonLoss=1;
    }
        else if (score[2]>score[1]){
            //server test/////////////////////////////////////
            strcpy(serverWords, "Server wins.");
            strcat(test, serverWords);
            strcat(test, newLine);
            bzero(serverWords, 64);
            /////////////////////////////////////////////////
            printf("Server Wins");
            player1WonLoss=0;
        }
        else{
            //server test/////////////////////////////////////
            strcpy(serverWords, "You tied.");
            strcat(test, serverWords);
            strcat(test, newLine);
            bzero(serverWords, 64);
            /////////////////////////////////////////////////
            printf("You tied");
        }
    }

    if(menuOp==1){

    readScoreSinglePlayer(client_socket);

    }
    else if(menuOp==2){
        readScore();
    }
}
