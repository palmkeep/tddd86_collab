#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

void wordChain(string word1, string word2){
    queue<stack<string>> queueOfStacks;
    stack<string> words;
    words.push(word1);
    queueOfStacks.push(words);

    while(!queueOfStacks.empty())
    {
        stack<string> currentStack = queueOfStacks.front();
        if (word2 == currentStack.top()) {
            return currentStack;
        }
        else
        {

        }
    }

    cout << queueOfStacks.front().top() << endl;
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
