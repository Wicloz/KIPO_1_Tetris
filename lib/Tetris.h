//
// Created by hermes on 28-1-18.
//

#ifndef TETRIS_TETRIS_H
#define TETRIS_TETRIS_H

#include <iostream>
#include <ctime>         // for time stuff
#include <cstdlib>       // for rand ( )

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
    void clearrows();

    void displayboard();

    void letitfall(PieceName piece, int orientation, int position);

    void infothrowpiece(PieceName piece, int orientation, int position);

    bool endofgame();

    Tetris(int height, int width);

    Tetris();

    void statistics();

    int possibilities(PieceName piece);

    void computeorandpos(PieceName piece, int &orientation, int &position, int themove);

    void randomchoice(PieceName piece, int &orientation, int &position);

    void toprow(bool therow[wMAX], int &numberrow, int &empties);

    int numberempties(int numberrow);

    void playrandomgame();
};//Tetris

#endif //TETRIS_TETRIS_H