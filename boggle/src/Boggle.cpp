// This is the .cpp file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace it with your own

#include <iostream>
#include <sstream>

#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"
#include "lexicon.h"

using std::cout;        using std::endl;

static const int NUM_CUBES = 16;    // the number of cubes in the game
static const int GRID_SIZE = 4;     // the grid side length
static const int CUBE_SIDES = 6;    // the number of sides on each cube

static string CUBES[NUM_CUBES] = {  // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
string* shuffledCubes = CUBES;

// TODO: implement the members you declared in Boggle.h


struct cube
{
    char c;
    bool visited;
} grid [NUM_CUBES];



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

Boggle::Boggle()
{
    this->shuffleCubes();

}

void Boggle::shuffleCubes()
{
    shuffle(shuffledCubes, NUM_CUBES);
    for (int i = 0; i < NUM_CUBES; i++)
    {
        grid[i].c = shuffledCubes[i].at(randomInteger(0,5));
        grid[i].visited = false;
    }
}

void Boggle::setBoard(const string cubeFaces)
{
    for (int i = 0; i < NUM_CUBES; i++)
    {
        grid[i].c = cubeFaces.at(i);
        grid[i].visited = false;
    }
}

bool Boggle::isWordInLexicon(const string word)
{
    return wordList.contains(word);
}

/*
void nextCharInChain(const int& i, const int& j, int& length, vector<string>& possibleWords)
{

}
*/

void getWordsForPoint(const int& index, const string& prefix, vector<string>& possibleWords)
{
    if () // PSUEDO: prefix is in lexicon (kan hitta bara de första bokstäverna?)
    {
        // Kolla om de finns i lexicon + fortsätt (prefix.length() > 4)
        grid[index].visited = true;

        int x = index % 4;
        int y = index / 4;

        vector<int> nextIndex;
        for (int i = 0; i < 16; i++)
        {
            int newX = i % 4;
            int newY = i / 4;
            if ( !grid[index].visited && newX != (x + 2) % 4 && newY != (y + 2) % 4 )
            {
                nextIndex.push_back(i);
            }
        }

        for (vector<int>::iterator newIndex = nextIndex.begin(); newIndex != nextIndex.end(); newIndex++)
        {
            string newPrefix = prefix + grid[*newIndex];
            getWordsForPoint(*newIndex, newPrefix, possibleWords);
        }
    }
}

vector<string> Boggle::getWordsOnBoard()
{
    vector<string> possibleWords;

    for (int index = 0; i < 16; i++)
    {
        string prefix = grid[index].c;
        getWordsForPoint(index, prefix, possibleWords);
    }
}
