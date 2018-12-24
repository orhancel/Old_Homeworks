//
// Created by ORHAN on 26.11.2017.
//

#ifndef HW5_CONNECTFOURABSTRACT_H
#define HW5_CONNECTFOURABSTRACT_H
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include<fstream>
#include <cstdlib>
#include <vector>
#include <ctype.h>
#include "Cell.h"

using namespace std;

class ConnectFourAbstract {
public:

    ConnectFourAbstract();
    ConnectFourAbstract(int,int);

    ConnectFourAbstract(int square);
    ConnectFourAbstract(string filename);


    int playGame();

    ~ConnectFourAbstract();


    ConnectFourAbstract( const ConnectFourAbstract &other );



    inline char GetPosToVector(int position){
        int row=position/DimensionX;
        int col=position%DimensionX;
        return gameBoard[row][col].getType();
    }

    inline void SetPosToVector(int position,char type){
        gameBoard[position/DimensionX][position%DimensionX].setType(type);

    }



    int getWidth() const;

    void setWidth(int width);

    int getHeight() const;

    void setHeight(int height);




    inline int getLivingCells() const{
        return LivingCells;
    }

    void setLivingCells(int LivingCells){

        this->LivingCells = LivingCells;
    }
    bool getIsEnded() const;

    void setIsEnded(bool isEnded);


protected:

    bool isEnded= false;//////////////HAS GAME ENDED?
    bool isBoardInitialized= false;
    char AiOrPlayer='N';/*1 ai  2 player*/
    int LivingCells=0;

    int totalCells=0;
    char player1Pos[2]={'a','a'};


    Cell ** gameBoard;

    int DimensionX;
    int DimensionY;


    virtual char Play()=0;///new enemy ai
    int Play(int position);

    int CheckMove(char type);
    virtual int CheckWin(const int &position,const char &type)=0;


    inline void PrintBoard(){
        char type='a';
        for (int i = 0; i < DimensionX; ++i) {

            cout<<type<<" ";
            type++;
        }
        cout<<endl;

        for (int i = 0; i < DimensionY; ++i) {

            for(int j=0;j<DimensionX;++j){
                if(gameBoard[i][j].getType()=='S')
                    cout<<" "<<" ";
                else
                    cout<<gameBoard[i][j].getType()<<" ";
            }


            cout<<endl;

        }
        cout<<endl;
    }


    int  FileArraySize( string DosyaAd);
    int LoadFile(string DosyaAd);
    void SaveFile(const string &DosyaAd);
    void printWin(int position, char type, int winType);
    int PlayHand(char HandType,string User);




};

#endif //HW5_CONNECTFOURABSTRACT_H
