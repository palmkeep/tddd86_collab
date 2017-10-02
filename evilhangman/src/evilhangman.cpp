#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <iterator>
#include <set>
#include <unordered_set>
#include <vector>
#include <map>
#include <stack>

using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";


// Reads in all the words of length $wordLength from the dictionary from dictionary.txt.
set<string> initDictionary(const u_int wordLength)
{
    ifstream inDictionary;
    inDictionary.open("dictionary.txt");

    set<string> dictionary;
    string dictWord;
    while(!inDictionary.eof())
    {
        inDictionary >> dictWord;
        if (dictWord.size() == wordLength)
        {
            dictionary.insert(dictWord);
        }
    }

    return dictionary;
}


//Returns the input string along with an array that contains the indicies of all occurences of inout guess.
pair< string, vector<int> > findGuessInWord(const string& word, const char& guess)
{
    vector<int> indexGuessOccurence;
    int lengthWord = word.size();
    for (int i = 0; i < lengthWord; i++)
    {
        if (word[i] == guess)
        {
            indexGuessOccurence.push_back(i);
        }
    }
    pair<string, vector<int>> wordPair(word,indexGuessOccurence);
    return wordPair;
}


// Find and return the largest dictionary
vector<int> findBiggestDictionary(const char guess, set<string>& dictionary)
{
    // Creates a stack containing pairs of words and the indices of the guessed letter
    stack< pair<string, vector<int>> > wordGuessOccurencePairs;
    for (set<string>::iterator word = dictionary.begin(); word != dictionary.end(); ++word)
    {
        wordGuessOccurencePairs.push( findGuessInWord(*word, guess) );
    }


    // Divides the pairs in the stack generated into sets where all words in a set share the same
    // index vector
    map< vector<int>, set<string> > dictSet;
    while ( !wordGuessOccurencePairs.empty() )
    {
        pair< string, vector<int> > wordGuessOccurence = wordGuessOccurencePairs.top();
        string word = wordGuessOccurence.first;
        vector<int> guessIndex = wordGuessOccurence.second;
        dictSet.find(guessIndex);

        set<string> &newDictionary = dictSet[guessIndex];
        newDictionary.insert(word);

        wordGuessOccurencePairs.pop();
    }

    // Picks out the largest and worst (one that gives the feweset letters in the constraint) set of strings
    int sizeBiggestDict = 0;
    int biggestBonusPoints = 0;
    vector<int> newConstraint;
    set<string> biggestDictionary;
    const string leastCommonLetters = "qjxz";
    for (map< vector<int>, set<string> >::iterator dict = dictSet.begin(); dict != dictSet.end(); ++dict)
    {

        int bonusPoints = 0;
        for (set<string>::const_iterator word = (dict->second).begin(); word != (dict->second).end(); ++word) // E2: Calculate bonus for having hard to guess letters in the dictionary
        {
            for (string::const_iterator stringIt = leastCommonLetters.begin(); stringIt != leastCommonLetters.end(); ++stringIt)
            {
                if ((*word).find(*stringIt) != string::npos)
                {
                    bonusPoints += 1;
                }
            }
        }
        if ( (dictSet.at(dict->first)).size() + bonusPoints >= sizeBiggestDict + biggestBonusPoints ) // E2: will be handled by the extra weight given by bonusPoints
        {
            if ( (dictSet.at(dict->first)).size() + bonusPoints == sizeBiggestDict + biggestBonusPoints ) // E1: will be handled by this and the next if-statement
            {
                if ( (dict->first).size() < newConstraint.size() )
                {
                    biggestDictionary = dictSet.at(dict->first);
                    newConstraint = dict->first;
                    sizeBiggestDict = dictSet.at(dict->first).size();
                    biggestBonusPoints = bonusPoints;
                }
            }
            else
            {
                biggestDictionary = dictSet.at(dict->first);
                newConstraint = dict->first;
                sizeBiggestDict = dictSet.at(dict->first).size();
                biggestBonusPoints = bonusPoints;
            }
        }
    }

    dictionary = biggestDictionary;
    return newConstraint;
    //return make_pair(dictionary, newConstraint);
}



// Main loop handles user input and updates the dictionary of possible words accordingly
// quits when the player has guessed the correct word or ran out of guesses
int main()
{
    cout << "Welcome to Hangman." << endl;

    int wordLength;
    cout << "Enter word length: " << endl;
    cin >> wordLength;

    int numGuesses;
    cout << "Enter number of guesses: " << endl;
    cin >> numGuesses;

 
    set<string> dictionary = initDictionary(wordLength);


    string constraint;
    int numBlanks = 0;
    for (int i = 0; i < wordLength; i++)
    {
        constraint += '_';
        numBlanks += 1;
    }
    cout << constraint << endl;



    while (numGuesses > 0)
    {
        cout << "Guess a new character: " << endl;
        char guess;
        cin >> guess;

        if (numGuesses == 1)    // E1: Handles the last guess without E2 interfering
        {
            for (set<string>::const_iterator word = dictionary.begin(); word != dictionary.end(); ++word)
            {
                if ((*word).find(guess) == string::npos)
                {
                    cout << "YOU LOST!" << endl;
                    return 0;
                }
            }
        }

        vector<int> newConstraint = findBiggestDictionary(guess, dictionary);


        for (vector<int>::iterator it = newConstraint.begin(); it != newConstraint.end(); ++it)
        {
            constraint.at(*it) = guess;
        }
        cout << constraint << endl;

        int numBlanks = 0;
        for (string::iterator it = constraint.begin(); it != constraint.end(); ++it)
        {
            if (*it == '_')
            {
                numBlanks += 1;
            }
        }
        if (numBlanks == 0)
        {
            cout << "YOU WIN!" << endl;
            break;
        }


        if (newConstraint.size() == 0)
        {
            numGuesses -= 1;
        }
    }

    if (numGuesses == 0)
    {
        cout << "YOU LOST!" << endl;
    }

    /* DEBUG
    cout << endl << endl;
    cout << dictionary.size() << endl;
    for(set<string>::iterator setIt = dictionary.begin(); setIt != dictionary.end(); ++setIt)
    {
        cout << *setIt << endl;
    }
    */
    

    return 0;
}
