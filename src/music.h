#include <stdio.h>
#include <windows.h>
#include <MMsystem.h>
#include <conio.h>

void playMusic(){
    PlaySound(TEXT("..\\c8763.wav"), NULL, SND_SYNC);
}
