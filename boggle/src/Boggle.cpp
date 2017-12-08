// This is the .cpp file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace it with your own

#include <iostream>
#include <sstream>
#include <algorithm>
#include <set>

#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"
#include "lexicon.h"

using std::cout;        using std::endl;

static const int NUM_CUBES = 16;    // the number of cubes in the game
static const int GRID_SIZE = 4;     // the grid side length
static const int CUBE_SIDES = 6;    // the number of sides on each cube
static const int POSSIBLE_UP_DOWN_DIAG_STEPS [3] = { 3, 4, 5 };

static string CUBES[NUM_CUBES] = {  // the letters on all 6 sides of every cube
                                    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
                                    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
                                    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
                                    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
                                 };


// Draws the grid of characters
void Boggle::draw()
{
    for (int i = 0; i < NUM_CUBES; i++)
    {
        cout << grid[i].c;
        if (i % GRID_SIZE == 3)
        {
            cout << endl;
        }
    }
    cout << endl;
}

// Constructors that randomizes the characters of the grid
Boggle::Boggle()
{
    shuffledCubes = CUBES;

    struct CUBE grid[NUM_CUBES];
    shuffleCubes();
}

// Randomizes the grid
void Boggle::shuffleCubes()
{
    shuffle(this->shuffledCubes, NUM_CUBES);
    for (int i = 0; i < NUM_CUBES; i++)
    {
        grid[i].c = this->shuffledCubes[i].at(randomInteger(0,5));
        grid[i].visited = false;
    }
}

// Created grid
void Boggle::setBoard(const string cubeFaces)
{
    for (int i = 0; i < NUM_CUBES; i++)
    {
        grid[i].c = cubeFaces.at(i);
        grid[i].visited = false;
    }
}

// Returns true if the lexicon contains word.
bool Boggle::isWordInLexicon(const string& word) const
{
    return wordList.contains(word);
}

// Returns true if the lexicon contains prefix.
bool Boggle::containsPrefix(const string& prefix) const
{
    return wordList.containsPrefix(prefix);
}

// Checks if a given word can be formed from the given index starting with the given prefix
bool Boggle::findWordForPoint(const int index, string prefix, const string& word)
{
    if (prefix == word.substr(0,prefix.size()))
    {
        if (prefix == word)
        {
            return true;
        }
        // Kolla om de finns i lexicon + fortsätt (prefix.length() > 4)
        grid[index].visited = true;

        int x = index % 4;
        int y = index / 4;

        // Create a list of indexes for all neighbouring cubes
        set<int> possibleDx;
        set<int> possibleDy;
        if (x!= 0)
        {
            possibleDx.insert(-1);
        }
        if (y != 0)
        {
            possibleDy.insert(-1);
        }
        if (x != 3)
        {
            possibleDx.insert(1);
        }
        if (y != 3)
        {
            possibleDy.insert(1);
        }
        possibleDx.insert(0);
        possibleDy.insert(0);


        for (set<int>::iterator dx = possibleDx.begin(); dx != possibleDx.end(); dx++)
        {
            for (set<int>::iterator dy = possibleDy.begin(); dy != possibleDy.end(); dy++)
            {
                if ( !grid[index + *dx + 4*(*dy)].visited)
                {

                    string newPrefix = prefix;
                    newPrefix += (tolower(grid[index + *dx + 4*(*dy)].c));
                    if (findWordForPoint(index + *dx + 4*(*dy), newPrefix, word))
                    {
                        grid[index].visited = false;
                        return true;
                    }
                }
            }
        }

        grid[index].visited = false;
    }
    return false;
}

// Recursive backtracking algorithm for checking if a given word is on the board
bool Boggle::findWord(const string& word)
{
    for (int index = 0; index < 16; index++)
    {
        if (tolower(grid[index].c) == word.at(0))
        {
            string prefix = "";
            prefix += tolower(grid[index].c);
            grid[index].visited = true;

            if(findWordForPoint(index, prefix, word))
            {
                grid[index].visited = false;
                return true;
            }
            grid[index].visited = false;
        }
    }
    return false;
}


// Adds possible words in "possibleWords".
void Boggle::getWordsForPoint(const int index, string prefix, set<string>& possibleWords)
{
    if (containsPrefix(prefix))
    {
        if (4 <= prefix.length() && isWordInLexicon(prefix))
        {
            possibleWords.insert(prefix);
        }
        // Kolla om de finns i lexicon + fortsätt (prefix.length() > 4)
        grid[index].visited = true;

        int x = index % 4;
        int y = index / 4;

        // Create a list of indexes for all neighbouring cubes
        vector<int> nextIndex;


        set<int> possibleDx;
        set<int> possibleDy;
        if (x!= 0)
        {
            possibleDx.insert(-1);
        }
        if (y != 0)
        {
            possibleDy.insert(-1);
        }
        if (x != 3)
        {
            possibleDx.insert(1);
        }
        if (y != 3)
        {
            possibleDy.insert(1);
        }

        possibleDx.insert(0);
        possibleDy.insert(0);


        for (set<int>::iterator dx = possibleDx.begin(); dx != possibleDx.end(); dx++)
        {
            for (set<int>::iterator dy = possibleDy.begin(); dy != possibleDy.end(); dy++)
            {
                if ( !grid[index + *dx + 4*(*dy)].visited)
                {
                    string newPrefix = prefix;
                    newPrefix += (tolower(grid[index + *dx + 4*(*dy)].c));
                    this->getWordsForPoint(index + *dx + 4*(*dy), newPrefix, possibleWords);
                }
            }
        }

        this->grid[index].visited = false;
    }
}

// Returns all possible words created on board.
set<string> Boggle::getWordsOnBoard()
{
    set<string> possibleWords;

    for (int index = 0; index < 16; index++)
    {
        string prefix = "";
        prefix += tolower(grid[index].c);
        grid[index].visited = true;
        getWordsForPoint(index, prefix, possibleWords);
        grid[index].visited = false;
    }

    return possibleWords;
}
