#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

typedef struct {
    int size;
    int hits;
    bool sunk;
} Ship;

typedef struct {
    Ship *ships;
    int count;
} Fleet;

typedef enum {
    CELL_WATER,
    CELL_SHIP,
    CELL_HIT,
    CELL_MISS
} CellState;

typedef struct {
    CellState state;
    int ship_id;
} Cell;

typedef struct Board {
    int rows, cols;
    Cell *cells;
} Board;

void initBoard(Board *b, int rows, int cols);
int inBounds(Board *b, int r, int c);
Cell *getCell(Board *b, int r, int c);
int shootCell(Board *target, Board *shots, Fleet *fleet, int r, int c);
void printBoard(Board *b, bool showShips);
void freeBoard(Board *b);

#endif
