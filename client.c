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
    address.sin_port = htons(5999);
    address.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr*)&address, sizeof(address));
    printf("Successfully connected to server\n");
    printf("Type anything to begin \n");

    //while loop running when connected to server
    while(1) {
        bzero(buffer, buffer_size);
        
        
        scanf("%s", buffer);
        write(sock, buffer, strlen(buffer));
        bzero(buffer, buffer_size);

        read(sock, buffer, buffer_size);

        if(strcmp(buffer, "3") == 0) {
            printf("disconnected from server\n");
            close(sock);
            break;
        }

        printf("%s", buffer);
    }

    return 0;
}
