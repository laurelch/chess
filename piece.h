#ifndef PIECE_H
#define PIECE_H
#include <string>
#define B 66 // Bishop
#define K 75 // King
#define P 80 // Pawn
#define Q 81 // Queen
#define R 82 // Rook
#define N 110 // Knight
using namespace std;

class Piece{
    public:
        Piece(int p,int r):player{p},role{r}
        {}
        Piece(){}
        ~Piece(){}
        int getPlayer() const;
        string printPlayer() const;
        int getRole() const;
        string printRole() const;
        string printRoleShort() const;
        string printUnicode() const;
        bool inRange(int f,int r){return f>='a'&&f<='h'&&r>=1&&r<=8;}
        int getMoves() const{return moves;}
        void setMoves(int m){moves=m;}
        void setPosition(int,int);
        void getPosition(int&,int&) const;
        void move(int f,int r){setPosition(f,r);++moves;}
        void promotion(int);
        void empty();
        bool isEmpty() const;
        // returns potential moves sort from near to far
        void directionalMoves(vector<vector<int>>&,int,int);
        void oneMove(vector<vector<int>>&,int,int);
        vector<vector<int>> potentialMoves();
        vector<vector<int>> potentialBishopMoves();
        vector<vector<int>> potentialKingMoves();
        vector<vector<int>> potentialPawnMoves();
        vector<vector<int>> potentialQueenMoves();
        vector<vector<int>> potentialRookMoves();
        vector<vector<int>> potentialKnightMoves();

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

string Piece::printPlayer() const{
    if(player==1){return "w";}
    else if(player==-1){return "b";}
    return {};
}

int Piece::getRole() const{
    return role;
}

string Piece::printRole() const{
    if(role==P){return "Pawn";}
    else if(role==R){return "Rook";}
    else if(role==N){return "Knight";}
    else if(role==B){return "Bishop";}
    else if(role==Q){return "Queen";}
    else if(role==K){return "King";}
    return {};
}

string Piece::printRoleShort() const{
    if(role==P){return "P";}
    else if(role==R){return "R";}
    else if(role==N){return "N";}
    else if(role==B){return "B";}
    else if(role==Q){return "Q";}
    else if(role==K){return "K";}
    return {};
}

string Piece::printUnicode() const{
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

void Piece::setPosition(int f,int r){
    file=f;
    rank=r;
}

void Piece::getPosition(int &f,int &r) const{
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

void Piece::directionalMoves(vector<vector<int>> &moves,int f_dir,int r_dir){
    vector<int> dir_moves{};
    for(int i=0;i<8;++i){
        int f_new=file+f_dir;
        int r_new=rank+r_dir;
        if(inRange(f_new,r_new)){dir_moves.push_back(f_new);dir_moves.push_back(r_new);}
        else break;
    }
    if(dir_moves.size()>0){moves.push_back(dir_moves);}
}

void Piece::oneMove(vector<vector<int>>& moves,int f_diff,int r_diff){
    if(inRange(file+f_diff,rank+r_diff)){
        vector<int> move{file+f_diff,rank+r_diff};
        moves.push_back(move);
    }
}

vector<vector<int>> Piece::potentialMoves(){
    switch(role){
        case B:
            return potentialBishopMoves();
        case K:
            return potentialKnightMoves();
        case P:
            return potentialPawnMoves();
        case Q:
            return potentialQueenMoves();
        case R:
            return potentialRookMoves();
        case N:
            return potentialKnightMoves();
    }
    return vector<vector<int>>{};
}

vector<vector<int>> Piece::potentialBishopMoves(){
    vector<vector<int>> moves;
    //[-1,-1],[1,1],[1,-1],[-1,1]
    directionalMoves(moves,-1,-1);
    directionalMoves(moves,1,1);
    directionalMoves(moves,1,-1);
    directionalMoves(moves,-1,1);
    return moves;
}

vector<vector<int>> Piece::potentialKingMoves(){
    vector<vector<int>> moves{};
    for(int i=-1;i<=1;++i){
        for(int j=-1;j<=1;++i){
            if(i==0&&j==0)continue;
            oneMove(moves,i,j);
        }
    }
    return moves;
}

vector<vector<int>> Piece::potentialPawnMoves(){
    vector<vector<int>> moves{};
    if(getMoves()==0){
        vector<int> move{file,rank+player};
        moves.push_back(move);
        vector<int> move2{file,rank+2*player};
        moves.push_back(move2);
    }
    oneMove(moves,-1,player);
    oneMove(moves,1,player);
    return moves;
}

vector<vector<int>> Piece::potentialQueenMoves(){
    vector<vector<int>> moves{};
    for(int i=-1;i<=1;++i){
        for(int j=-1;j<=1;++i){
            if(i==0&&j==0)continue;
            directionalMoves(moves,i,j);
        }
    }
    return moves;
}

vector<vector<int>> Piece::potentialRookMoves(){
    vector<vector<int>> moves{};
    directionalMoves(moves,-1,0);
    directionalMoves(moves,0,1);
    directionalMoves(moves,1,0);
    directionalMoves(moves,0,-1);
    return moves;
}

vector<vector<int>> Piece::potentialKnightMoves(){
    vector<vector<int>> moves{};
    oneMove(moves,-2,-1);
    oneMove(moves,-1,-2);
    oneMove(moves,1,2);
    oneMove(moves,2,1);
    oneMove(moves,1,-2);
    oneMove(moves,2,-1);
    oneMove(moves,-1,2);
    oneMove(moves,-2,1);
    return moves;
}
#endif