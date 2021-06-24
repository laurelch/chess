#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <iostream>
#include "piece.h"
#define BOARD_SIZE 8
using namespace std;
class Board{
    std::vector<Piece> board;
    std::vector<Piece> offBoardWhite;
    std::vector<Piece> offBoardBlack;
    int lastPiece;
    int whiteKing;
    int blackKing;
    public:
        Board(){
            init();
        }
        void init();
        void print() const;
        void illegal(string) const;
        Piece getPiece(int,int) const;
        Piece getPiece(int) const;
        int getKing(int) const;
        void setKing(int,int);
        int lastMoved() const;
        int getIndex(int,int) const;
        bool isEmpty(int,int) const;
        void addEmpty(int);
        bool emptyBetween(Piece*,Piece*) const;
        bool move(string);
        bool moveBishop(Piece*,Piece*) const;
        bool moveKing(Piece*,Piece*);
        bool movePawn(Piece*,Piece*,int);
        bool moveQueen(Piece*,Piece*) const;
        bool moveRook(Piece*,Piece*) const;
        bool moveKnight(Piece*,Piece*) const;
        bool moveRole(int,Piece*,Piece*,int);
        void afterMove(Piece*);
        bool check(Piece*);
        bool checkmate() const;
        bool stalemate() const;
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
            else if(file==int('e')){
                role=K;
                setKing(player,getIndex(file,rank));
            }
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
    std::cout<<"___________________________"<<std::endl;
    for(int i=0;i<offBoardWhite.size();++i){
        if(i==0)std::cout<<"Captured by Black: ";
        std::cout<<offBoardWhite[i].printPlayer()<<offBoardWhite[i].printRoleShort()<<" ";
    }
    std::cout<<std::endl<<"  a  b  c  d  e  f  g  h"<<std::endl;
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
    for(int i=0;i<offBoardBlack.size();++i){
        if(i==0)std::cout<<"Captured by White: ";
        std::cout<<offBoardBlack[i].printPlayer()<<offBoardBlack[i].printRoleShort()<<" ";
    }
    std::cout<<std::endl<<"___________________________"<<std::endl;
}

void Board::illegal(string info="") const{
    std::cout<<"Illegal move, try again.";
    if(!info.empty()){
        std::cout<<" Error info: "<<info<<std::endl;
    }else{
        std::cout<<std::endl;
    }
}

Piece Board::getPiece(int f,int r) const{
    int index=getIndex(f,r);
    // std::cout<<"Board::getPiece index="<<index<<std::endl;
    return board[index];
}

Piece Board::getPiece(int index) const{
    return board[index];
}

int Board::getKing(int player) const{
    if(player==1){return whiteKing;}
    else if(player==-1){return blackKing;}
    return -1;
}

void Board::setKing(int player,int index){
    if(player==1){whiteKing=index;}
    else if(player==-1){blackKing=index;}
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

void Board::addEmpty(int index){
    Piece empty{};
    board[index]=empty;
}

bool Board::emptyBetween(Piece* from,Piece* to) const{
    int f1=0,r1=0,f2=0,r2=0;
    from->getPosition(f1,r1);
    to->getPosition(f2,r2);
    // std::cout<<"Board::emptyBetween "<<f1<<","<<f2<<","<<r1<<","<<r2<<std::endl;
    int fstep=f2-f1;
    int rstep=r2-r1;
    for(int i=f1,j=r1;i!=f2||j!=r2;i+=fstep,j+=rstep){
        if(i==f1&&j==r1){continue;}
        if(!isEmpty(i,j)){return false;}
    }
    return true;
}

bool Board::move(string user_input){
    int f1=int(user_input[0]);
    int r1=int(user_input[1]-'0');
    int f2=int(user_input[3]);
    int r2=int(user_input[4]-'0');
    Piece from=getPiece(f1,r1);
    Piece to=getPiece(f2,r2);
    int promoteTo=0;
    if(user_input.size()==7){promoteTo=user_input[6];}
    bool succeed=false;
    // std::cout<<"Board::move role="<<role<<std::endl;
    succeed=moveRole(from.getRole(),&from,&to,promoteTo);
    if(succeed){
        int index_from=getIndex(f1,r1);
        int index_to=getIndex(f2,r2);
        int player=from.getPlayer();
        addEmpty(index_from);
        if(to.getPlayer()!=0){
            if(player==1){offBoardBlack.push_back(to);}
            else if(player==-1){offBoardWhite.push_back(to);}
        }
        from.move(f2,r2);
        board[index_to]=from;
        lastPiece=index_to;
        if(from.getRole()==K){setKing(from.getPlayer(),index_to);}
    }
    return succeed;
}

bool Board::moveBishop(Piece* from,Piece* to) const{
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
    cout<<"Board::moveKing f1="<<f1<<", r1="<<r1<<", f2="<<f2<<", r2="<<r2<<", moves="<<from->getMoves()<<endl;
    //basic
    if(abs(f1-f2)<=1&&abs(r1-r2)<=1){return true;}
    //castling
    else if(from->getMoves()==0&&abs(f1-f2)==2){
        int way=(f2-f1)/2;
        int f_rook=0;
        if(way>0){f_rook=int('h');}else{f_rook=int('a');}
        Piece rook=getPiece(f_rook,r1);
        if(rook.getMoves()!=0){cout<<"Board::moveKing 1"<<endl;return false;}
        for(int f=f1+way;f!=f_rook;f+=way){
            Piece tmp=getPiece(f,r1);
            if(tmp.getPlayer()!=0){cout<<"Board::moveKing 2"<<endl;return false;}
        }
        int f_rook2=f1+way;
        int index_cross=getIndex(f_rook2,r1);
        int index_rook=getIndex(f_rook,r1);
        board[index_cross]=rook;
        addEmpty(index_rook);
        addEmpty(getIndex(f1,r1));
        return true;
    }
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
    //basic
    if(from->getMoves()==0&&f1==f2){
        if(r2-r1==player||r2-r1==2*player){return true;}
    }else if(((player==1&&r1==5)||(player==-1&&r1==4))&&abs(f2-f1)==1){
        //en passant
        Piece last=getPiece(lastMoved());
        int role=last.getRole();
        int f3=0;
        int r3=0;
        last.getPosition(f3,r3);
        if(role==P&&f2==f3&&(r2==r3||r2==r3+player)){
            if(player==1){offBoardBlack.push_back(last);}//opponent
            else if(player==-1){offBoardWhite.push_back(last);}
            addEmpty(lastMoved());
            return true;
        }
    }else{
        if(f1==f2&&r2-r1==player){return true;}
    }
    return false;
}

bool Board::moveQueen(Piece* from,Piece* to) const{
    int f1=0,r1=0,f2=0,r2=0;
    from->getPosition(f1,r1);
    to->getPosition(f2,r2);
    cout<<"Board::moveQueen f1="<<f1<<", r1="<<r1<<", f2="<<f2<<", r2="<<r2<<endl;
    if(f1==f2&&r1!=r2){return true;}
    else if(f1!=f2&&r1==r2){return true;}
    else if(abs(f1-f2)==abs(r1-r2)){return true;}
    return false;
}

bool Board::moveRook(Piece* from,Piece* to) const{
    int f1=0,r1=0,f2=0,r2=0;
    from->getPosition(f1,r1);
    to->getPosition(f2,r2);
    cout<<"Board::moveRook f1="<<f1<<", r1="<<r1<<", f2="<<f2<<", r2="<<r2<<endl;
    if(f1==f2&&r1!=r2){return true;}
    else if(f1!=f2&&r1==r2){return true;}
    return false;
}

bool Board::moveKnight(Piece* from,Piece* to) const{
    int f1=0,r1=0,f2=0,r2=0;
    from->getPosition(f1,r1);
    to->getPosition(f2,r2);
    cout<<"Board::moveKnight f1="<<f1<<", r1="<<r1<<", f2="<<f2<<", r2="<<r2<<endl;
    if(abs(f1-f2)==1&&abs(r1-r2)==2){return true;}
    else if(abs(f1-f2)==2&&abs(r1-r2)==1){return true;}
    return false;
}

bool Board::moveRole(int role,Piece* from,Piece* to,int promoteTo){
    if(role!=N&&!emptyBetween(from,to)){
        return false;
    }
    switch(role){
        case B:
            return moveBishop(from,to);
        case K:
            return moveKing(from,to);
        case P:
            if(promoteTo==0)promoteTo=Q;
            return movePawn(from,to,promoteTo);
        case Q:
            return moveQueen(from,to);
        case R:
            return moveRook(from,to);
        case N:
            return moveKnight(from,to);
        default:
            return false;
    }
}

void Board::afterMove(Piece* from){
    if(check(from)){
        if(checkmate()){
            std::cout<<"Checkmate"<<std::endl;
        }else{
            std::cout<<"Check"<<std::endl;
        }
    }else if(stalemate()){
            std::cout<<"Stalemate"<<std::endl;
    }
}

bool Board::check(Piece* last){
    Piece opponentKing=getPiece(getKing(-(last->getPlayer())));
    int promoteTo=Q;
    if(moveRole(last->getRole(),last,&opponentKing,promoteTo)){return true;}
    return false;
}

bool Board::checkmate() const{
    return false;
}

bool Board::stalemate() const{
    return false;
}
#endif