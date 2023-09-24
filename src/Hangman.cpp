#include "../headers/Hangman.h"
#include "../headers/DoubleLinkedList.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Hangman constructor implementation
Hangman::Hangman()
{
    lives = 8;
    originalWord = "";
    enteredLetters = "";
}
// Implementation of the destructor to free the memory of the list nodes
Hangman::~Hangman()
{
    gameWord.clear();
}

//  * Plays the Hangman game.
//  * @throws ErrorType if there is an error loading the game
void Hangman::play()
{
    cout << "Welcome to Hangman Game!" << endl;

    string savedFileName;
    // Ask the user for the name of the save file

    cout << "Enter the name of file from which you want to load: ";
    cin >> savedFileName;
    // Load the game if it exists
    if (!loadGame(savedFileName))
    {
        return;
    }
    bool saved = false;

    while (lives > 0 && showWord() != originalWord)
    {
        if (wantsToQuit())
            break;
        if (wantsToSave())
        {
            saveGame(savedFileName);
            saved = true;
            break;
        }
        printBoard();

        cout << "Enter a letter: ";
        char letter;
        cin >> letter;

        if (isalpha(letter))
        {
            letter = toupper(letter); // Convert the entered word to uppercase
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
    else if (saved)
    {
        cout << "You saved the game!" << endl;
    }
    else
    {
        cout << "Sorry, you lost. The word was: " << originalWord << endl;
    }
}
//  * Determines if the player wants to quit the game.
//  * @return True if the player wants to quit, false otherwise.
bool Hangman::wantsToQuit()
{
    char choice;
    cout << "Do you want to exit the game? (Y/N): ";
    cin >> choice;
    return (choice == 'Y' || choice == 'y');
}

//  * Prompt the user if they want to save the game.
//  * @return true if the user wants to save the game, false otherwise.
bool Hangman::wantsToSave()
{
    char choice;
    cout << "Do you want to save the game? (Y/N): ";
    cin >> choice;
    return (choice == 'Y' || choice == 'y');
}

//  * Loads a game from a file.
//  * @param fileName the name of the file to load the game from
//  * @return true if the game was successfully loaded, false otherwise
//  * @throws None
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
            cout << "Wrong format for 'Name player'" << endl; // The Throw is like a cout << endl.
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

            for (auto &c : word) // automatically grabs the indices 1 by 1.
                originalWord += toupper(c);

            if (!checkBoard(board)) // check if there are no letters inside board. If it didn't find anything, it initializes it as empty.
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
            lives = lives - stoi(loadedLives); // String to int. Go from string data to int data
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
// Saves the current game state to a file.
//   param fileName the name of the file to save to
//  return true if the game was successfully saved, false otherwise
//   @throws ofstream::failure if the file cannot be opened for writing

bool Hangman::saveGame(const string &fileName)
{
    ofstream outputFile(fileName);
    if (outputFile.is_open())
    {
        outputFile << "Name player:" << endl
                   << playerName << endl;
        outputFile << "Board" << endl;
        outputFile << "| ";
        for (int i = 0; i < gameWord.size; i++)
        {
            if (i == gameWord.size - 1)
            {
                outputFile << gameWord.get(i) << " |" << endl;
            }
            else
            {
                outputFile << gameWord.get(i) << " | ";
            }
        }
        outputFile << "Word" << endl
                   << originalWord << endl;
        outputFile << "Failed attempts:" << endl
                   << 8 - lives << endl;
        outputFile << "Selected letters:" << endl
                   << enteredLetters;
        outputFile.close();
        return true;
    }
    return false;
}
// Updates the game state based on the letter entered by the player.
//  * @param letter The letter entered by the player.
//  * @return None.
//  * @throws None.
void Hangman::enterLetter(char letter)
{

    // Check if the letter is in the original word
    bool letterGuessed = false;
    bool letterUsed = false;

    for (int i = 0; i < static_cast<int>(enteredLetters.size()); i++)
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

    for (int i = 0; i < static_cast<int>(originalWord.length()); i++)
    {
        if (originalWord[i] == letter)
        {
            letterGuessed = true;
            gameWord.set(i, letter);
        }
    }

    if (!letterGuessed) // Lose lives if you make a mistake
    {
        --lives;
    }
}

//  * Returns the word to be displayed in the Hangman game.
string Hangman::showWord()
{
    string displayedWord;

    for (int i = 0; i < gameWord.size; i++)
    {
        displayedWord += gameWord.get(i);
    }

    return displayedWord;
}
//  * Prints the Hangman board to the console.
void Hangman::printBoard()
{
    cout << "Name player:" << endl
         << playerName << endl;
    cout << "Board" << endl;
    string displayWord = showWord();
    cout << "| ";
    for (int i = 0; i < static_cast<int>(displayWord.size()); i++)
    {
        if (i == static_cast<int>(displayWord.size()) - 1)
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
//  * Check if the hangman board is loaded.
//  * @param board the hangman board to check
//  * @return true if the board is loaded, false otherwise
//  * @throws None
bool Hangman::checkBoard(string &board)
{
    bool isLoaded = false;
    for (int i = 0; i < board.length(); i++)
    {

        if (board[i] != '|' && board[i] != ' ')
        {
            isLoaded = true;
        }
    }
    return isLoaded;
}
