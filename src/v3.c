//unistd.h for linux or Mac 
//windows.h for windows
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>// for tcxxxattr, ECHO, etc ...
#include <time.h>
#include <stdbool.h>
#include <fcntl.h>

#define CANVAS 50

void printLine(char line[], int begin, int end);//display graphics
void displayAtFloor(char floor[], char ceiling[], int dino);
void displayAtCeiling(char floor[], char ceiling[], int dino);
void leftshift(char line[]);//let object move to left
int getch( void );
int kbhit( void );
void insertBox(char line[], int n);
void changemode(int dir);
bool isDead(char line[], int current, int dino);

int main(){

    srand( time(0) );

    char ceiling[CANVAS];
    char floor[CANVAS];
    int dino = 6;
    int sleeptime = 2;
    
    for(int i=0; i<CANVAS; i++){
        floor[i] = '_';
        ceiling[i] = ' ';
    }

    //add object in graphics
    floor[CANVAS - 1] = 'X';
    int current = 1;
    int countDown = 3;
    int score = 0;
    
    while(true){

        changemode(1);
        if(kbhit() && getch() == 32 && current == 1){
            current = 2;
            countDown = 3;
        }
        if(countDown){ --countDown; }
        if(!countDown){ current = 1; }

        if(score % 10 == 2){ insertBox(floor, 15); }
        if(isDead(floor, current, dino)){
            printf("Your Score: %d\n", score);
            printf("GAME OVER\n");
            break;
        }

        printf("Your Score: %d", score);
        if(current == 1){ displayAtFloor(floor, ceiling, dino); }
        else if(current == 2){ displayAtCeiling(floor, ceiling, dino); }

        usleep( sleeptime * 1000 * 100 );
        system("clear");
        leftshift( floor );
        ++score;
        changemode(0);
    }
    return 0;
}

void printLine(char line[], int begin, int end){

    size_t i = 0;
    for(i=begin; i<end; i++){
        printf("%c", line[i]);
    }
}

void leftshift(char line[]){

    size_t i = 0;
    for(i=0; i<CANVAS-1; i++){
        line[ i ] = line[ i+1 ];
    }
    line[ CANVAS-1 ] = '_';
}

int getch( void ){

    int ch;
    struct termios oldt, newt;
 
    tcgetattr(STDIN_FILENO, &oldt);
    memcpy(&newt, &oldt, sizeof(newt));
    newt.c_lflag &= ~( ECHO | ICANON | ECHOE | ECHOK |
                        ECHONL | ECHOPRT | ECHOKE | ICRNL);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
 
    return ch;
}

int kbhit( void ){
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF){
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

void insertBox(char line[], int n){
    int r = rand() % n;
    if(line[ CANVAS-r ] == 'X')
        ++r;
    line[ CANVAS-r-1 ] = 'X';
}

void changemode(int dir){
    static struct termios oldt, newt;
    if(dir == 1){
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    }
    else
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
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
bool isDead(char line[], int current, int dino){
    if(line[dino] == 'X' && current == 1)
        return 1;
    return 0;
}
