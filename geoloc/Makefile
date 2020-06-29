#Variables

CC=gcc
BIN=geoloc
SRC=main.c graphic.c init.c cluster.c fichier.c conversion.c liste_point.c route.c logs.c stats.c stat_graph.c
OBJ=$(SRC: .c=.o)
FLAGS= -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio -lm

#Construction du programme

all: $(BIN)

$(BIN): $(SRC)
	gcc -g $(SRC) -o $(BIN) $(FLAGS) 

#Nettoyage

clean: 
	rm -f *.o
