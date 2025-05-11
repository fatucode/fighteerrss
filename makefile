CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = 
SRC = src/main.c src/personnage.c src/combat.c src/jeu.c
OBJ = $(SRC:.c=.o)
EXEC = rpg_game

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean
