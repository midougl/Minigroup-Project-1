/**
 * Group A
 * Brian Beach
 * 2/16/22
 * Game_Server Description:
 * Created a game server that should be able to connect to multiple clients (on the same machine I believe).  Used tcp/ip form 
 * where used socket/bind/listen/accept where socket creates a socket, bind beinds a socket to a given address information like port and ip,
 * listen will listen for clients and then if a client shows up to be connect, it is accepted. If accepted, checks to see if child process was
 * made with fork and will create a seperate response to the every child 
 * 
 * Need to change to posix message passing instead of send/rcv between client and server, but used that for now just to see if it works
 * Also need to actually add the game's once the posix message passing is added
 *
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

//#include "randomFile.h"
#include "Word_Game.c"

#define buffer_size 1024

int main() {
    /**used to test randomFile.h
    char *file = randomInputFile();
    printf("%s", file);
    **/

    //make string with big enough size for buffering and messages
    char server_mssg[buffer_size];

    //make child_pid for fork
    int child_Created;

    //create the socket
    int game_socket;
    game_socket = socket(AF_INET, SOCK_STREAM, 0);

    //check if socket was made
    if (game_socket < 0) {
        printf("Socket is less than 0");
    }
    printf("Server socket created\n");


    //give all address information for socket
    struct sockaddr_in game_address;
    game_address.sin_family = AF_INET;
    game_address.sin_port = htons(5998);                     //port address
    game_address.sin_addr.s_addr = inet_addr("127.0.0.1");   //server address


    int binded;
    //bind socket to address and port
    binded = bind(game_socket, (struct sockaddr*)&game_address, sizeof(game_address));

    //check for errors when binding
    if (binded < 0) {
        printf("Socket is NOT BINDED \n");
    }

    else {
            printf("Socket binded \n");
    }


    //listen for connections
    int listener;
    listener = listen(game_socket, 1);

    //check for listening errors
    if (listener == 0) {
        printf("Listening for client...\n");
    }
    else {
        printf("Error while listening\n");      
    }


    //client socket and struct
    int client_socket;
    struct sockaddr_in client_address;
    socklen_t client_address_size;          //<-- used for the accept function


    //while loop to use to connect to client(s)
    while (1) {
        //accept client
        client_socket = accept(game_socket, (struct sockaddr*)&client_address, &client_address_size);  //<-- check this one when using fork

        //printf("Child socket made\n");

        //if accepted child socket is less than zero for some reason, error
        if (client_socket < 0) {
            printf("socket not accepted\n");
            exit(1);
        }

        //fork child and see if it creates a child
        child_Created = fork();
        if (child_Created == 0) {
        close(game_socket);

        //******************************************** Server should be connected with child at this point**************************************
        //******************************************** Posix message passing belown here            **************************************
        while (1) {
            
            bzero(server_mssg, buffer_size);

            read(client_socket, server_mssg, buffer_size);
            printf("user entered %s\n", server_mssg);
            
            if(strcmp(server_mssg, "3") == 0) {
                printf("Disconnected from the server\n");
                break;
            }
            else if (strcmp(server_mssg, "2") == 0){
                printf("MultiPlayer Selected\n");
                //multiplayer 
            }
             else if (strcmp(server_mssg, "1") == 0){
               printf("SinglePlayer Selected\n");
               //single player
            }

            bzero(server_mssg, buffer_size);
            
            char* mainMenu = "\n1.    Single Player Mode\n2.    Multi-Player Mode\n3.    Exit\n \n";
            strcpy(server_mssg, mainMenu);
            printf("menu made\n");
            write(client_socket, server_mssg, buffer_size);
            
            

            
        }
    }

    }

    close(client_socket);


    return 0;

}
