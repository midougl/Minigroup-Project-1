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

    int sock;
    struct sockaddr_in address;
    socklen_t address_size;
    char buffer[buffer_size];
    int n;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0){
        printf("socket is less than 0\n");
    }
    printf("Client socket created\n");

    memset(&address, '\0', sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(5998);
    address.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr*)&address, sizeof(address));
    printf("Successfully connected to server\n");

    //while loop running when connected to server
    while(1) {
        bzero(buffer, buffer_size);
        printf("******************MAIN MENU*****************\n");
        printf("1) Single player\n");
        printf("2) Multiplayer\n");
        printf("3) Exit\n");
        
        scanf("%s", buffer);
        send(sock, buffer, strlen(buffer), 0);

        recv(sock, buffer, sizeof(buffer), 0);

        if(strcmp(buffer, "dc") == 0) {
            printf("disconnected from server\n");
            close(sock);
            break;
        }

        printf("%s", buffer);
    }

    return 0;
}
