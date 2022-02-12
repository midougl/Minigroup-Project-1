#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define buffer_size 1024

int main() {

    //make string with big enough size for buffering and messages
    char server_mssg[buffer_size];

    //make child_pid for fork
    pid_t child_pid;

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
    listen(game_socket, 1);

    if (listen(game_socket, 1) == 0) {
        printf("Listening for client...\n");
    }
    else {
        printf("Error while listening\n");      //check for listening errors
    }


    //client socket and struct
    int client_socket;
    struct sockaddr_in client_address;
    socklen_t client_address_size;          //<-- used for the accept function


    while (1) {
        //accept client
        client_socket = accept(game_socket, (struct sockaddr*)&client_address, &client_address_size);  //<-- check this one when using fork

        //printf("Child socket made\n");

        //if accepted child socket is less than zero for some reason, error
        if (client_socket < 0) {
            printf("socket not accepted\n");
            exit(1);
        }

        //fork child pid to get multiple clients
        if ((child_pid = fork()) == 0) {
        close(game_socket);

        while (1) {
            recv(client_socket, server_mssg, buffer_size, 0);
            if(strcmp(server_mssg, "disconnect") == 0) {
                printf("Disconnected from the server\n");
                break;
            }
            else {
                printf("Client message - %s\n", server_mssg);
                send(client_socket, server_mssg, strlen(server_mssg), 0);
                bzero(server_mssg, buffer_size);
            }
        }
    }

    }

    close(client_socket);


    return 0;

}
