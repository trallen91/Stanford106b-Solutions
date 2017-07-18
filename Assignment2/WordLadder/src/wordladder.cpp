//TODO:  Make insensitive to case

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "queue.h"
#include "stack.h"
#include "map.h"
#include <algorithm>

using namespace std;

//this method is not my code.  Got it online for an easy way to get a file -TA
void GetStream(ifstream &in) {
    while(true) {
        cout << "Enter data filename: ";
        string fileName = getLine();
        in.open(fileName.c_str());
        if (!in.fail()) break;
        in.clear();
        cout << "File open error." << endl;
    }
    return;
}

void createDictionary(ifstream &in, Map<string,bool> &map) {
    string line;
    while(true) {
        getline(in, line);
        if (in.fail()) break; // end of file
        map[line] = true;
    }
}

bool isValidWord(string word, Map<string, bool> dictionaryMap){
    if (dictionaryMap[word]) {
        return true;
    }
    else {
        return false;
    }
}

bool wordAlreadyUsed(string word, Vector<string> wordsUsed) {
    for (int i = 0; i < wordsUsed.size(); i++) {
        if (wordsUsed[i] == word) {
            return true;
        }
    }
    return false;
}

int main() {
    Map<string, bool> dictionaryMap;
    ifstream in;
    Vector<string> allWordsUsed; //vector to hold all words that were ever put in any stack
    Stack<string> ladder;
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    Queue<Stack<string>> wordQ;
    Stack<string> wordStack;
    bool wordFound; //bool used to establish whether the ladder has been connected, so that all loops can be broken

    GetStream(in);
    createDictionary(in, dictionaryMap); //create Map to represent dictionary

    cout << "Enter first word:";
    string w1 = getLine();
    cout << "Enter second word:";
    transform(w1.begin(), w1.end(), w1.begin(), ::tolower);
    string w2 = getLine();
    transform(w2.begin(), w2.end(), w2.begin(), ::tolower);
    wordStack.push(w1);
    wordQ.enqueue(wordStack);
    allWordsUsed.add(w1);

    while(wordQ.size() > 0) {
        ladder = wordQ.dequeue();
        for (int i = 0; i < ladder.peek().length(); i++) {
            for (int j = 0; j < alphabet.length(); j++) {
                string newWord = ladder.peek();
                newWord[i] = alphabet[j];
                if (isValidWord(newWord, dictionaryMap) && !wordAlreadyUsed(newWord, allWordsUsed)) {
                    allWordsUsed.add(newWord);
                    if (newWord == w2) {
                        wordFound = true;
                        break;
                    }
                    else {
                        Stack<string> newPartialLadder = ladder;
                        newPartialLadder.push(newWord);
                        wordQ.enqueue(newPartialLadder);
                    }

                }
            }
            if (wordFound) break;
        }
        if (wordFound) break;
    }
    cout << "A ladder from " << w2 << " back to " << w1 << ":" << endl;
    cout << w2 << " ";
    while (ladder.size() > 0) {
        cout << ladder.pop() << " " ;
    }
    return 0;
 }
