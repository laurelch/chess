#ifndef PIECE_H
#define PIECE_H
#include <string>
#define P 80 // Pawn
#define R 82 // Rock
#define N 110 // Knight
#define B 66 // Bishop
#define Q 81 // Queen
#define K 75 // King
class Piece{
    public:
        Piece(int p,int r):player{p},role{r}
        {}
        Piece(){}
        ~Piece(){}
        std::string getPlayer() const;
        std::string getRole() const;
        std::string getRoleShort() const;
    private:
        int player=0;
        int role=0;
};

std::string Piece::getPlayer() const{
    if(player==1){return "w";}
    else if(player==2){return "b";}
    return {};
}

std::string Piece::getRole() const{
    if(role==P){return "Pawn";}
    else if(role==R){return "Rook";}
    else if(role==N){return "Knight";}
    else if(role==B){return "Bishop";}
    else if(role==Q){return "Queen";}
    else if(role==K){return "King";}
    return {};
}

std::string Piece::getRoleShort() const{
    if(role==P){return "P";}
    else if(role==R){return "R";}
    else if(role==N){return "K";}
    else if(role==B){return "B";}
    else if(role==Q){return "Q";}
    else if(role==K){return "K";}
    return {};
}

#endif