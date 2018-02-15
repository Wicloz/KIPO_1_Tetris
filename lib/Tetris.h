#ifndef TETRIS_TETRIS_H
#define TETRIS_TETRIS_H

#include <iostream>
#include <ctime>         // for time stuff
#include <cstdlib>       // for rand ( )
#include <climits>

using namespace std;

enum PieceName {
    Sq, LG, RG, LS, RS, I, T
};

const int wMAX = 20;     // maximum width of the game board
const int hMAX = 15;     // maximum total height of the game board

class Tetris {
private:
    int h, w;               // actual height and width
    bool board[hMAX][wMAX]; // the game board; board[i][j] true <=> occupied
    int piececount;         // number of pieces that has been used so far
    int rowscleared;        // number of rows cleared so far
public:
    void clearFullRows();

    void displayBoard();

    void dropPiece(PieceName piece, int orientation, int position);

    void printInfoCurrentPiece(PieceName piece, int orientation, int position);

    bool endOfGame();

    Tetris(int height, int width);

    Tetris();

    void statistics();

    int possibilities(PieceName piece);

    void computeOrAndPos(PieceName piece, int &orientation, int &position, int themove);

    void randomChoice(PieceName piece, int &orientation, int &position);

    void topRow(bool *therow, int &numberrow, int &empties);

    int numberOfEmpties(int numberrow);

    int getSmartScore();

    void playRandomGame();

    void playSmartGame();

    void playSmarterGame();

    void playRandomSilentGame(int &score, PieceName piece, int orientation, int position);
};

#endif //TETRIS_TETRIS_H
