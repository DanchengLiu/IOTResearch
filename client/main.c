// Client side
#include <stdio.h> 
#include <stdlib.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <pthread.h>
#include <time.h>
#include <stdbool.h>
#include <sys/stat.h>
#define PORT 3000 

#include <netinet/in.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close


void doOffload( int sockID, int fileID ){
    // not yet sure if we actually want anything in here
    // offloading technique is unknown yet
    printf("Offload\n");
}

void doLocal( int fileID ){
    // not implemented yet
    printf("DO it local\n");
}



//passed in complexity
//in the first draft:
//assume every quest has greater than O(n) complexity
//try to offload every task
void *requestOffload(int sockID, int complexity){
    while(true){
        // I am thinking about switching this to a posix timer if this does not         // work as expected.
        sleep(10);

        //get file information
        char file[14];
        char data[1024];
        char instruction[3];
        //random file
        int randomFile = rand() % 10;
        snprintf(file,14, "Videos/Video%d", randomFile);

        struct stat st;
        stat(file, &st);
        int sizeOfFile = st.st_size;

        snprintf(data,1024,"%d,%d,10", complexity, sizeOfFile);
        send(sockID, data, 1024, 0);
        printf("Random file %d descriptor sent\n", randomFile);
        read(sockID, instruction, 3);
        printf("Permission received: %s\n", instruction);
        if(strcmp(instruction,"yes") == 0){
            doOffload(sockID, randomFile);
        }
        else{
            doLocal(randomFile);
        }
    }
}



int main(int argc, char const *argv[]) 
{ 
    int sock = 0; 
    struct sockaddr_in serv_addr; 
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
    char greeting[1024];
    read(sock, greeting, 1024);
    printf("Greeting message received: %s\n", greeting);
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
    close(sock);
    pthread_exit(NULL);

}

