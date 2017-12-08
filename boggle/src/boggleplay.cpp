// You will edit and turn in this CPP file.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace with your own

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"


using std::cout;        using std::endl;
// TODO: include any other header files you need

/*
 * Plays one game of Boggle using the given boggle game state object.
 */

// Returns true if player already guessed the word.
bool checkIsOldWord(const string& word, const set<string>& playersWords)
{
    bool ret = false;
    if (!playersWords.empty())
    {
        for (set<string>::const_iterator oldWord = playersWords.begin(); oldWord != playersWords.end(); oldWord++)
        {
            if (word == *oldWord)
            {
                ret = true;
            }
        }
    }
    return ret;
}

// Returns true if guessed word can be formed on board.
bool canBeFormedOnBoard(const string& word, set<string>& wordsOnBoard)
{
    bool ret = false;
    if (!wordsOnBoard.empty())
    {
        for (set<string>::iterator wordOnBoard = wordsOnBoard.begin(); wordOnBoard != wordsOnBoard.end(); wordOnBoard++)
        {
            if (word == *wordOnBoard)
            {
                ret = true;
            }
        }
    }
    return ret;
}

// Checks if guessed word follows the requirements, changes playersScore and removes the correct guessed word from wordsOnBoard.
void checkWordUpdateScore(const string& word, Boggle& boggle, set<string>& wordsOnBoard, set<string>& playersWords, int& playersWordCount, int& playersScore)
{
    if (word.length() < 4)
    {
        cout << "That word is not long engough." << endl;
    }
    else if (checkIsOldWord(word, playersWords))
    {
        cout << "You've already guessed that word." << endl;
    }
    else
    {
        if (boggle.findWord(word) && canBeFormedOnBoard(word, wordsOnBoard))
        {
            playersScore += word.length() - 3;
            playersWords.insert(word);
            playersWordCount++;

            for (set<string>::iterator it = wordsOnBoard.begin(); it != wordsOnBoard.end(); it++)
            {
                if( *it == word ){
                    wordsOnBoard.erase(it);
                    break;
                }
            }

            cout << "You found a new word! \"" << word << "\"" << endl;
        }
        else
        {
            cout << "That word can't be formed on the board." << endl;
        }
    }
}

// Handels the guessed words and prints them out.
void promptPlayerInput(const set<string> playersWords, const int playersWordCount, const int playersScore)
{
    cout << "Your words (" << playersWordCount << "): {";
    if(!playersWords.empty())
    {
        set<string>::const_iterator word = playersWords.begin();
        cout << "\"" << *word << "\" ";
        word++;

        if (1 < playersWords.size())
        {
            for(word; word != playersWords.end(); word++)
            {
                cout << ", \"" << *word << "\" ";
            }
        }
    }
    cout << "}" << endl;
    cout << "Your score: " << playersScore << endl;
    cout << "Type a word (or press Enter to end your turn): ";
}

// The main program that handles the game logic and game structure.
void playOneGame(Boggle& boggle) {
    set<string> playersWords;
    int playersWordCount = 0;
    int playersScore = 0;


    if (!yesOrNo("Do you want to generate a random board? "))
    {
        bool niceInput = false;
        string input;
        while(!niceInput)
        {
            std::getline(cin, input);
            if (input.length() == 16)
            {
                niceInput = true;
            }
        }
        boggle.setBoard(input);

        std::getline(cin, input); // Captures newline char so it does not end up in player input
    }
    else
    {
        boggle.shuffleCubes();
    }

    set<string> wordsOnBoard = boggle.getWordsOnBoard();

    cout << "It's your turn!" << endl;
    boggle.draw();


    string line = "FILIP_APPROVES_OF_MAGIC";
    while (!line.empty())
    {
        promptPlayerInput(playersWords, playersWordCount, playersScore);

        std::getline( std::cin, line);
        checkWordUpdateScore(line, boggle, wordsOnBoard, playersWords, playersWordCount, playersScore);


        boggle.draw();
    }

    for (auto it = wordsOnBoard.begin(); it != wordsOnBoard.end(); it++)
    {
        cout << *it << endl;
    }

    //COMPUTERS TURN
    cout << "It's my turn" << endl;
    cout << "My words (" << playersWordCount << "): {";
    int computerScore = 0;
    if(!playersWords.empty())
    {
        set<string>::const_iterator word = wordsOnBoard.begin();
        computerScore += word->length() - 3;
        cout << "\"" << *word << "\" ";
        word++;

        if (1 < wordsOnBoard.size())
        {
            for(word; word != wordsOnBoard.end(); word++)
            {
                computerScore += word->length() - 3;
                cout << ", \"" << *word << "\" ";
            }
        }
    }
    cout << "}" << endl;
    cout << "My score: " << computerScore << endl;
    if (playersScore < computerScore)
    {
        cout << "Ha ha ha, I destroyed you. Better luck next time, puny human!" << endl;
    }
    else
    {
        cout << "You beat me yet I see no sticks a' ram sticking out of your face. How can this be?" << endl;
    }
}



/*
 * Erases all currently visible text from the output console.
 */
void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("CLS");
#else
    // assume POSIX
    std::system("clear");
#endif
}
