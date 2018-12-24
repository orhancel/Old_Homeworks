//
// Created by ORHAN on 26.11.2017.
//

#ifndef HW5_CONNECTFOURPLUS_H
#define HW5_CONNECTFOURPLUS_H

#include "ConnectFourAbstract.h"

class ConnectFourPlus:public ConnectFourAbstract{

public:
    char DikeyKazanma(const char &Side);
    char YatayKazanma(const char &Side);
    int CheckWin(const int &position,const char &type);
    char Play();



};


#endif //HW5_CONNECTFOURPLUS_H
