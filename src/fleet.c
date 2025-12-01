#include <stdio.h>
#include <stdlib.h>
#include "fleet.h"
#include "board.h"

void initFleet(Fleet *f) {
    f->count = 6; //tipos de navios: 1x5, 1x4, 2x3, 2x2

    f->ships = malloc(f->count * sizeof(Ship));
    if (!f->ships) {
        fprintf(stderr, "Erro ao alocar frota.\n");
        exit(1);
    }

    //tamanhos dos navios: 1x5, 1x4, 2x3, 2x2
    int sizes[] = {5, 4, 3, 3, 2, 2};

    for (int i = 0; i < f->count; i++) {
        f->ships[i].size = sizes[i];
        f->ships[i].hits = 0;
        f->ships[i].sunk = false;
    }
}

//verifica se o navio vai caber na posição
bool canPlaceShip(Board *b, int r, int c, int size, bool horizontal) {

    //verifica se as células estão dentro dos limites
    if (horizontal) {
        if (c + size > b->cols) return false;
    } else {
        if (r + size > b->rows) return false;
    }

    //verifica se houve colisão com outros navios
    for (int i = 0; i < size; i++) {
        int rr = horizontal ? r : r + i;
        int cc = horizontal ? c + i : c;

        Cell *cell = getCell(b, rr, cc);
        if (!cell || cell->state != CELL_WATER)
            return false;
    }

    return true;
}

//coloca o navio no tabuleiro
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
        
    }
}

// verifica se todos os navios foram destruídos
bool allShipsDestroyed(Fleet *f) {
    for (int i = 0; i < f->count; i++) {
        if (!f->ships[i].sunk)
            return false;
    }
    return true;
}

//tiro
int shootCell(Board *target, Board *shots, Fleet *fleet, int r, int c) {

    Cell *alvo = getCell(target, r, c);
    Cell *tiro = getCell(shots, r, c);

    // segurança
    if (!alvo || !tiro) {
        printf("Coordenada inválida! Escolha uma posição dentro do tabuleiro.\n");
        return 0;
    }

    // se já atirou nessa posição
    if (tiro->state == CELL_HIT || tiro->state == CELL_MISS) {
        printf("Coordenada inválida! Você já atirou nesse lugar.\n");
        return -1;
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
