#ifndef GAME_H 
#define GAME_H 

#include <stdbool.h> 
#include "board.h"
#include "fleet.h"


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

// Estrutura para configurações
typedef struct {
    int board_size;
    char placement_mode; // 'A' para automático, 'M' para manual
} GameConfig;

// Funções do jogo
void initGame(Game *g, GameConfig *cfg); 
void startGame(Game *g, GameConfig *cfg); 
void doTurn(Game *g); 
bool checkVictory(Game *g); 

// Funções de posicionamento
void placeFleetManual(Board *b, Fleet *f, const char *nickname);
void placeFleetAuto(Board *b, Fleet *f);

#endif
