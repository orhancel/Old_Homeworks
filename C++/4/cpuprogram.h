#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

const int sizeoflist=200;

class CPUProgram{
	public:
		CPUProgram(string);
		CPUProgram(int);
		CPUProgram();
		string getLine(int);
		void ReadFile(string);
		int size();
		string getfilename();
	private:
		string filename;
		string inList[sizeoflist];
		void setfilename(string);
		int sze;
		int option;
		
	};
	
#endif
