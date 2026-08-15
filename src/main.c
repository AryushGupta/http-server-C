#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

void send_response(int client_fd, const char *filename, const char *content_type)
{
    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        perror("fopen");
        return;
    }

    // Find the size of the file
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // HTTP response header
    char header[1024];

    int header_length = snprintf(
        header,
        sizeof(header),

        "HTTP/1.1 200 OK\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %ld\r\n"
        "\r\n",

        content_type,
        file_size
    );

    // Send the HTTP header
    write(client_fd, header, header_length);

    // Send the actual file
    char buffer[8192];

    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0){
        write(client_fd, buffer, bytes_read);
    }
    fclose(file);
}

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
    
    // when you're repeatedly stopping and restarting your server, we may encounter an error even after a clean shutdown because TCP can temporarily keep connection state around.So this code helps to stop the server when the client disconnects.
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

    // Putting the socket into listening mode -> start waiting for incoming TCP connection requests
    if(listen(server_fd , 5) < 0){
        perror("listen");
        return 1;
    }
    printf("Server is listening on port 8080\n");

    // Accept the incoming client connection
    client_fd = accept(server_fd , NULL, NULL);
    if(client_fd < 0){
        perror("Accept failed");
        return 1;
    }
    printf("Client connected!\n");

    // Interactive client-server communication
    while (1) {

        char buffer[1024];

        int bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);

        // Client request
        if (bytes_read < 0) {
            perror("read");
            break;
        } else if (bytes_read == 0) {
            printf("Client disconnected\n");
            break;
        } else {
            buffer[bytes_read] = '\0';
            printf("Client sent : %s\n", buffer);
            // Send response
            if (strncmp(buffer, "GET / HTTP", 10) == 0) {
                send_response(client_fd, "../public/index.html", "text/html");
            }
            else if (strncmp(buffer, "GET /style.css", 14) == 0) {
                send_response(client_fd, "../public/style.css", "text/css");
            }
            else if (strncmp(buffer, "GET /script.js", 14) == 0) {
                send_response(client_fd, "../public/script.js", "application/javascript");
            }
            else {
                printf("Unknown request\n");
            }
        }
    }
    // Close connection
    close(client_fd);

    return 0;
}