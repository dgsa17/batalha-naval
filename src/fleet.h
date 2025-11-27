#ifndef FLEET_H
#define FLEET_H

#include <stdbool.h>

typedef struct Board Board;

typedef struct {
    int size;
    int hits;
    bool sunk;
} Ship;

typedef struct {
    Ship *ships;
    int count;
} Fleet;

void initFleet(Fleet *f);
bool allShipsDestroyed(Fleet *f);
bool canPlaceShip(Board *b, int r, int c, int size, bool horizontal);
void placeShip(Board *b, Fleet *f, int ship_id, int r, int c, bool horizontal);
void registerHit(Fleet *f, int ship_id);

#endif
