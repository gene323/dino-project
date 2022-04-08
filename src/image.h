#include <stdio.h>
#include <stdlib.h>

void showImage(){
    FILE *fp = fopen("../kirito.txt", "r");
    char image[150];
    while(fgets(image, sizeof(image), fp) != NULL){
        printf("%s", image);
    }
    puts("");
    fclose(fp);
}

void gameOverImage(){
    FILE *fp = fopen("../usodayo.txt", "r");
    char image[200];
    while(fgets(image, sizeof(image), fp) != NULL){
        printf("%s", image);
    }
    puts("");
    fclose(fp);
}