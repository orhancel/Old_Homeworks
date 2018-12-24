all: _mainTester

_mainTester: _mainTester.o cpu.o cpuprogram.o memory.o computer.o
	g++ -std=c++11 _mainTester.o cpu.o cpuprogram.o memory.o computer.o -o program

_mainTester.o: _mainTester.cpp
	g++ -std=c++11 -c _mainTester.cpp

cpu.o: cpu.cpp
	g++ -std=c++11 -c cpu.cpp

cpuprogram.o: cpuprogram.cpp
	g++ -std=c++11 -c cpuprogram.cpp
memory.o: memory.cpp
	g++ -std=c++11 -c memory.cpp
computer.o: computer.cpp
	g++ -std=c++11 -c computer.cpp

clean:
	rm *.o program
