#ifndef HANGMAN_H
#define HANGMAN_H
#include <string>
#include <iostream>
#include <fstream>
#include "DoubleLinkedList.h"

using namespace std;

// The code is defining a class called `Hangman`.
class Hangman
{
private:
    int lives; // Number of lives

    string playerName;               // Player Name
    string originalWord;             // Guees word
    string enteredLetters;           // Letters entered
    DoubleLinkedList<char> gameWord; // The line DoubleLinkedList<char> gameWord; declares a variable named gameWord of type DoubleLinkedList<char>.

    bool loadGame(const string &fileName);
    bool saveGame(const string &fileName);
    void printBoard();
    void enterLetter(char letter);
    bool checkBoard(string &board); // Check if the board is loaded.
    string showWord();
    bool wantsToQuit();
    bool wantsToSave();

public:
    Hangman();
    ~Hangman();
    void play();
};

#endif
