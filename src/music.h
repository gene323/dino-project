#include <stdio.h>
#include <windows.h>
#include <MMsystem.h>
#include <conio.h>

void playMusic(){
    PlaySound(TEXT("C:\\Users\\gene\\code\\dino-project\\c8763.wav"), NULL, SND_SYNC);
    return ;
}

void playBackGroundMusic(){
    PlaySound(TEXT("C:\\Users\\gene\\code\\dino-project\\76u3o-ux9ue.wav"), NULL, SND_ASYNC);
    return ;
}