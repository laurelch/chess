#include "chess.h"
#include "board.h"
#include "piece.h"

int main(int argc, char const *argv[])
{
    // Board board;
    // board.print();
    Chess chess;
    chess.printBoard();
    chess.play();
    return 0;
}