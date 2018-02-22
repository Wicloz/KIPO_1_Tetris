#include "../lib/Tetris.h"

int main(int argc, char *argv[]) {
    bool output = true;

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

    int start = clock();

    if (string(argv[1]) == "Random" || string(argv[1]) == "random" || string(argv[1]) == "R" || string(argv[1]) == "r")
        board.playRandomGame(output);
    else if (string(argv[1]) == "Smart" || string(argv[1]) == "smart" || string(argv[1]) == "S" || string(argv[1]) == "s")
        board.playSmartGame(output);
    else if (string(argv[1]) == "Smarter" || string(argv[1]) == "smarter" || string(argv[1]) == "Ss" || string(argv[1]) == "ss")
        board.playSmarterGame(output);
    else if (string(argv[1]) == "Smartest" || string(argv[1]) == "smartest" || string(argv[1]) == "Sss" || string(argv[1]) == "sss")
        board.playSmartestGame(output);

    else {
        cerr << "Invalid playing type!" << endl;
        return 1;
    }

    board.statistics();
    cout << "Time taken: " << (clock()-start)/double(CLOCKS_PER_SEC)*1000 << "ms" << endl;

    return 0;

}//main
