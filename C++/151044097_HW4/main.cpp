#include <iostream>

#include <vector>
#include "ConnectFour.h"


int main() {

    int i=0;
    int finishedGames=0;
    int obje=0;
    string Line;
    cout<<"M for multi,S for single"<<endl;
    getline(cin,Line);
    Line[0]=toupper(Line[0]);
    if(Line[0]=='S'){
        ConnectFour oyun;
        oyun.playGame();
        cout<<"main"<<endl;
        return 0;
    }

    else if(Line[0]=='M'){

        ConnectFour oyun[5];
        for(int i=0;i<5;i++){
            oyun[i].SetMultiGame(true);
            oyun[i].playGame();
        }

        while(true){

            while(true){
                cout<<"Obje  seciniz"<<endl;
                getline(cin,Line);
            
                if((Line[0]-'0')>5  && (Line[0]-'0')<1 )
                {
                    cerr<<"Unrecognized object number "<<endl;

                }
                else{
                    obje=Line[0]-'0';
                    break;
                }
            }
            

            oyun[obje].playGame();
            if(oyun[obje].getIsEnded()==true)
                finishedGames++;

            

            if(finishedGames==5){
                cout<<"All games have eneded"<<endl;
                return 0;
            }
        }

    }

    return 0;
}