// This is a .h file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "lexicon.h"
#include "grid.h"
#include "simpio.h"
using namespace std;

class Boggle {
public:
    Boggle(Lexicon& dictionary, string boardText = "");
    char getLetter(int row, int col);
    bool checkWord(string word);
    bool humanWordSearch(string word);
    Set<string> computerWordSearch();
    int getScoreHuman();
    int getScoreComputer();

    // TODO: add any other member functions/variables necessary
    Lexicon dictionary;
    friend ostream& operator<<(ostream& out, Boggle& boggle);
    Grid<char> board;
    void generateBoard(int size);
    void displayBoard();
    void humanTurn();
    void computerTurn();
    Set<string> computerWords;
    Vector<string> usedWords;


private:

    string compWord;
    bool wordBeenUsed(string word);
    bool wordHasPotential(string word);
    int lastLetterRow;
    int lastLetterCol;
    bool alreadyUsedByComputer(string word);
};

#endif // _boggle_h
