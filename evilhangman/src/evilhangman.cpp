#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <iterator>
#include <set>
#include <unordered_set>
#include <vector>

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
            indexGuessOccurence.insert(i);
        }
    }
    return pair <word, indexGuessOccurence>;
}


//Reads in all the words of length $wordLength from the dictionary from dictionary.txt.
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

// Singles out the stupid words from dic.
set<string> updateDictionary(string wordConstraints, set<string> dictionary)
{
    queue< pair<char, int> > constraintsQueue;
    for(string::iterator constIt = wordConstraints.begin(); constIt != wordConstraints.end(); ++constIt)
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
    for(set<string>::iterator setIt = dictionary.begin(); setIt != dictionary.end(); ++setIt)
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

    for (int i = 0; i < numGuesses; i++)
    {
        cout << "Guess a new character: " << endl;
        char guess;
        cin >> guess;
        dictionary = applyConstraint(dictionary, constraint, guess);
    }

    cout << endl << endl;
    cout << dictionary.size() << endl;
    for(set<string>::iterator setIt=dictionary.begin(); setIt!=dictionary.end(); ++setIt)
    {
        cout << *setIt << endl;
    }
    

    return 0;
}
