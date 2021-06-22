#ifndef CHESS_H
#define CHESS_H
#include <string>
#include <stdlib.h>
#include "board.h"
using namespace std;

class Chess{
    public:
        Chess(){
            player=1;
        }
        void play();
        bool notEnd();
        void printBoard();
        int move(string);
        bool isValid(Board);
        bool validUserInput(string);
        string printPlayer();
    private:
        Board board;
        bool end=false;
        int stepcount=0;
        int player=0; //white=player 1, black=player -1
};

void Chess::play(){
    while(!end){
        std::cout<<printPlayer()<<" move: ";
        string user_input;
        getline(cin,user_input);
        
        while(!validUserInput(user_input)){
            board.illegal("invalid input.");
            std::cout<<printPlayer()<<" move: ";
            getline(cin,user_input);
        }

        while(!board.move(user_input)){
            board.illegal("invalid move.");
            std::cout<<printPlayer()<<" move: ";
            getline(cin,user_input);
        }
        ++stepcount;
        player=-player;
        board.print();
    }
    if(player==1){
        std::cout<<"White wins"<<std::endl;
        exit(0);
    }else if(player==-1){
        std::cout<<"Black wins"<<std::endl;
        exit(0);
    }
}

bool Chess::validUserInput(string user_input){
    if(user_input.length()!=5&&user_input.length()!=7){
        std::cout<<"Chess::validUserInput 1"<<std::endl;
        return false;
    }
    int f1=int(user_input[0]);
    int r1=int(user_input[1]-'0');
    int f2=int(user_input[3]);
    int r2=int(user_input[4]-'0');
    if(user_input.length()==7){
        int promoteTo=int(user_input[6]);
        if(promoteTo!=B&&promoteTo!=Q&&promoteTo!=R&&promoteTo!=N){
            std::cout<<"Chess::validUserInput 7"<<std::endl;
            return false;
        }
    }
    if(f1<int('a')||f1>int('h')||f2<int('a')||f2>int('h')){
        std::cout<<"Chess::validUserInput 2"<<std::endl;
        return false;
    }else if(r1<1||r1>8||r2<1||r2>8){
        std::cout<<"Chess::validUserInput 3. r1="<<r1<<"r2="<<r2<<std::endl;
        return false;
    }else if(f1==f2&&r1==r2){
        std::cout<<"Chess::validUserInput 4"<<std::endl;
        return false;
    }
    Piece from=board.getPiece(f1,r1);
    Piece to=board.getPiece(f2,r2);
    if(from.getPlayer()!=player){
        std::cout<<"Chess::validUserInput 5"<<std::endl;
        return false;
    }else if(to.getPlayer()!=0&&to.getPlayer()!=-player){
        std::cout<<"Chess::validUserInput 6"<<std::endl;
        return false;
    }
    return true;
}

void Chess::printBoard(){
    board.print();
}

string Chess::printPlayer(){
    if(player==1){
        return "White";
    }else if(player==-1){
        return "Black";
    }
    return {};
}

#endif