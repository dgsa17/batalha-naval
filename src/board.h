#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

// O estado de uma célula no tabuleiro.
// Usar para marcar erros, acertos e verificar navios.
typedef enum {
    CELL_WATER,
    CELL_SHIP,
    CELL_HIT,
    CELL_MISS
} CellState; 

//O estadi de cada célula (água; návio; acerto; erro)
//O ID do návio, ou -1 se não tiver navio
//Usar isso para verificar se um tiro acertou o navio
typedef struct {
    CellState state;
    int ship_id; 
} Cell;

//Tabuleiro do jogo
typedef struct {
    int rows, cols;
    Cell *cells; 
} Board;

//Cria o tabuleiro vazio com todas as células como água
//Chamar essa função antes de iniciar o jogo
void initBoard(Board *b, int rows, int cols);

// Retorna true se (r,c) estiver dentro do tabuleiro 
int inBounds(Board *b, int r, int c);

// Retorna um ponteiro para a célula (r, c)
// Usar isso para verificar se um tiro acertou o návio
// Usar HIT para se acertar e Miss para quando errar
Cell *getCell(Board *b, int r, int c);

// Imprime o tabuleiro no terminal.
// Chamar isso a cada turno
void printBoard(Board *b, bool showShips);

// Libera memória do tabuleiro 
//Chamar no final do jogo
void freeBoard(Board *b);

#endif
