//
// Created by ORHAN on 26.11.2017.
//

#ifndef HW5_CONNECTFOURPLUSUNDO_H
#define HW5_CONNECTFOURPLUSUNDO_H

#include "ConnectFourPlus.h"

class ConnectFourPlusUndo:public ConnectFourPlus{
    public:

        void Undo();
        void AddUndoList(int);
        const vector<int > &getUndoList() const;

        void setUndoList(const vector<int > &undoList);
        int playGame();
        int PlayHand(char HandType,string User);

    private:
        vector<int> undoList;



};


#endif //HW5_CONNECTFOURPLUSUNDO_H
