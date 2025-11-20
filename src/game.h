#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "board.h"
#include "fleet.h"
#include "io.h"

void initGame(Game *g);
void startGame(Game *g);
void doTurn(Game *g);
bool checkVictory(Game *g);

#endif
