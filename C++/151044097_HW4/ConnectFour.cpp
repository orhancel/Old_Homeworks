//
// Created by ORHAN on 15.10.2017.
//

#include "ConnectFour.h"




        ConnectFour::ConnectFour() {
            this->DimensionY=5;
            this->DimensionX=5;

        }

        ConnectFour::ConnectFour(int width,int height) {
            this->DimensionY=height;
            this->DimensionX=width;


        }

        ConnectFour::ConnectFour(int square) {
            this->DimensionY=square;
            this->DimensionX=square;

        }

        ConnectFour::ConnectFour(string filename){

            if(FileArraySize(filename)==0)
            {
                this->DimensionY=5;
                this->DimensionX=5;
            }

            LoadFile(filename);

        }

        int ConnectFour::LivingGames=0;

        bool ConnectFour::Compare(ConnectFour other){


            if(other.CompareWinCounts()>this->CompareWinCounts())
                return false;
            else
                return true;


        }

        int ConnectFour::CompareWinCounts(){

            int winCount=0;

            int position=0;
            int positions[2];


            char Side='X';

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
                     winCount++;
                    continue;
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
                     winCount++;
                    continue;

                }


                SetPosToVector(positions[0],'*');
                SetPosToVector(positions[1],'*');


            }


            for(int i=0;i<DimensionX;i++){


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
                         winCount++;
                        continue;
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
                         winCount++;
                        continue;
                    }

                    SetPosToVector(positions[0],'*');
                    SetPosToVector(positions[1],'*');
                }


            }



            return winCount;



        }

        int ConnectFour::Play(int position){
            if(turnCount%2==0)
                SetPosToVector(position,'X');
            else
                SetPosToVector(position,'O');



        }

        char ConnectFour::Play(){/////////////New EnemyAi function
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



        /*Yatay ve çapraz kazanma kontrolü*/
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

        int ConnectFour::playGame(){

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

                do{
                    cout << "Enter file" << endl;

                    getline(cin,DimeIn);



                    auto size=FileArraySize(DimeIn);//////AUTO AUTO AUTO AUTO  AUTO  AUTO  AUTO  AUTO
                    if(size==0)
                        continue;

                    gameBoard = new Cell*[DimensionY];

                    for (int i = 0; i < DimensionY; ++i) {
                        gameBoard[i]=new Cell[DimensionX];
                    }

                    if(LoadFile(DimeIn)==1)
                        break;




                }while(true);

                setLivingGames(getLivingGames()+DimensionX*DimensionY);
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
            if(MultiGame==true && multiGameBegin==false){
            	multiGameBegin=true;
            	return 0;
            }

            if(AiOrPlayer=='P'){
                do{
                    position=PlayHand('X',"User1");

                    if(position==-1){
                    	cout<<"exit"<<endl;
                    	exit(0);
                    }

                    turnCount++;
                    setLivingGames(getLivingGames()-1);

                    cout<<"Living Cell: "<<turnCount<<endl;
                    if(turnCount>2)
                        if((winType=CheckWin(position,'X'))>=1){
                            printWin(position,'X',winType);
                            PrintBoard();

                            cout<<"User1 has Won"<<endl;
                            setIsEnded(true);
                            return 0;
                        }

                    if(turnCount>=emptyCells){
                        cout<<"DRAW"<<endl;
                        setIsEnded(true);
                        return 0;
                    }

                    position=PlayHand('O',"User2");
                    if(position==-1){
                    	cout<<"exit"<<endl;
                    	exit(0);
                    }

                    turnCount++;
                    setLivingGames(getLivingGames()-1);
                    cout<<"Living Cell: "<<turnCount<<endl;
                    if((winType=CheckWin(position,'O'))>=1){
                        printWin(position,'O',winType);
                        PrintBoard();
                        cout<<"User2 has Won"<<endl;
                        setIsEnded(true);
                        return 0;
                    }


                    if(turnCount>=emptyCells){
                        cout<<"DRAW"<<endl;
                        setIsEnded(true);
                        return 0;
                    }

                    if(multiGameBegin==true)
                    	return 0;

                }while (true);
            }


            else{
                do{


                    position=PlayHand('X',"User1");
                    if(position==-1){
                    	cout<<"exit"<<endl;
                    	exit(0);
                    }

                    setLivingGames(getLivingGames()-1);

                    turnCount++;

                    cout<<"Living Cell: "<<turnCount<<endl;

                    if((winType=CheckWin(position,'X'))>=1){
                        printWin(position,'X',winType);
                        PrintBoard();
                        cout<<"User1 has Won"<<endl;
                        setIsEnded(true);
                        return 0;
                    }

                    if(turnCount>=emptyCells){
                        cout<<"DRAW"<<endl;
                        setIsEnded(true);
                        return 0;
                    }

                    int posMove=0;

                    do{
                        cout << "Ai move" << endl;

                        type=Play();/////////////////////////////////////////////PLAY()///////////////


                    }while((position=CheckMove( type)) == -1);

                    turnCount++;
                    setLivingGames(getLivingGames()-1);
                    cout<<"Living Cell: "<<turnCount<<endl;
                    SetPosToVector(position,'O');
                    PrintBoard();


                    if((winType=CheckWin(position,'O'))>=1){
                        printWin(position,'O',winType);
                        PrintBoard();
                        cout<<"Ai has Won"<<endl;
                        setIsEnded(true);
                        return 0;
                    }


                    if(turnCount>=emptyCells){
                        cout<<"DRAW"<<endl;
                        setIsEnded(true);
                        return 0;
                    }

                    if(multiGameBegin==true)
                    	return 0;

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



      /*  void PrintBoard(){
            char type='a';
            for (int i = 0; i < DimensionX; ++i) {

                cout<<type<<" ";
                type++;
            }
            cout<<endl;

            for (int i = 0; i < DimensionY; ++i) {

                for(int j=0;j<DimensionX;++j){

                    cout<<Board[i][j].getType()<<" ";
                }


                    cout<<endl;

            }
            cout<<endl;

    }*/

        bool ConnectFour::getIsEnded() const {
            return isEnded;
        }

        void ConnectFour::setIsEnded(bool isEnded) {
            ConnectFour::isEnded = isEnded;
        }

        int ConnectFour::getWidth() const {
            return DimensionX;
        }

        void ConnectFour::setWidth(int width) {
            ConnectFour::DimensionX = width;
        }

        int ConnectFour::getHeight() const {
            return DimensionY;
        }

        void ConnectFour::setHeight(int height) {
            ConnectFour::DimensionY = height;
        }

        int ConnectFour::getLivingGames() {
            return LivingGames;
        }

        void ConnectFour::setLivingGames(int LivingGames) {
            ConnectFour::LivingGames = LivingGames;
        }







        int ConnectFour::PlayHand(char HandType,string User){

        string typeIn;
        char type;
        int position=0;

        do{
            do{

                cin.clear();
                cout <<User<< " move or save(Save filename.txt) or type 'exit' to exit  " << endl;



                getline(cin,typeIn);

                if(typeIn[0]==EOF)
                	return -1;

                if(typeIn.length()==0)
                	return -1;

                if(toupper(typeIn[0]) =='S'&&toupper(typeIn[1])=='A'&&toupper(typeIn[2])=='V'&& toupper(typeIn[3]) =='E'){
                    SaveFile(typeIn.substr(5,typeIn.length()));
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
                	cout<<typeIn<<endl;
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





        int ConnectFour::CheckMove(char type){

            if( DimensionX<=(type-'a')){
                //cerr<<"Invalid Move1"<<endl;
                return -1;
            }


            int position=type-'a';
            if(position>DimensionX){
                //cerr<<"Invalid Move2  " <<endl;
                return -1;
            }
            position=position+((DimensionY-1)*DimensionX);

            for(int i=0;i<DimensionY;i++){

                if(GetPosToVector(position)=='*')
                    return position;
                position-=DimensionX;
            }

            //cerr<<"Invalid Move3  "<<type<<endl;
            return -1;


        }

        void ConnectFour::printWin(int position,char type,int winType){
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
                                if (GetPosToVector(TempPos - (DimensionX - 1) * i) != type)
                                    break;
                                if (i == 3) {
                                    SetPosToVector(TempPos,type + ('a' - 'A')) ;
                                    SetPosToVector(TempPos - DimensionX + 1,type + ('a' - 'A')) ;
                                    SetPosToVector(TempPos - 2 * DimensionX + 2,type + ('a' - 'A')) ;
                                    SetPosToVector(TempPos - 3 * DimensionX + 3,type + ('a' - 'A')) ;

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

        int ConnectFour::CheckWin(const int &position,const char &type){


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

                        if((TempPos-(DimensionX-1)*i)>=DimensionX*DimensionY )
                            break;
                        if( GetPosToVector(TempPos-(DimensionX-1)*i)!=type)
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



        char ConnectFour::DikeyKazanma(const char &Side){

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

        char ConnectFour::YatayKazanma(const char &Side){

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



        int  ConnectFour::FileArraySize( string DosyaAd) {

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

        void ConnectFour::SaveFile(const string &DosyaAd){
            ofstream file;
            file.open(DosyaAd);


            for(int i=0;i<DimensionX*DimensionY;i++){



                if(i%DimensionX==0 && i!=0 ){
                    file<<endl;
                    cout<<endl;
                    
                    if(GetPosToVector(i)=='S'){

                        file<<' ';
                        cout<<' ';
                    }
                    else{
                    	cout<<GetPosToVector(i);
                        file<<GetPosToVector(i);
                    }
                }


                else{
                    
                    if(GetPosToVector(i)=='S'){

                        file<<' ';
                        cout<<' ';
                    }
                    else{
                    	cout<<GetPosToVector(i);
                        file<<GetPosToVector(i);
                    }

                }


            }
            cout<<endl;
            file.close();

        }

        int ConnectFour::LoadFile(string DosyaAd){
            char c;


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
                    else
                        emptyCells++;
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


ConnectFour::~ConnectFour()
{
    for (int i = 0; i < DimensionY; ++i) {
        delete [] gameBoard[i];
    }

    delete [] gameBoard;
    gameBoard = nullptr;
}

ConnectFour::ConnectFour( const ConnectFour &other )
{
    DimensionX = other.DimensionX;
    DimensionY=other.DimensionY;
    isEnded=other.isEnded;
    isBoardInitialized=other.isBoardInitialized;
    AiOrPlayer=other.AiOrPlayer;
    turnCount=other.turnCount;
    emptyCells=other.emptyCells;
    player1Pos[0] = other.player1Pos[0];
    player1Pos[1] = other.player1Pos[1];
    MultiGame=other.MultiGame;


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


ConnectFour& ConnectFour::operator =(const ConnectFour &other)
{
    if ( &other != this )
    {
        DimensionX = other.DimensionX;
        DimensionY=other.DimensionY;
        isEnded=other.isEnded;
        isBoardInitialized=other.isBoardInitialized;
        AiOrPlayer=other.AiOrPlayer;
        turnCount=other.turnCount;
        emptyCells=other.emptyCells;
        player1Pos[0]=other.player1Pos[0];
        player1Pos[1]=other.player1Pos[1];
        MultiGame=other.MultiGame;
        multiGameBegin=other.multiGameBegin;


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
    return *this;
}

bool ConnectFour::operator == (const ConnectFour & other){

    if(other.turnCount!=turnCount)
        return false;
    else if(other.DimensionX!=DimensionX)
        return false;
    else if(other.DimensionY!=DimensionY)
        return false;
    else if(other.isBoardInitialized!=isBoardInitialized)
        return false;
    else if(other.isEnded!=isEnded)
        return false;
    else if(other.AiOrPlayer!=AiOrPlayer)
        return false;
    else if(other.emptyCells!=emptyCells)
        return false;
    else if(other.MultiGame!=MultiGame)
    	return false;
    else if(other.multiGameBegin!=multiGameBegin)
    	return false;

    for (int i = 0; i <DimensionY ; ++i) {
        for (int j = 0; j < DimensionX; ++j) {
            if(gameBoard[i][j].getType() !=other.gameBoard[i][j].getType() ){
                return false;
            }
        }
    }

    return true;

}

bool ConnectFour::operator != (const ConnectFour & other){

    if(other.turnCount!=turnCount)
        return true;
    else if(other.DimensionX!=DimensionX)
        return true;
    else if(other.DimensionY!=DimensionY)
        return true;
    else if(other.isBoardInitialized!=isBoardInitialized)
        return true;
    else if(other.isEnded!=isEnded)
        return true;
    else if(other.AiOrPlayer!=AiOrPlayer)
        return true;
    else if(other.emptyCells!=emptyCells)
        return true;
    else if(other.MultiGame!=MultiGame)
    	return true;
    else if(other.multiGameBegin!=multiGameBegin)
    	return true;

    for (int i = 0; i <DimensionY ; ++i) {
        for (int j = 0; j < DimensionX; ++j) {
            if(gameBoard[i][j].getType() !=other.gameBoard[i][j].getType() ){
                return true;
            }
        }
    }

    return false;

}

bool ConnectFour::getMultiGame()const{
		return  MultiGame;
    
}

void ConnectFour::SetMultiGame(bool set){
		MultiGame=set;
}













