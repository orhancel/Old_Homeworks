#include <iostream>
#include <string.h>
#include <stdlib.h>
#include<fstream>
#include <cstdlib>


using namespace std;


int CheckMove(char Board[],int DimensionX,int DimensionY,char type){
    if( DimensionX<=(type-'a')){
        cerr<<"Invalid Move1"<<endl;
        return -1;
    }


    int position=type-'a';
    if(position>DimensionX){
        cerr<<"Invalid Move2  " <<endl;
        return -1;
    }
    position=position+((DimensionY-1)*DimensionX);
    for(int i=0;i<DimensionX;i++){

        if(Board[position]=='.')
            return position;
        position-=DimensionX;
    }

    cerr<<"Invalid Move3  "<<type<<endl;
    return -1;



}



void printWin(char Board[],int position,int DimensionX,int DimensionY,char type,int winType){
    int TempPos;

    switch (winType) {


        case 1:
            TempPos = position;
            /*Dikey kazanma kontrolü*/
            for (int i = 0; i < 3; ++i) {
                TempPos += DimensionX;
                if (Board[TempPos] != type)
                    break;
                if (i == 2) {
                    Board[TempPos] = type + ('a' - 'A');
                    Board[TempPos - DimensionX] = type + ('a' - 'A');
                    Board[TempPos - 2 * DimensionX] = type + ('a' - 'A');
                    Board[TempPos - 3 * DimensionX] = type + ('a' - 'A');

                    return;
                }

            }
            break;

        case 2:
            /*Yatay kazanma kontrolü*/
            TempPos = (position / DimensionX) * DimensionX;
            for (int i = 0; i < DimensionX - 3; ++i) {
                if (Board[TempPos] == type) {
                    for (int j = 0; j < 3; ++j) {
                        if (Board[TempPos + j + 1] != type)
                            break;
                        if (j == 2) {
                            Board[TempPos + j + 1] = type + ('a' - 'A');
                            Board[TempPos + j + 1 - 1] = type + ('a' - 'A');
                            Board[TempPos + j + 1 - 2] = type + ('a' - 'A');
                            Board[TempPos + j + 1 - 3] = type + ('a' - 'A');

                            return;
                        }

                    }
                }
                TempPos++;

            }
            break;

        case 3:
            TempPos = position;

            while (TempPos > 0) {
                if (TempPos % DimensionX != 0)
                    TempPos -= (DimensionX + 1);
                else
                    break;
            }
            if (TempPos < 0)
                TempPos += (DimensionX + 1);

            /*Soldan sağa çapraz kazanma kontrolü*/
            while (TempPos < (DimensionX * DimensionY)) {
                if (Board[TempPos] == type) {
                    for (int i = 0; i < 4; ++i) {
                        if (Board[TempPos + (DimensionX + 1) * i] != type)
                            break;
                        if (i == 3) {
                            Board[TempPos + (DimensionX + 1) * i] = type + ('a' - 'A');
                            Board[TempPos + (DimensionX + 1) * i - DimensionX - 1] = type + ('a' - 'A');
                            Board[TempPos + (DimensionX + 1) * i - 2 * DimensionX - 2] = type + ('a' - 'A');
                            Board[TempPos + (DimensionX + 1) * i - 3 * DimensionX - 3] = type + ('a' - 'A');
                            return;
                        }

                    }
                    if (TempPos % DimensionX == DimensionX - 1)
                        break;
                }
                TempPos += DimensionX + 1;

            }
            break;

        case 4:
            TempPos = position;
            /*Sağdan sola çapraz kazanma kontrolü*/
            while (TempPos % DimensionX != (DimensionX - 1) && TempPos > 0) {
                TempPos -= (DimensionX - 1);
            }
            if (TempPos < 0)
                TempPos += (DimensionX - 1);
            int x = TempPos;
            while (TempPos < (DimensionX * DimensionY) - 2) {
                if (TempPos % DimensionX == 0)
                    break;
                if (Board[TempPos] == type) {
                    for (int i = 0; i < 4; ++i) {
                        if (Board[TempPos - (DimensionX - 1) * i] != type)
                            break;
                        if (i == 3) {
                            Board[TempPos] = type + ('a' - 'A');
                            Board[TempPos - DimensionX + 1] = type + ('a' - 'A');
                            Board[TempPos - 2 * DimensionX + 2] = type + ('a' - 'A');
                            Board[TempPos - 3 * DimensionX + 3] = type + ('a' - 'A');
                            return;
                        }

                    }

                }
                TempPos += (DimensionX - 1);


            }
            break;

    }
    return;


}

int CheckWin(const char Board[],const int &DimensionX,const int &DimensionY,const int &position,const char &type){


    int TempPos=position;
    /*Dikey kazanma kontrolü*/
    for (int i = 0; i < 3; ++i) {
        TempPos+=DimensionX;
        if(Board[TempPos]!=type)
            break;
        else if(TempPos>=(DimensionX*DimensionY))
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
        if(Board[TempPos]==type){
            for (int j = 0; j <3 ; ++j) {
                if(Board[TempPos+j+1]!=type)
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



    TempPos=position;

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
        if(Board[TempPos]==type){
            for (int i = 0; i < 4; ++i) {
                if(Board[TempPos+(DimensionX+1)*i]!=type)
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
        if(Board[TempPos]==type){
            for (int i = 0; i < 4; ++i) {
                if(Board[TempPos-(DimensionX-1)*i]!=type)
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

void PrintBoard(char Board[],const int &DimensionX,const int &DimensionY){
    char type='a';
    for (int i = 0; i < DimensionX; ++i) {

        cout<<type<<" ";
        type++;
    }
    cout<<endl;

    for (int i = 0; i < DimensionX*DimensionY; ++i) {


        if(i%DimensionX==0 && i!=0)
            cout<<endl;
        cout<<Board[i]<<" ";
    }
    cout<<endl;

}







/*Ai için kontrol fonksiyonu*/
/*2 el sonrasını kontrol eder*/
char DikeyKazanma(char Board[],const int &DimensionX,const int &DimensionY,const char &Side){

    int position=0;
    int positions[2];

    for(int i=0;i<DimensionX;i++){
        char type='a'+i;


        positions[0]=CheckMove(Board, DimensionX,DimensionY, type);
        if(positions[0]!=-1)
            Board[positions[0]]=Side;
        else{
            Board[positions[0]]='.';
            break;

        }


        if(CheckWin(Board,DimensionX,DimensionY,positions[0],Side)>=1){
            Board[positions[0]]='.';
            return type;
        }

        positions[1]=CheckMove(Board, DimensionX,DimensionY, type);

        if(positions[0]!=-1)
            Board[positions[1]]=Side;
        else{
            Board[positions[0]]='.';
            Board[positions[1]]='.';
            continue;

        }

        if(CheckWin(Board,DimensionX,DimensionY,positions[1],Side)>=1){
            Board[positions[0]]='.';
            Board[positions[1]]='.';
            return type;

        }


        Board[positions[0]]='.';
        Board[positions[1]]='.';


    }



    return 'a'-1;
}
/*Ai için kontrol fonksiyonu*/
/*2 el sonrasını kontrol eder*/
/*Çaprazlar ve yatay için*/
char YatayKazanma(char Board[],const int &DimensionX,const int &DimensionY,const char &Side){

    int position;
    int positions[2];

    for(int i=0;i<DimensionX;i++){


        for (int j = 0; j < DimensionX-1; ++j) {

            char type='a'+j;

            positions[0]=(DimensionX*DimensionY-DimensionX*(i+1))+j;

            if(Board[positions[0]]=='.')
                Board[positions[0]]=Side;

            else{

                continue;
            }


            if(CheckWin(Board,DimensionX,DimensionY,positions[0],Side)>=1){
                Board[positions[0]]='.';
                return type;
            }


            positions[1]=(DimensionX*DimensionY-DimensionX*(i+1))+j+1;

            if(Board[positions[1]]=='.')
                Board[positions[1]]=Side;

            else{
                Board[positions[0]]='.';

                continue;
            }


            if(CheckWin(Board,DimensionX,DimensionY,positions[1],Side)>=1){
                Board[positions[0]]='.';
                Board[positions[1]]='.';
                return type+1;
            }

            Board[positions[0]]='.';
            Board[positions[1]]='.';
        }


    }

    return 'a'-1;


}



char EnemyAI(char Board[],const int &DimensionX,const int &DimensionY,char playerPos[2]){
    int position=0;
    int positions[3];
    char type;
    /*Tek hareketle kazanma kontrolü*/
    for(int i=0;i<DimensionX;i++){
        char type='a'+i;
        position=CheckMove(Board, DimensionX,DimensionY, type);
        Board[position]='O';
        if(position!=-1){
            if(CheckWin(Board,DimensionX,DimensionY,position,'O')>=1){
                Board[position]='.';

                return type;
            }
        }
        Board[position]='.';

    }

    /*Rakibin kazanmasını bloklama*/
    for(int i=0;i<DimensionX;i++){
        char type='a'+i;
        position=CheckMove(Board, DimensionX,DimensionY, type);
        Board[position]='X';
        if(position!=-1){
            if(CheckWin(Board,DimensionX,DimensionY,position,'X')>=1){
                Board[position]='.';
                return type;
            }
        }
        Board[position]='.';

    }


    /* Rakip Dikey kazanma kontrol*/
    type=DikeyKazanma(Board,DimensionX,DimensionY,'X');
    if(type!='a'-1)
        return type;

    /*Rakip Yatay ve çapraz kazanma kontrolü*/
    type=YatayKazanma(Board,DimensionX,DimensionY,'X');

    if(type!='a'-1)
        return type;


    /*Dikey kazanma kontrol*/

    type=DikeyKazanma(Board,DimensionX,DimensionY,'O');
    if(type!='a'-1){

        return type;
    }



    /*Yatay ve çapraz kazanma kontrolü*/
    type=YatayKazanma(Board,DimensionX,DimensionY,'O');
    if(type!='a'-1){

        return type;
    }





        if(playerPos[1]-playerPos[0]<0)
            type=playerPos[1]+rand()%DimensionX;
        else if(playerPos[1]-playerPos[0]>0)
            type=playerPos[1]-rand()%DimensionX;
        else
            type=playerPos[1];

        position=CheckMove(Board, DimensionX,DimensionY, type);
        if(position!=-1)
            return type;
    for (int i = 0; i < DimensionX; ++i) {
        type=playerPos[1]+i;
        if(type>='a'+DimensionX)
            type=type-DimensionX;
        position=CheckMove(Board, DimensionX,DimensionY, type);
        if(position!=-1)
            return type;
    }


    return 'a'-1;

}


int  FileArraySize( string DosyaAd, int& width, int& lenght) {

    while (true) {

            ifstream file;
            file.open(DosyaAd);
            string line;
            if(!file.is_open()){
                cerr<<"File does not exist"<<endl;/////////////////////////////////////CERR CERR CERR CERR CERR CERR CERR CERR CERR
                return 0;
            }

            getline(file, line);
            width = line.length();
            lenght = 1;

            while (getline(file, line)) {
                int temp = line.length();

                if (temp != width) {
                    cout << "Board shape is not proper" << endl;
                    return 0;
                }
                lenght++;
            }
            file.close();
            break;


    }


    return width*lenght;


}

void LoadFile(char Board[],string DosyaAd){
    char c;


    ifstream file;
    file.open(DosyaAd);
    if(!file.is_open()){
        cerr<<"File does not exist"<<endl;
        return ;
    }

    int count = 0;
    while (file.get(c)) {

        if (c != '.' || c != 'X' || c != 'O' || c != '\n') {
            if(c=='\n')
                continue;
            Board[count] = c;
            count++;
        } else {
            cerr << "Unrecognized character.File is not a board" << endl;

            return;

        }


    }
    file.close();



}

void SaveFile(const string &DosyaAd,const char Board[],const int &DimensionX,const int &DimensionY){
    ofstream file;
    file.open(DosyaAd);


    for(int i=0;i<DimensionX*DimensionY;i++){



        if(i%DimensionX==0 && i!=0 ){
            file<<endl;
            cout<<endl;
            cout<<Board[i];
            file<<Board[i];
        }


        else{
            cout<<Board[i];
            file<<Board[i];
        }


    }
    file.close();

}


int PlayHand(char Board[],int DimensionX,int DimensionY,char HandType,char player1Pos[2],string User){

    string typeIn;
    char type;
    int position=0;

    do{
        do{

            cin.clear();
            cout <<User<< " move or save(Save filename.txt) or type 'exit' to exit  " << endl;



            getline(cin,typeIn);

            if(typeIn[0]=='S'&&typeIn[1]=='a'&&typeIn[2]=='v'&&typeIn[3]=='e'){
                SaveFile(typeIn.substr(5,typeIn.length()),Board,DimensionX,DimensionY);
                continue;
            }
            else if(typeIn[0]=='e'&&typeIn[1]=='x'&&typeIn[2]=='i'&&typeIn[3]=='t'){
                cout<<"Bye"<<endl;
                return -1 ;
            }
            type=typeIn[0];
            if(type<='Z' && type>='A'){
                type=type+('a'-'A');

                player1Pos[0]=player1Pos[1];
                player1Pos[1]=type;
                break;
            }
            else if(type>='a' && type<='z')
                break;

            else{
                cerr<<"invalid input"  <<endl;
                continue;
            }
            break;
        }while(true);

    }while((position=CheckMove(Board, DimensionX,DimensionY, type)) == -1);

    Board[position]=HandType;
    PrintBoard(Board,DimensionX,DimensionY);
    return position;

}

int main() {
    int Dimension;
    int AiOrPlayer=0;/*1 ai  2 player*/
    int winType=0;
    char type;
    char player1Pos[2]={'a','a'};
    string typeIn;
    int position=0;
    int count=0;

    string DimeIn="00";
    decltype(DimeIn) AiPlayer;////////////////DECLTYPE   DECLTYPE   DECLTYPE  DECLTYPE  DECLTYPE  DECLTYPE
    int DimensionX;
    char *Board;
    int DimensionY;
    do{
        cout << "Enter dimension  (Example: 2 or 4 or 6,8,12,14,16,18,20) Only single one of them" << endl;
        cout << "or load a file (Example : Load filename.txt)" << endl;
        getline(cin,DimeIn);

        if(DimeIn[0]=='L'&&DimeIn[1]=='o'&&DimeIn[2]=='a'&&DimeIn[3]=='d'){

            auto size=FileArraySize(DimeIn.substr(5,DimeIn.length()),DimensionX,DimensionY);//////AUTO AUTO AUTO AUTO  AUTO  AUTO  AUTO  AUTO
            if(size==0)
                continue;
            Board=new char[size];
            LoadFile(Board,DimeIn.substr(5,DimeIn.length()));
            break;
        }
        else{
            Dimension= atoi(DimeIn.c_str())  ;
            if(Dimension%2==0 && Dimension<20 && Dimension!=0){
                DimensionX=Dimension;
                DimensionY=Dimension;
                Board=new char[DimensionX*DimensionY];
                for(int i=0;i<DimensionX*DimensionY;i++)
                    Board[i]='.';
                break;
            }


        }
        cerr<<"invalid command"<<endl;


    }while(true);


    while(AiOrPlayer!=1 && AiOrPlayer!=2){
        cout<<"Enter 1 or 2"<<endl;
        cout << "1-Play against AI" << endl;
        cout<<"2-Player vs Player"<<endl;
        cin.clear();
        getline(cin,AiPlayer);

        AiOrPlayer=atoi(AiPlayer.c_str());
        if(AiOrPlayer>2 || AiOrPlayer<1)
            cerr<<"Wrong command"<<endl;
    }

    int ifExit=0;
    PrintBoard(Board,DimensionX,DimensionY);

    if(AiOrPlayer==2){
        do{
            position=PlayHand(Board,DimensionX,DimensionY,'X',player1Pos,"User1");
            count++;
            if(position==-1)
                return 0;

            if(count>2)
                if((winType=CheckWin(Board,DimensionX,DimensionY,position,'X'))>=1){
                    printWin(Board,position,DimensionX,DimensionY,'X',winType);
                    PrintBoard(Board,DimensionX,DimensionY);

                    cout<<"User1 has Won"<<endl;
                    return 0;
                }


            position=PlayHand(Board,DimensionX,DimensionY,'O',player1Pos,"User2");

            if(ifExit==-1)
                return 0;
            count++;


                if((winType=CheckWin(Board,DimensionX,DimensionY,position,'O'))>=1){
                    printWin(Board,position,DimensionX,DimensionY,'O',winType);
                    PrintBoard(Board,DimensionX,DimensionY);
                    cout<<"User2 has Won"<<endl;
                    return 0;
                }


            if(count>=(DimensionX*DimensionY)){
                cout<<"DRAW"<<endl;
                return 0;
            }

           }while (true);
    }


    else{
        do{


            position=PlayHand(Board,DimensionX,DimensionY,'X',player1Pos,"User1");
            if(ifExit==-1)
                return 0;
            count++;



                if((winType=CheckWin(Board,DimensionX,DimensionY,position,'X'))>=1){
                    printWin(Board,position,DimensionX,DimensionY,'X',winType);
                    PrintBoard(Board,DimensionX,DimensionY);
                    cout<<"User1 has Won"<<endl;
                    return 0;
                }


            int posMove=0;

            do{
                cout << "Ai move" << endl;

                type=EnemyAI(Board,DimensionX,DimensionY,player1Pos);


            }while((position=CheckMove(Board, DimensionX,DimensionY, type)) == -1);

            count++;

            Board[position]='O';
            PrintBoard(Board,DimensionX,DimensionY);


            if((winType=CheckWin(Board,DimensionX,DimensionY,position,'O'))>=1){
                printWin(Board,position,DimensionX,DimensionY,'O',winType);
                PrintBoard(Board,DimensionX,DimensionY);
                cout<<"Ai has Won"<<endl;
                return 0;
            }


            if(count>=(DimensionX*DimensionY)){
                cout<<"DRAW"<<endl;
                return 0;
            }

        }while (true);
    }






}