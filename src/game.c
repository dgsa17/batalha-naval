#include <stdio.h>
#include <stdlib.h>
#include "game.h"

// Inicializa a estrutura Game
void initGame(Game *g){
    g->current_player = 0;
    g->game_over = 0;

    // Lê apelidos
    printf("Jogador 1:\n");
    readNickname(g->p1.nickname, 32);
    printf("Jogador 2:\n");
    readNickname(g->p2.nickname, 32);

    // Tamanho
    int size = readBoardSize();

    // Inicializa tabuleiros
    initBoard(&g->p1.board, size, size);
    initBoard(&g->p2.board, size, size);

    initBoard(&g->p1.shots, size, size);
    initBoard(&g->p2.shots, size, size);

    // Inicializa frotas
    initFleet(&g->p1.fleet);
    initFleet(&g->p2.fleet);

    // Posicionamento
    char mode = readPlacementMode();
    if (mode == 'A' || mode == 'a'){
        placeFleetAuto(&g->p1.board, &g->p1.fleet);
        placeFleetAuto(&g->p2.board, &g->p2.fleet);
    } else {
        placeFleetManual(&g->p1.board, &g->p1.fleet, g->p1.nickname);
        placeFleetManual(&g->p2.board, &g->p2.fleet, g->p2.nickname);
    }
}


// Loop principal do jogo
void startGame(Game *g){

    while (!g->game_over){

        doTurn(g);

        if (checkVictory(g)){
            g->game_over = 1;
        }

        // Alterna jogadores
        g->current_player = (g->current_player == 0 ? 1 : 0);
    }

    printf("\n*** FIM DE JOGO ***\n");
    int winner = g->current_player == 0 ? 1 : 0;  
    printf("Vencedor: %s\n", winner == 0 ? g->p1.nickname : g->p2.nickname);
}


// Executa um turno completo
void doTurn(Game *g){

    Player *atual = (g->current_player == 0 ? &g->p1 : &g->p2);
    Player *alvo  = (g->current_player == 0 ? &g->p2 : &g->p1);

    printf("\n-- Turno de %s --\n", atual->nickname);

    int r, c;
    readCoordinate("Digite coordenada: ", &r, &c);

    // Checa se o tiro é válido no tabuleiro
    if (!inBounds(&alvo->board, r, c)){
        printf("Coordenada fora do tabuleiro!\n");
        return;
    }

    int result = shootCell(&alvo->board, &atual->shots, &alvo->fleet, r, c);

    showResultMessage(result);
}


// Verifica se algum jogador perdeu TODA a frota
bool checkVictory(Game *g){

    if (allShipsDestroyed(&g->p1.fleet)){
        printf("\n%s perdeu todas as embarcações!\n", g->p1.nickname);
        return true;
    }

    if (allShipsDestroyed(&g->p2.fleet)){
        printf("\n%s perdeu todas as embarcações!\n", g->p2.nickname);
        return true;
    }

    return false;
}
