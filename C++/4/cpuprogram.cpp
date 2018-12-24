
#include <string>
#include <iostream>
#include <fstream>
#include "cpuprogram.h"
#include "cpu.h"

CPUProgram::CPUProgram(int op){
	option=op;
	}

CPUProgram::CPUProgram(){}

void CPUProgram::setfilename(string name){
	filename=name;
}
void CPUProgram::ReadFile(const string name){
	setfilename(name);
	ifstream dosya;
	int temp=0;
	dosya.open(filename);
	while(getline(dosya,inList[temp]))
		temp++;
		
	sze=temp;
}
int CPUProgram::size(){
	return sze;
}
string CPUProgram::getfilename(){
	return filename;
}
string CPUProgram::getLine(int line){
	return inList[line];
}
