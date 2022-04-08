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
#define JUMPTIME 5
#define FPS 1.5

void printLine(char line[], int begin, int end);//display graphics
void displayAtFloor(char floor[], char ceiling[], int dino);
void displayAtCeiling(char floor[], char ceiling[], int dino);
void leftshift(char line[], int dino, bool pos);//let object move to left
void insertBox(char line[], int n);
bool isDead(char line[], int current, int dino, bool kiritoFlag);
void liftEnemy(char floor[], char ceiling[], int dino);
void killEnemy(char floor[]);
void gotoxy(int x, int y);

int main(){

    srand( time(0) );
    char ceiling[CANVAS];
    char floor[CANVAS];
    int dino = 6;
    
    for(int i=0; i<CANVAS; i++){
        floor[i] = '_';
        ceiling[i] = ' ';
    }

    //add object in graphics
    floor[CANVAS - 1] = 'X';
    int current = 1;
    int score = 0;
    int countDown = JUMPTIME;
    float sleeptime = FPS;
    int kiritoTime = 300;
    bool kiritoFlag = 0;

    system("cls");
    while(true){
        gotoxy(0, 0);//set cursor position
        printf("\e[?25l");//hide cursor
        char op = '1';
        if(kbhit()){
            op = getch();
        }
        if(op == ' '){
            if(current == 1){
                current = 2;
                countDown = JUMPTIME;
            }
        }
        else if(op == 'x' && kiritoFlag == 0){
            showImage();
            playMusic();
            kiritoFlag = 1;
            system("cls");
        }

        if(countDown){ --countDown; }
        if(!countDown){ current = 1; }
        if(kiritoFlag && kiritoTime){
            --kiritoTime;
            killEnemy(floor);
            sleeptime = 0.5;
        }
        else if(kiritoTime == 0){
            kiritoFlag = 0;
            kiritoTime = 300;
            sleeptime = FPS;
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

        //kiritoFlag == 0
        if(!kiritoFlag){ printf("Press [x] to trigger [starburst stream]\n"); }
        //kiritoFlag == 1
        else{ printf("Launching skill ...\n"); }
        printf("Your Score: %d", score);

        Sleep(sleeptime * 100);

        //0 represent floor
        //1 represent ceiling
        leftshift(floor, dino, 0);
        leftshift(ceiling, dino, 1);
        ++score;
    }
    system("pause");
    return 0;
}

void printLine(char line[], int begin, int end){
    size_t i = 0;
    for(i=begin; i<end; i++){
        if(line[i] == 'X'){
            //print red text
            printf("\033[31m");
            printf("X");
            printf("\033[0m");
        }
        else
            printf("%c", line[i]);
    }
}

void leftshift(char line[], int dino, bool pos){
    size_t i = 0;
    for(i=0; i<CANVAS; i++){
        line[i] = line[ i+1 ];
        if(line[i] == '?' && i < dino + 3)
            line[i] = '-';
        else if(line[i] == '-')
            line[i] = '_';
    }
    //pos = 0, line is floor
    //pos = 1, line is ceiling
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


    //print green text
    printf("\033[32m");
    printf("T");
    printf("\033[0m");
    printLine(floor, dino+1, CANVAS);

    printf("\n\n");
}

void displayAtCeiling(char floor[], char ceiling[], int dino){
    printf("\n\n\n\t");
    printLine(ceiling, 0, dino);

    //print green text
    printf("\033[32m");
    printf("T");
    printf("\033[0m");
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

void liftEnemy(char floor[], char ceiling[], int dino){
    for(int i=0; i<dino + 3; i++){
        if(floor[i] == 'X'){
            ceiling[i] = 'X';
            floor[i] = '_';
        }
    }
}

void killEnemy(char floor[]){
    int enemySum = 0;
    for(int i=0; i<CANVAS; i++){
        if(floor[i] == 'X'){ ++enemySum; }
    }

    if(enemySum >= 3){
        for(int i=0; i<CANVAS; i++){
            if(floor[i] == 'X'){
                floor[i] = '?';
            }
        }
    }
}
void gotoxy(int x, int y){
    printf("\033[%d;%dH", (y), (x));
}