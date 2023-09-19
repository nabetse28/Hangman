.PHONY: all clean

BANDERAS = -std=c++11 -Wall -g
SALIDA = game

all: game

game:
	g++ $(BANDERAS) main.cpp src/Hangman.cpp -o $(SALIDA)

clean:
	rm -r *.dSYM $(SALIDA)