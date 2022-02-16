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
    struct sockaddress_in address;
    socklen_t address_size;
    char buffer[buffer_size];
    int n;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0){
        printf("socket is less than 0");
    }
    printf("Client socket created");

    memset(&address, '\0', sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(5998);
    address.sin_addr.s_addr = inet_addr("127.0.01");

    connect(sock, (struct sockaddress*)&address, sizeof(address));
    printf("Successfully connected to server");

    bzero(buffer, buffer_size);
    send(sock, buffer, strlen(buffer), 0);

    recv(sock, buffer, sizeof(buffer), 0);

    close(sock);
    printf("disconnected from server");

    return 0;
}
