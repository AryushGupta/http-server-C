#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main(){
    int server_fd;
    struct sockaddr_in address = {0};
    int client_fd;
    
    // Create the listening socket
    server_fd = socket(AF_INET , SOCK_STREAM , 0);
    if(server_fd < 0){
        printf("Socket creation failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Socket created successfully!\n");
    
    // when you're repeatedly stopping and restarting your server, you may encounter this error even after a clean shutdown because TCP can temporarily keep connection state around.
    int opt = 1;
    setsockopt(
        server_fd,
        SOL_SOCKET,
        SO_REUSEADDR,
        &opt,
        sizeof(opt)
    );

    // Configure and bind address details
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

    // Putting the socket into listening mode
    if(listen(server_fd , 5) < 0){
        perror("listen");
        return 1;
    }
    printf("Server is listening on port 8080\n");

    // Accept the incoming client connection
    client_fd = accept(server_fd , NULL , NULL);
    if(client_fd < 0){
        perror("Accept");
        return 1;
    }
    printf("Client connected!\n");

    while(1){
        char buffer[1024];
        int bytes_read = read(client_fd , buffer , sizeof(buffer)-1);
        if(bytes_read < 0){
            break;
        }else if(bytes_read == 0){
            printf("Client disconnected");
        }
        buffer[bytes_read] = '\0';
        printf("%s", buffer);

        char body[] = "<h1>Hello Client</h1>";
        char response[1024];
        int response_length = snprintf(
                                response,
                                sizeof(response),
                                "HTTP/1.1 200 OK\r\n"
                                "Content-Type: text/html\r\n"
                                "Content-Length: %zu\r\n"
                                "\r\n"
                                "%s",
                                strlen(body),
                                body
        );
        write(client_fd, response, response_length);
    }

    close(client_fd);
    return 0;
}