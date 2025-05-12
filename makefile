CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SRC = main.c personnage.c combat.c jeu.c
OBJ = $(SRC:.c=.o)
EXEC = rpg_game

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean
