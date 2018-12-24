#ifndef MEMORY_H
#define MEMORY_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Memory{
	public:
		Memory(int);
		Memory();
		int &getMem(int);
		void printAll();
		void setMem(int,int);
	private:
		vector<int> Mem{vector<int>(50,0)};
		int option;
};

#endif
