#ifndef FLEET_H
#define FLEET_H

#include <stdbool.h>
#include "board.h"

typedef struct {
    int size;      // tamanho do navio
    int hits;      // quantas partes foram atingidas
    bool sunk;     // true se afundou
} Ship;

typedef struct {
    Ship *ships;   // vetor de navios
    int count;     // quantidade de navios
} Fleet;

void initFleet(Fleet *f);
bool canPlaceShip(Board *b, int r, int c, int size, bool horizontal);
void placeShip(Board *b, Fleet *f, int ship_id, int r, int c, bool horizontal);
void registerHit(Fleet *f, int ship_id);

#endif
