//
// Created by ORHAN on 26.11.2017.
//

#include "ConnectFourDiag.h"


int ConnectFourDiag::CheckWin(const int &position,const char &type){


    int TempPos=position;

    while( TempPos>0){
        if(TempPos%DimensionX!=0 )
            TempPos-=(DimensionX+1);
        else
            break;
    }
    if(TempPos<0)
        TempPos+=(DimensionX+1);

    /*Soldan sağa çapraz kazanma kontrolü*/
    while (TempPos<(DimensionX*DimensionY)){
        if(  GetPosToVector(TempPos)==type){
            for (int i = 0; i < 4; ++i) {

                if((TempPos+(DimensionX+1)*i)>=DimensionX*DimensionY  )
                    break;

                else if( GetPosToVector( TempPos+(DimensionX+1)*i)!=type)
                    break;

                if(i==3){
                    /*   Board[TempPos+(Dimension+1)*i]=type+('a'-'A');
                       Board[TempPos+(Dimension+1)*i-Dimension-1]=type+('a'-'A');
                       Board[TempPos+(Dimension+1)*i-2*Dimension-2]=type+('a'-'A');
                       Board[TempPos+(Dimension+1)*i-3*Dimension-3]=type+('a'-'A');*/
                    return 3;
                }

            }
            if(TempPos%DimensionX==DimensionX-1)
                break;
        }
        TempPos+=DimensionX+1;

    }

    TempPos=position;
    /*Sağdan sola çapraz kazanma kontrolü*/
    while(TempPos%DimensionX!=(DimensionX-1) && TempPos>0 ){
        TempPos-=(DimensionX-1);
    }
    if(TempPos<0)
        TempPos+=(DimensionX-1);
    int x=TempPos;
    while (TempPos<(DimensionX*DimensionY)-2){
        if(TempPos%DimensionX==0)
            break;
        if(GetPosToVector(TempPos)==type){
            for (int i = 0; i < 4; ++i) {

                if((TempPos+(DimensionX-1)*i)>=DimensionX*DimensionY )
                    break;
                if( GetPosToVector(TempPos+(DimensionX-1)*i)!=type)
                    break;
                if(i==3){
                    /*   Board[TempPos]=type+('a'-'A');
                       Board[TempPos-Dimension+1]=type+('a'-'A');
                       Board[TempPos-2*Dimension+2]=type+('a'-'A');
                       Board[TempPos-3*Dimension+3]=type+('a'-'A');*/
                	
                    return 4;
                }

            }

        }
        TempPos+=(DimensionX-1);


    }
    return -1;



}


char ConnectFourDiag::Play() {/////////////New EnemyAi function
    int position = 0;
    int positions[3];
    char type;
    /*Tek hareketle kazanma kontrolü*/
    for (int i = 0; i < DimensionX; i++) {
        char type = 'a' + i;
        position = CheckMove(type);
        SetPosToVector(position, 'O');
        if (position != -1) {
            if (CheckWin(position, 'O') >= 1) {
                SetPosToVector(position, '*');

                return type;
            }
        }
        SetPosToVector(position, '*');

    }

    /*Rakibin kazanmasını bloklama*/
    for (int i = 0; i < DimensionX; i++) {
        char type = 'a' + i;
        position = CheckMove(type);
        SetPosToVector(position, 'X');
        if (position != -1) {
            if (CheckWin(position, 'X') >= 1) {
                SetPosToVector(position, '*');
                return type;
            }
        }
        SetPosToVector(position, '*');

    }

    /*Rakip çapraz kazanma kontrolü*/
    type = YatayKazanma('X');

    if (type != 'a' - 1)
        return type;

    /*Yatay ve çapraz kazanma kontrolü*/
    type = YatayKazanma('O');
    if (type != 'a' - 1) {

        return type;
    }

}

char ConnectFourDiag::YatayKazanma(const char &Side){

    int position;
    int positions[2];

    for(int i=0;i<DimensionY;i++){


        for (int j = 0; j < DimensionX-1; ++j) {

            char type = 'a' + j;

            positions[0] = (DimensionX * DimensionY - DimensionX * (i + 1)) + j;

            if (GetPosToVector(positions[0]) == '*')
                SetPosToVector(positions[0], Side);

            else {

                continue;
            }


            if (CheckWin(positions[0], Side) >= 1) {
                SetPosToVector(positions[0], '*');
                return type;
            }


            positions[1] = (DimensionX * DimensionY - DimensionX * (i + 1)) + j + 1;

            if (GetPosToVector(positions[1])=='*'){
                SetPosToVector(positions[1], Side);
            }
            else{
                SetPosToVector(positions[0],'*');

                continue;
            }


            if(CheckWin(positions[1],Side)>=1){
                SetPosToVector(positions[0],'*');
                SetPosToVector(positions[1],'*');
                return type+1;
            }

            SetPosToVector(positions[0],'*');
            SetPosToVector(positions[1],'*');
        }


    }

    return 'a'-1;


}





