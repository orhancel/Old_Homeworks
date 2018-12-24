//
// Created by ORHAN on 26.11.2017.
//

#ifndef HW5_CONNECTFOURDIAG_H
#define HW5_CONNECTFOURDIAG_H

#include "ConnectFourAbstract.h"

class ConnectFourDiag:public ConnectFourAbstract{

public:
    char YatayKazanma(const char &Side);
    int CheckWin(const int &position,const char &type);
    char Play();


};



#endif //HW5_CONNECTFOURDİAG_H
