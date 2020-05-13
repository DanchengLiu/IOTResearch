// Client side
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <pthread.h>
#include <time.h>
#include <stdbool.h>
#include <sys/stat.h>
#define PORT 3000 
//passed in complexity
//in the first draft:
//assume every quest has greater than O(n) complexity
//try to offload every task
void *requestOffload(int sockID, int complexity){
    while(true){
        sleep(10);

        //get file information
        char file[14];
        char data[1024];
        //random file
        int randomFile = rand() % 10;
        snprintf(file,14, "Videos/Video%d", randomFile);
        struct stat st;
        stat(file, &st);
        int sizeOfFile = st.st_size;
        snprintf(data,1024,"%d,%d", complexity, sizeOfFile);
        send(sockID, data, 1024, 0);

    }
}


int main(int argc, char const *argv[]) 
{ 

    //socket initialization
    //attribute to https://www.geeksforgeeks.org/socket-programming-cc/
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char *hello = "Hello from client"; 
    char buffer[1024] = {0}; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 


/*---------------------------------------------------------------*/
//thread to communicate every ten seconds
    pthread_t work;
    pthread_create(&work, NULL, requestOffload(sock, 2), NULL);
    /*
    send(sock , hello , strlen(hello) , 0 ); 
    printf("Hello message sent\n"); 
    valread = read( sock , buffer, 1024); 
    printf("%s\n",buffer ); 
    */
    return 0; 
} 
