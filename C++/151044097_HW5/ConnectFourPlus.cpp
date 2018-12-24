//
// Created by ORHAN on 26.11.2017.
//
#include "ConnectFourPlus.h"


int ConnectFourPlus::CheckWin(const int &position,const char &type){


    int TempPos=position;
    /*Dikey kazanma kontrolü*/
    for (int i = 0; i < 3; ++i) {
        TempPos+=DimensionX;

        if (TempPos>=(DimensionX*DimensionY))
            break;
        else if( GetPosToVector(TempPos)!=type)
            break;
        if (i==2){
            /*Board[TempPos]=type+('a'-'A');
            Board[TempPos-Dimension]=type+('a'-'A');
            Board[TempPos-2*Dimension]=type+('a'-'A');
            Board[TempPos-3*Dimension]=type+('a'-'A');*/

            return 1;
        }

    }


    /*Yatay kazanma kontrolü*/
    TempPos=(position/DimensionX)*DimensionX;
    for (int i = 0; i < DimensionX-3; ++i) {
        if( TempPos<DimensionX*DimensionY  &&GetPosToVector(TempPos)==type){
            for (int j = 0; j <3 ; ++j) {

                if(TempPos+j+1>=DimensionX*DimensionY )
                    break;
                else if(GetPosToVector(TempPos+j+1)!=type)
                    break;
                if(j==2){
                    /* Board[TempPos+j+1]=type+('a'-'A');
                     Board[TempPos+j+1-1]=type+('a'-'A');
                     Board[TempPos+j+1-2]=type+('a'-'A');
                     Board[TempPos+j+1-3]=type+('a'-'A');*/

                    return 2;
                }

            }
        }
        TempPos++;

    }


    return -1;



}


char ConnectFourPlus::DikeyKazanma(const char &Side){

    int position=0;
    int positions[2];

    for(int i=0;i<DimensionX;i++){
        char type='a'+i;


        positions[0]=CheckMove(type);
        if(positions[0]!=-1)


            SetPosToVector(positions[0],Side);
        else{
            SetPosToVector(positions[0],'*');
            break;

        }


        if(CheckWin(positions[0],Side)>=1){
            SetPosToVector(positions[0],'*');
            return type;
        }

        positions[1]=CheckMove( type);

        if(positions[0]!=-1)
            SetPosToVector(positions[1],Side);
        else{
            SetPosToVector(positions[0],'*');
            SetPosToVector(positions[1],'*');
            continue;

        }

        if(CheckWin(positions[1],Side)>=1){
            SetPosToVector(positions[0],'*');
            SetPosToVector(positions[1],'*');
            return type;

        }


        SetPosToVector(positions[0],'*');
        SetPosToVector(positions[1],'*');


    }



    return 'a'-1;
}

char ConnectFourPlus::YatayKazanma(const char &Side){

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

char ConnectFourPlus::Play(){/////////////New EnemyAi function
    int position=0;
    int positions[3];
    char type;
    /*Tek hareketle kazanma kontrolü*/
    for(int i=0;i<DimensionX;i++){
        char type='a'+i;
        position=CheckMove(type);
        SetPosToVector(position,'O');
        if(position!=-1){
            if(CheckWin(position,'O')>=1){
                SetPosToVector(position,'*');

                return type;
            }
        }
        SetPosToVector(position,'*');

    }

    /*Rakibin kazanmasını bloklama*/
    for(int i=0;i<DimensionX;i++){
        char type='a'+i;
        position=CheckMove( type);
        SetPosToVector(position,'X');
        if(position!=-1){
            if(CheckWin(position,'X')>=1){
                SetPosToVector(position,'*');
                return type;
            }
        }
        SetPosToVector(position,'*');

    }


    /* Rakip Dikey kazanma kontrol*/
    type=DikeyKazanma('X');
    if(type!='a'-1)
        return type;

    /*Rakip Yatay ve çapraz kazanma kontrolü*/
    type=YatayKazanma('X');

    if(type!='a'-1)
        return type;


    /*Dikey kazanma kontrol*/

    type=DikeyKazanma('O');
    if(type!='a'-1){

        return type;
    }



    /*Yatay  kazanma kontrolü*/
    type=YatayKazanma('O');
    if(type!='a'-1){

        return type;
    }





    if(player1Pos[1]-player1Pos[0]<0)
        type=player1Pos[1]+rand()%DimensionX;
    else if(player1Pos[1]-player1Pos[0]>0)
        type=player1Pos[1]-rand()%DimensionX;
    else
        type=player1Pos[1];

    position=CheckMove(type);
    if(position!=-1)
        return type;
    for (int i = 0; i < DimensionX; ++i) {
        type=player1Pos[1]+i;
        if(type>='a'+DimensionX)
            type=type-DimensionX;
        position=CheckMove( type);
        if(position!=-1)
            return type;
    }


    return 'a'-1;
}

