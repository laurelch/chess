#ifndef PIECE_H
#define PIECE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <iostream>
#include <string>
#define B 66 // Bishop
#define K 75 // King
#define N 78 // Knight
#define P 80 // Pawn
#define Q 81 // Queen
#define R 82 // Rook
#define BOARD_SIZE 8

class Piece:public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Piece(int p,int r,QGraphicsItem *parent=0):player{p},role{r}{}
    Piece(){}
    ~Piece(){}

    int getPlayer() const;
    int getRole() const;
    std::string getRoleFullName() const;
    int getIndex() const;
    int getMoves() const{return moves;}
    void getPosition(int&,int&) const;
    std::string getImageFileName() const;
    void setMoves(int m){moves=m;}
    void setPosition(int,int);
    std::string printFileRank() const;
    std::string printPlayer() const;
    bool inRange(int f,int r){return f>='a'&&f<='h'&&r>=1&&r<=8;}
    bool isEmpty() const;

    void promotion(int);
    void directionalMoves(std::vector<std::vector<int>>&,int,int);
    std::vector<std::vector<int>> potentialMoves();
    std::vector<std::vector<int>> potentialBishopMoves();
    std::vector<std::vector<int>> potentialKnightMoves();
    std::vector<std::vector<int>> potentialKingMoves();
    std::vector<std::vector<int>> potentialPawnMoves();
    std::vector<std::vector<int>> potentialQueenMoves();
    std::vector<std::vector<int>> potentialRookMoves();

public slots:
    void oneMove(std::vector<std::vector<int>>&,int,int);
protected:
    int player=0;
    int role=0;
    int moves=-1;
    int file=0;
    int rank=0;
};

#endif // PIECE_H
