#include <stdio.h>
#include <stdlib.h>

// creates the "video" files before test
void createRandomBernoulliFile(){
    int i = 0;
    for( i = 0; i < 10; i++){
        int randomLength = rand() % (6249000*2); // average is 6.249 M
        char buf[14];
        snprintf(buf, 14, "Videos/Video%d", i);
        FILE* current = fopen(buf,"w");
        int j = 0;
        for(j = 0; j < randomLength; j++){
            fputc( rand() % 128, current);
        }
        fclose(current);
    }

}

int main(int argc, char** argv[]){
    createRandomBernoulliFile();
    return 0;
}

