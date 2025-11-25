#include <stdlib.h>
#include <time.h>
#include "rnd.h"
#include "board.h"
#include "fleet.h"

void initRandom() {
    srand(time(NULL));
}

//posiciona os navios automaticamente
void placeFleetAuto(Board *b, Fleet *f) {

    for (int id = 0; id < f->count; id++) {

        int size = f->ships[id].size;
        int r, c;
        int horizontal;

        while (1) {
            //linha aleatória
            r = rand() % b->rows;

            //coluna aleatória
            c = rand() % b->cols;

            //0 = vertical e 1 = horizontal
            horizontal = rand() % 2;

            //verifica se pode colocar
            if (canPlaceShip(b, r, c, size, horizontal)) {

                //coloca os navios
                placeShip(b, f, id, r, c, horizontal);
                break;
            }
        }
    }
}
