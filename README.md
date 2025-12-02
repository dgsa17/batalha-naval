# Batalha Naval em C

Projeto desenvolvido para a disciplina de PIF, com o objetivo de implementar o jogo Batalha Naval utilizando a linguagem C.

---

## Objetivo do Projeto

Desenvolver um jogo completo de Batalha Naval no terminal, permitindo que dois jogadores joguem alternadamente, com posicionamento manual ou automático das embarcações, controle de tiros, detecção de acertos, erros e vitória.

---

## Funcionalidades Implementadas

- Menu principal interativo
- Cadastro de apelidos dos jogadores
- Definição de tamanho do tabuleiro (6 a 26)
- Posicionamento de navios:
  - Automático
  - Manual
- Sistema de tiro com:
  - Água
  - Acerto
  - Afundamento
- Controle de frota
- Verificação automática de vitória
- Dois tabuleiros por jogador:
  - Tabuleiro próprio
  - Tabuleiro de tiros
- Alocação dinâmica de memória
- Organização por módulos:
  - `board`
  - `fleet`
  - `game`
  - `io`
  - `rnd`

---

## Estrutura do Projeto

batalha-naval/
│
├── src/
│ ├── main.c
│ ├── game.c / game.h
│ ├── board.c / board.h
│ ├── fleet.c / fleet.h
│ ├── io.c / io.h
│ ├── rnd.c / rnd.h
│
├── Makefile
└── README.md


## ▶️ Como Compilar e Executar

Dentro da pasta do projeto:

```bash
make
./batalha_naval
Para limpar os arquivos compilados:

bash
Copiar código
make clean
🎮 Como Jogar
Escolha a opção "Novo jogo"

Informe o apelido dos jogadores

Escolha o tamanho do tabuleiro

Selecione o modo de posicionamento dos navios:

Manual

Automático

Os jogadores se alternam digitando coordenadas no formato:

Exemplo: A1, C5, J10

O jogo informa:

Água

Acerto

Afundou

O jogo termina automaticamente quando toda a frota de um jogador for destruída.

🛠 Tecnologias Utilizadas
Linguagem C

Compilador GCC

Makefile

Terminal (Linux / macOS)

👥 Autores
Pedro

Renato