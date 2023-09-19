#include "../headers/Hangman.h"
#include "../headers/DoubleLinkedList.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Implementación del constructor de Hangman
Hangman::Hangman()
{
    lives = 8;
    originalWord = "";
    enteredLetters = "";
}

// Implementación del destructor para liberar la memoria de los nodos de la lista
Hangman::~Hangman()
{
    gameWord.clear();
}

void Hangman::play()
{
    cout << "Welcome to Hangman Game!" << endl;

    string savedFileName;

    // Pedir al usuario el nombre del archivo de guardado

    cout << "Enter the name of file from which you want to load: ";
    cin >> savedFileName;
    // Cargar el juego si existe
    if (!loadGame(savedFileName))
    {
        return;
    }

    while (lives > 0 && showWord() != originalWord)
    {
        printBoard();

        cout << "Enter a letter: ";
        char letter;
        cin >> letter;

        if (isalpha(letter))
        {
            letter = toupper(letter); // Convertir la palabra ingresada en mayuscula
            enterLetter(letter);
        }
        else
        {
            cout << "Please enter a valid letter!" << endl;
        }
    }

    if (showWord() == originalWord)
    {
        cout << "Congratulations! You won! The word is: " << originalWord << endl;
    }
    else
    {
        cout << "Sorry, you lost. The word was: " << originalWord << endl;
    }
}

bool Hangman::loadGame(const string &fileName)
{
    ifstream inputFile(fileName);

    if (inputFile.is_open())
    {
        string line;
        string boardHeader;
        string board;
        string loadedLives;
        string word;

        getline(inputFile, line);
        if (line.find("Name player") != std::string::npos)
        {
            getline(inputFile, playerName);
        }
        else
        {
            cout << "Wrong format for 'Name player'" << endl; // El Throw es como un cou << endl.
        }
        getline(inputFile, boardHeader); // Header Board name
        if (boardHeader.find("Board") != std::string::npos)
        {
            getline(inputFile, board);
        }
        else
        {
            cout << "Wrong format for 'Board game'" << endl;
        }

        getline(inputFile, line);
        if (line.find("Word") != std::string::npos)
        {
            getline(inputFile, word);
            // for (int i = 0; i < word.length(); i++)
            // {
            //     originalWord += toupper(word[i]);
            // }
            for (auto &c : word) // automaticamente agarra los indices 1*1
                originalWord += toupper(c);

            if (!checkBoard(board)) // revisa si no hay ninguna letra dentro de board. Si no encontro nada lo inicializa como vacio.
            {
                for (int i = 0; i < originalWord.length(); ++i)
                {
                    gameWord.pushBack(' ');
                }
            }
            else
            {
                int index = 2;
                while (index <= board.size())
                {
                    gameWord.pushBack(board[index]);
                    index += 4;
                }
            }
        }
        else
        {
            cout << "Wrong format for 'Word'" << endl;
        }
        getline(inputFile, line);
        if (line.find("Failed attempts") != std::string::npos)
        {
            getline(inputFile, loadedLives);
            lives = lives - stoi(loadedLives); // String to int. Pasar un string a un Int.
        }
        else
        {
            cout << "Wrong format for 'Failed attempts'" << endl;
        }
        getline(inputFile, line);
        if (line.find("Selected letters") != std::string::npos)
        {
            getline(inputFile, enteredLetters);
        }
        else
        {
            cout << "Wrong format for 'Selected letters'" << endl;
        }
        inputFile.close();
        return true;
    }
    else
    {
        cout << "Error: Unable to open the input file." << endl;
        return false;
    }

    inputFile.close();
    return false;
}

bool Hangman::saveGame(const string &fileName)
{

    return true;
}

void Hangman::enterLetter(char letter)
{

    // Verificar si la letra está en la palabra original
    bool letterGuessed = false;
    bool letterUsed = false;

    for (int i = 0; i < enteredLetters.size(); i++)
    {
        if (enteredLetters[i] == letter)
        {
            cout << "The letter '" << letter << "' was already used! Please select a new letter..." << endl;
            letterUsed = true;
        }
    }

    if (letterUsed)
    {
        return;
    }

    enteredLetters += letter;

    for (int i = 0; i < originalWord.size(); i++)
    {
        if (originalWord[i] == letter)
        {
            letterGuessed = true;
            gameWord.set(i, letter);
        }
    }

    if (!letterGuessed) // Perder vidas si se equivoca
    {
        --lives;
    }
}

string Hangman::showWord()
{
    string displayedWord;

    for (int i = 0; i < gameWord.size; i++)
    {
        displayedWord += gameWord.get(i);
    }

    return displayedWord;
}

void Hangman::printBoard()
{
    cout << "Board" << endl;
    string displayWord = showWord();
    cout << "| ";
    for (int i = 0; i < displayWord.size(); i++)
    {
        if (i == displayWord.size() - 1)
        {
            cout << displayWord[i] << " |" << endl;
        }
        else
        {
            cout << displayWord[i] << " | ";
        }
    }

    cout
        << "Failed attempts:" << endl;
    cout << to_string(8 - lives) << endl; // para pasarlo a string.
    cout
        << "Selected letters:" << endl;
    cout << enteredLetters << endl;
}

bool Hangman::checkBoard(string &board)
{
    bool isLoaded = false;
    for (int i = 0; i <= board.length(); i++)
    {
        if (board[i] != '|' || board[i] != ' ')
        {
            isLoaded = true;
        }
    }
    return isLoaded;
}