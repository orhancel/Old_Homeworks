all: _mainTester

_mainTester: _mainTester.o cpu.o cpuprogram.o memory.o computer.o cpuprogramdyn.o
	g++ -std=c++11 _mainTester.o cpu.o cpuprogram.o memory.o computer.o cpuprogramdyn.o -o exe

_mainTester.o: _mainTester.cpp
	g++ -std=c++11 -c _mainTester.cpp

cpu.o: cpu.cpp
	g++ -std=c++11 -c cpu.cpp

cpuprogramdyn.o: cpuprogramdyn.cpp
	g++ -std=c++11 -c cpuprogramdyn.cpp

cpuprogram.o: cpuprogram.cpp
	g++ -std=c++11 -c cpuprogram.cpp
memory.o: memory.cpp
	g++ -std=c++11 -c memory.cpp
computer.o: computer.cpp
	g++ -std=c++11 -c computer.cpp



clean:
	rm *.o program
