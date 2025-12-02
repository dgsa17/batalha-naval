# Batalha Naval em C
Projeto desenvolvido para a disciplina de PIF, com o objetivo de implementar o  jogo Batalha Naval utilizando a linguagem C e o terminal como interface.

# Objetivo do Projeto
Desenvolver um jogo completo de Batalha Naval para dois jogadores no terminal, com aprimoramentos como tamanho de tabuleiro configurável e múltiplas opções de posicionamento de embarcações (manual ou automático), além de controle completo de tiros, detecção de acertos, erros e verificação automática da condição de vitória.

# Funcionalidades Implementadas
Menu principal interativo para iniciar um novo jogo ou sair.

Cadastro de apelidos dos jogadores.

Configurações de Jogo:

Definição do tamanho do tabuleiro (de 6x6 até 26x26, permitindo coordenadas de A1 a Z26).

Seleção do modo de posicionamento dos navios (Automático ou Manual).

Sistema de tiro com feedback detalhado:

Água (tiro errado).

Acerto.

Afundamento (toda a embarcação foi destruída).

Controle de frota e pontuação.

Verificação automática de vitória ao destruir toda a frota adversária.

Dois tabuleiros por jogador para rastreamento:

Tabuleiro próprio: Onde a própria frota está posicionada.

Tabuleiro de tiros: Onde os tiros dados no adversário são registrados.

Alocação dinâmica de memória para suportar tabuleiros de tamanhos variados.

Organização modular do código para maior clareza e manutenção:

board (Manipulação dos tabuleiros).

fleet (Gerenciamento das embarcações).

game (Lógica principal do jogo).

io (Entrada/Saída e interface com o usuário).

rnd (Geração de números aleatórios para posicionamento automático).

# Estrutura do Projeto
batalha-naval/
│
├── src/
│ ├── main.c              # Inicializa o programa.
│ ├── game.c / game.h     # Lógica do jogo (turnos, tiros, vitória).
│ ├── board.c / board.h   # Funções de criação, exibição e atualização do tabuleiro.
│ ├── fleet.c / fleet.h   # Definições das frotas e regras de posicionamento/acerto.
│ ├── io.c / io.h         # Funções de I/O específicas (leitura de coordenadas, mensagens).
│ └── rnd.c / rnd.h       # Funções auxiliares para randomização.
│
├── Makefile              # Script de compilação.
└── README.md
▶️ Como Compilar e Executar
Certifique-se de estar na pasta raiz do projeto (batalha-naval/).

Compilar o Projeto:

Bash

make
Executar o Jogo:

Bash

./batalha_naval
Limpar Arquivos Compilados (.o e executável):

Bash

make clean

# Como Jogar
Início: Selecione a opção "Novo jogo" no menu principal.

Cadastro: Informe o apelido dos dois jogadores.

Configurações:

Defina o tamanho do tabuleiro desejado.

Escolha o modo de posicionamento dos navios (Manual ou Automático).

Posicionamento (se Manual): Siga as instruções para inserir as coordenadas e orientação de cada embarcação da sua frota.

Turnos de Tiro: Os jogadores se alternam digitando as coordenadas do tiro no formato LetraNúmero (Exemplo: A1, C5, J10).

Feedback: O jogo irá informar o resultado do tiro:

Água

Acerto

Afundou (nome da embarcação)

Fim do Jogo: O jogo termina automaticamente quando toda a frota de um jogador for destruída, declarando o vencedor.

# Tecnologias Utilizadas
Linguagem C

Compilador GCC

GNU Make (via Makefile)

Terminal (Linux / macOS)

# Autores

David

Renato