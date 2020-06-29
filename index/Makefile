#Variables

CC=gcc
BIN=index
SRC= main.c read_log.c liste_point.c conversion.c
OBJ=$(SRC: .c=.o)
FLAGS=

#Construction du programme

all: $(BIN)

$(BIN): $(SRC)
	gcc -g $(SRC) -o $(BIN) $(FLAGS) -lm

#Nettoyage

clean: 
	rm -f *.o
