#ifndef IO_H
#define IO_H
#include <stdio.h>   
#include <ctype.h>   
#include <string.h>  
#include "game.h" 


int mainMenu();
void readNickname(char *buf, int size);
int readBoardSize();
char readPlacementMode();
void readCoordinate(const char *prompt, int *r, int *c);
void showResultMessage(int hit);


void readConfig(GameConfig *cfg);

#endif 
