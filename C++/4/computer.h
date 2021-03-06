#ifndef COMPUTER_H
#define COMPUTER_H
#include "cpu.h"
#include "cpuprogram.h"
#include "memory.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Computer{
	public:
		Computer(CPU myC,CPUProgram myCP,Memory myM,int);//CONSTRUCTOR
		Computer(int);
		Computer();
		CPU getCPU();//DEFAULT CONSTRUCTOR
		void setCPU(CPU);
		CPUProgram getCPUProgram();
		void setCPUProgram(CPUProgram);
		Memory getMemory();
		void setMemory(Memory);
		void execute();
	private:
		int option;
		CPU myC;
		CPUProgram myCP;
		Memory myM;
		
};

#endif
