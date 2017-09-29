#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <iterator>
#include <set>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";


//Reads in all the words of length $wordLength from the dictionary from dictionary.txt.
set<string> initDictionary(const u_int& wordLength)
{
    ifstream inDictionary;
    inDictionary.open("dictionary.txt");

    string dictWord;
    set<string> dictionary;
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

// Singles out the bad words from dic.
set<string> updateDictionary(const set<string>& dictionary, const string& wordConstraints)
{

    // Creates a Queue of pairs containing each letter in the constraint alongside that letters index in the word
    queue< pair<char, int> > constraintsQueue;
    for(string::const_iterator constIt = wordConstraints.begin(); constIt != wordConstraints.end(); ++constIt)
    {
        if (*constIt != '_')
        {
            constraintsQueue.push(pair<char, int>(*constIt, distance(wordConstraints.begin(), constIt) ));
        }
    }

    int numConstraints = constraintsQueue.size();

    cout << "Constraints" << endl;
    for(int i = 0; i < numConstraints; i++)
    {
        pair<char,int> currentConstraint = constraintsQueue.front();
        cout << currentConstraint.first << ' ' << currentConstraint.second << endl;

        constraintsQueue.push(constraintsQueue.front());
        constraintsQueue.pop();
    }

    cout << endl; // Huh?

    set<string> newDictionary;
    for(set<string>::const_iterator setIt = dictionary.begin(); setIt != dictionary.end(); ++setIt)
    {
        pair<char, int> currentConstraint = constraintsQueue.front();
        string currentWord = *setIt;

        bool fitsConstraint = true;
        int i = 0;
        while(i < numConstraints && fitsConstraint)
        {
            /* DEBUG MODE
            cout << endl;
            cout << currentConstraint.first << ' ' << currentConstraint.second << endl;
            cout << currentWord << endl;
            */
            if(currentWord.at(currentConstraint.second) != currentConstraint.first)
            {
                fitsConstraint = false;
            }

            constraintsQueue.push(constraintsQueue.front());
            constraintsQueue.pop();
            currentConstraint = constraintsQueue.front();
            i += 1;
        }
        if (fitsConstraint)
        {
            newDictionary.insert(currentWord);
        }
    }

    return newDictionary;
}


// Gives back the largest dictionary given a guess from the user.
// Updates the constraint to match the new dictionary.
set<string> findLargestDictionary(const set<string> dictionary, const char& guess, string& constraint)
{
    set<string> largestDictionary;

    return largestDictionary; 
}


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
    for (int i = 0; i < wordLength; i++)
    {
        constraint += '_';
    }
    cout << constraint << endl;

    for (int i = 0; i < numGuesses; i++)
    {
        char guess;
        cin >> guess;


    }

    cout << endl << endl;
    cout << dictionary.size() << endl;
    for(set<string>::iterator setIt = dictionary.begin(); setIt != dictionary.end(); ++setIt)
    {
        cout << *setIt << endl;
    }
    // TODO: Finish the program!

    return 0;
}
