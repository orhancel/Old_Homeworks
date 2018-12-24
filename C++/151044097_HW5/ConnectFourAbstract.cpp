//
// Created by ORHAN on 26.11.2017.
//

#include "ConnectFourAbstract.h"

ConnectFourAbstract::ConnectFourAbstract() {
    this->DimensionY=5;
    this->DimensionX=5;

}

ConnectFourAbstract::ConnectFourAbstract(int width,int height) {
    this->DimensionY=height;
    this->DimensionX=width;


}

ConnectFourAbstract::ConnectFourAbstract(int square) {
    this->DimensionY=square;
    this->DimensionX=square;

}

ConnectFourAbstract::ConnectFourAbstract(string filename){

    if(FileArraySize(filename)==0)
    {
        this->DimensionY=5;
        this->DimensionX=5;
    }

    LoadFile(filename);

}




int ConnectFourAbstract::Play(int position){
    if(LivingCells%2==0)
        SetPosToVector(position,'X');
    else
        SetPosToVector(position,'O');



}



int ConnectFourAbstract::playGame(){

    if(isEnded== true){
        cout<<"Game already has ended"<<endl;
        return 0;
    }

    int Dimension;

    int winType=0;
    char type;

    string typeIn;
    int position=0;


    string DimeIn="00";
    decltype(DimeIn) AiPlayer;////////////////DECLTYPE   DECLTYPE   DECLTYPE  DECLTYPE  DECLTYPE  DECLTYPE
    if(isBoardInitialized== false){



            getline(cin,DimeIn);

            DimensionY=atoi(DimeIn.c_str());

            getline(cin,DimeIn);

            DimensionX=atoi(DimeIn.c_str());

            gameBoard = new Cell*[DimensionY];

            for (int i = 0; i < DimensionY; ++i) {
                gameBoard[i]=new Cell[DimensionX];
                for (int j = 0; j <DimensionX ; ++j) {
                    gameBoard[i][j].setType('*');
                    gameBoard[i][j].setCol(j);
                    gameBoard[i][j].setRow(i);
                    gameBoard[i][j].setColumn('A'+j);
                }
            }

            totalCells=DimensionX*DimensionY;



    }



    if (isBoardInitialized== false){

        while(AiOrPlayer!='P' && AiOrPlayer!='C'){
            cout<<"Enter C or P"<<endl;
            cout << "C - Play against AI" << endl;
            cout<<"P - Player vs Player"<<endl;
            cin.clear();
            getline(cin,AiPlayer);

            AiOrPlayer=toupper(AiPlayer[0]);
            if(AiOrPlayer!='P' || AiOrPlayer!='C')
                cerr<<"Wrong command"<<endl;
        }
    }




    PrintBoard();

    isBoardInitialized= true;

    if(AiOrPlayer=='P'){
        do{
            position=PlayHand('X',"User1");
            if(position==-1)
                return 0;
            
            LivingCells++;


            cout<<"Living Cell: "<<LivingCells<<endl;
            if(LivingCells>2)
                if((winType=CheckWin(position,'X'))>=1){
                    printWin(position,'X',winType);
                    PrintBoard();

                    cout<<"User1 has Won"<<endl;
                    setIsEnded(true);
                    return 0;
                }

            if(LivingCells>=totalCells){
                cout<<"DRAW"<<endl;
                setIsEnded(true);
                return 0;
            }

            position=PlayHand('O',"User2");
            if(position==-1)
                return 0;
            
            LivingCells++;

            cout<<"Living Cell: "<<LivingCells<<endl;
            if((winType=CheckWin(position,'O'))>=1){
                printWin(position,'O',winType);
                PrintBoard();
                cout<<"User2 has Won"<<endl;
                setIsEnded(true);
                return 0;
            }


            if(LivingCells>=totalCells){
                cout<<"DRAW"<<endl;
                setIsEnded(true);
                return 0;
            }

        }while (true);
    }


    else{
        do{


            position=PlayHand('X',"User1");
            if(position==-1)
                return 0;


            LivingCells++;

            cout<<"Living Cell: "<<LivingCells<<endl;

            if((winType=CheckWin(position,'X'))>=1){
                printWin(position,'X',winType);
                PrintBoard();
                cout<<"User1 has Won"<<endl;
                setIsEnded(true);
                return 0;
            }

            if(LivingCells>=totalCells){
                cout<<"DRAW"<<endl;
                setIsEnded(true);
                return 0;
            }

            int posMove=0;

            do{
                cout << "Ai move" << endl;

                type=Play();/////////////////////////////////////////////PLAY()///////////////


            }while((position=CheckMove( type)) == -1);

            LivingCells++;

            cout<<"Living Cell: "<<LivingCells<<endl;
            SetPosToVector(position,'O');
            PrintBoard();


            if((winType=CheckWin(position,'O'))>=1){
                printWin(position,'O',winType);
                PrintBoard();
                cout<<"Ai has Won"<<endl;
                setIsEnded(true);
                return 0;
            }


            if(LivingCells>=totalCells){
                cout<<"DRAW"<<endl;
                setIsEnded(true);
                return 0;
            }

            /*cout<<"Wanna switch to next game?Type 'Y'.Any other button to continue."<<endl;
            cin.clear();
            getline(cin,DimeIn);
            if(DimeIn[0]=='Y')
                return 0;
*/

        }while (true);
    }


    return 0;


}





bool ConnectFourAbstract::getIsEnded() const {
    return isEnded;
}

void ConnectFourAbstract::setIsEnded(bool isEnded) {
    ConnectFourAbstract::isEnded = isEnded;
}

int ConnectFourAbstract::getWidth() const {
    return DimensionX;
}

void ConnectFourAbstract::setWidth(int width) {
    ConnectFourAbstract::DimensionX = width;
}

int ConnectFourAbstract::getHeight() const {
    return DimensionY;
}

void ConnectFourAbstract::setHeight(int height) {
    ConnectFourAbstract::DimensionY = height;
}









int ConnectFourAbstract::PlayHand(char HandType,string User){

    string typeIn;
    char type;
    int position=0;

    do{
        do{

            cin.clear();
            cout <<User<< " move or LOAD filename.txt or save(SAVE filename.txt) or type 'exit' to exit  " << endl;



            getline(cin,typeIn);

            if(typeIn[0]==EOF)
                return -1;

            if(typeIn.length()==0)
                return -1;

            if(typeIn[0]=='S'&&typeIn[1]=='A'&&typeIn[2]=='V'&&typeIn[3]=='E'){
                SaveFile(typeIn.substr(5,typeIn.length()));
                continue;
            }
            else if(typeIn[0]=='e'&&typeIn[1]=='x'&&typeIn[2]=='i'&&typeIn[3]=='t'){
                cout<<"Bye"<<endl;
                return -1 ;
            }

            else if(typeIn[0]=='L'&&typeIn[1]=='O'&&typeIn[2]=='A'&&typeIn[3]=='D'){
                LoadFile(typeIn.substr(5,typeIn.length()));
                continue;
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

    }while((position=CheckMove(type)) == -1);

    //SetPosToVector(position,HandType);
    Play(position);/////////////////////////////////////////////////////////PLAY(İNT VARİABLE)////////////////
    PrintBoard();
    return position;

}





int ConnectFourAbstract::CheckMove(char type){

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

    for(int i=0;i<DimensionY;i++){

        if(GetPosToVector(position)=='*')
            return position;
        position-=DimensionX;
    }

    cerr<<"Invalid Move3  "<<type<<endl;
    return -1;


}

void ConnectFourAbstract::printWin(int position,char type,int winType){
    int TempPos;

    switch (winType) {


        case 1:
            TempPos = position;
            /*Dikey kazanma kontrolü*/
            for (int i = 0; i < 3; ++i) {
                TempPos += DimensionX;
                if (GetPosToVector(TempPos) != type)
                    break;
                if (i == 2) {
                    SetPosToVector(TempPos,type + ('a' - 'A')) ;
                    SetPosToVector(TempPos - DimensionX,type + ('a' - 'A')) ;
                    SetPosToVector(TempPos - 2 * DimensionX,type + ('a' - 'A')) ;
                    SetPosToVector(TempPos - 3 * DimensionX,type + ('a' - 'A')) ;


                    return;
                }

            }
            break;

        case 2:
            /*Yatay kazanma kontrolü*/
            TempPos = (position / DimensionX) * DimensionX;
            for (int i = 0; i < DimensionX - 3; ++i) {
                if (GetPosToVector(TempPos)  == type) {
                    for (int j = 0; j < 3; ++j) {
                        if (GetPosToVector(TempPos + j + 1)!= type)
                            break;
                        if (j == 2) {
                            SetPosToVector(TempPos + j + 1,type + ('a' - 'A')) ;
                            SetPosToVector(TempPos + j + 1-1,type + ('a' - 'A')) ;
                            SetPosToVector(TempPos + j + 1-2,type + ('a' - 'A')) ;
                            SetPosToVector(TempPos + j + 1-3,type + ('a' - 'A')) ;

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
                if (GetPosToVector(TempPos) == type) {
                    for (int i = 0; i < 4; ++i) {
                        if (GetPosToVector(TempPos + (DimensionX + 1) * i)!= type)
                            break;
                        if (i == 3) {
                            SetPosToVector(TempPos + (DimensionX + 1) * i ,type + ('a' - 'A')) ;
                            SetPosToVector(TempPos + (DimensionX + 1) * i - DimensionX - 1 ,type + ('a' - 'A')) ;
                            SetPosToVector(TempPos + (DimensionX + 1) * i - 2 * DimensionX - 2,type + ('a' - 'A')) ;
                            SetPosToVector(TempPos + (DimensionX + 1) * i - 3 * DimensionX - 3,type + ('a' - 'A')) ;

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
                if (GetPosToVector(TempPos) == type) {
                    for (int i = 0; i < 4; ++i) {
                        if (GetPosToVector(TempPos + (DimensionX - 1) * i) != type)
                            break;
                        if (i == 3) {
                            SetPosToVector(TempPos,type + ('a' - 'A')) ;
                            
                            SetPosToVector(TempPos + (DimensionX - 1) * 1,type + ('a' - 'A')) ;
                          
                            SetPosToVector(TempPos + (DimensionX - 1) * 2,type + ('a' - 'A')) ;
                           
                            SetPosToVector(TempPos + (DimensionX - 1) * 3,type + ('a' - 'A')) ;
                            
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







int  ConnectFourAbstract::FileArraySize( string DosyaAd) {

    while (true) {

        ifstream file;
        file.open(DosyaAd);
        string line;
        if(!file.is_open()){
            cerr<<"File does not exist"<<endl;/////////////////////////////////////CERR CERR CERR CERR CERR CERR CERR CERR CERR
            return 0;
        }

        DimensionX=0;
        DimensionY = 0;

        while (getline(file, line)) {
            if(DimensionX<line.length())
                DimensionX = line.length();

            /* if (temp != DimensionX) {
                 cout << "Board shape is not proper" << endl;
                 return 0;
             }*/
            DimensionY++;
        }
        file.close();
        break;


    }


    return DimensionX*DimensionY;


}

void ConnectFourAbstract::SaveFile(const string &DosyaAd){
    ofstream file;
    file.open(DosyaAd);


    for(int i=0;i<DimensionX*DimensionY;i++){



        if(i%DimensionX==0 && i!=0 ){
            file<<endl;
            cout<<endl;
            cout<<GetPosToVector(i);
            if(GetPosToVector(i)=='S')
                file<<' ';
            else
                file<<GetPosToVector(i);
        }


        else{
            cout<<GetPosToVector(i);
            if(GetPosToVector(i)=='S')
                file<<' ';
            else
                file<<GetPosToVector(i);

        }


    }
    file.close();

}

int ConnectFourAbstract::LoadFile(string DosyaAd){
    char c;

    totalCells=0;
    LivingCells=0;

    int size=FileArraySize(DosyaAd);//////AUTO AUTO AUTO AUTO  AUTO  AUTO  AUTO  AUTO
    for (int i = 0; i < DimensionY; ++i) {
        delete [] gameBoard[i];
    }

    delete [] gameBoard;
    gameBoard = nullptr;

    gameBoard = new Cell*[DimensionY];

    for (int i = 0; i < DimensionY; ++i) {
        gameBoard[i]=new Cell[DimensionX];
    }


    ifstream file;
    file.open(DosyaAd);
    if(!file.is_open()){
        cerr<<"File does not exist"<<endl;
        return 0;
    }

    int count = 0;
    int lineLenth=0;
    while (file.get(c)) {

        if (c != '*' || c != 'X' || c != 'O' || c != '\n' || c != ' ') {
            if(c=='\n'){

                while (lineLenth<DimensionX){
                    c='S';

                    SetPosToVector(count,c);
                    count++;
                    lineLenth++;
                }
                lineLenth=0;

                continue;
            }

            if(c==' ')
                c='S';
            else{
                totalCells++;
                if(c=='X' || c=='O')
                    LivingCells++;
            }

            lineLenth++;
            SetPosToVector(count,c);
            count++;
        } else {
            cerr << "Unrecognized character.File is not a board" << endl;

            return 0;

        }


    }
    file.close();


    return 1;



}


ConnectFourAbstract::~ConnectFourAbstract()
{
    for (int i = 0; i < DimensionY; ++i) {
        delete [] gameBoard[i];
    }

    delete [] gameBoard;
    gameBoard = nullptr;
}

ConnectFourAbstract::ConnectFourAbstract( const ConnectFourAbstract &other )
{
    DimensionX = other.DimensionX;
    DimensionY=other.DimensionY;
    isEnded=other.isEnded;
    isBoardInitialized=other.isBoardInitialized;
    AiOrPlayer=other.AiOrPlayer;
    LivingCells=other.LivingCells;
    totalCells=other.totalCells;
    player1Pos[0] = other.player1Pos[0];
    player1Pos[1] = other.player1Pos[1];
    for (int i = 0; i < DimensionY; ++i) {
        delete [] gameBoard[i];
    }

    delete [] gameBoard;

    gameBoard = new Cell*[DimensionY];

    for (int i = 0; i < DimensionY; ++i) {
        gameBoard[i]=new Cell[DimensionX];
    }



    for (int i = 0; i < DimensionY; ++i) {

        for (int j = 0; j < DimensionX; ++j) {
            gameBoard[i][j]=other.gameBoard[i][j];
        }
    }

}



