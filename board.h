#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <iostream>
#include "piece.h"
#define BOARD_SIZE 8
using namespace std;

class Board{
    std::vector<Piece> board;
    std::vector<Piece> boardCopy;
    // std::vector<Piece> onBoardWhite;
    // std::vector<Piece> onBoardBlack;
    std::vector<Piece> offBoardWhite;
    std::vector<Piece> offBoardBlack;
    int lastPiece;
    int whiteKing;
    int blackKing;
    bool verbose;
    bool gameOver;
    int round;
    std::string gameOverMessage;
    public:
        Board(){init();}
        void init();
        void print() const;
        void setVerbose(bool);
        void illegal(string) const;
        bool inRange(int f,int r) const{return f>='a'&&f<='h'&&r>=1&&r<=8;}
        Piece getPiece(int,int) const;
        Piece getPiece(int) const;
        int getKing(int) const;
        void setKing(int,int);
        int lastMoved() const;
        int getIndex(int,int) const;
        void getFileRank(int,int&,int&) const;
        bool isEmpty(int,int) const;
        void addEmpty(int);
        void addEmpty(int,int);
        bool emptyBetween(Piece*,Piece*) const;
        bool move(string);
        bool move(int,int,int,int,int);
        bool tentativeMove(Piece*,Piece*,int);
        bool moveRole(Piece*,Piece*,int);
        bool moveBishop(Piece*,Piece*) const;
        bool moveKing(Piece*,Piece*);
        bool moveKnight(Piece*,Piece*) const;
        bool movePawn(Piece*,Piece*,int);
        bool moveQueen(Piece*,Piece*) const;
        bool moveRook(Piece*,Piece*) const;
        void afterMove(Piece*);
        // prints a block of important message
        void printNotice(string) const;
        bool check(Piece*);
        bool checked(int);
        bool checkmate(Piece*);
        bool stalemate(Piece*);
        bool isGameOver() const;
        std::string getGameOverMessage() const;
};

void Board::init(){
    verbose=false;
    gameOver=false;
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
                // if(player==1)onBoardWhite.push_back(piece);
                // else if(player==-1)onBoardBlack.push_back(piece);
            }else{
                piece.move(file,rank);
                initialBoard.push_back(piece);
            }
        }
    }
    board=initialBoard;
    round=0;
}

void Board::print() const{
    for(int i=0;i<27;++i)std::cout<<"-";
    std::cout<<std::endl;
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
            if(board[index].isEmpty()){
                std::cout<<"__|";
            }else{
                std::cout<<board[index].printPlayer()<<board[index].printRoleShort()<<'|';
                // std::cout<<board[index].printUnicode()<<'|';
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
    std::cout<<std::endl;
    for(int i=0;i<27;++i)std::cout<<"-";
    std::cout<<std::endl;
}

void Board::setVerbose(bool v){
    verbose=v;
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

void Board::getFileRank(int index,int &f,int &r) const{
    f=index%BOARD_SIZE+'a';
    r=index/BOARD_SIZE+1;
}

bool Board::isEmpty(int f,int r) const{
    int index=getIndex(f,r);
    Piece piece=board[index];
    int player=piece.getPlayer();
    if(player==0){return true;}
    return false;
}

void Board::addEmpty(int index){
    int f=0;
    int r=0;
    getFileRank(index,f,r);
    addEmpty(f,r);
}

void Board::addEmpty(int f,int r){
    int index=getIndex(f,r);
    Piece empty{};
    empty.move(f,r);
    board[index]=empty;
}

// !Bug: piece can cross over other pieces
bool Board::emptyBetween(Piece* from,Piece* to) const{
    int f1=0,r1=0,f2=0,r2=0;
    from->getPosition(f1,r1);
    to->getPosition(f2,r2);
    if(verbose)cout<<"Board::emptyBetween "<<char(f1)<<r1<<"=>"<<char(f2)<<r2<<endl;
    int fstep=f2-f1;
    int rstep=r2-r1;
    if(fstep>0){fstep=1;} else if(fstep<0){fstep=-1;}
    if(rstep>0){rstep=1;} else if(rstep<0){rstep=-1;}
    for(int i=f1,j=r1;i!=f2||j!=r2;i+=fstep,j+=rstep){
        if(i==f1&&j==r1)continue;
        if(!inRange(i,j))break;
        if(!isEmpty(i,j)){
            if(verbose)cout<<"Board::emptyBetween "<<char(i)<<j<<" not empty."<<endl;
            return false;
        }
    }
    return true;
}

bool Board::move(string user_input){
    int f1=int(user_input[0]);
    int r1=int(user_input[1]-'0');
    int f2=int(user_input[3]);
    int r2=int(user_input[4]-'0');
    int promoteTo=Q;
    if(user_input.size()==7){promoteTo=user_input[6];}
    return move(f1,r1,f2,r2,promoteTo);
}

bool Board::move(int f1,int r1,int f2,int r2,int promoteTo=Q){
    // real move
    Piece from=getPiece(f1,r1);
    Piece to=getPiece(f2,r2);
    bool succeed=false;
    succeed=moveRole(&from,&to,promoteTo);
    if(succeed){
        boardCopy=board;
        int index_from=getIndex(f1,r1);
        int index_to=getIndex(f2,r2);
        int player=from.getPlayer();
        addEmpty(f1,r1);
        from.move(f2,r2);
        board[index_to]=from;
        if(from.getRole()==K){setKing(player,index_to);}
        if(checked(player)){
            board=boardCopy;
            return false;
        }
        if(!to.isEmpty()){
            if(player==1){offBoardBlack.push_back(to);}
            else if(player==-1){offBoardWhite.push_back(to);}
        }
        lastPiece=index_to;
        afterMove(&from);
    }
    round+=0.5;
    return succeed;
}

bool Board::tentativeMove(Piece* from,Piece* to,int promoteTo=Q){
    // not real move
    bool succeed=false;
    boardCopy=board;
    succeed=moveRole(from,to,promoteTo);
    if(succeed){
        int player=from->getPlayer();
        int f1=0,r1=0;
        from->getPosition(f1,r1);
        addEmpty(f1,r1);
        int f2=0,r2=0;
        to->getPosition(f2,r2);
        from->move(f2,r2);
        int index_to=to->getIndex();
        board[index_to]=*from;
        if(checked(player)){
            board=boardCopy;
            return false;
        }
    }
    board=boardCopy;
    return succeed;
}

bool Board::moveRole(Piece* from,Piece* to,int promoteTo=Q){
    int role=from->getRole();
    if(from->getPlayer()==to->getPlayer()){
        // std::cout<<"Board::moveRole, same player's piece , role="<<char(role)<<std::endl;
        return false;
    }else if(role!=N&&!emptyBetween(from,to)){
        // std::cout<<"Board::moveRole, not empty between, role="<<char(role)<<std::endl;
        return false;
    }
    switch(role){
        case B:
            return moveBishop(from,to);
        case K:
            return moveKing(from,to);
        case P:
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

bool Board::moveBishop(Piece* from,Piece* to) const{
    int f1=0,r1=0,f2=0,r2=0;
    from->getPosition(f1,r1);
    to->getPosition(f2,r2);
    if(verbose)cout<<"Board::moveBishop "<<char(f1)<<r1<<"=>"<<char(f2)<<r2<<endl;
    if(abs(f1-f2)==abs(r1-r2)){return true;}
    return false;
}

bool Board::moveKing(Piece* from,Piece* to){
    int f1=0,r1=0,f2=0,r2=0;
    from->getPosition(f1,r1);
    to->getPosition(f2,r2);
    if(verbose)cout<<"Board::moveKing "<<char(f1)<<r1<<"=>"<<char(f2)<<r2<<", moves="<<from->getMoves()<<endl;
    //basic
    if(abs(f1-f2)<=1&&abs(r1-r2)<=1){return true;}
    //castling
    else if(from->getMoves()==0&&abs(f1-f2)==2){
        int way=(f2-f1)/2;
        int f_rook=0;
        if(way>0){f_rook=int('h');}else{f_rook=int('a');}
        Piece rook=getPiece(f_rook,r1);
        if(verbose){if(rook.getMoves()!=0){cout<<"Board::moveKing 1"<<endl;return false;}}
        for(int f=f1+way;f!=f_rook;f+=way){
            Piece tmp=getPiece(f,r1);
            if(verbose){if(tmp.getPlayer()!=0){cout<<"Board::moveKing 2"<<endl;return false;}}
        }
        int f_rook2=f1+way;
        int index_cross=getIndex(f_rook2,r1);
        int index_rook=getIndex(f_rook,r1);
        board[index_cross]=rook;
        addEmpty(f_rook,r1);
        addEmpty(f1,r1);
        return true;
    }
    return false;
}

bool Board::moveKnight(Piece* from,Piece* to) const{
    int f1=0,r1=0,f2=0,r2=0;
    from->getPosition(f1,r1);
    to->getPosition(f2,r2);
    if(verbose)cout<<"Board::moveKnight "<<f1<<char(f1)<<r1<<"=>"<<char(f2)<<r2<<endl;
    if(abs(f1-f2)==1&&abs(r1-r2)==2){return true;}
    else if(abs(f1-f2)==2&&abs(r1-r2)==1){return true;}
    return false;
}

bool Board::movePawn(Piece* from,Piece* to,int promoteTo){
    int f1=0,r1=0,f2=0,r2=0;
    from->getPosition(f1,r1);
    to->getPosition(f2,r2);
    if(verbose)cout<<"Board::movePawn "<<char(f1)<<r1<<"=>"<<char(f2)<<r2<<", moves="<<from->getMoves()<<endl;
    int player=from->getPlayer();
    //promotion
    if((player==1&&r2==8)||(player==-1&&r2==1)){
        if(promoteTo!=0){from->promotion(promoteTo);}
        else{from->promotion(Q);}
    }
    //basic
    if(f1==f2&&to->isEmpty()){
        if(r2-r1==player){return true;}
        if(from->getMoves()==0&&r2-r1==2*player){return true;}
    }else if(abs(f1-f2)==1&&r2-r1==player&&!to->isEmpty()){
        //capture opponent
        return true;
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
    }
    return false;
}

bool Board::moveQueen(Piece* from,Piece* to) const{
    int f1=0,r1=0,f2=0,r2=0;
    from->getPosition(f1,r1);
    to->getPosition(f2,r2);
    if(verbose)cout<<"Board::moveQueen "<<char(f1)<<r1<<"=>"<<char(f2)<<r2<<endl;
    if(f1==f2&&r1!=r2){return true;}
    else if(f1!=f2&&r1==r2){return true;}
    else if(abs(f1-f2)==abs(r1-r2)){return true;}
    return false;
}

bool Board::moveRook(Piece* from,Piece* to) const{
    int f1=0,r1=0,f2=0,r2=0;
    from->getPosition(f1,r1);
    to->getPosition(f2,r2);
    if(verbose)cout<<"Board::moveRook "<<f1<<char(f1)<<r1<<"=>"<<char(f2)<<r2<<endl;
    if(f1==f2&&r1!=r2){return true;}
    else if(f1!=f2&&r1==r2){return true;}
    return false;
}

void Board::afterMove(Piece* from){
    if(check(from)){
        if(checkmate(from)){
            printNotice("Checkmate");
            gameOver=true;
            if(from->getPlayer()==1){gameOverMessage="White wins";}
            else if(from->getPlayer()==-1){gameOverMessage="Black wins";}
        }else{
            printNotice("Check");
        }
    }
    else if(stalemate(from)){
        printNotice("Stalemate");
        gameOver=true;
        gameOverMessage="draw";
    }
}

void Board::printNotice(string info) const{
    int lineWidth=27;
    for(int i=0;i<lineWidth;++i)std::cout<<"_";
    std::cout<<std::endl;
    int space=(lineWidth-info.size()-1)/2;
    std::cout<<"|";
    for(int i=0;i<space;++i)std::cout<<" ";
    std::cout<<info;
    for(int i=0;i<space;++i)std::cout<<" ";
    std::cout<<"|"<<std::endl;
    for(int i=0;i<lineWidth;++i)std::cout<<"‾";
    std::cout<<std::endl;
}

bool Board::check(Piece* last){
    // check if one player's last move put opponent's King in check
    Piece opponentKing=getPiece(getKing(-(last->getPlayer())));
    int promoteTo=Q;
    if(moveRole(last,&opponentKing,promoteTo)){return true;}
    return false;
}

bool Board::checked(int player){
    // check if my king can be captured by opponent after a potential move
    for(int p=0;p<board.size();++p){
        Piece opponentPiece=getPiece(p);
        //TODO: get all of one player's pieces on board
        if(opponentPiece.getPlayer()==-player){
            Piece myKing=getPiece(getKing(player));
            if(moveRole(&opponentPiece,&myKing)){
                if(verbose)cout<<"Board::checked "<<opponentPiece.printFileRank()<<"=>"<<myKing.printFileRank()<<endl;
                return true;
            }
        }
    }
    return false;
}

bool Board::checkmate(Piece* last){
    // check all possible moves of opponent's King, and see
    // if any of my piece can capture opponent's King after any possible move
    int player=last->getPlayer();
    int kingCopy=getKing(-player);
    Piece opponentKing=getPiece(getKing(-player));
    // if(verbose)cout<<"Board::checkmate player="<<player<<" opponent's king index="<<getKing(-player)<<endl;
    int f1=0;
    int r1=0;
    opponentKing.getPosition(f1,r1);
    bool canEscape=false;
    for(int f2=f1-1;f2<=f1+1;++f2){
        for(int r2=r1-1;r2<=r1+1;++r2){
            if((f2==f1&&r2==r1)||!inRange(f2,r2))continue;
            Piece to=getPiece(f2,r2);
            // if(verbose)cout<<"Board::checkmate "<<char(f1)<<r1<<"=>"<<char(f2)<<r2<<endl;
            bool canCapture=false;
            // one possible move of opponent's King
            if(moveRole(&opponentKing,&to)){
                setKing(-player,getIndex(f2,r2));
                for(int i=0;i<board.size();++i){
                    Piece myPiece=getPiece(i);
                    if(myPiece.getPlayer()==player&&i!=last->getIndex()){
                        // if(moveRole(myPiece.getRole(),&myPiece,&to)){
                        //     canCapture=true;
                        //     break;
                        // }
                        if(check(&myPiece)){
                            canCapture=true;
                            break;
                        }
                    }
                }
                if(!canCapture){
                    setKing(-player,kingCopy);
                    return false;
                }
            }
        }
    }
    setKing(-player,kingCopy);
    return true;
}

bool Board::stalemate(Piece* last){
    // check if opponent has a possible legal move (does not make itself in check)
    int me=last->getPlayer();
    int opponent=-me;
    for(int p=0;p<board.size();++p){
        Piece opponentPiece=getPiece(p);
        if(opponentPiece.getPlayer()==opponent){
            vector<vector<int>> moves=opponentPiece.potentialMoves();
            for(int i=0;i<moves.size();++i){
                vector<int> dirMoves=moves[i];
                for(int j=0;j<dirMoves.size();j=j+2){
                    Piece to=getPiece(dirMoves[j],dirMoves[j+1]);
                    int o_f=0,o_r=0;
                    opponentPiece.getPosition(o_f,o_r);
                    if(verbose)cout<<"Board::stalemate move "<<char(o_f)<<o_r<<" => "<<char(dirMoves[j])<<dirMoves[j+1]<<endl;
                    if(tentativeMove(&opponentPiece,&to)){
                        return false;
                    }
                    break;
                }
            }
        }
    }
    return true;
}

bool Board::isGameOver() const{
    return gameOver;
}

std::string Board::getGameOverMessage() const{
    return gameOverMessage;
}

#endif