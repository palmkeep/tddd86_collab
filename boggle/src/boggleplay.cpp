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

bool checkIsOldWord(const string &word, const vector<string> &playersWords)
{
    bool ret = false;
    if (!playersWords.empty())
    {
        for (vector<string>::const_iterator oldWord = playersWords.begin(); oldWord != playersWords.end(); oldWord++)
        {
            if (word == *oldWord)
            {
                ret = true;
            }
        }
    }
    return ret;
}

bool canBeFormedOnBoard(const string word, vector<string> &wordsOnBoard)
{
    bool ret = false;
    if (!wordsOnBoard.empty())
    {
        for (vector<string>::iterator wordOnBoard = wordsOnBoard.begin(); wordOnBoard != wordsOnBoard.end(); wordOnBoard++)
        {
            if (word == *wordOnBoard)
            {
                ret = true;
            }
        }
    }
    return ret;
}

void checkWordUpdateScore(const string &word, Boggle &boggle, vector<string> &wordsOnBoard, vector<string> &playersWords, int &playersWordCount, int &playersScore)
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
        if (boggle.isWordInLexicon(word) && canBeFormedOnBoard(word, wordsOnBoard))
        {
            playersScore += word.length() - 3;
            playersWords.push_back(word);
            playersWordCount++;
            cout << "You found a new word! \"" << word << "\"" << endl;
        }
        else
        {
            cout << "That word can't be formed on the board." << endl;
        }
    }
}

void promptPlayerInput(const vector<string> playersWords, const int playersWordCount, const int playersScore)
{
    cout << "Your words (" << playersWordCount << "): {";
    if(!playersWords.empty())
    {
        vector<string>::const_iterator word = playersWords.begin();
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

void playOneGame(Boggle& boggle) {
    vector<string> playersWords;
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

    vector<string> wordsOnBoard = boggle.getWordsOnBoard();

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

    //COMPUTERS TURN
    cout << "ExitPlay" << endl;
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
