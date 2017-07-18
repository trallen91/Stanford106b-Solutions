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



using namespace std;

ifstream in;

void GetStream(ifstream &in) {
    while(true) {
        cout << "Input file name? ";
        string fileName = getLine();
        in.open(fileName.c_str());
        if (!in.fail()) break;
        in.clear();
        cout << "File open error." << endl;
    }
    return;
}

Map<Queue<string>,Vector<string>> CreateMap(ifstream &in, int intOfN) {
    Map<Queue<string>,Vector<string>> gramMap;
    Queue<string> firstWindow;
    string word;
    Queue<string> window;
    int countOfWords = 0;
    while (in >> word)
    {
        countOfWords++;
        if (countOfWords < intOfN) {
            window.enqueue(word);
        }
        else {
            if (gramMap.containsKey(window)) {
                gramMap[window].add(word);
            }
            else {
                Vector<string> newVal;
                newVal.add(word);
                gramMap[window] = newVal;
            }
            if (countOfWords == intOfN) {
                firstWindow = window; //store the first queue
            }
            window.dequeue();
            window.enqueue(word);
        }
    }

    //loop through the first key, which was stored as variable, to do all the wrapping
    while(firstWindow.size()) {
        string wrappedWord = firstWindow.dequeue();
        if (gramMap.containsKey(window)) {
            gramMap[window].add(wrappedWord);
        }
        else {
            Vector<string> newVal;
            newVal.add(wrappedWord);
            gramMap[window] = newVal;
        }
        window.dequeue();
        window.enqueue(wrappedWord);
    }


    return gramMap;
}

void GenerateText(Map<Queue<string>, Vector<string>> gramMap, int numWords) {
    Vector<Queue<string>> allKeys = gramMap.keys();
    int randKeyIndex = randomInteger(0, (allKeys.size()-1));
    Queue<string> randKey = allKeys[randKeyIndex];
    Queue<string> copyForText = randKey;
    int outputtedWords = 0;

    cout << "...";

    //output the contents of initially selected key
    while (copyForText.size()) {
        cout << copyForText.dequeue() << " ";
        outputtedWords++;
    }

    while(outputtedWords < numWords) {
        int randValueIndex = randomInteger(0, (gramMap[randKey].size()-1));
        string randSuffix = gramMap[randKey][randValueIndex];
        cout << randSuffix << " ";
        outputtedWords++;

        randKey.dequeue();
        randKey.enqueue(randSuffix);
    }

    cout << "..." << endl;
    return;
}

int main() {
    GetStream(in);
    cout << "Value of N? ";
    string stringOfN = getLine();
    int intOfN = stringToInteger(stringOfN);

    Map<Queue<string>,Vector<string>> wordMap = CreateMap(in, intOfN);

    cout << "Number of words? ";
    string stringOfNumWords = getLine();
    int numWords = stringToInteger(stringOfNumWords);

    GenerateText(wordMap, numWords);

    //code for printing out the wordMap generated
    /*
    Vector<Queue<string>> keys = wordMap.keys();

    for (int i = 0; i < keys.size(); i++) {
        cout << "Key: " << integerToString(i);
        Queue<string> keyCopy = keys[i];
        while(keyCopy.size()) {
            cout << " " << keyCopy.dequeue();
        }
        cout << "" << endl;
        cout << "Value: " << integerToString(i);
        for (int k=0; k < wordMap[keys[i]].size(); k++) {
            cout << " " << wordMap[keys[i]][k];
        }
        cout << "" << endl;
    }*/

    return 0;
}
