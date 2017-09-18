#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <iterator>
#include <set>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

set<string> dictionary;
//Maybe not the right data type??


void initDictionary(u_int wordLength)
//Reads in all the words of length $wordLength from the dictionary from dictionary.txt.
{
    ifstream inDictionary;
    inDictionary.open("dictionary.txt");

    string dictWord;
    while(!inDictionary.eof())
    {
        inDictionary >> dictWord;
        if (dictWord.size() == wordLength)
        {
            dictionary.insert(dictWord);
        }
    }
}

set<string> updateDictionary(string wordConstraints)
// Singles out the stupid words from dic.
{
    queue< pair<char, int> > constraintsQueue;
    for(string::iterator constIt=wordConstraints.begin(); constIt!=wordConstraints.end(); ++constIt)
    {
        if (*constIt != '_')
        {
            constraintsQueue.push(pair<char, int>(*constIt, distance(wordConstraints.begin(), constIt)));
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


    cout << endl;



    set<string> newDictionary;
    for(set<string>::iterator setIt=dictionary.begin(); setIt!=dictionary.end(); ++setIt)
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


int main()
{
    cout << "Welcome to Hangman." << endl;

    int wordLength;
    cout << "Enter word length: " << endl;
    cin >> wordLength;

    int numGuesses;
    cout << "Enter number of guesses: " << endl;
    cin >> numGuesses;

    initDictionary(wordLength);

    string constraint = ;
    for (int i = 0; i < numGuesses; i++)
    {
        char guess;
        cin >> guess;


    }

    cout << endl << endl;
    cout << dictionary.size() << endl;
    for(set<string>::iterator setIt=dictionary.begin(); setIt!=dictionary.end(); ++setIt)
    {
        cout << *setIt << endl;
    }
    // TODO: Finish the program!

    return 0;
}
