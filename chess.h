#ifndef CHESS_H
#define CHESS_H
#include <string>
#include "board.h"
using namespace std;

class Chess{
    Board board();
    int stepcount=0;
    int player=0; // player 1, player 2
    public:
        // default constructor
        Chess(){
            player=1;
        }
        int move(string user_input){
            // parse user_input
            // if move is valid
            ++stepcount;
            player=(player+1)%2;
            return 0;
        }
        bool isValid(Board){
            return false;
        }
};
#endif