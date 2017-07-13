#include "grid.h"
#include "lexicon.h"
#include "shuffle.h"
#include "Boggle.h"
using namespace std;

void playOneGame(Lexicon& dictionary) {
    Boggle game(dictionary);
    game.generateBoard(4);
    game.displayBoard();
    game.humanTurn();

    cout << "Your score: " << game.getScoreHuman() << endl;
    cout << "It's my turn!" << endl;

    game.computerTurn();
    cout << "My words are: (" << game.computerWords.size() << ")" << endl;
    Set<string>::iterator it;
    for (it = game.computerWords.begin(); it != game.computerWords.end(); ++it)
    {
        string compWord = *it;
        cout << compWord << " ";
    }
    cout << "" << endl;
    cout << "My score: " << game.getScoreComputer() << endl;

    if (game.getScoreComputer() > game.getScoreHuman()) {
        cout << "Ha Ha Ha.  I have crushed you, you measly human" << endl;
    }
    else if (game.getScoreHuman() > game.getScoreComputer()) {
        cout << "You have stunned me by beating me :(" << endl;
    }
    else {
        cout << "We have tied" << endl;
    }
}
