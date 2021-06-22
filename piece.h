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
        int countMoves() const;
        void move(int,int);
        void setPosition(int,int);
        void getPosition(int*,int*);
        void promotion(int);
        
    protected:
        int player=0;
        int role=0;
        int moves=0;
        int file=0;
        int rank=0;
};

int Piece::getPlayer() const{
    return player;
}

std::string Piece::printPlayer() const{
    if(player==1){return "w";}
    else if(player==2){return "b";}
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

int Piece::countMoves() const{
    return moves;
}

void Piece::move(int f,int r){
    Piece::setPosition(f,r);
}

void Piece::setPosition(int f,int r){
    file=f;
    rank=r;
}

void Piece::getPosition(int* f,int* r){
    *f=file;
    *r=rank;
}

void Piece::promotion(int r_new){
    if(role==P)role=r_new;
}
#endif