#ifndef HANGMAN_H
#define HANGMAN_H
#include <string>
#include <iostream>
#include <fstream>
#include "DoubleLinkedList.h"

using namespace std;

class Hangman
{
private:
    int lives; // Numero de vidas.

    string playerName;               // Nombre de jugador
    string originalWord;             // La palabra a advinar
    string enteredLetters;           // Ingreso de letras del jugador
    DoubleLinkedList<char> gameWord; // Doble lista enlazada. Le especifico que esa doble lista es de tipo char.

    bool loadGame(const string &fileName);
    bool saveGame(const string &fileName);
    void printBoard();
    void enterLetter(char letter);
    bool checkBoard(string &board); // Chea si el tablero del txt contiene algo.
    string showWord();
    bool wantsToQuit();
    bool wantsToSave();

public:
    Hangman();
    ~Hangman();
    void play();
};

#endif
