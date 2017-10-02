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


//Returns the input string along with an array that contains the indicies of all occurences of inout guess.
pair<string, vector<int>> findGuessInWord(const string& word, const char& guess)
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
set<string> biggestDict(const char& guess, const set<string>& dictionary)
{
    stack< pair<string, vector<int>> > wordGuessOccurencePairs;
    for (set<string>::iterator word = dictionary.begin(); word != dictionary.end(); ++word)
    {
        wordGuessOccurencePairs.push( findGuessInWord(*word, guess) );
    }


    map< int, pair<string, vector<int>> > dictSet;  // ERROR: need to fix .insert() or similar for map datatype
    while ( !wordGuessOccurencePairs.empty() )
    {
        pair< string, vector<int> > wordGuessOccurence = wordGuessOccurencePairs.top();

        string word = wordGuessOccurence.first;
        vector<int> guessIndex = wordGuessOccurence.second;
        int correctGuessInWord = (wordGuessOccurence.second).size();
        if (dictSet.find(correctGuessInWord))
        {
            dictSet.insert(correctGuessInWord, wordGuessOccurence);
        } // WHAT IF NOT?
    }

    int biggestDict;
    for (map<int, pair<string, vector<int>> >::iterator dict = dictSet.begin(); dict != dictSet.end(); ++dict)
    {
        if (*dict.second)
    }
}


//Reads in all the words of length $wordLength from the dictionary from dictionary.txt.
set<string> initDictionary(const u_int wordLength)
{
    ifstream inDictionary;
    inDictionary.open("dictionary.txt");

    set<string> dictionary;
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
        string currentWord = *word;

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


// To be constructed!!!
set<string> applyConstraint(const set<string>& prevDict, string constraint, char guess)
{

    int lengthWord = (*prevDict.begin()).size(); // COMMENT GOES HERE
    set<string> newDict;
    for (int i = 0; i < lengthWord; i++)
    {
        for (set<string>::iterator dictIt = prevDict.begin(); dictIt != prevDict.end(); ++dictIt)
        {
            if ((*dictIt)[i] == guess)
            {

            }
        }
    }
    return newDict;
}


// Main loop
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
        cout << "Guess a new character: " << endl;
        char guess;
        cin >> guess;
        dictionary = applyConstraint(dictionary, constraint, guess);
    }

    cout << endl << endl;
    cout << dictionary.size() << endl;
    for(set<string>::iterator setIt = dictionary.begin(); setIt != dictionary.end(); ++setIt)
    {
        cout << *setIt << endl;
    }
    

    return 0;
}
