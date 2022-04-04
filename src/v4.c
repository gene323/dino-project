//unistd.h for linux or Mac 
//windows.h for windows
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <stdbool.h>
#include <fcntl.h>
#include <conio.h>
#include "music.h"
#include "image.h"

#define CANVAS 50

void printLine(char line[], int begin, int end);//display graphics
void displayAtFloor(char floor[], char ceiling[], int dino);
void displayAtCeiling(char floor[], char ceiling[], int dino);
void leftshift(char line[], bool pos);//let object move to left
void insertBox(char line[], int n);
bool isDead(char line[], int current, int dino, bool kiritoFlag);
void killEnemy(char floor[], char ceiling[], int dino);

int main(){

    srand( time(0) );
    char ceiling[CANVAS];
    char floor[CANVAS];
    int dino = 6;
    float sleeptime = 2;
    
    for(int i=0; i<CANVAS; i++){
        floor[i] = '_';
        ceiling[i] = ' ';
    }

    //add object in graphics
    floor[CANVAS - 1] = 'X';
    int current = 1;
    int countDown = 3;
    int score = 0;
    int kiritoTime = 300;
    bool kiritoFlag = 0;

    while(true){
        char op = '1';
        if(kbhit()){
            op = getch();
        }
        if(op == ' '){
            if(current == 1){
                current = 2;
                countDown = 3;
            }
        }
        else if(op == 'x' && kiritoFlag == 0){
            showImage();
            playMusic();
            kiritoFlag = 1;
        }
        if(countDown){ --countDown; }
        if(!countDown){ current = 1; }
        if(kiritoFlag && kiritoTime){
            --kiritoTime;
            killEnemy(floor, ceiling, dino);
            sleeptime = 0.1;
        }
        else if(kiritoTime == 0){
            kiritoFlag = 0;
            kiritoTime = 300;
            sleeptime = 2;
        }

        if(score % 10 == 2){ insertBox(floor, 15); }
        if(isDead(floor, current, dino, kiritoFlag)){
            gameOverImage();
            printf("Your score: %d\n", score);
            printf("GAME OVER\n");
            break;
        }

        if(current == 1){ displayAtFloor(floor, ceiling, dino); }
        else if(current == 2){ displayAtCeiling(floor, ceiling, dino); }
        printf("Your Score: %d", score);

        Sleep(sleeptime * 100);
        system("cls");
        leftshift(floor, 0);
        leftshift(ceiling, 1);
        ++score;
    }
    return 0;
}

void printLine(char line[], int begin, int end){
    size_t i = 0;
    for(i=begin; i<end; i++){
        printf("%c", line[i]);
    }
}

void leftshift(char line[], bool pos){
    size_t i = 0;
    for(i=0; i<CANVAS-1; i++){
        line[i] = line[ i+1 ];
    }
    if(!pos)
        line[ CANVAS-1 ] = '_';
    else if(pos)
        line[ CANVAS-1 ] = ' ';
}

void insertBox(char line[], int n){
    int r = rand() % n;
    if(line[CANVAS - r - 1] == 'X' || line[CANVAS - r + 1] == 'X')
        return insertBox(line, n);
    line[CANVAS - r] = 'X';
}

void displayAtFloor(char floor[], char ceiling[], int dino){
    printf("\n\n\n\t");
    printLine(ceiling, 0, CANVAS);

    printf("\n\t");
    printLine(floor, 0, dino);

    printf("T");
    printLine(floor, dino+1, CANVAS);

    printf("\n\n");
}

void displayAtCeiling(char floor[], char ceiling[], int dino){
    printf("\n\n\n\t");
    printLine(ceiling, 0, dino);

    printf("T");
    printLine(ceiling, dino-1, CANVAS);

    printf("\n\t");
    printLine(floor, 0, CANVAS);

    printf("\n\n");
}
bool isDead(char line[], int current, int dino, bool kiritoFlag){
    if(line[dino] == 'X' && current == 1 && !kiritoFlag)
        return 1;
    return 0;
}

void killEnemy(char floor[], char ceiling[], int dino){
    for(int i=0; i<dino + 3; i++){
        if(floor[i] == 'X'){
            ceiling[i] = 'X';
            floor[i] = '_';
        }
    }
}
