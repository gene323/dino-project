#include <stdio.h>

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
