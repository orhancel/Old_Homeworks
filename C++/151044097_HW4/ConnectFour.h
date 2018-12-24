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
#include <ctype.h>

using namespace std;

class ConnectFour {
    public:

    ConnectFour();
    ConnectFour(int,int);

    ConnectFour(int square);
    ConnectFour(string filename);


    int playGame();

    ~ConnectFour();


    ConnectFour( const ConnectFour &other );


    ConnectFour& operator =(const ConnectFour &other);



    inline char GetPosToVector(int position){
        int row=position/DimensionX;
        int col=position%DimensionX;
        return gameBoard[row][col].getType();
    }

    inline void SetPosToVector(int position,char type){
        gameBoard[position/DimensionX][position%DimensionX].setType(type);
    }

    bool operator == (const ConnectFour & other);
    bool operator != (const ConnectFour & other);

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

    bool getMultiGame()const;
    void SetMultiGame(bool);


private:

        bool isEnded= false;//////////////HAS GAME ENDED?
        bool isBoardInitialized= false;
        char AiOrPlayer='N';/*1 ai  2 player*/
        int turnCount=0;
        static int LivingGames;
        int emptyCells=0;
        char player1Pos[2]={'a','a'};
        bool  MultiGame=false;
        bool  multiGameBegin=false;
        class Cell{
            public:

                bool operator == (const Cell & other){

                    if(this->row == other.col  && this->col == other.col && this->type == other.type)
                        return true;
                    else
                        return false;

                }

                Cell operator++(int)
                {
                    Cell tmp(*this);
                    if(type=='x')
                        type='o';
                    else if (type =='o')
                        type='*';
                    else
                        type ='x';

                    return tmp;   // return value before increment
                }

                Cell& operator++()
                {
                    if(this->type=='x')
                        this->type='o';
                    else if (this->type =='o')
                        this->type='.';
                    else
                        this->type ='x';

                    return *this;
                }

                friend std::ostream& operator<< (std::ostream& out, const Cell& other){
                    out<<"Row: "<<other.row<<endl<<"Col: "<<other.col<<endl<<"Type: "<<other.type<<endl;
                    return out;

                }
                friend std::istream& operator>> (std::istream& in, Cell& other){
                    in>>other.row;  //>>other.col>>other.type;
                    in>>other.col;
                    in>>other.type;
                    return in;
                }

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





        Cell ** gameBoard;

        int DimensionX;
        int DimensionY;


        char Play();
        int Play(int);

        int CheckMove(char type);
        int CheckWin(const int &position,const char &type);
        int CompareWinCounts();
        bool Compare(ConnectFour other);

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

        char DikeyKazanma(const char &Side);
        char YatayKazanma(const char &Side);
        char EnemyAI(char playerPos[2]);
        int  FileArraySize( string DosyaAd);
        int LoadFile(string DosyaAd);
        void SaveFile(const string &DosyaAd);
        void printWin(int position, char type, int winType);
        int PlayHand(char HandType,string User);




};


#endif //HW3_CONNECTFOUR_H
