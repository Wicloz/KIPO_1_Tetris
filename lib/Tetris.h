#ifndef TETRIS_TETRIS_H
#define TETRIS_TETRIS_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>

using namespace std;

enum PieceName {
    Sq, LG, RG, LS, RS, I, T
};

const int wMAX = 20;            // maximum width of the game board
const int hMAX = 20;            // maximum total height of the game board
const int numEvals = 1000;      // number of evaluations per branch for the monte carlo strategy

class Tetris {
private:
    int h, w;                   // actual height and width
    bool board[hMAX][wMAX];     // the game board; board[i][j] true <=> occupied
    int piececount;             // number of pieces that has been used so far
    int rowscleared;            // number of rows cleared so far
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

    void topRow(bool *therow, int &numberrow, int &empties);

    int numberOfEmpties(int numberrow);

    int getSmartScore();

    void playGameSkeleton(bool output, void (*callback)(Tetris&, PieceName, int&, int&, double&));

    void playRandomGame(bool output);

    void playSmartGame(bool output);

    void playSmarterGame(bool output);

    static void randomGameDetermineBest(Tetris& tetris, PieceName randomPiece, int& bestOrientation, int& bestPosition, double& extra);

    static void smartGameDetermineBest(Tetris& tetris, PieceName randomPiece, int& bestOrientation, int& bestPosition, double& extra);

    static void smarterGameDetermineBest(Tetris& tetris, PieceName randomPiece, int& bestOrientation, int& bestPosition, double& extra);
};

#endif //TETRIS_TETRIS_H
