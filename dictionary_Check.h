#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "main.h"
#include <time.h>
#include <unistd.h>





// posix stuff
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define SERVER_QUEUE_NAME   "/sp-example-server"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10
// posix stuff end



int dictionary(char* userInput) {
    FILE* file;
    int buffer = strlen(userInput)+1;
    char dictionaryWord[buffer];
    char wordCheck[buffer];
    int dictCount =0;



    char temp[5];

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
            //foundInDic= true;    **** this is what was reaplaced ****
            fclose(file);

            // starts of posix stuff ***********************************************************************
            strcpy(temp, "t");    // was replaced with this
            //return true;         **** this is what was reaplaced ****
        }
    }
    fclose(file);

    // if it wasn't true then set it to f for false
    if(temp[0]!='t'){
        strcpy(temp, "f");
    }

    //posix setup stuff ******************************************************
    char client_queue_name [64];
    mqd_t qd_server, qd_client;   // queue descriptors
    sprintf (client_queue_name, "/sp-example-client-%d", getpid ());

    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    // end of setup stuff ****************************************************

    // opens the connections


    if ((qd_client = mq_open (client_queue_name, O_RDONLY | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1) {
        perror ("Client: mq_open (client)");
        exit (1);
    }

    if ((qd_server = mq_open (SERVER_QUEUE_NAME, O_WRONLY)) == -1) {
        perror ("Client: mq_open (server)");
        exit (1);
    }

    // sends the message
    if (mq_send (qd_server, temp, strlen (client_queue_name), 0) == -1) {
        perror ("Client: Not able to send message to server");
        exit(1);
    }

    // close the message
    if (mq_close (qd_server) == -1) {
        perror ("Client: mq_close");
        exit (1);
    }

    // close the message
    if (mq_close (qd_client) == -1) {
        perror ("Client: mq_close");
        exit (1);
    }

    // closes the message


fclose(file);
exit(0);  // make sure the child exit very impormant!!!!!!!!!!!!!!!

   // fclose(file); // what was replaced!!!!!!!!
    //return false;

// end of posix ***************************************************************************************



}
