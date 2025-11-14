#include <stdio.h>   
#include <ctype.h>   
#include <string.h>  
#include <stdlib.h>
#include "io.h"

int mainMenu(){
    char buf[16];
    int resposta_menu;

    do{
        printf("=== BATALHA NAVAL ===\n1) Novo jogo\n2) Configurações\n3) Sair\n>");
        fgets(buf, sizeof(buf), stdin);
        resposta_menu = atoi(buf);
    } while (resposta_menu < 1 || resposta_menu > 3);

    return resposta_menu;
}   

void readNickname(char *buf, int size){
    do{
        printf("Informe seu apelido: ");
        fgets(buf, size, stdin);
        buf[strcspn(buf, "\n")] = '\0';

    } while (strlen(buf) == 0);  
}

int readBoardSize(){
    char buf[16];
    int tam;

    do{
        printf("Tamanho do tabuleiro (6-26)\n>");
        fgets(buf, sizeof(buf), stdin);
        tam = atoi(buf);

    } while (tam < 6 || tam > 26);

    return tam;
}

char readPlacementMode(){
    char buf[8];
    char c;

    do {
        printf("Posicionamento (M)anual ou (A)utomático? ");
        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = '\0';

        if (strlen(buf) == 1) {
            c = toupper(buf[0]);  
        } else {
            c = '\0';
        }

    } while (!(c == 'A' || c == 'M'));

    return c;
}

void readCoordinate(const char *prompt, int *r, int *c){
    char buf[32];

    do{
        printf("%s", prompt);
        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = '\0';

  
        if (strlen(buf) < 2) 
            continue;

       
        if (!isalpha(buf[0]))
            continue;

        
        char letra = toupper(buf[0]);
        int col = letra - 'A';

        
        int valido = 1;
        for (int i = 1; buf[i]; i++) {
            if (!isdigit(buf[i])) valido = 0;
        }
        if (!valido)
            continue;

        int row = atoi(buf + 1) - 1;

        *r = row;
        *c = col;
        return;

    } while (1);
}

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
