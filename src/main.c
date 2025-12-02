#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "rnd.h"
#include "board.h"
#include "fleet.h"
#include "io.h"

int main() {

    int opcao;
    Game g;
    // Configuração padrão: 10x10, Auto
    GameConfig cfg = {10, 'A'}; 
    
    initRandom();

    while (1) { // Loop

        opcao = mainMenu();

        if (opcao == 1) {  
            // NOVO JOGO
            
            // Inicializa o jogo com as configurações atuais
            initGame(&g, &cfg);
            startGame(&g, &cfg);

            // Libera memória no final
            freeBoard(&g.p1.board);
            freeBoard(&g.p1.shots);
            free(g.p1.fleet.ships);

            freeBoard(&g.p2.board);
            freeBoard(&g.p2.shots);
            free(g.p2.fleet.ships);

        } else if (opcao == 2) {
            // CONFIGURAÇÕES 
            readConfig(&cfg);

        } else if (opcao == 3) {
            printf("Saindo...\n");
            break;
        }
    }

    return 0;
}
