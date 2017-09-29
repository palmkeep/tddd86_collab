#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <iterator>
#include <unordered_set>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";
unordered_set<string> prevWords;
unordered_set<string> dictionary;



void initDictionary()
{
    ifstream inDictionary;
    inDictionary.open("dictionary.txt");

    string dictWord;
    while(!inDictionary.eof())
    {
        inDictionary >> dictWord;
        dictionary.insert(dictWord);
    }
}


bool checkIsValidNewWord(string word)
{

    unordered_set<string>::const_iterator dictIterator = dictionary.find(word);

    if (dictIterator == dictionary.end())
    {
        return false;
    }
    else
    {
        unordered_set<string>::const_iterator prevWordsIterator = prevWords.find(word);
        if (prevWordsIterator == dictionary.end())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

stack<string> wordChain(string word1, string word2)
{
    queue<stack<string>> queueOfStacks;
    stack<string> words;
    words.push(word1);
    queueOfStacks.push(words);

    prevWords.insert(word1);

    while(!queueOfStacks.empty())
    {
        stack<string> currentStack = queueOfStacks.front();
        string currentWord = currentStack.top();

        for(int i = 0; i < currentWord.size(); ++i)
        {
            for(string::const_iterator letter=ALPHABET.begin(); letter!=ALPHABET.end(); ++letter)
            {
                string newWord = currentWord;
                //char diffChar = *letter;
                newWord[i] = *letter;
                if (word2 == newWord)
                {
                    currentStack.push(newWord);
                    return currentStack;        //Subroutine exit
                }
                else if (checkIsValidNewWord(newWord))
                {
                    //cout << newWord << endl;
                    stack<string> newStack = currentStack;
                    newStack.push(newWord);
                    queueOfStacks.push(newStack);
                    prevWords.insert(newWord);
                }
            }
        }
        queueOfStacks.pop();
    }
}


int main() {
    initDictionary();
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    cout << "Please type two words: ";
    string word1, word2;
    cin >> word1 >> word2;
    cout << "Chain from " << word1 << " back to " << word2 << ":" << endl;


    stack<string> correctStack;
    correctStack = wordChain(word1, word2);


    while (!correctStack.empty())
    {
        cout << correctStack.top();
        cout << ' ';
        correctStack.pop();
    }
    cout << endl;

    return 0;
}
