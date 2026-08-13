#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

// void send_http_response(int client_socket, const char *file_path){
//     // defining standard http response header
//     const char *http_header = 
//                 "HTTP/1.1 200 OK\r\n"
//                 "Content-Type: text/html\r\n"
//                 "Connection: close\r\n"
//                 "\r\n";
    
//     // send the header to the browser client
//     send(client_socket, http_header, strlen(http_header), 0);

//     // sending the requested html body to the client
//     FILE *html_file = fopen(file_path, "r");
//     if(html_file == NULL){
//         perror("Failed to open the file");
//         const char *error_msg = "<h1>404 file not found</h1>";
//         send(client_socket, error_msg, strlen(error_msg), 0);
//         return;
//     }

//     // streaming the file over the socket
//     char buffer[BUFFER_SIZE];
//     size_t bytes_read;

//     while((bytes_read = fread(buffer, 1, sizeof(buffer), html_file)) > 0){
//         send(client_socket, buffer, bytes_read, 0);
//     }

//     fclose(html_file);
// }

const char* get_mime_type(const char *file_path) {
    const char *dot = strrchr(file_path, '.');
    if (!dot) return "text/plain";
    
    if (strcmp(dot, ".html") == 0 || strcmp(dot, ".htm") == 0) return "text/html";
    if (strcmp(dot, ".css") == 0)  return "text/css";
    if (strcmp(dot, ".js") == 0)   return "text/javascript";
    // if (strcmp(dot, ".png") == 0)  return "image/png";
    // if (strcmp(dot, ".jpg") == 0 || strcmp(dot, ".jpeg") == 0) return "image/jpeg";
    
    return "text/plain";
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

    // Putting the socket into listening mode -> start waiting for incoming TCP connection requests
    if(listen(server_fd , 5) < 0){
        perror("listen");
        return 1;
    }
    printf("Server is listening on port 8080\n");

    // Accept the incoming client connection
    // Now how to make it handle mutliple clients at a same time(Parallelism)?
    client_fd = accept(server_fd , NULL , NULL);
    if(client_fd < 0){
        perror("Accept");
        return 1;
    }
    printf("Client connected!\n");

    // Interactive client-server communication
    while (1) {
        char buffer[BUFFER_SIZE];

        int bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);

        if (bytes_read < 0) {
            perror("read");
            break;
        } else if (bytes_read == 0) {
            printf("Client disconnected\n");
            break;
        }

        buffer[bytes_read] = '\0';

        // 1. EXTRACT PATH: Parse "GET /path HTTP/1.1" from buffer
        char method[16], path[256], protocol[16];
        if (sscanf(buffer, "%15s %255s %15s", method, path, protocol) < 2) {
            break; // Bad request line
        }

        // 2. MAP ROOT PATH: If path is "/", serve "index.html"
        char file_path[256];
        if (strcmp(path, "/") == 0) {
            strcpy(file_path, "index.html");
        } else {
            // Strip leading '/' (e.g., "/script.js" -> "script.js")
            strcpy(file_path, path + 1); 
        }

        // 3. READ THE REQUESTED FILE dynamically
        char body[8192];
        FILE *file = fopen(file_path, "rb"); // "rb" for safe binary/text reading
        
        if (file == NULL) {
            // Send 404 response if requested file doesn't exist
            const char *not_found = 
                "HTTP/1.1 404 Not Found\r\n"
                "Content-Length: 13\r\n"
                "Content-Type: text/plain\r\n"
                "\r\n"
                "404 Not Found";
            write(client_fd, not_found, strlen(not_found));
            continue; 
        }

        size_t body_length = fread(body, 1, sizeof(body) - 1, file);
        body[body_length] = '\0';
        fclose(file);

        // 4. GET MIME TYPE based on the actual file opened
        const char *content_type = get_mime_type(file_path);

        // 5. CONSTRUCT AND SEND HTTP RESPONSE
        char response[10240];
        int response_length = snprintf(
            response,
            sizeof(response),

            "HTTP/1.1 200 OK\r\n"
            "Content-Type: %s\r\n"
            "Content-Length: %zu\r\n"
            "Connection: keep-alive\r\n"
            "\r\n",

            content_type,
            body_length
        );

        // Send Header first, then Body
        write(client_fd, response, response_length);
        write(client_fd, body, body_length);
    }

    close(client_fd);
    return 0;
}