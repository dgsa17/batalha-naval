#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "fleet.h"

//verifica se o tamanho do tabuleiro é válido
void initBoard(Board *b, int rows, int cols) {
    
    if (rows <= 0 || cols <= 0) {
        fprintf(stderr, "initBoard: dimensões inválidas\n");
        exit(1);
    }

    //guarda as dimensões
    b->rows = rows;
    b->cols = cols;
    b->cells = malloc(rows * cols * sizeof(Cell));
    
    if (b->cells == NULL) {
        fprintf(stderr, "initBoard: erro ao alocar memória\n");
        exit(1);
    }

    //preenche todas as células como água
    for (int i = 0; i < rows * cols; i++) {
        b->cells[i].state = CELL_WATER;
        b->cells[i].ship_id = -1;
    }
}

//checa se as linhas e colunas estão dentro do tabuleiro
int inBounds(Board *b, int r, int c) {
    return (r >= 0 && r < b->rows && c >= 0 && c < b->cols);
}

Cell *getCell(Board *b, int r, int c) {
    if (!inBounds(b, r, c)) return NULL;
    return &b->cells[r * b->cols + c];
}

//impressão do tabuleiro
void printBoard(Board *b, bool showShips) {
    
    printf("   ");
    for (int c = 0; c < b->cols; c++) {
        printf("%2c", 'A' + c);
    }
    printf("\n");

    for (int r = 0; r < b->rows; r++) {
        printf("%2d ", r + 1);
        for (int c = 0; c < b->cols; c++) {
            Cell *cell = getCell(b, r, c);
            char symbol;
            switch (cell->state) {
                case CELL_WATER: symbol = '~'; break;
                case CELL_SHIP:  symbol = showShips ? 'S' : '~'; break;
                case CELL_HIT:   symbol = 'X'; break;
                case CELL_MISS:  symbol = 'o'; break;
                default: symbol = '?';
            }
            printf("%2c", symbol);
        }
        printf("\n");
    }
}

//libera memoria do tabuleiro
void freeBoard(Board *b) {
    if (b->cells != NULL) {
        free(b->cells);
        b->cells = NULL;
    }
}

//tiro
int shootCell(Board *target, Board *shots, Fleet *fleet, int r, int c) {

    Cell *alvo = getCell(target, r, c);
    Cell *tiro = getCell(shots, r, c);

    // segurança
    if (!alvo || !tiro) {
        printf("Coordenada inválida! Escolha uma posição dentro do tabueleiro.\n");
        return 0;
    }

    // se já atirou nessa posição
    if (tiro->state == CELL_HIT || tiro->state == CELL_MISS) {
        printf("Coordenazda iválida! Você já atirou nesse lugar.\n");
        return 0;
    }

    // se acertou um navio
    if (alvo->state == CELL_SHIP) {
        alvo->state = CELL_HIT;
        tiro->state = CELL_HIT;

        int id = alvo->ship_id;
        registerHit(fleet, id);

        if (fleet->ships[id].sunk)
            return 2;   // afundou

        return 1;       // apenas acertou
    }

    // se errou
    tiro->state = CELL_MISS;
    return 0;
}

