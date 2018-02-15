//
// aitetris.cc
// from http://www.liacs.leidenuniv.nl/~kosterswa/AI/
// January 22, 2018
// Walter Kosters, w.a.kosters@liacs.leidenuniv.nl
//
// Tetris playing programme
//
// Compile: g++ -Wall -O2 -o aitetris aitetris.cc 
//
// Every piece has a unique name (see below), orientation (0/1/2/3),
// and starting position (0...width of game board - 1), indicating
// the column of the leftmost square of the position of the piece.
// Note that possible orientation and position depend on the piece!
// As an example: move 7 (out of 34, being 0..33) for piece LG (a Left 
// Gun), on a width 10 board, corresponds with orientation 0, starting 
// in column 7.
//
// The program generates a random series of pieces, and then needs
// an orientation and position (random in this version, see the function
// playRandomSilentGame ( )); the piece then drops as required.
// After that rows are cleared, and the board is displayed.
//
// The board is of size h (height) times w (width);
// bottom left is (0,0); the top 3 rows are "outside" the board: 
// if part of a piece ends here, the game stops.
//
// If you have a piece, the function possibilities returns the number
// of possible moves p. These moves are denoted by 0,1,...,p-1. Given 
// a number n in this range, the function computeOrAndPos then computes
// the corresponding orientation and position. These can be used in
// the function dropPiece to drop the piece.
//

//
// The 7 pieces, with orientations:
//
//  LS  0:  XX     1:  X                          Left Snake
//           XX       XX
//                    X
//
//  RS  0:   XX    1: X                           Right Snake
//          XX        XX
//                     X
//
//  I   0:  XXXX   1:  X                          I
//                     X
//                     X
//                     X
//
//  Sq  always 0: XX                              Square
//                XX
//                
//  T   0:   XXX   1:  X     2:   X      3:   X   T
//            X        XX        XXX         XX
//                     X                      X
//
//  LG  0:  XXX    1:  XX    2:  X       3:   X   Left Gun
//            X        X         XXX          X
//                     X                     XX
//
//  RG  0:  XXX    1:  X     2:    X     3:  XX   Right Gun
//          X          X         XXX          X
//                     XX                     X
//                   

#include "../lib/Tetris.h"

// default constructor
Tetris::Tetris() {
    int i, j;
    h = hMAX;
    w = wMAX;
    for (i = 0; i < hMAX; i++)
        for (j = 0; j < wMAX; j++)
            board[i][j] = false;
}//Tetris::Tetris

// constructor
Tetris::Tetris(int height, int width) {
    int i, j;
    piececount = 0;
    rowscleared = 0;
    if (height < hMAX)
        h = height;
    else
        h = hMAX;
    if (4 <= width && width < wMAX)
        w = width;
    else
        w = wMAX;
    for (i = 0; i < hMAX; i++)
        for (j = 0; j < wMAX; j++)
            board[i][j] = false;
}//Tetris::Tetris

// some statistics
void Tetris::statistics() {
    cout << endl << "Done!" << endl
         << rowscleared << " row(s) cleared." << endl
         << piececount << " pieces." << endl << endl;
}//Tetris::statistics

// how many empties has row numberrow?
int Tetris::numberOfEmpties(int numberrow) {
    int j, theempties = w;
    for (j = 0; j < w; j++)
        if (board[numberrow][j])
            theempties--;
    return theempties;
}//Tetris::numberOfEmpties

// gives number of empties in heighest non-empty row,
// and copies this row into therow; its row index being numberrow
// if this is -1, the whole field is empty
void Tetris::topRow(bool *therow, int &numberrow, int &empties) {
    int i, j, theempties;
    numberrow = -1;
    empties = w;
    for (i = 0; i < h; i++) {
        theempties = numberOfEmpties(i);
        if (theempties < w) {
            for (j = 0; j < w; j++)
                therow[j] = board[i][j];
            empties = theempties;
            numberrow = i;
        }//if
    }//for
}//Tetris::topRow

// checks for full rows --- and removes them
void Tetris::clearFullRows() {
    int i, j, k;
    bool full;
    for (i = h - 2; i >= 0; i--) {
        full = true;
        j = 0;
        while (full && j < w)
            if (!board[i][j])
                full = false;
            else
                j++;
        if (full) {
            //cout << "Row cleared ..." << endl;
            rowscleared++;
            for (k = i; k < h - 1; k++)
                for (j = 0; j < w; j++)
                    board[k][j] = board[k + 1][j];
            for (j = 0; j < w; j++)
                board[h - 1][j] = false;
        }//if
    }//for
}//Tetris::clearFullRows

// displays current board on the screen
void Tetris::displayBoard() {
    int i, j;
    for (i = h - 1; i >= 0; i--) {
        if (i < h - 3)
            cout << "|";
        else
            cout << " ";
        for (j = 0; j < w; j++)
            if (board[i][j])
                cout << "X";
            else
                cout << " ";
        if (i < h - 3)
            cout << "|" << endl;
        else
            cout << endl;
    }//for
    for (j = 0; j < w + 2; j++)
        cout << "-";
    cout << endl;
    cout << " ";
    for (j = 0; j < w; j++)
        cout << j % 10;
    cout << endl;
}//Tetris::displayBoard

// let piece fall in position and orientation given
// assume it still fits in top rows
void Tetris::dropPiece(PieceName piece, int orientation, int position) {
    int x[4] = {0};
    int y[4] = {0};
    int i;
    piececount++;
    switch (piece) {
        case Sq:
            x[0] = position;
            y[0] = h - 2;
            x[1] = position;
            y[1] = h - 1;
            x[2] = position + 1;
            y[2] = h - 2;
            x[3] = position + 1;
            y[3] = h - 1;
            break;
        case LG:
            switch (orientation) {
                case 0:
                    x[0] = position + 2;
                    y[0] = h - 2;
                    x[1] = position + 2;
                    y[1] = h - 1;
                    x[2] = position + 1;
                    y[2] = h - 1;
                    x[3] = position;
                    y[3] = h - 1;
                    break;
                case 1:
                    x[0] = position;
                    y[0] = h - 3;
                    x[1] = position;
                    y[1] = h - 2;
                    x[2] = position;
                    y[2] = h - 1;
                    x[3] = position + 1;
                    y[3] = h - 1;
                    break;
                case 2:
                    x[0] = position;
                    y[0] = h - 2;
                    x[1] = position + 1;
                    y[1] = h - 2;
                    x[2] = position + 2;
                    y[2] = h - 2;
                    x[3] = position;
                    y[3] = h - 1;
                    break;
                case 3:
                    x[0] = position;
                    y[0] = h - 3;
                    x[1] = position + 1;
                    y[1] = h - 1;
                    x[2] = position + 1;
                    y[2] = h - 2;
                    x[3] = position + 1;
                    y[3] = h - 3;
                    break;
            }//switch
            break;
        case RG:
            switch (orientation) {
                case 0:
                    x[0] = position;
                    y[0] = h - 2;
                    x[1] = position + 2;
                    y[1] = h - 1;
                    x[2] = position + 1;
                    y[2] = h - 1;
                    x[3] = position;
                    y[3] = h - 1;
                    break;
                case 1:
                    x[0] = position;
                    y[0] = h - 3;
                    x[1] = position;
                    y[1] = h - 2;
                    x[2] = position;
                    y[2] = h - 1;
                    x[3] = position + 1;
                    y[3] = h - 3;
                    break;
                case 2:
                    x[0] = position;
                    y[0] = h - 2;
                    x[1] = position + 1;
                    y[1] = h - 2;
                    x[2] = position + 2;
                    y[2] = h - 2;
                    x[3] = position + 2;
                    y[3] = h - 1;
                    break;
                case 3:
                    x[0] = position + 1;
                    y[0] = h - 3;
                    x[1] = position + 1;
                    y[1] = h - 1;
                    x[2] = position + 1;
                    y[2] = h - 2;
                    x[3] = position;
                    y[3] = h - 1;
                    break;
            }//switch
            break;
        case LS:
            switch (orientation) {
                case 0:
                    x[0] = position + 1;
                    y[0] = h - 2;
                    x[1] = position + 1;
                    y[1] = h - 1;
                    x[2] = position + 2;
                    y[2] = h - 2;
                    x[3] = position;
                    y[3] = h - 1;

                    break;
                case 1:
                    x[0] = position;
                    y[0] = h - 3;
                    x[1] = position;
                    y[1] = h - 2;
                    x[2] = position + 1;
                    y[2] = h - 1;
                    x[3] = position + 1;
                    y[3] = h - 2;
                    break;
            }//switch
            break;
        case RS:
            switch (orientation) {
                case 0:
                    x[0] = position + 1;
                    y[0] = h - 2;
                    x[1] = position + 1;
                    y[1] = h - 1;
                    x[2] = position + 2;
                    y[2] = h - 1;
                    x[3] = position;
                    y[3] = h - 2;
                    break;
                case 1:
                    x[0] = position + 1;
                    y[0] = h - 3;
                    x[1] = position;
                    y[1] = h - 2;
                    x[2] = position + 1;
                    y[2] = h - 2;
                    x[3] = position;
                    y[3] = h - 1;
                    break;
            }//switch
            break;
        case I :
            switch (orientation) {
                case 0:
                    x[0] = position;
                    y[0] = h - 1;
                    x[1] = position + 1;
                    y[1] = h - 1;
                    x[2] = position + 2;
                    y[2] = h - 1;
                    x[3] = position + 3;
                    y[3] = h - 1;
                    break;
                case 1:
                    x[0] = position;
                    y[0] = h - 4;
                    x[1] = position;
                    y[1] = h - 3;
                    x[2] = position;
                    y[2] = h - 2;
                    x[3] = position;
                    y[3] = h - 1;
                    break;
            }//switch
            break;
        case T :
            switch (orientation) {
                case 0:
                    x[0] = position + 1;
                    y[0] = h - 2;
                    x[1] = position;
                    y[1] = h - 1;
                    x[2] = position + 1;
                    y[2] = h - 1;
                    x[3] = position + 2;
                    y[3] = h - 1;
                    break;
                case 1:
                    x[0] = position;
                    y[0] = h - 3;
                    x[1] = position;
                    y[1] = h - 2;
                    x[2] = position;
                    y[2] = h - 1;
                    x[3] = position + 1;
                    y[3] = h - 2;
                    break;
                case 2:
                    x[0] = position;
                    y[0] = h - 2;
                    x[1] = position + 1;
                    y[1] = h - 2;
                    x[2] = position + 2;
                    y[2] = h - 2;
                    x[3] = position + 1;
                    y[3] = h - 1;
                    break;
                case 3:
                    x[0] = position + 1;
                    y[0] = h - 3;
                    x[1] = position + 1;
                    y[1] = h - 2;
                    x[2] = position + 1;
                    y[2] = h - 1;
                    x[3] = position;
                    y[3] = h - 2;
                    break;
            }//switch
            break;
    }//switch
    while (y[0] > 0 && !board[y[0] - 1][x[0]]
           && !board[y[1] - 1][x[1]] && !board[y[2] - 1][x[2]]
           && !board[y[3] - 1][x[3]])
        for (i = 0; i < 4; i++)
            y[i]--;
    for (i = 0; i < 4; i++)
        board[y[i]][x[i]] = true;
}//Tetris::dropPiece

// give piece a chance: info to the screen
void Tetris::printInfoCurrentPiece(PieceName piece, int orientation, int position) {
    int j;
    cout << endl;
    for (j = 0; j < w + 5; j++)
        cout << "=";
    if (piececount < 10)
        cout << "   ";
    else if (piececount < 100)
        cout << "  ";
    else
        cout << " ";
    cout << piececount << ": ";
    switch (piece) {
        case Sq:
            cout << "Square      ";
            break;
        case LG:
            cout << "Left gun    ";
            break;
        case RG:
            cout << "Right gun   ";
            break;
        case LS:
            cout << "Left snake  ";
            break;
        case RS:
            cout << "Right snake ";
            break;
        case I:
            cout << "I           ";
            break;
        case T:
            cout << "T           ";
            break;
    }//switch
    cout << orientation << " " << position << endl;
}//Tetris::printInfoCurrentPiece

// check whether top 3 rows are somewhat occupied (so game has ended?)
bool Tetris::endOfGame() {
    int j;
    for (j = 0; j < w; j++)
        if (board[h - 3][j])
            return true;
    return false;
}//Tetris::endOfGame

// how many possibilities has piece?
int Tetris::possibilities(PieceName piece) {
    if (piece == Sq)
        return (w - 1);
    else if (piece == LS || piece == RS || piece == I)
        return (2 * w - 3);
    else
        return (4 * w - 6);
}//Tetris::possibilities

// compute orientation and position for move themove from piece
void Tetris::computeOrAndPos(PieceName piece, int &orientation, int &position, int themove) {
    orientation = 0;
    position = themove;
    switch (piece) {
        case LS:
        case RS:
            if (themove > w - 3) {
                orientation = 1;
                position = themove - (w - 2);
            }//if
            break;
        case I:
            if (themove > w - 4) {
                orientation = 1;
                position = themove - (w - 3);
            }//if
            break;
        case Sq:
            break;
        case T:
        case LG:
        case RG:
            if (themove > 3 * w - 6) {
                orientation = 3;
                position = themove - (3 * w - 5);
            }//if
            else if (themove > 2 * w - 4) {
                orientation = 2;
                position = themove - (2 * w - 3);
            }//if
            else if (themove > w - 3) {
                orientation = 1;
                position = themove - (w - 2);
            }//if
            break;
    }//switch
}//Tetris::computeOrAndPos

// now choose (random) orientation and position for piece
void Tetris::randomChoice(PieceName piece, int &orientation, int &position) {
    int themove = rand() % possibilities(piece);
    computeOrAndPos(piece, orientation, position, themove);
}//Tetris::randomChoice

// generate a random piece
void getRandomPiece(PieceName &piece) {
    int intpiece = rand() % 7;
    switch (intpiece) {
        case 0:
            piece = LS;
            break;
        case 1:
            piece = RS;
            break;
        case 2:
            piece = I;
            break;
        case 3:
            piece = Sq;
            break;
        case 4:
            piece = T;
            break;
        case 5:
            piece = LG;
            break;
        case 6:
            piece = RG;
            break;
    }//switch
}//getRandomPiece

//play a random game
void Tetris::playRandomGame() {
    PieceName piece;
    int orientation;
    int position;
    int nr, emp;
    bool theRow[wMAX];
    displayBoard();
    while (!endOfGame()) {
        getRandomPiece(piece);                    // obtain some piece
        randomChoice(piece, orientation, position); // how to drop it?
        dropPiece(piece, orientation, position);    // let it go
        clearFullRows();                             // clear rows

        // the following output lines can be easily removed
        printInfoCurrentPiece(piece, orientation, position);  // some text
        displayBoard();                          // print the board
        topRow(theRow, nr, emp);                    // how is top row?
        if (nr != -1)
            cout << "Top row " << nr << " has " << emp << " empties" << endl;
    }
}

void Tetris::playRandomSilentGame(int &score, PieceName piece, int orientation, int position) {
    //First move
    dropPiece(piece, orientation, position);    // let it go
    clearFullRows();

    //Rest of game
    while (!endOfGame()) {
        score++;
        getRandomPiece(piece);                    // obtain some piece
        randomChoice(piece, orientation, position); // how to drop it?
        dropPiece(piece, orientation, position);    // let it go
        clearFullRows();                             // clear rows
    }
}

//play a 'smart' game by looking at optimal piece placement
void Tetris::playSmartGame() {
    displayBoard();

    while (!endOfGame()) {
        // Track best move
        int bestScore = INT_MAX;
        int bestOrientation;
        int bestPosition;

        // Get a random piece
        PieceName randomPiece;
        getRandomPiece(randomPiece);

        // Determine best move
        for (int i = 0; i < possibilities(randomPiece); ++i) {
            int orientation;
            int position;
            computeOrAndPos(randomPiece, orientation, position, i);
            Tetris newBoard = new Tetris(this);
            newBoard.dropPiece(randomPiece, orientation, position);
            int score = newBoard.getSmartScore();

            if (score < bestScore) {
                bestScore = score;
                bestOrientation = orientation;
                bestPosition = position;
            }
        }

        // Do best move
        dropPiece(randomPiece, bestOrientation, bestPosition);
        clearFullRows();

        // Print information
        int nr, emp;
        bool therow[wMAX];
        printInfoCurrentPiece(randomPiece, bestOrientation, bestPosition);
        displayBoard();
        topRow(therow, nr, emp);
        if (nr != -1)
            cout << "Top row " << nr << " has " << emp << " empties" << endl;
    }
}

//play a 'smarter' game using monte carlo piece placement
void Tetris::playSmarterGame() {
    const int numEvals = 1000;
    int bestScore;
    int newOrientation;
    int newPosition;
    PieceName piece;
    int orientation;
    int position;
    int nr, emp;
    bool theRow[wMAX];
    displayBoard();
    while (!endOfGame()) {
        getRandomPiece(piece);
        randomChoice(piece, orientation, position); // how to drop it

        bestScore = 0;
        for (int i = 0; i < possibilities(piece); ++i) {
            computeOrAndPos(piece, newOrientation, newPosition, i);
            int newScore = 0;
            for (int j = 0; j < numEvals; ++j) {
                auto *clone = new Tetris(this);
                clone->playRandomSilentGame(newScore, piece, newOrientation, newPosition);
            }
            if (newScore > bestScore) {
                bestScore = newScore;
                orientation = newOrientation;
                position = newPosition;
            }
        }

        dropPiece(piece, orientation, position);    // let it go
        clearFullRows();                            // clear rows

        // the following output lines can be easily removed
        printInfoCurrentPiece(piece, orientation, position);  // some text
        displayBoard();                          // print the board
        topRow(theRow, nr, emp);                    // how is top row?
        if (nr != -1)
            cout << "Top row " << nr << " has " << emp << " empties" << endl;
    }

}

// Copy constructor
Tetris::Tetris(Tetris* copy) {
    h = copy->h;
    w = copy->w;
    piececount = copy->piececount;
    rowscleared = copy->rowscleared;

    for (int i = 0; i < hMAX; ++i) {
        for (int j = 0; j < wMAX; ++j) {
            board[i][j] = copy->board[i][j];
        }
    }
}

// Get the score for this board to use in playSmartGame, higher is worse
int Tetris::getSmartScore() {
    int highest = h - 1;
    while (numberOfEmpties(highest) == w && highest > 0) {
        --highest;
    }

    int broken = 0;
    for (int i = 0; i < h - 1; ++i) {
        for (int j = 0; j < w; ++j) {
            if (!board[i][j]) {
                for (int k = i; k < h; ++k) {
                    if (board[k][j]) {
                        ++broken;
                        break;
                    }
                }
            }
        }
    }

    int fullrows = h;
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (!board[i][j]) {
                --fullrows;
                break;
            }
        }
    }

    return broken + highest - fullrows;
}
