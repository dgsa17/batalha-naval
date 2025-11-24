#include <stdio.h>
#include <stdlib.h>
#include "fleet.h"
#include "board.h"

void initFleet(Fleet *f) {
    f->count = 4; //tipos de navios

    f->ships = malloc(f->count * sizeof(Ship));
    if (!f->ships) {
        fprintf(stderr, "Erro ao alocar frota.\n");
        exit(1);
    }

    //tamanhos dos navios
    int sizes[] = {5, 4, 3, 2};

    for (int i = 0; i < f->count; i++) {
        f->ships[i].size = sizes[i];
        f->ships[i].hits = 0;
        f->ships[i].sunk = false;
    }
}

//verjfjca se o navio vai caber na posição
bool canPlaceShip(Board *b, int r, int c, int size, bool horizontal) {

    //verifica se as células estão dentro dos limites
    if (horizontal) {
        if (c + size > b->cols) return false;
    } else {
        if (r + size > b->rows) return false;
    }

    // verifica se há colisão com outros navios
    for (int i = 0; i < size; i++) {
        int rr = horizontal ? r : r + i;
        int cc = horizontal ? c + i : c;

        Cell *cell = getCell(b, rr, cc);
        if (!cell || cell->state != CELL_WATER)
            return false;
    }

    return true;
}

//posiciona o navio no tabueleiro
void placeShip(Board *b, Fleet *f, int ship_id, int r, int c, bool horizontal) {

    int size = f->ships[ship_id].size;

    for (int i = 0; i < size; i++) {
        int rr = horizontal ? r : r + i;
        int cc = horizontal ? c + i : c;

        Cell *cell = getCell(b, rr, cc);
        cell->state = CELL_SHIP;
        cell->ship_id = ship_id;
    }
}

//registra que um navio foi atingido
void registerHit(Fleet *f, int ship_id) {
    Ship *s = &f->ships[ship_id];

    s->hits++;

    if (s->hits == s->size) {
        s->sunk = true;
        printf("Navio de tamanho %d AFUNDOU!\n", s->size);
    }
}
