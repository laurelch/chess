#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <iostream>
#include "piece.h"
#define BOARD_SIZE 8
using namespace std;
class Board{
    std::vector<Piece> board;
    int lastPiece;
    public:
        Board(){
            init();
        }
        void init();
        void print() const;
        void move();
        void illegal(string) const;
        Piece getPiece(int,int) const;
        int lastMoved() const;
        int getIndex(int,int) const;
        bool isEmpty(int f,int r) const;
        bool emptyBetween(Piece*,Piece*);
        bool move(string);
        bool moveBishop(Piece*,Piece*);
        bool moveKing(Piece*,Piece*);
        bool movePawn(Piece*,Piece*,int);
        bool moveQueen(Piece*,Piece*);
        bool moveRook(Piece*,Piece*);
        bool moveKnight(Piece*,Piece*);
};

//initialize board
void Board::init(){
    Piece piece{};
    vector<Piece> initialBoard;
    for(int rank=1;rank<=8;++rank){
        for(int file=int('a');file<=int('h');++file){
            int player=0;//white=1,black=-1
            int role=0;
            if(rank<=2){player=1;}
            else if(rank>=7){player=-1;}
            if(rank==2||rank==7){role=P;}
            else if(file==int('a')||file==int('h')){role=R;}
            else if(file==int('b')||file==int('g')){role=N;}
            else if(file==int('c')||file==int('f')){role=B;}
            else if(file==int('d')){role=Q;}
            else if(file==int('e')){role=K;}
            if(player!=0){
                Piece piece(player,role);
                piece.move(file,rank);
                initialBoard.push_back(piece);
            }else{
                piece.move(file,rank);
                initialBoard.push_back(piece);
            }
        }
    }
    board=initialBoard;
}

//print current board
void Board::print() const{
    std::cout<<"  a  b  c  d  e  f  g  h"<<std::endl;
    std::cout<<" |--|--|--|--|--|--|--|--|"<<std::endl;
    for(int i=BOARD_SIZE-1;i>=0;--i){
        std::cout<<i+1<<"|";
        for(int j=0;j<BOARD_SIZE;++j){
            const int index=i*BOARD_SIZE+j;
            if(board[index].printPlayer().empty()){
                std::cout<<"__|";
            }else{
                std::cout<<board[index].printPlayer()<<board[index].printRoleShort()<<'|';
            }
        }
        std::cout<<i+1<<std::endl;
    }
    std::cout<<" |--|--|--|--|--|--|--|--|"<<std::endl;
    std::cout<<"  a  b  c  d  e  f  g  h"<<std::endl;
}

void Board::illegal(string info="") const{
    std::cout<<"Illegal move, try again.";
    if(!info.empty()){
        std::cout<<" Error info: "<<info<<std::endl;
    }else{
        std::cout<<std::endl;
    }
}

bool Board::move(string user_input){
    int f1=int(user_input[0]);
    int r1=int(user_input[1]-'0');
    int f2=int(user_input[3]);
    int r2=int(user_input[4]-'0');
    Piece from=getPiece(f1,r1);
    int role=from.getRole();
    Piece to=getPiece(f2,r2);
    int promoteTo=0;
    if(user_input.size()==7){promoteTo=user_input[6];}
    bool succeed=false;
    std::cout<<"Board::move role="<<role<<std::endl;
    if(role!=N&&!emptyBetween(&from,&to)){
        return false;
    }
    switch(role){
        case B:
            succeed=moveBishop(&from,&to);
            break;
        case K:
            succeed=moveKing(&from,&to);
            break;
        case P:
            succeed=movePawn(&from,&to,promoteTo);
            break;
        case Q:
            succeed=moveQueen(&from,&to);
            break;
        case R:
            succeed=moveRook(&from,&to);
            break;
        case N:
            succeed=moveKnight(&from,&to);
            break;
        default:
            return false;
    }
    if(succeed){
        int index1=getIndex(f1,r1);
        to.setPosition(f1,r1);
        int moves=to.getMoves();
        to.empty();
        int index2=getIndex(f2,r2);
        from.setPosition(f2,r2);
        from.setMoves(moves);
        board[index1]=to;
        board[index2]=from;
        lastPiece=index2;
    }
    return succeed;
}

Piece Board::getPiece(int f,int r) const{
    int index=getIndex(f,r);
    // std::cout<<"Board::getPiece index="<<index<<std::endl;
    return board[index];
}

int Board::lastMoved() const{
    return lastPiece;
}

int Board::getIndex(int f,int r) const{
    int file=f-'a';
    int rank=r-1;
    return rank*BOARD_SIZE+file;
}

bool Board::isEmpty(int f,int r) const{
    int index=getIndex(f,r);
    Piece piece=board[index];
    int player=piece.getPlayer();
    if(player==0){return true;}
    return false;
}

bool Board::emptyBetween(Piece* from,Piece* to){
    int f1=0,r1=0,f2=0,r2=0;
    from->getPosition(f1,r1);
    to->getPosition(f2,r2);
    std::cout<<"Board::emptyBetween "<<f1<<","<<f2<<","<<r1<<","<<r2<<std::endl;
    int fstep=f2-f1;
    int rstep=r2-r1;
    for(int i=f1,j=r1;i!=f2||j!=r2;i+=fstep,j+=rstep){
        if(i==f1&&j==r1){continue;}
        if(!isEmpty(i,j)){return false;}
    }
    return true;
}

bool Board::moveBishop(Piece* from,Piece* to){
    int f1=0,r1=0,f2=0,r2=0;
    from->getPosition(f1,r1);
    to->getPosition(f2,r2);
    cout<<"Board::moveBishop f1="<<f1<<", r1="<<r1<<", f2="<<f2<<", r2="<<r2<<endl;
    if(abs(f1-f2)==abs(r1-r2)){return true;}
    return false;
}

bool Board::moveKing(Piece* from,Piece* to){
    int f1=0,r1=0,f2=0,r2=0;
    from->getPosition(f1,r1);
    to->getPosition(f2,r2);
    cout<<"Board::moveBishop f1="<<f1<<", r1="<<r1<<", f2="<<f2<<", r2="<<r2<<endl;
    if(abs(f1-f2)<=1){return true;}
    else if(abs(r1-r2)<=1){return true;}
    return false;
}

bool Board::movePawn(Piece* from,Piece* to,int promoteTo){
    int f1=0,r1=0,f2=0,r2=0;
    from->getPosition(f1,r1);
    to->getPosition(f2,r2);
    cout<<"Board::movePawn f1="<<f1<<", r1="<<r1<<", f2="<<f2<<", r2="<<r2<<", moves="<<from->getMoves()<<endl;
    int player=from->getPlayer();
    //promotion
    if((player==1&&r2==8)||(player==-1&&r2==1)){
        if(promoteTo!=0){from->promotion(promoteTo);}
        else{from->promotion(Q);}
    }
    //basic movement
    if(from->getMoves()==0&&f1==f2){
        if(r2-r1==player||r2-r1==2*player){return true;}
    }else if(((player==1&&r1==5)||(player==-1&&r1==4))&&abs(f2-f1)==1){
        //en passant
        Piece last=board[lastMoved()];
        int role=last.getRole();
        int f3=0;
        int r3=0;
        last.getPosition(f3,r3);
        if(role==P&&f2==f3&&(r2==r3||r2==r3+player)){
            last.empty();
            board[lastMoved()]=last;
            return true;
        }
    }else{
        if(f1==f2&&r2-r1==player){return true;}
    }
    return false;
}

bool Board::moveQueen(Piece* from,Piece* to){
    int f1=0,r1=0,f2=0,r2=0;
    from->getPosition(f1,r1);
    to->getPosition(f2,r2);
    cout<<"Board::moveQueen f1="<<f1<<", r1="<<r1<<", f2="<<f2<<", r2="<<r2<<endl;
    if(f1==f2&&r1!=r2){return true;}
    else if(f1!=f2&&r1==r2){return true;}
    else if(abs(f1-f2)==abs(r1-r2)){return true;}
    return false;
}

bool Board::moveRook(Piece* from,Piece* to){
    int f1=0,r1=0,f2=0,r2=0;
    from->getPosition(f1,r1);
    to->getPosition(f2,r2);
    cout<<"Board::moveRook f1="<<f1<<", r1="<<r1<<", f2="<<f2<<", r2="<<r2<<endl;
    if(f1==f2&&r1!=r2){return true;}
    else if(f1!=f2&&r1==r2){return true;}
    return false;
}

bool Board::moveKnight(Piece* from,Piece* to){
    int f1=0,r1=0,f2=0,r2=0;
    from->getPosition(f1,r1);
    to->getPosition(f2,r2);
    cout<<"Board::moveKnight f1="<<f1<<", r1="<<r1<<", f2="<<f2<<", r2="<<r2<<endl;
    if(abs(f1-f2)==1&&abs(r1-r2)==2){return true;}
    else if(abs(f1-f2)==2&&abs(r1-r2)==1){return true;}
    return false;
}
#endif