#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <iostream>
#include "piece.h"
#define BOARD_SIZE 8

using namespace std;
class Board{
    vector<Piece> board;
    public:
        Board(){
            init();
        }
        void init(){
            //initialize empty board
            Piece piece{};
            vector<Piece> initialBoard;
            for(int rank=1;rank<=8;++rank){
                // std::cout<<"|";
                for(int file=int('a');file<=int('h');++file){
                    int player=0;//white=1,black=2
                    int role=0;
                    //determine player: white or black
                    if(rank<=2){player=1;}
                    else if(rank>=7){player=2;}
                    //determine role: pawn, rock, knight, bishop, queen, or king
                    if(rank==2||rank==7){role=P;}
                    else if(file==int('a')||file==int('h')){role=R;}
                    else if(file==int('b')||file==int('g')){role=N;}
                    else if(file==int('c')||file==int('f')){role=B;}
                    else if(file==int('d')){role=Q;}
                    else if(file==int('e')){role=K;}
                    //initialize piece with player and role
                    if(player>0){
                        Piece piece(player,role);
                        initialBoard.push_back(piece);
                        // std::cout<<piece.getPlayer()<<piece.getRoleShort()<<"|";
                    }else{
                        initialBoard.push_back(piece);
                        // std::cout<<"__|";
                    }
                }
                // std::cout<<std::endl;
            }
            // std::cout<<std::endl;
            board=initialBoard;
            // print(initialBoard,"initial board");
        }
        void print() const{
            std::cout<<"|--|--|--|--|--|--|--|--|"<<std::endl;
            for(int i=0;i<BOARD_SIZE;++i){
                std::cout<<"|";
                for(int j=0;j<BOARD_SIZE;++j){
                    const int index=i*BOARD_SIZE+j;
                    if(board[index].getPlayer().empty()){
                        std::cout<<"__|";
                    }else{
                        std::cout<<board[index].getPlayer()<<board[index].getRoleShort()<<'|';
                    }
                }
                std::cout<<std::endl;
            }
            std::cout<<"|--|--|--|--|--|--|--|--|"<<std::endl;
        }

        static void print(vector<Piece> board,std::string name=""){
            std::cout<<"    "<<name<<std::endl;
            for(int i=0;i<BOARD_SIZE;++i){
                std::cout<<"|";
                for(int j=0;j<BOARD_SIZE;++j){
                    const int index=i*BOARD_SIZE+j;
                    if(board[index].getPlayer().empty()){
                        std::cout<<"__|";
                    }else{
                        std::cout<<board[index].getPlayer()<<board[index].getRoleShort()<<'|';
                    }
                }
                std::cout<<std::endl;
            }
            std::cout<<std::endl;
        }

        // valid move, make change to board
        void move(){

        }

};
#endif