#include "../lib/Tetris.h"


int main(int argc, char *argv[]) {

    if (argc != 4 && argc != 5) {
        cout << "Usage: " << argv[0] << " <playing type {1, 2, 3}> <height> <width>" << endl;
        cout << "Or:    " << argv[0] << " <playing type {1, 2, 3}> <height> <width> <seed>" << endl;
        return 1;
    }//if
    int h = atoi(argv[2]);
    int w = atoi(argv[3]);
    Tetris board(h, w);
    if (argc == 4)
        srand(time(NULL));
    else
        srand(atoi(argv[4]));

    switch (atoi(argv[1])) {
        case 1:
            board.playRandomGame(true);
            break;
        case 2:
            board.playSmartGame(true);
            break;
        case 3:
            board.playSmarterGame(true);
            break;
        default:
            cerr << "Invalid playing type!" << endl;
            return -1;
    }
    board.statistics();

    return 0;

}//main