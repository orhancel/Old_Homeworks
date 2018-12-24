all: exe

exe: main.o 
	g++  main.o  Cell.o ConnectFourAbstract.o ConnectFourDiag.o ConnectFourPlus.o ConnectFourPlusUndo.o -o exe

main.o: main.cpp
	g++ -c -std=c++11 main.cpp Cell.cpp ConnectFourAbstract.cpp ConnectFourDiag.cpp ConnectFourPlus.cpp ConnectFourPlusUndo.cpp 



clean:
	rm *.o exe
