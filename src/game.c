#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "board.h"
#include "fleet.h"
#include "io.h"

// Inicializa a estrutura Game
void initGame(Game *g, GameConfig *cfg){
    g->current_player = 0;
    g->game_over = 0;

    // Lê apelidos
    printf("Jogador 1:\n");
    readNickname(g->p1.nickname, 32);
    printf("Jogador 2:\n");
    readNickname(g->p2.nickname, 32);

    // Inicializa tabuleiros com o tamanho da configuração
    initBoard(&g->p1.board, cfg->board_size, cfg->board_size);
    initBoard(&g->p2.board, cfg->board_size, cfg->board_size);

    initBoard(&g->p1.shots, cfg->board_size, cfg->board_size);
    initBoard(&g->p2.shots, cfg->board_size, cfg->board_size);

    // Inicializa frotas
    initFleet(&g->p1.fleet);
    initFleet(&g->p2.fleet);
}


// Loop principal do jogo
void startGame(Game *g, GameConfig *cfg){

    // Posicionamento
    char mode = cfg->placement_mode;
    if (mode == 'A' || mode == 'a'){
        placeFleetAuto(&g->p1.board, &g->p1.fleet);
        placeFleetAuto(&g->p2.board, &g->p2.fleet);
    } else {
        placeFleetManual(&g->p1.board, &g->p1.fleet, g->p1.nickname);
        placeFleetManual(&g->p2.board, &g->p2.fleet, g->p2.nickname);
    }

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

    printf("\nSeu Tabuleiro de Tiros:\n");
    printBoard(&atual->shots, false); // Tabuleiro de tiros (mostra acertos/erros)

    printf("\nSeu Tabuleiro de Navios:\n");
    printBoard(&atual->board, true); // Tabuleiro de navios (mostra seus navios)

    int r, c;
    
    while (1) {
        readCoordinate("Digite coordenada: ", &r, &c);

        // Checa se o tiro é válido no tabuleiro
        if (!inBounds(&alvo->board, r, c)){
            printf("Coordenada fora do tabuleiro!\n");
            continue;
        }

        int result = shootCell(&alvo->board, &atual->shots, &alvo->fleet, r, c);
        
        // Se result for 0 e for por coordenada inválida (já atirou), continua pedindo
        if (result == -1) {
            continue;
        }

        showResultMessage(result);
        
        // Exibe o tabuleiro de tiros após o resultado
        printf("\nSeu Tabuleiro de Tiros Atualizado:\n");
        printBoard(&atual->shots, false);
        
        break;
    }
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

// Posicionamento manual de navios
void placeFleetManual(Board *b, Fleet *f, const char *nickname) {
    printf("\n=== Posicionamento de navios para %s ===\n", nickname);
    
    // A frota tem 6 navios: 1x5, 1x4, 2x3, 2x2
    const char *ship_names[] = {"Porta-aviões (5)", "Encouraçado (4)", "Cruzador (3)", "Cruzador (3)", "Destroyer (2)", "Destroyer (2)"};
    
    for (int id = 0; id < f->count; id++) {
        int size = f->ships[id].size;
        printf("\nPosicionando %s\n", ship_names[id]);
        
        while (1) {
            printBoard(b, true);
            
            int r, c;
            char orientation;
            
            readCoordinate("Digite a coordenada inicial: ", &r, &c);
            
            printf("Orientação (H)orizontal ou (V)ertical)? ");
            char buf[8];
            fgets(buf, sizeof(buf), stdin);
            orientation = toupper(buf[0]);
            
            if (orientation != 'H' && orientation != 'V') {
                printf("Orientação inválida! Use H ou V.\n");
                continue;
            }
            
            bool horizontal = (orientation == 'H');
            
            if (canPlaceShip(b, r, c, size, horizontal)) {
                placeShip(b, f, id, r, c, horizontal);
                printf("Navio posicionado com sucesso!\n");
                break;
            } else {
                printf("Não é possível posicionar o navio nessa posição. Tente novamente.\n");
            }
        }
    }
    
    printf("\nTodos os navios foram posicionados!\n");
    printBoard(b, true);
    printf("Pressione Enter para continuar...");
    // Limpa o buffer de entrada para o próximo getchar
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
