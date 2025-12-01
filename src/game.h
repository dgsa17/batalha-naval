#ifndef GAME_H 
#define GAME_H 

#include <stdbool.h> 
#include "board.h"
#include "fleet.h"
#include "io.h"

// Definições de estruturas
typedef struct {
    char nickname[32];
    Board board;
    Board shots;
    Fleet fleet;
} Player;

typedef struct {
    Player p1;
    Player p2;
    int current_player;
    int game_over;
} Game;

void initGame(Game *g); 
void startGame(Game *g); 
void doTurn(Game *g); 
bool checkVictory(Game *g); 

// Funções de posicionamento
void placeFleetManual(Board *b, Fleet *f, const char *nickname);
void placeFleetAuto(Board *b, Fleet *f);

#endif
