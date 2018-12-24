//
// Created by ORHAN on 26.11.2017.
//

#ifndef HW5_CELL_H
#define HW5_CELL_H

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include<fstream>
#include <cstdlib>
#include <vector>
#include <ctype.h>

using namespace std;

class Cell{
            public:






                int getRow() const ;

                void setRow(int row) ;

                int getCol() const ;

                void setCol(int col) ;

                char getType() const ;

                void setType(char type) ;

                char getColumn() const;

                void setColumn(char column);


            private:
                int row;
                int col;
                char column;
                char type;


        };


#endif //HW5_CELL_H
