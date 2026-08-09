#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080

int main(){
    int server_fd;
    struct sockaddr_in address;
    
    // Creating the Socket file descriptor
    server_fd = socket(AF_INET , SOCK_STREAM , 0);
    if(server_fd < 0){
        printf("Socket creation failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Socket created successfully!\n");
    
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = INADDR_ANY;
    printf("server_fd = %d\n", server_fd);
    printf("sin_family = %d\n", address.sin_family);
    printf("sin_port = %d\n", ntohs(address.sin_port));
    printf("sin_addr = %u\n", address.sin_addr.s_addr);
    printf("address size = %zu\n", sizeof(address));

    if(bind(server_fd, (struct sockaddr *)&address , sizeof(address)) < 0){
        perror("Bind Failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Bind successful\n");
    close(server_fd);

    return 0;
}