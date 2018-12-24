all: exe

exe: main.o 
	g++  main.o  GTUSet.o GTUIterator.o GTUMap.o -o exe

main.o: main.cpp
	g++ -c -std=c++11 main.cpp GTUSet.cpp GTUIterator.cpp GTUMap.cpp



clean:
	rm *.o exe
