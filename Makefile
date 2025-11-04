# Compilador que será usado
CC = gcc

# Flags de compilação (avisos e padrão C99)
CFLAGS = -Wall -Wextra -std=c99

# Todos os arquivos .c do projeto
SRC = src/main.c src/board.c src/fleet.c src/game.c src/io.c src/rnd.c

# Gera uma lista de arquivos objeto (.o)
OBJ = $(SRC:.c=.o)

# Nome do executável final
TARGET = batalha_naval

# Regra principal: compila tudo
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Regra opcional: limpa arquivos gerados
clean:
	rm -f $(OBJ) $(TARGET)