#include <stdio.h>   
#include <ctype.h>   
#include <string.h>  
#include <stdlib.h>
#include "io.h"

// Menu inicial do jogo
int mainMenu(){
    char buf[16];
    int resposta_menu;

    do{
        // Mostra as opções pro jogador
        printf("=== BATALHA NAVAL ===\n1) Novo jogo\n2) Configurações\n3) Sair\n>");
        fgets(buf, sizeof(buf), stdin);
        // converte a string para número
        resposta_menu = atoi(buf);

        // repete se for inválido
    } while (resposta_menu < 1 || resposta_menu > 3);

    return resposta_menu;
}   

// Lê o apelido do jogador
void readNickname(char *buf, int size){
    do{
        printf("Informe seu apelido: ");

        // Lê o texto
        fgets(buf, size, stdin);

        // remove o "\n" no final
        buf[strcspn(buf, "\n")] = '\0';

        // repete se o apelido for vazio
    } while (strlen(buf) == 0);  
}

// Lê o tamanho do tabuleiro
int readBoardSize(){
    char buf[16];
    int tam;

    do{
        printf("Tamanho do tabuleiro (6-26)\n>");
        
        // lê como string
        fgets(buf, sizeof(buf), stdin);

        // converte pra inteiro
        tam = atoi(buf);

        // repete até estar dentro do limite
    } while (tam < 6 || tam > 26);

    return tam;
}

// Lê se o jogador quer posicionar manualmente ou automaticamente
char readPlacementMode(){
    char buf[8];
    char c;

    do {
        printf("Posicionamento (M)anual ou (A)utomático? ");
        fgets(buf, sizeof(buf), stdin);

        // tira "\n"
        buf[strcspn(buf, "\n")] = '\0';

        // só aceita uma letra
        if (strlen(buf) == 1) {
            c = toupper(buf[0]);  // converte pra maiúscula
        } else {
            c = '\0';
        }

        // repete até ser A ou M
    } while (!(c == 'A' || c == 'M'));

    return c;
}

// Lê coordenada e converte para linha/coluna 
void readCoordinate(const char *prompt, int *r, int *c){
    char buf[32];

    do{
        printf("%s", prompt);
        fgets(buf, sizeof(buf), stdin);

        // remove o '\n'
        buf[strcspn(buf, "\n")] = '\0';

        // mínimo 2 chars
        if (strlen(buf) < 2) 
            continue;

        // primeiro caractere tem que ser letra
        if (!isalpha(buf[0]))
            continue;

        // pega a letra e transforma em número da coluna
        char letra = toupper(buf[0]);
        int col = letra - 'A';   // A=0, B=1, C=2...

        // verifica se o resto da string é número
        int valido = 1;
        for (int i = 1; buf[i]; i++) {
            if (!isdigit(buf[i])) valido = 0;
        }
        if (!valido)
            continue;

        // converte a parte numérica para linha
        int row = atoi(buf + 1) - 1; 

        // devolve valores via ponteiro
        *r = row;
        *c = col;

        return; 

    } while (1); 
}

// Mostra mensagem de resultado do tiro
void showResultMessage(int hit){
    switch(hit){
        case 0: 
            printf("Resultado: ÁGUA.\n"); 
            break;
        case 1: 
            printf("Resultado: ACERTOU!\n"); 
            break;
        case 2: 
            printf("Resultado: AFUNDOU!\n"); 
            break;
        default: 
            printf("Resultado desconhecido.\n");
    }
}

// Implementação da função readConfig
void readConfig(GameConfig *cfg) {
    printf("\n=== CONFIGURAÇÕES DO JOGO ===\n");

    // 1. Tamanho do Tabuleiro
    printf("Tamanho atual do tabuleiro: %d\n", cfg->board_size);
    cfg->board_size = readBoardSize();

    // 2. Modo de Posicionamento
    printf("Modo de posicionamento atual: %c (%s)\n", 
           cfg->placement_mode, 
           (cfg->placement_mode == 'A' ? "Automático" : "Manual"));
    
    printf("Deseja mudar o modo de posicionamento? (A)utomático ou (M)anual: ");
    cfg->placement_mode = readPlacementMode();

    printf("\nConfigurações salvas!\n");
}
