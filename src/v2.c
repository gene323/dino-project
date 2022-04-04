//unistd.h for linux or Mac 
//windows.h for windows
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define CANVAS 50

void display(char line[], int start, int finish);//display graphics
void leftshift(char line[], int start, int finish);//let object move to left
void hop(char ceiling[], char floor[], int dino);//dino jump

int main(){

    char ceiling[CANVAS];
    char floor[CANVAS];
    int dino = 6;
    float sleeptime = 1;
    
    for(int i=0; i<CANVAS; i++){
        floor[i] = '_';
        ceiling[i] = ' ';
    }
    //add dino in graphics
    floor[dino] = 'T';
    //add object in graphics
    floor[CANVAS - 1] = 'X';

    while(floor[dino+1] != 'X'){
        printf("\n");
        system("clear");
        printf("\n\n\n\t");
        display(ceiling, 0, CANVAS);

        printf("\n\t");
        display(floor, 0, CANVAS);

        leftshift(floor, dino+1, CANVAS);
        sleep(sleeptime);
    }
    return 0;
}

void display(char line[], int start, int finish){
    for(int i=start; i<finish; i++){
        printf("%c", line[i]);
    }
}

void leftshift(char line[], int start, int finish){
    for(int i=start; i<finish; i++){
        (i != finish-1)? (line[i] = line[i+1]) : (line[i] = '_');
    }
}
void hop(char ceiling[], char floor[], int dino){
    ceiling[dino] = 'T';
    floor[dino] = '_';
}
