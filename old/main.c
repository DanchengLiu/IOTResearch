#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>

int checkerPA = 0;
int checkerNA = 0;

/* detect miss */
int PAalarm = 0;
int NAalarm = 0;

int CA_length = 0;
int PA_length = 0;
int NA_length = 0;

/* every 10 second shuffer in a work */
/*
   void *sleepTimer(){
// set checker to 1 every 10 seconds
while(true){
wait(10);
if(checkerPA == 0){
checkerPA = 1;
}
else{
checkerPA = 1;
PAalarm  = 1;
}
if(checkerNA == 0){
checkerNA = 1;
}
else{
checkerNA = 1;
NAalarm = 1;
}
printf("cycle\n");
}
}
 */

// the tasks need to be changed
// discussion need on what exactly it is and how to schedule it
void *PAwork(FILE * input){
    if( checkerPA == 1 && PAalarm == 0 ){
        PA_length += 6;  
        // do the work with CA_length;

        printf("PA test. Thread executed. PA_length = %d\n", PA_length);
        // after that, change checkerPA to 0
        checkerPA = 0;
    }
    else if(PAalarm == 1){
        // add the work to wailist
        // miss a work
        PA_length += 12;
        // do the work

        // reset things
        checkerPA = 0;
        PAalarm = 0;
    }
    return 0;
}

void *NAwork(FILE * input){
    if( checkerNA == 1 && NAalarm == 0 ){
        NA_length += 6;  
        // do the work with CA_length;

        printf("NA test. Thread executed. NA_length = %d\n", NA_length);
        // after that, change checkerPA to 0
        checkerNA = 0;
    }
    else if(NAalarm == 1){
        // add the work to wailist
        // miss a work
        NA_length += 12;
        // do the work

        // reset things
        checkerNA = 0;
        NAalarm = 0;
    }
    return 0;
}

// I need to change it to sync.
// cause seg fault when unsync
int main(int argc, char** argv){
    pthread_t PA;
    pthread_t NA;
    /* notice: 
     * if PA and NA are using same processor, we need to combine them */
    /*pthread_t timer;

      pthread_create( &timer, NULL, sleepTimer, NULL);
      pthread_join( timer, NULL );
     */
        FILE* input = fopen(argv[1], "rw");
    while(true){
        if( input != NULL ){
            pthread_create( &PA, NULL, PAwork(input), NULL);

            pthread_create( &NA, NULL, NAwork(input), NULL);
        }
    }
    return 0;
}
