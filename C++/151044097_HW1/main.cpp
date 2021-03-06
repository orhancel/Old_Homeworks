#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

/*Hareket etmek istenilen harf ,tahtanın boyutunu aşıyor mu diye kontrol edilir*/
int CheckMove(char Board[],int Dimension,char type){
    if( Dimension<=(type-'a')){
        cout<<"Invalid Move"<<endl;
        return -1;
    }


    int position=type-'a';
    if(position>Dimension){
        cout<<"Invalid Move  " <<endl;
        return -1;
    }
    position=position+((Dimension-1)*Dimension);
    for(int i=0;i<Dimension;i++){

        if(Board[position]=='.')
            return position;
        position-=Dimension;
    }

    cout<<"Invalid Move  "<<endl;
    return -1;



}


/*Kazandıktan sonra kazanan taş türünü küçük harf yapar*/
void printWin(char Board[],int position,int Dimension,char type,int winType){
    int TempPos;

    switch (winType) {


        case 1:
            TempPos = position;
            /*Dikey kazanma kontrolü*/
            for (int i = 0; i < 3; ++i) {
                TempPos += Dimension;
                if (Board[TempPos] != type)
                    break;
                if (i == 2) {
                    Board[TempPos] = type + ('a' - 'A');
                    Board[TempPos - Dimension] = type + ('a' - 'A');
                    Board[TempPos - 2 * Dimension] = type + ('a' - 'A');
                    Board[TempPos - 3 * Dimension] = type + ('a' - 'A');

                    return;
                }

            }

        case 2:
            /*Yatay kazanma kontrolü*/
            TempPos = (position / Dimension) * Dimension;
            for (int i = 0; i < Dimension - 3; ++i) {
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

        case 3:
            TempPos = position;

            while (TempPos > 0) {
                if (TempPos % Dimension != 0)
                    TempPos -= (Dimension + 1);
                else
                    break;
            }
            if (TempPos < 0)
                TempPos += (Dimension + 1);

            /*Soldan sağa çapraz kazanma kontrolü*/
            while (TempPos < (Dimension * Dimension)) {
                if (Board[TempPos] == type) {
                    for (int i = 0; i < 4; ++i) {
                        if (Board[TempPos + (Dimension + 1) * i] != type)
                            break;
                        if (i == 3) {
                            Board[TempPos + (Dimension + 1) * i] = type + ('a' - 'A');
                            Board[TempPos + (Dimension + 1) * i - Dimension - 1] = type + ('a' - 'A');
                            Board[TempPos + (Dimension + 1) * i - 2 * Dimension - 2] = type + ('a' - 'A');
                            Board[TempPos + (Dimension + 1) * i - 3 * Dimension - 3] = type + ('a' - 'A');
                            return;
                        }

                    }
                    if (TempPos % Dimension == Dimension - 1)
                        break;
                }
                TempPos += Dimension + 1;

            }

        case 4:
            TempPos = position;
            /*Sağdan sola çapraz kazanma kontrolü*/
            while (TempPos % Dimension != (Dimension - 1) && TempPos > 0) {
                TempPos -= (Dimension - 1);
            }
            if (TempPos < 0)
                TempPos += (Dimension - 1);
            int x = TempPos;
            while (TempPos < (Dimension * Dimension) - 2) {
                if (Board[TempPos] == type) {
                    for (int i = 0; i < 4; ++i) {
                        if (Board[TempPos - (Dimension - 1) * i] != type)
                            break;
                        if (i == 3) {
                            Board[TempPos] = type + ('a' - 'A');
                            Board[TempPos - Dimension + 1] = type + ('a' - 'A');
                            Board[TempPos - 2 * Dimension + 2] = type + ('a' - 'A');
                            Board[TempPos - 3 * Dimension + 3] = type + ('a' - 'A');
                            return;
                        }

                    }
                    if (TempPos % Dimension == 0)
                        break;
                }
                TempPos += (Dimension - 1);


            }


    }
    return;


}
/*Return degeri kazanma türünü belirler*/

			/*Oyun tahtası,   Boyut     ,son pozisyon, taş türü X yada O */
int CheckWin(char Board[],int Dimension,int position,char type){


    int TempPos=position;
    /*Dikey kazanma kontrolü*/
    for (int i = 0; i < 3; ++i) {
        TempPos+=Dimension;
        if(Board[TempPos]!=type)
            break;
        if (i==2){
            

            return 1;
        }

    }


    /*Yatay kazanma kontrolü*/
    TempPos=(position/Dimension)*Dimension;
    for (int i = 0; i < Dimension-3; ++i) {
        if(Board[TempPos]==type){
            for (int j = 0; j <3 ; ++j) {
                if(Board[TempPos+j+1]!=type)
                    break;
                if(j==2){
                   

                    return 2;
                }

            }
        }
        TempPos++;

    }



    TempPos=position;

    while( TempPos>0){
        if(TempPos%Dimension!=0 )
            TempPos-=(Dimension+1);
        else
            break;
    }
    if(TempPos<0)
        TempPos+=(Dimension+1);

    /*Soldan sağa çapraz kazanma kontrolü*/
    while (TempPos<(Dimension*Dimension)){
        if(Board[TempPos]==type){
            for (int i = 0; i < 4; ++i) {
                if(Board[TempPos+(Dimension+1)*i]!=type)
                    break;
                if(i==3){
                 
                    return 3;
                }

            }
            if(TempPos%Dimension==Dimension-1)
                break;
        }
        TempPos+=Dimension+1;

    }

    TempPos=position;
    /*Sağdan sola çapraz kazanma kontrolü*/
    while(TempPos%Dimension!=(Dimension-1) && TempPos>0 ){
        TempPos-=(Dimension-1);
    }
    if(TempPos<0)
        TempPos+=(Dimension-1);
    int x=TempPos;
    while (TempPos<(Dimension*Dimension)-2){
        if(Board[TempPos]==type){
            for (int i = 0; i < 4; ++i) {
                if(Board[TempPos-(Dimension-1)*i]!=type)
                    break;
                if(i==3){
                 
                    return 4;
                }

            }
            if(TempPos%Dimension==0)
                break;
        }
        TempPos+=(Dimension-1);


    }
    return -1;



}

void PrintBoard(char Board[],int Dimension){
    char type='a';
    for (int i = 0; i < Dimension; ++i) {

        cout<<type<<" ";
        type++;
    }
    cout<<endl;

    for (int i = 0; i < Dimension*Dimension; ++i) {


        if(i%Dimension==0 && i!=0)
            cout<<endl;
        cout<<Board[i]<<" ";
    }
    cout<<endl;

}







/*Ai için kontrol fonksiyonu*/
/*2 el sonrasını kontrol eder*/
char DikeyKazanma(char Board[],int Dimension,char Side){

    int position=0;
    int positions[2];

    for(int i=0;i<Dimension;i++){
        char type='a'+i;


        positions[0]=CheckMove(Board, Dimension, type);
        if(positions[0]!=-1)
            Board[positions[0]]=Side;
        else{
            Board[positions[0]]='.';
            break;

        }


        if(CheckWin(Board,Dimension,positions[0],Side)>=1){
            Board[positions[0]]='.';
            return type;
        }

        positions[1]=CheckMove(Board, Dimension, type);

        if(positions[0]!=-1)
            Board[positions[1]]=Side;
        else{
            Board[positions[0]]='.';
            Board[positions[1]]='.';
            continue;

        }

        if(CheckWin(Board,Dimension,positions[1],Side)>=1){
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
char YatayKazanma(char Board[],int Dimension,char Side){

    int position;
    int positions[2];

    for(int i=0;i<Dimension;i++){


        for (int j = 0; j < Dimension-1; ++j) {

            char type='a'+j;

            positions[0]=(Dimension*Dimension-Dimension*(i+1))+j;

            if(Board[positions[0]]=='.')
                Board[positions[0]]=Side;

            else{

                continue;
            }


            if(CheckWin(Board,Dimension,positions[0],Side)>=1){
                Board[positions[0]]='.';
                return type;
            }


            positions[1]=(Dimension*Dimension-Dimension*(i+1))+j+1;

            if(Board[positions[1]]=='.')
                Board[positions[1]]=Side;

            else{
                Board[positions[0]]='.';

                continue;
            }


            if(CheckWin(Board,Dimension,positions[1],Side)>=1){
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


/*Ai Fonksiyonu.1 hareket sonra kendi kazanmasına ,2 hareket sonrasında 
rakibin kazanmasını kontrol eder*/
char EnemyAI(char Board[],int Dimension,char playerPos[2]){
    int position=0;
    int positions[3];
    char type;
    /*Tek hareketle kazanma kontrolü*/
    for(int i=0;i<Dimension;i++){
        char type='a'+i;
        position=CheckMove(Board, Dimension, type);
        Board[position]='O';
        if(position!=-1){
            if(CheckWin(Board,Dimension,position,'O')>=1){
                Board[position]='.';

                return type;
            }
        }
        Board[position]='.';

    }

    /*Rakibin kazanmasını bloklama*/
    for(int i=0;i<Dimension;i++){
        char type='a'+i;
        position=CheckMove(Board, Dimension, type);
        Board[position]='X';
        if(position!=-1){
            if(CheckWin(Board,Dimension,position,'X')>=1){
                Board[position]='.';
                return type;
            }
        }
        Board[position]='.';

    }


    /* Rakip Dikey kazanma kontrol*/
    type=DikeyKazanma(Board,Dimension,'X');
    if(type!='a'-1)
        return type;

    /*Rakip Yatay ve çapraz kazanma kontrolü*/
    type=YatayKazanma(Board,Dimension,'X');

    if(type!='a'-1)
        return type;


    /*Dikey kazanma kontrol*/

    type=DikeyKazanma(Board,Dimension,'O');
    if(type!='a'-1){

        return type;
    }



    /*Yatay ve çapraz kazanma kontrolü*/
    type=YatayKazanma(Board,Dimension,'O');
    if(type!='a'-1){

        return type;
    }


    while(true) {


        if(playerPos[1]-playerPos[0]<0)
            type=playerPos[1]+rand()%(playerPos[1]-playerPos[0]);
        else if(playerPos[1]-playerPos[0]>0)
            type=playerPos[1]-rand()%(playerPos[1]-playerPos[0]);
        else
            type=playerPos[1];

        position=CheckMove(Board, Dimension, type);
        if(position!=-1)
            return type;

        
        if(type>Dimension)
            type='a'+(type-Dimension);

    }


    return 'a'-1;

}

int main() {
    int Dimension;
    int AiOrPlayer=0;/*1 ai  2 player*/
    int winType=0;/*Kazanma çeşidi,Dikey,Yatay,Çapraz*/
    char type;
    string typeIn;/*cin<< ile alınan değeri konrol için.Fazla girilse bile ilk değer kabul edilir.*/
    int position=0;
    int count=0;
    char player1Pos[2]={'a','a'};/*Kullanıcının son 2 hamlesi kaydedilir.Ai için*/
    string DimeIn="00";/*cin<< ile alınan değeri konrol için.Fazla girilse bile ilk değer kabul edilir.*/
    string AiPlayer;

    do{
        cout << "Enter dimension  (Example: 2 or 4 or 6,8,12,14,16,18,20) Only single one of them" << endl;
        cin>>DimeIn;
        Dimension= atoi(DimeIn.c_str())  ;

    }while(Dimension==0 || Dimension%2!=0 || Dimension>20);


    while(AiOrPlayer!=1 && AiOrPlayer!=2){
        cout << "1-Play against AI" << endl;
        cout<<"2-Player vs Player"<<endl;
        cin>>AiPlayer;
        AiOrPlayer=atoi(AiPlayer.c_str());
        if(AiOrPlayer>2 || AiOrPlayer<1)
            cout<<"Wrong command"<<endl;
    }


    char Board[Dimension*Dimension];
    for(int i=0;i<Dimension*Dimension;i++)
        Board[i]='.';

    PrintBoard(Board,Dimension);
	/*Player Vs Player*/
    if(AiOrPlayer==2){
        do{
            do{
                do{
                    cout << "User1 move" << endl;
                    cin>>typeIn;
                    type=typeIn[0];
					/*Küçük ,Büyük harf konrolü ve değişimi*/
                    if(type<'a' && type>'A'){
                        type=type+('a'-'A');

                        
                        break;
                    }
					/*Harf küçük harf ise */
                    else if(type>='a' && type<='z')
                        break;

                    else{
                        cout<<"invalid input"<<endl;
                        continue;
                    }
                    break;
                }while(true);

            }while((position=CheckMove(Board, Dimension, type)) == -1);


            Board[position]='X';
            PrintBoard(Board,Dimension);
		
            if(count>2)
                if(winType=CheckWin(Board,Dimension,position,'X')>=1){
                    printWin(Board,position,Dimension,'X',winType);
                    PrintBoard(Board,Dimension);
                    cout<<"User1 has Won"<<endl;
                    return 0;
                }



            do{
                do{
                    cout << "User2 move" << endl;
                    cin>>typeIn;
                    type=typeIn[0];
                    if(type<'a' && type>'A'){
                        type=type+('a'-'A');

                        
                        break;
                    }
                    else if(type>='a' && type<='z')
                        break;

                    else{
                        cout<<"invalid input"<<endl;
                        continue;
                    }
                    break;
                }while(true);
            }while((position=CheckMove(Board, Dimension, type)) == -1);


            Board[position]='O';
            PrintBoard(Board,Dimension);

            if(count>2)
                if(winType=CheckWin(Board,Dimension,position,'O')>=1){
                    printWin(Board,position,Dimension,'O',winType);
                    PrintBoard(Board,Dimension);
                    cout<<"User2 has Won"<<endl;
                    return 0;
                }


            if(count>=(Dimension*Dimension)){
                cout<<"DRAW"<<endl;
                return 0;
            }
            count++;
           }while (true);
    }


    else{


		/*Player vs Ai*/
        do{
            do{

                do{
                    cout << "User1 move" << endl;
                    cin>>typeIn;
                    type=typeIn[0];
                    if(type<'a' && type>'A'){
                        type=type+('a'-'A');

                        player1Pos[0]=player1Pos[1];
                        player1Pos[1]=type;
                        break;
                    }
                    else if(type>='a' && type<='z'){
                        player1Pos[0]=player1Pos[1];
                        player1Pos[1]=type;
                        break;

                    }
                    else{
                        cout<<"invalid input"<<endl;
                        continue;
                    }
                    break;
                }while(true);



            }while((position=CheckMove(Board, Dimension, type)) == -1);


            Board[position]='X';
            PrintBoard(Board,Dimension);
            if(count>2)
                if(winType=CheckWin(Board,Dimension,position,'X')>=1){
                    printWin(Board,position,Dimension,'X',winType);
                    PrintBoard(Board,Dimension);
                    cout<<"User1 has Won"<<endl;
                    return 0;
                }


            int posMove=0;
            do{
                cout << "Ai move" << endl;

                type=EnemyAI(Board,Dimension,player1Pos);


            }while((position=CheckMove(Board, Dimension, type)) == -1);
            count++;

            Board[position]='O';
            PrintBoard(Board,Dimension);

            if(count>2)
                if(winType=CheckWin(Board,Dimension,position,'O')>=1){
                    printWin(Board,position,Dimension,'O',winType);
                    PrintBoard(Board,Dimension);
                    cout<<"Ai has Won"<<endl;
                    return 0;
                }


            if(count>=(Dimension*Dimension)){
                cout<<"DRAW"<<endl;
                return 0;
            }
            count++;
        }while (true);
    }






}
