#include "piece.h"

int Piece::getPlayer() const{
    return player;
}

int Piece::getRole() const{
    return role;
}

std::string Piece::getRoleFullName() const{
    if(role==P){return "Pawn";}
    else if(role==R){return "Rook";}
    else if(role==N){return "Knight";}
    else if(role==B){return "Bishop";}
    else if(role==Q){return "Queen";}
    else if(role==K){return "King";}
    return {};
}

int Piece::getIndex() const{
    int f=file-'a';
    int r=rank-1;
    return r*BOARD_SIZE+f;
}

void Piece::getPosition(int &f,int &r) const{
    f=file;
    r=rank;
}

std::string Piece::getImageFileName() const{
    std::string directory=":/images/";
    char black='d';
    char white='l';
    char color=(player==1)?white:black;
    char roleLowCase=char(role+32);
    std::string filePrefix="Chess_";
    std::string fileSuffix="t60";
    std::string fileName=filePrefix+roleLowCase+color+fileSuffix;
    return directory+fileName;
}

void Piece::setPosition(int f,int r){
    if(inRange(f,r)){
        file=f;
        rank=r;
    }
}

void Piece::promotion(int r_new){
    if(role==P)role=r_new;
}

void Piece::directionalMoves(std::vector<std::vector<int>> &moves,int f_dir,int r_dir){
    std::vector<int> dir_moves{};
    for(int i=0;i<8;++i){
        int f_new=file+i*f_dir;
        int r_new=rank+i*r_dir;
        if(inRange(f_new,r_new)){dir_moves.push_back(f_new);dir_moves.push_back(r_new);}
        else break;
    }
    if(dir_moves.size()>0){moves.push_back(dir_moves);}
}

void Piece::oneMove(std::vector<std::vector<int>>& moves,int f_diff,int r_diff){
    if(inRange(file+f_diff,rank+r_diff)){
        std::vector<int> move{file+f_diff,rank+r_diff};
        moves.push_back(move);
    }
}

std::vector<std::vector<int>> Piece::potentialMoves(){
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
        default:
            std::cout<<"Role incorrect"<<std::endl;
            break;
    }
    return std::vector<std::vector<int>>{};
}


std::vector<std::vector<int>> Piece::potentialBishopMoves(){
    std::vector<std::vector<int>> moves;
    //[-1,-1],[1,1],[1,-1],[-1,1]
    directionalMoves(moves,-1,-1);
    directionalMoves(moves,1,1);
    directionalMoves(moves,1,-1);
    directionalMoves(moves,-1,1);
    return moves;
}

std::vector<std::vector<int>> Piece::potentialKingMoves(){
    std::vector<std::vector<int>> moves{};
    for(int i=-1;i<=1;++i){
        for(int j=-1;j<=1;++j){
            if(i==0&&j==0)continue;
            oneMove(moves,i,j);
        }
    }
    return moves;
}

std::vector<std::vector<int>> Piece::potentialPawnMoves(){
    std::vector<std::vector<int>> moves{};
    if(getMoves()==0){
        std::vector<int> move{file,rank+player};
        moves.push_back(move);
        std::vector<int> move2{file,rank+2*player};
        moves.push_back(move2);
    }
    oneMove(moves,-1,player);
    oneMove(moves,1,player);
    return moves;
}

std::vector<std::vector<int>> Piece::potentialQueenMoves(){
    std::vector<std::vector<int>> moves{};
    for(int i=-1;i<=1;++i){
        for(int j=-1;j<=1;++j){
            if(i==0&&j==0)continue;
            directionalMoves(moves,i,j);
        }
    }
    return moves;
}

std::vector<std::vector<int>> Piece::potentialRookMoves(){
    std::vector<std::vector<int>> moves{};
    directionalMoves(moves,-1,0);
    directionalMoves(moves,0,1);
    directionalMoves(moves,1,0);
    directionalMoves(moves,0,-1);
    return moves;
}

std::vector<std::vector<int>> Piece::potentialKnightMoves(){
    std::vector<std::vector<int>> moves{};
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
