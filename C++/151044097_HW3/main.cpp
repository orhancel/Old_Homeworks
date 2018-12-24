#include <iostream>

#include <vector>
#include "ConnectFour.h"


int main() {

    ConnectFour oyun[5];
    string Line;

    int i=0;
    while (true){
        cout<<i+1<<". Game"<<endl;

        oyun[i].playGame();
        cout<<"To exit ,type 'E'"<<endl;
        getline(cin,Line);
        if(Line[0]=='E')
            return 0;
        i++;
    }


    std::cout << "Hel1lo, World!" << std::endl;
    return 0;
}