#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "main.h"

void readScore();
void readScoreSinglePlayer();


void readScore(){

    FILE *filesc = fopen("multiPlayer.txt", "r+");
    char *header = "First name	Last name	Country Score	Score   Win/lose     Number of Words Found 	Number of Words Added In The Dictionary ";
    char firsthold[1][20];
    char lasthold[1][20];
    char countryhold[1][20];
    char winhold[1][20];
    int foundhold[1];
    int addedhold[1];
    int scorehold[1];
    char firstName[32];
    char lastName[32];
    char Enteredcountry[32];
    char first[10][20];
    char last[10][20];
    char country[10][20];
    char win[10][20];
    int found[10];
    int added[10];
    int scoreb[10];
    int counter=0;

    // player 1 code starting here
    // gets what is already in the txt file
     while(fscanf(filesc, "%*[^\n]\n %s %s %s %d %s %d %d", firsthold[0], lasthold[0], countryhold[0], &scorehold[0],winhold[0], &foundhold[0], &addedhold[0]) !=EOF){

            for(int i=0; i<5; i++){
                strcpy(first[counter],firsthold[0]);
                strcpy(last[counter], lasthold[0]);
                strcpy(country[counter], countryhold[0]);
                strcpy(win[counter], winhold[0]);
                found[counter]=foundhold[0];
                added[counter]=addedhold[0];
                scoreb[counter]=scorehold[0];
            }
            counter++;
        }
/*
    //keep for testing

    for(int i=0; i<5; i++){
        printf("%s %s %s %d %s %d %d\n", first[i], last[i], country[i], scoreb[i], win[i], found[i], added[i]);

    }
    */

    printf("\n");
    int needToAdd1=0;
    int needToAdd2=0;
    int whatplace1=0;
    int whatplace2=0;
    char * lossWin="loss";

    // tells us what place the player should be on the board if at all
    for(int i=0; i<5; i++){
        if(score[1]>scoreb[i]){
            whatplace1++;
            needToAdd1=1;
        }
    }

    int whereToStart=0;
    whereToStart = 5-whatplace1;
    int n =0;

    // if we do need to be on the board this is were it starts
    if(needToAdd1==1){


        // gets info from player
         printf("Please enter first name\n");
         scanf("%s", firstName);
         printf("Please enter last name\n");
         scanf("%s", lastName);
         printf("Please enter country\n");
         scanf("%s", Enteredcountry);

        //sets the print out for the score if the player won or lost the game
         if(player1WonLoss==1){
            lossWin="win";
         }
         else{
            lossWin="loss";
         }

        fclose(filesc);

        //********************************************************************************************
        // forking here ********************************** to write to scoreboard files****************
        //********************************************************************************************

        int pid = fork();
        int child_status;

        if (pid==0){





        // clears the txt file so only the top 5 are there
        filesc = fopen("multiPlayer.txt", "w");//clears txt
        fprintf(filesc,"%s",header);

            for(int i=0; i<4; i++){
                if(i==whereToStart&&n==0){

                        // prints the current players info in the spot of the txt where it should be
                     fprintf( filesc,"\n%-18s%-18s%-14s%-8d%-20s%-40d%-10d"  ,firstName,lastName, Enteredcountry, score[1], lossWin,wordsFoundPlayer1 ,wordsAddPlayer1);
                     n=1;
                    i--;
                }
                else{
                // prints the other people that was in the txt already back to the txt file in the right order
                    fprintf(filesc,"\n%-18s%-18s%-14s%-8d%-20s%-40d%-10d", first[i], last[i], country[i], scoreb[i], win[i], found[i], added[i]);
                }
            }
            exit(0); // close child*******************************************************************
        }
        else {
            wait(pid, &child_status,0);

        }

    }


        // for player2 starting here///////////////////////   all comments for this code should be the same as above.
    fclose(filesc);
    filesc = fopen("multiPlayer.txt", "r+");

    counter=0;
     while(fscanf(filesc, "%*[^\n]\n %s %s %s %d %s %d %d", firsthold[0], lasthold[0], countryhold[0], &scorehold[0],winhold[0], &foundhold[0], &addedhold[0]) !=EOF){

        for(int i=0; i<5; i++){
            strcpy(first[counter],firsthold[0]);
            strcpy(last[counter], lasthold[0]);
            strcpy(country[counter], countryhold[0]);
            strcpy(win[counter], winhold[0]);
            found[counter]=foundhold[0];
            added[counter]=addedhold[0];
            scoreb[counter]=scorehold[0];
        }
        counter++;
    }

    for(int i=0; i<5; i++){
        if(score[2]>scoreb[i]){
            whatplace2++;
            needToAdd2=1;
        }
    }

    int whereToStart2=0;
    whereToStart2 = 5-whatplace2;
    int n2 =0;

    if(needToAdd2==1){

     printf("Please enter first name\n");
     scanf("%s", firstName);
     printf("Please enter last name\n");
     scanf("%s", lastName);
     printf("Please enter country\n");
     scanf("%s", Enteredcountry);

     if(player1WonLoss==1){
        lossWin="win";
     }
     else{
        lossWin="loss";
     }

    fclose(filesc);
    filesc = fopen("multiPlayer.txt", "w");//clears txt
    fprintf(filesc,"%s",header);

        for(int i=0; i<4; i++){
            if(i==whereToStart2&&n2==0){
                 fprintf(filesc, "\n%-18s%-18s%-14s%-8d%-20s%-40d%-10d"   ,firstName,lastName, Enteredcountry, score[2], lossWin,wordsFoundPlayer1 ,wordsAddPlayer1);
                 //printf( "\n%-18s%-18s%-14s%-8d%-20s%-40d%-10d"   ,firsttest,lastTest, countrytest, scoretest[2], lossWin,foundtest,dicttest);
                 n2=1;
                 i--;
            }
            else{
                fprintf(filesc,"\n%-18s%-18s%-14s%-8d%-20s%-40d%-10d" , first[i], last[i], country[i], scoreb[i], win[i], found[i], added[i]);
                //printf("\n%-18s%-18s%-14s%-8d%-20s%-40d%-10d" , first[i], last[i], country[i], scoreb[i], win[i], found[i], added[i]);
            }
        }
    }
     fclose(filesc);

    // for showing the new scoreboard
    filesc = fopen("multiPlayer.txt", "r+");

    // reads the txt file and stores the values
     while(fscanf(filesc, "%*[^\n]\n %s %s %s %d %s %d %d", firsthold[0], lasthold[0], countryhold[0], &scorehold[0],winhold[0], &foundhold[0], &addedhold[0]) !=EOF){

        for(int i=0; i<5; i++){
            strcpy(first[counter],firsthold[0]);
            strcpy(last[counter], lasthold[0]);
            strcpy(country[counter], countryhold[0]);
            strcpy(win[counter], winhold[0]);
            found[counter]=foundhold[0];
            added[counter]=addedhold[0];
            scoreb[counter]=scorehold[0];
        }
        counter++;
    }

    // shows the scoreboard to the user
    printf("\n");
    for(int i=0; i<5;i++){
        printf("%s %s %s %d %s %d %d\n" , first[i], last[i], country[i], scoreb[i], win[i], found[i], added[i]);
    }

    fclose(filesc);


    // wait for use to hit the enter key
    while(true){
        if (getchar() == '\n') {
            break;
        }
    }
    main();

}


void readScoreSinglePlayer(){

    FILE *filesc = fopen("singlePlayer.txt", "r+");
    char *header = "First name	Last name	Country Score	Score   Win/lose     Number of Words Found 	Number of Words Added In The Dictionary ";
    char firsthold[1][20];
    char lasthold[1][20];
    char countryhold[1][20];
    char winhold[1][20];
    int foundhold[1];
    int addedhold[1];
    int scorehold[1];
    char firstName[32];
    char lastName[32];
    char Enteredcountry[32];
    char first[10][20];
    char last[10][20];
    char country[10][20];
    char win[10][20];
    int found[10];
    int added[10];
    int scoreb[10];
    int counter=0;

    // player 1 code starting here
    // gets what is already in the txt file
     while(fscanf(filesc, "%*[^\n]\n %s %s %s %d %s %d %d", firsthold[0], lasthold[0], countryhold[0], &scorehold[0],winhold[0], &foundhold[0], &addedhold[0]) !=EOF){

            for(int i=0; i<5; i++){
                strcpy(first[counter],firsthold[0]);
                strcpy(last[counter], lasthold[0]);
                strcpy(country[counter], countryhold[0]);
                strcpy(win[counter], winhold[0]);
                found[counter]=foundhold[0];
                added[counter]=addedhold[0];
                scoreb[counter]=scorehold[0];
            }
            counter++;
        }
/*
    //keep for testing

    for(int i=0; i<5; i++){
        printf("%s %s %s %d %s %d %d\n", first[i], last[i], country[i], scoreb[i], win[i], found[i], added[i]);

    }
    */

    printf("\n");
    int needToAdd1=0;
    int whatplace1=0;
    char * lossWin="loss";

    // tells us what place the player should be on the board if at all
    for(int i=0; i<5; i++){
        if(score[1]>scoreb[i]){
            whatplace1++;
            needToAdd1=1;
        }
    }

    int whereToStart=0;
    whereToStart = 5-whatplace1;
    int n =0;

    // if we do need to be on the board this is were it starts
    if(needToAdd1==1){

        // gets info from player
         printf("Please enter first name\n");
         scanf("%s", firstName);
         printf("Please enter last name\n");
         scanf("%s", lastName);
         printf("Please enter country\n");
         scanf("%s", Enteredcountry);

        //sets the print out for the score if the player won or lost the game
         if(player1WonLoss==1){
            lossWin="win";
         }
         else{
            lossWin="loss";
         }

        fclose(filesc);
        // clears the txt file so only the top 5 are there
        filesc = fopen("singlePlayer.txt", "w");//clears txt
        fprintf(filesc,"%s",header);

            for(int i=0; i<4; i++){
                if(i==whereToStart&&n==0){

                        // prints the current players info in the spot of the txt where it should be
                     fprintf( filesc,"\n%-18s%-18s%-14s%-8d%-20s%-40d%-10d"  ,firstName,lastName, Enteredcountry, score[1], lossWin,wordsFoundPlayer1 ,wordsAddPlayer1);
                     n=1;
                    i--;
                }
                else{
                // prints the other people that was in the txt already back to the txt file in the right order
                    fprintf(filesc,"\n%-18s%-18s%-14s%-8d%-20s%-40d%-10d", first[i], last[i], country[i], scoreb[i], win[i], found[i], added[i]);
                }
            }
        }


    // shows the scoreboard to the user
    printf("\n");
    for(int i=0; i<5;i++){
        printf("%s %s %s %d %s %d %d\n" , first[i], last[i], country[i], scoreb[i], win[i], found[i], added[i]);
    }

    fclose(filesc);


    // wait for use to hit the enter key
    while(true){
        if (getchar() == '\n') {
            break;
        }
    }
    main();

}


