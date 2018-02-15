#include "../lib/Tetris.h"


int main(int argc, char *argv[]) {

    if (argc != 3 && argc != 4) {
        cout << "Usage: " << argv[0] << " <height> <width>" << endl;
        cout << "Or:    " << argv[0] << " <height> <width> <seed>" << endl;
        return 1;
    }//if
    int h = atoi(argv[1]);
    int w = atoi(argv[2]);
    Tetris board(h, w);
    if (argc == 3)
        srand(time(NULL));
    else
        srand(atoi(argv[3]));

    board.playSmarterGame();
    board.statistics();

    return 0;

}//main