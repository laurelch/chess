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
        bool waitForDraw=false;
};

void Chess::play(){
    while(!end){
        std::cout<<printPlayer()<<" move: ";
        string user_input;
        getline(cin,user_input);
        
        string resign_str("resign");
        if(user_input.compare(resign_str)==0){
            if(player==1){board.printNotice("Black wins");}
            else if(player==-1){board.printNotice("White wins");}
            break;
        }

        while(!validUserInput(user_input)){
            board.illegal("not validUserInput");
            std::cout<<printPlayer()<<" move: ";
            getline(cin,user_input);
        }
        if(end)break;
        while(!board.move(user_input)){
            board.illegal("cannot move.");
            std::cout<<printPlayer()<<" move: ";
            getline(cin,user_input);
        }
        ++stepcount;
        board.print();
        end=board.isGameOver();
        player=-player;
    }
    if(board.getGameOverMessage().size()>0){
        board.printNotice(board.getGameOverMessage());
    }
}

bool Chess::validUserInput(string user_input){
    int length=user_input.length();
    if(length!=4&&length!=5&&length!=7&&length!=10&&length!=13){
        std::cout<<"Chess::validUserInput 1"<<std::endl;
        return false;
    }
    if(length==4&&waitForDraw){
        string draw_str("draw");
        if(user_input.compare(draw_str)==0){
            end=true;
            board.printNotice(draw_str);
            return true;
        }
    }

    int f1=int(user_input[0]);
    int r1=int(user_input[1]-'0');
    int f2=int(user_input[3]);
    int r2=int(user_input[4]-'0');
    if(user_input.length()==7){
        int promoteTo=int(user_input[6]);
        if(promoteTo!=B&&promoteTo!=Q&&promoteTo!=R&&promoteTo!=N){
            std::cout<<"Chess::validUserInput 7, promoteTo="<<promoteTo<<std::endl;
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
    }else if(!to.isEmpty()&&to.getPlayer()!=-player){
        std::cout<<"Chess::validUserInput 6"<<std::endl;
        return false;
    }
    if(length>=10){
        size_t draw_pos=user_input.find("draw?");
        if(draw_pos!=string::npos){waitForDraw=true;}
    }else{
        waitForDraw=false;
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