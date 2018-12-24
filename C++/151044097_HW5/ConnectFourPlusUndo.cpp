//
// Created by ORHAN on 26.11.2017.
//

#include "ConnectFourPlusUndo.h"


const vector<int > &ConnectFourPlusUndo::getUndoList() const {
    return undoList;
}

void ConnectFourPlusUndo::setUndoList(const vector<int > &undoList) {
    ConnectFourPlusUndo::undoList = undoList;
}

void ConnectFourPlusUndo::Undo() {
    if(!undoList.empty()){
        SetPosToVector(undoList.back(),'*');

        undoList.pop_back();
        LivingCells-=1;
    }
    else
        cerr<<"Game is at beginning"<<endl;

}

void ConnectFourPlusUndo::AddUndoList(int position) {

    undoList.push_back(position);
}

int ConnectFourPlusUndo::PlayHand(char HandType,string User){

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

            if(typeIn[0]=='S'&&typeIn[1]=='A'&&typeIn[2]=='V'&&typeIn[3]=='E'){
                SaveFile(typeIn.substr(5,typeIn.length()));

                continue;
            }
            else if(typeIn[0]=='E'&&typeIn[1]=='X'&&typeIn[2]=='I'&&typeIn[3]=='T'){
                cout<<"Bye"<<endl;
                return -1 ;
            }
            else if(typeIn[0]=='L'&&typeIn[1]=='O'&&typeIn[2]=='A'&&typeIn[3]=='D'){
                LoadFile(typeIn.substr(5,typeIn.length()));
                PrintBoard();
                continue;
            }
            else if(typeIn[0]=='U'&&typeIn[1]=='N'&&typeIn[2]=='D'&&typeIn[3]=='O'){

                Undo();
                PrintBoard();
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
    ConnectFourAbstract::Play(position);/////////////////////////////////////////////////////////PLAY(İNT VARİABLE)////////////////
    PrintBoard();
    return position;

}



int ConnectFourPlusUndo::playGame(){

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

            AddUndoList(position);///

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

            AddUndoList(position);///

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

            AddUndoList(position);///



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

            AddUndoList(position);///

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



        }while (true);
    }


    return 0;


}
