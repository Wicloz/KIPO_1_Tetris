#include "../lib/Tetris.h"

int main(int argc, char *argv[]) {

    if (argc != 4 && argc != 5) {
        cout << "Usage: " << argv[0] << " <playing type> <height> <width>" << endl;
        cout << "   Or: " << argv[0] << " <playing type> <height> <width> <seed>" << endl;
        return 1;
    }

    int h = atoi(argv[2]);
    int w = atoi(argv[3]);

    Tetris board(h, w);

    if (argc == 4)
        srand(time(NULL));
    else
        srand(atoi(argv[4]));

    if (string(argv[1]) == "Random" || string(argv[1]) == "random" || string(argv[1]) == "R" || string(argv[1]) == "r")
        board.playRandomGame(false);
    else if (string(argv[1]) == "Smart" || string(argv[1]) == "smart" || string(argv[1]) == "S" || string(argv[1]) == "s")
        board.playSmartGame(false);
    else if (string(argv[1]) == "Smarter" || string(argv[1]) == "smarter" || string(argv[1]) == "Ss" || string(argv[1]) == "ss")
        board.playSmarterGame(false);

    else {
        cerr << "Invalid playing type!" << endl;
        return 1;
    }

    board.statistics();

    return 0;

}//main
