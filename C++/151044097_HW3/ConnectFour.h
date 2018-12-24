//
// Created by ORHAN on 15.10.2017.
//

#ifndef HW3_CONNECTFOUR_H
#define HW3_CONNECTFOUR_H

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include<fstream>
#include <cstdlib>
#include <vector>

using namespace std;

class ConnectFour {
    public:

    ConnectFour();
    ConnectFour(int,int);

    ConnectFour(int square);


    int playGame();




    inline char GetPosToVector(int position){
        int row=position/DimensionY;
        int col=position%DimensionX;
        return Board[row][col].getType();
    }

    inline void SetPosToVector(int position,char type){
        Board[position/DimensionY][position%DimensionX].setType(type);
    }


    int getWidth() const;

    void setWidth(int width);

    int getHeight() const;

    void setHeight(int height);

    static int getLivingGames();

    static void setLivingGames(int LivingGames);





    inline int getTurnCount() const{
        return turnCount;
    }

    void setTurnCount(int turnCount){

        this->turnCount = turnCount;
    }
    bool getIsEnded() const;

    void setIsEnded(bool isEnded);


private:

        bool isEnded= false;//////////////HAS GAME ENDED?
        bool isBoardInitialized= false;
        int AiOrPlayer=0;/*1 ai  2 player*/
        int turnCount=0;
        static int LivingCells;
        char player1Pos[2]={'a','a'};
        class Cell{
    public:
        int getRow() const {
            return row;
        }

        void setRow(int row) {
            this->row=row  ;
        }

        int getCol() const {
            return this->col;
        }

        void setCol(int col) {
            this->col=col;
        }

        char getType() const {
            return type;
        }

        void setType(char type) {
            this->type = type;
        }



    private:
        int row;
        int col;
        char type;




    };
        vector< vector<Cell> > Board;

        int DimensionX;
        int DimensionY;


        char Play();
        int Play(int);

        int CheckMove(char type);
        int CheckWin(const int &position,const char &type);
        int CompareWinCounts();
        bool Compare(ConnectFour other);

        void PrintBoard(){ char type='a';
            for (int i = 0; i < DimensionX; ++i) {

                cout<<type<<" ";
                type++;
            }
            cout<<endl;

            for (int i = 0; i < DimensionY; ++i) {

                for(int j=0;j<DimensionX;++j){

                    cout<<Board[i][j].getType()<<" ";
                }


                cout<<endl;

            }
            cout<<endl;
        }

        char DikeyKazanma(const char &Side);
        char YatayKazanma(const char &Side);
        char EnemyAI(char playerPos[2]);
        int  FileArraySize( string DosyaAd);
        void LoadFile(string DosyaAd);
        void SaveFile(const string &DosyaAd);
        void printWin(int position, char type, int winType);
        int PlayHand(char HandType,string User);

    public:
        const vector<vector<Cell>> &getBoard() const;
        void setBoard(const vector<vector<ConnectFour::Cell>> &Board);


};


#endif //HW3_CONNECTFOUR_H
