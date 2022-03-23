//unistd.h for linux or Mac 
//windows.h for windows
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>// for tcxxxattr, ECHO, etc ...
#include <time.h>
#include <fcntl.h>

#define CANVAS 50

void display(char line[], int start, int finish);//display graphics
void leftshift(char line[]);//let object move to left
int getch( void );
int kbhit( void );
void insertBox(char line[], int n);

int main(){

    srand( time(0) );

    char ceiling[CANVAS];
    char floor[CANVAS];
    int dino = 6;
    float sleeptime = 1;
    
    for(int i=0; i<CANVAS; i++){
        floor[i] = '_';
        ceiling[i] = ' ';
    }

    //add object in graphics
    floor[CANVAS - 1] = 'X';
    int current = 1;

    while( 1 ){

        if( kbhit() ){
            if(getch() == 32){
                current = 2;
            }
        }
        if(current == 1){
            printf("\n\n\n\t");
            display(ceiling, 0, CANVAS);

            printf("\n\t");
            display(floor, 0, dino);

            printf("T");
            display( floor, dino+1, CANVAS);

            printf("\n\n");
        }
        else if(current == 2){
            printf("\n\n\n\t");
            display(ceiling, 0, dino);

            printf("T");
            display(ceiling, dino-1, CANVAS);

            printf("\n\t");

            display(floor, 0, CANVAS);

            printf("\n\n");
        }
        sleep( sleeptime );
        system("clear");
        leftshift( floor );
        insertBox(floor, 15);
        current = 1;
    }
    return 0;
}

void display(char line[], int start, int finish){

    size_t i = 0;
    for(i=start; i<finish; i++){
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

int kbhit( void )
{
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

    if(ch != EOF)
    {
    ungetc(ch, stdin);
    return 1;
    }

    return 0;
}

void insertBox(char line[], int n){
    int r = rand() % n;
    line[ CANVAS-r-1 ] = 'X';
}
