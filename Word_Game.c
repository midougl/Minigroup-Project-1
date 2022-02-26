/**
 * Group A
 * Brian Beach / Samuel Fipps
 * 2/16/22
 * 
 * Word_Game.c  Description:
 * Brian - made a game that took input file x (randomly generated from randomFile.h) and has the player create a word from those letters
 * The game then determines if the word is valid (checks if only given letters were used). If so, adds score and goes to next part where player
 * needs to make the word from the ending of the previously used word. Goes until the player messes up
 * 
 * Samuel - turned parts of the game into seperate functions (availableLetters, endOfWord) so that the game can be changed up when we create
 * a single_player and multi_player options. Added score.h to be able to keep correct scoring system.
 * 
 * Still things needed to be done -ex: create array to keep previously used words, turn word_game into two seperate games for single player and 
 * multi player
 **/


#include "main.h"
#include "randomFile.h"
#include "dictionary_Check.h"
#include "score.h"
#include "scoreBoard.h"
#include "gameRules.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <sys/wait.h>

#define SERVER_QUEUE_NAME   "/sp-example-server"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10

int game_main() {

    //readScore();  // for testing

    // calls menu function
    menu();

    //gets word from txt file
    getWordFromTxt();

    if(menuOp==1){
        // starts game
        //MainGameLoopSingle();
    }
    if(menuOp==2){ // for multiplayer
        //MainGameLoop();
    }

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
    //******************************************************************************************************************
    // starting posix
    //******************************************************************************************************************
    if(contToDict){


        int pid = fork(); // fork to make a child

        if(pid==0){ // child
            // what used to be here
            contToDict = dictionary(newInput);
            exit(0);
        }
        else if(pid <0){
            printf("pid failed");
            exit(1);
        }

        else{ //parent

            // wait for child to finish
            int child_status;
            waitpid(pid, &child_status, 0);

            // posix set up
            mqd_t qd_server;
            struct mq_attr attr;
            attr.mq_flags = 0;
            attr.mq_maxmsg = MAX_MESSAGES;

            attr.mq_msgsize = MAX_MSG_SIZE;
            attr.mq_curmsgs = 0;
            char in_buffer [MSG_BUFFER_SIZE];
            //end of posix set up

            // opens the server
            if ((qd_server = mq_open (SERVER_QUEUE_NAME, O_RDONLY | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1) {
                perror ("Server: mq_open (server)");
                exit (1);
            }

            // waits until it gets message
          //  while (1) {
                // get the oldest message with highest priority
                if (mq_receive (qd_server, in_buffer, MSG_BUFFER_SIZE, NULL) == -1) {

                    printf("error\n");

                    perror ("Server: mq_receive");


                    exit (1);
                }
                else{

                    // if the function said it was found in dict it sends a t
                    if(in_buffer[0]=='t'){
                        // so then set it true"
                        foundInDic= true;
                        addWordTotxt();
/*
                        if (mq_close (qd_server) == -1) {
                            perror ("Server: mq_close");
                            exit (1);
                        }
*/

                        return true;
                    }
                    else {
                        // if not then set it false
                        foundInDic= false;
                        printf("%s is not accepted in the given dictionary\n", newInput);
                        printf("Penalized 1 point\n");
                        score[playerTacker] = score[playerTacker] -1;
/*
                        if (mq_close (qd_server) == -1) {
                            perror ("Server: mq_close");
                            exit (1);
                        }
*/
                        return false;
                    }
                    //end the loop because message was got
                  //  break;
                }
/*
                if (mq_close (qd_server) == -1) {
                    perror ("Server: mq_close");
                    exit (1);
                }
*/
        }
    }

    // what was replaced ************************************************************************************************


// end of posix**********************************************************************************************************

/*
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
    */





    if(!contToDict){
        return true;
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
