#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(){
    int server_fd;
    
    server_fd = socket(AF_INET , SOCK_STREAM , 0);

    if(server_fd == -1){
        printf("Socket creation failed\n");
        return 1;
    }

    printf("Socket created successfully!\n");


    return 0;
}