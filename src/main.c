#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main(){
    int server_fd;
    struct sockaddr_in address = {0};
    int client_fd;
    
    // Creating the Socket file descriptor
    server_fd = socket(AF_INET , SOCK_STREAM , 0);
    if(server_fd < 0){
        printf("Socket creation failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Socket created successfully!\n");
    
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    // address.sin_addr.s_addr = INADDR_ANY;
    inet_pton(AF_INET , "127.0.0.1" , &address.sin_addr);

    if(bind(server_fd, (struct sockaddr *)&address , sizeof(address)) < 0){
        perror("Bind Failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Bind successful\n");

    if(listen(server_fd , 5) < 0){
        perror("listen");
        return 1;
    }

    printf("Server is listening on port 8080\n");

    client_fd = accept(server_fd , NULL , NULL);
    if(client_fd < 0){
        perror("Accept");
        return 1;
    }

    printf("Client connected!\n");

    return 0;
}