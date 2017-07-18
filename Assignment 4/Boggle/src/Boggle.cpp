// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "Boggle.h"
#include <stdlib.h>

// letters on all 6 sides of every cube
static string CUBES[16] = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

// letters on every cube in 5x5 "Big Boggle" version (extension)
static string BIG_BOGGLE_CUBES[25] = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

Boggle::Boggle(Lexicon& dictionary, string boardText) {
    this->dictionary = dictionary;
}

void Boggle::generateBoard(int size) {
    this->board = Grid<char>(size,size);
    for (int i=0; i < sizeof(CUBES)/sizeof(CUBES[0]); i++) {
        char randLetter = CUBES[i][randomInteger(0, CUBES[i].size()-1)]; //select random char from the string
        int row = i / size;
        int col;
        if (i < size) {
            col = i;
         }
        else {
            col = i % size;
        }

        this->board.set(row,col, randLetter);
    }

    shuffle(this->board);
}
void Boggle::displayBoard() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << this->board[i][j] << " ";
        }
        cout << "" << endl;
    }
}

bool Boggle::wordBeenUsed(string word) {
    for (int i = 0; i < this->usedWords.size(); i++) {
        if (this->usedWords[i] == word) return true;
    }
    return false;
}


void Boggle::humanTurn() {
    string word;

    while (true) {
        cout << "Type a word (or Enter to stop): ";
        word = getLine();
        if (word == "") break;

        if (!this->checkWord(word)) {
            cout << "Invalid word" << endl;
        }
        else if (!this->humanWordSearch(word + "$" + "99")) {
            cout << "Word not present in board" << endl;
        }

        else {
            cout << "You found a new word!" << "'" << word << "'" << endl;
            this->usedWords.add(word);
            cout << "Your words (" << this->usedWords.size() << "): ";
            for (int i = 0; i < usedWords.size(); i++){
                cout << "'" << usedWords[i] << "'";
                if (i < usedWords.size() - 1) {
                    cout << ",";
                }
                else {
                    cout << "" << endl;
                }
            }
        }
    }
}

char Boggle::getLetter(int row, int col) {
    return this->board[row][col];
}

bool Boggle::checkWord(string word) {
    return this->dictionary.contains(word) && word.length() >= 4 && !wordBeenUsed(word);
}

//overall, this function tries to look if first letter exists on board
//if it does, recursively pass in the rest of the word (without first letter)
//and search the adjacent positions for the first letter of the modified word
//making sure not to use the same position twice
bool Boggle::humanWordSearch(string word) {
    //word that gets passed in is the letters plus positions that have been used
    //in the search, separated by the delimiter
    int indexOfDelimiter = word.find("$");
    string usedPositions = word.substr(indexOfDelimiter + 1, word.length()-indexOfDelimiter);
    string actualWord = word.substr(0, indexOfDelimiter);

    int startingRowForLoop;
    int startingColForLoop;
    int finalRowForLoop;
    int finalColForLoop;

    //iterate thru string of used positions, and create vector
    //of vectors.  Each sub-vector represents
    //row and column of a letter that's been used already
    Vector<Vector<int>> usedPositionVector;
    for (int i = 0; i < usedPositions.length(); i++) {
        if (i % 2 != 0 ) {
            Vector<int> indexVector;
            indexVector.add(usedPositions[i-1]);
            indexVector.add(usedPositions[i]);
        }
    }
    //the 2 numbers at the end of the list of 'usedPositions'
    //represent row and column of previous character, respectively
    int rowOfPrevChar = stoi(usedPositions.substr(usedPositions.size()-2, 1));
    int colOfPrevChar = stoi(usedPositions.substr(usedPositions.size()-1, 1));

    //use this location to determine which values to loop thru
    if (rowOfPrevChar == 9) {
        startingRowForLoop = 0;
        finalRowForLoop = 3;
    }
    else if (rowOfPrevChar == 0) {
        startingRowForLoop = 0;
        finalRowForLoop = 1;
    }
    else {
        startingRowForLoop = rowOfPrevChar - 1;
        if (rowOfPrevChar == 3) {
            finalRowForLoop = 3;
        }
        else {
            finalRowForLoop = rowOfPrevChar + 1;
        }
    }
    if (colOfPrevChar == 9) {
        startingColForLoop = 0;
        finalColForLoop = 3;
    }
    else if (colOfPrevChar == 0) {
        startingColForLoop = 0;
        finalColForLoop = 1;
    }
    else {
        startingColForLoop = colOfPrevChar - 1;
        if (colOfPrevChar == 3) {
            finalColForLoop = 3;
        }
        else {
            finalColForLoop = colOfPrevChar + 1;
        }
    }

    for (int i = startingRowForLoop; i <= finalRowForLoop; i++) {
        for (int j = startingColForLoop; j <= finalColForLoop; j++) {
            char letterOnBoard = this->getLetter(i, j);
            char firstLetter = actualWord[0];
            bool positionBeenUsed = false;
            //skip any position that's already been used in the word
            for (int k = 0; k < usedPositionVector.size(); k++) {
                if (usedPositionVector[k][0] == i && usedPositionVector[k][1] == j) {
                    positionBeenUsed = true;
                }
            }
            if (positionBeenUsed) continue;

            if (letterOnBoard == firstLetter) {
                if (actualWord.length() == 1) {
                    return true;
                }
                else {
                    return this->humanWordSearch(actualWord.substr(1, actualWord.size()) + "$" + usedPositions + to_string(i) + to_string(j));
                }
            }
        }
    }


    return false;
}

int Boggle::getScoreHuman() {
    int score = 0;
    for (int i = 0; i < this->usedWords.size(); i++) {
        int wordLen = this->usedWords[i].length();
        int scoreForWord = 1 + (wordLen - 4);
        score += scoreForWord;
    }
    return score;
}



Vector<Vector<int>> findNeighborIndices(int i, int j) {
    Vector<Vector<int>> neighborIndices;
    if (i - 1 >= 0) {
        Vector<int> neighborIndex;
        neighborIndex.add(i-1);
        neighborIndex.add(j);
        neighborIndices.add(neighborIndex); //cube above
        if (j - 1 >= 0) {
            neighborIndex.clear();
            neighborIndex.add(i-1);
            neighborIndex.add(j-1);
            neighborIndices.add(neighborIndex); //cube above and left
        }
        if (j+1 <= 3) {
            neighborIndex.clear();
            neighborIndex.add(i-1);
            neighborIndex.add(j+1);
            neighborIndices.add(neighborIndex); //cube above and right
        }
    }
    if (i+1 <= 3) {
        Vector<int> neighborIndex;
        neighborIndex.add(i+1);
        neighborIndex.add(j);
        neighborIndices.add(neighborIndex); //cube below
        if (j - 1 >= 0) {
            neighborIndex.clear();
            neighborIndex.add(i+1);
            neighborIndex.add(j-1);
            neighborIndices.add(neighborIndex); //cube below and left
        }
        if (j+1 <= 3) {
            neighborIndex.clear();
            neighborIndex.add(i+1);
            neighborIndex.add(j+1);
            neighborIndices.add(neighborIndex); //cube below and right
        }
    }
    if (j - 1 >= 0) {
        Vector<int> neighborIndex;
        neighborIndex.add(i);
        neighborIndex.add(j-1);
        neighborIndices.add(neighborIndex); //cube left
    }
    if (j + 1 <= 3) {
        Vector<int> neighborIndex;
        neighborIndex.add(i);
        neighborIndex.add(j+1);
        neighborIndices.add(neighborIndex); //cube right
    }
    return neighborIndices;
}

bool Boggle::wordHasPotential(string word) {
    if (this->dictionary.containsPrefix(word)) {
        return true;
    }
    else {
        return false;
    }

}

bool Boggle::alreadyUsedByComputer(string word) {
    Set<string>::iterator it;
    for (it = this->computerWords.begin(); it != this->computerWords.end(); ++it)
    {
        string compWord = *it; // Note the "*" here
        if (compWord == word) return true;
    }
    return false;
}

void Boggle::computerTurn() {
    this->compWord = "";
    for (int i = 0; i < 4; i++) { //only explore first row for now
        for (int j = 0; j < 4; j++) {
            char cube = getLetter(i,j);
            if (islower(cube)){
                continue;
            }
            this->compWord += cube;
            this->board.set(i, j, tolower(cube)); //convert to lowercase to mark as visited

            this->lastLetterRow = i;
            this->lastLetterCol = j;
            computerWordSearch();
            this->board.set(i, j, toupper(cube));
            this->compWord = this->compWord.substr(0, this->compWord.size() - 1);
        }
    }

    return;
}

Set<string> Boggle::computerWordSearch() {
    if (checkWord(this->compWord) && !alreadyUsedByComputer(this->compWord)) {
        this->computerWords.add(this->compWord);
    }
    if(!wordHasPotential(this->compWord)) {
        Set<string> emptySet;
        return emptySet;
    }
    Vector<Vector<int>> neighborIndices = findNeighborIndices(this->lastLetterRow, this->lastLetterCol);
    for (int k = 0; k < neighborIndices.size(); k++) {
        int rowNeighbor = neighborIndices[k][0];
        int colNeighbor = neighborIndices[k][1];
        char neighborCube = getLetter(rowNeighbor, colNeighbor);

        if (islower(neighborCube)){
            continue;
        }

        this->board.set(rowNeighbor, colNeighbor, tolower(neighborCube)); //convert to lowercase to mark as visited

        this->compWord += neighborCube;
        this->lastLetterRow = rowNeighbor;
        this->lastLetterCol = colNeighbor;

        computerWordSearch();
        this->compWord = this->compWord.substr(0, this->compWord.size() - 1);
        this->board.set(rowNeighbor, colNeighbor, toupper(neighborCube));
    }

    return this->computerWords;
}

int Boggle::getScoreComputer() {
    int score = 0;

    Set<string>::iterator it;
    for (it = this->computerWords.begin(); it != this->computerWords.end(); ++it)
    {
        string compWord = *it;
        int wordLen = compWord.length();
        int scoreForWord = 1 + (wordLen - 4);
        score += scoreForWord;
    }

    return score;
}

ostream& operator<<(ostream& out, Boggle& boggle) {
    // TODO: implement
    return out;
}
