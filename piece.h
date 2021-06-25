#ifndef PIECE_H
#define PIECE_H
#include <string>
#define B 66 // Bishop
#define K 75 // King
#define P 80 // Pawn
#define Q 81 // Queen
#define R 82 // Rook
#define N 110 // Knight
class Piece{
    public:
        Piece(int p,int r):player{p},role{r}
        {}
        Piece(){}
        ~Piece(){}
        int getPlayer() const;
        std::string printPlayer() const;
        int getRole() const;
        std::string printRole() const;
        std::string printRoleShort() const;
        std::string printUnicode() const;
        void move(int,int);
        int getMoves() const;
        void setMoves(int);
        void setPosition(int,int);
        void getPosition(int&,int&);
        void promotion(int);
        void empty();
        bool isEmpty() const;
        
    protected:
        int player=0;
        int role=0;
        int moves=-1;
        int file=0;
        int rank=0;
};

int Piece::getPlayer() const{
    return player;
}

std::string Piece::printPlayer() const{
    if(player==1){return "w";}
    else if(player==-1){return "b";}
    return {};
}

int Piece::getRole() const{
    return role;
}

std::string Piece::printRole() const{
    if(role==P){return "Pawn";}
    else if(role==R){return "Rook";}
    else if(role==N){return "Knight";}
    else if(role==B){return "Bishop";}
    else if(role==Q){return "Queen";}
    else if(role==K){return "King";}
    return {};
}

std::string Piece::printRoleShort() const{
    if(role==P){return "P";}
    else if(role==R){return "R";}
    else if(role==N){return "N";}
    else if(role==B){return "B";}
    else if(role==Q){return "Q";}
    else if(role==K){return "K";}
    return {};
}

std::string Piece::printUnicode() const{
    if(player==-1){
        if(role==B){return "♝";}
        if(role==K){return "♚";}
        if(role==P){return "♟";}
        if(role==Q){return "♛";}
        if(role==R){return "♜";}
        if(role==N){return "♞";}
    }else if(player==1){
        if(role==B){return "♗";}
        if(role==K){return "♔";}
        if(role==P){return "♙";}
        if(role==Q){return "♕";}
        if(role==R){return "♖";}
        if(role==N){return "♘";}
    }
    return {};
}

void Piece::move(int f,int r){
    Piece::setPosition(f,r);
    ++moves;
}

int Piece::getMoves() const{
    return moves;
}

void Piece::setMoves(int m){
    moves=m;
}

void Piece::setPosition(int f,int r){
    file=f;
    rank=r;
}

void Piece::getPosition(int &f,int &r){
    f=file;
    r=rank;
}

void Piece::promotion(int r_new){
    if(role==P)role=r_new;
}

void Piece::empty(){
    player=0;
    role=0;
    moves=0;
}

bool Piece::isEmpty() const{
    return player==0;
}

#endif