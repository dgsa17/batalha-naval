#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "rnd.h"
#include "board.h"
#include "fleet.h"
#include "io.h"

int main() {

    int opcao;

    initRandom(); // inicializa do módulo rnd

    while (1) { // Loop

        opcao = mainMenu();

        if (opcao == 1) {  
            // NOVO JOGO
            Game g;

            initGame(&g);
            startGame(&g);

            // Libera memória no final
            freeBoard(&g.p1.board);
            freeBoard(&g.p1.shots);
            free(g.p1.fleet.ships);

            freeBoard(&g.p2.board);
            freeBoard(&g.p2.shots);
            free(g.p2.fleet.ships);

        } else if (opcao == 2) {
            // CONFIGURAÇÕES 
            printf("Configurações ainda não implementadas.\n");

        } else if (opcao == 3) {
            printf("Saindo...\n");
            break;
        }
    }

    return 0;
}
