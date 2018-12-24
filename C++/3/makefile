all: main

main: main.o cpu.o cpuprogram.o
	g++ -std=c++11 main.o cpu.o cpuprogram.o -o program

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

cpu.o: cpu.cpp
	g++ -std=c++11 -c cpu.cpp

cpuprogram.o: cpuprogram.cpp
	g++ -std=c++11 -c cpuprogram.cpp

clean:
	rm *.o program
