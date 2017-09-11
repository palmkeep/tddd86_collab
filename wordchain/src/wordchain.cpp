#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <iterator>
#include <unordered_set>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";


bool checkWordAgainstDictionary(string word){
    ifstream inDictionary;
    inDictionary.open("dictionary.txt");
    string dictWord;

    inDictionary >> dictWord;
    while(!inDictionary.eof()){
        if(dictWord == word) {
            inDictionary.close();
            return true;
        }
        inDictionary >> dictWord;
    }
    inDictionary.close();
    return false;
}

void wordChain(string word1, string word2){
    queue<stack<string>> queueOfStacks;
    stack<string> words;
    words.push(word1);
    queueOfStacks.push(words);
    unordered_set<string> prevWords;

    while(!queueOfStacks.empty())
    {
        stack<string> currentStack = queueOfStacks.front();
        string currentWord = currentStack.top();

        if (word2 == currentWord) {
            cout << queueOfStacks.front().top() << endl;
        }
        else
        {
            for(int i = 0; currentWord.size(); ++i){
                for(string::const_iterator letter=ALPHABET.begin(); letter!=ALPHABET.end(); ++letter) {
                    string newWord = currentWord;
                    char diffChar = *letter;
                    newWord[i] = diffChar;

                    if (checkWordAgainstDictionary(newWord)) {
                        currentStack.push(newWord);
                        prevWords.insert(newWord);
                    }
                }
            }
        }


        queueOfStacks.pop();
    }

    //FELMEDDELANDE
}


int main() {
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    cout << "Please type two words: ";
    string word1, word2;
    cin >> word1 >> word2;
    cout << "Chain from " << word1 << " back to " << word2 << ":" << endl;

    wordChain(word1, word2);

    // TODO: Finish the program!

    return 0;
}
