
#include <string>
#include <iostream>
#include <fstream>
#include "cpuprogram.h"

CPUProgram::CPUProgram(string name){
	setfilename(name);
}
void CPUProgram::setfilename(string name){
	filename=name;
}
void CPUProgram::ReadFile(){
	ifstream dosya;
	int temp=0;
	dosya.open(filename);
	while(getline(dosya,inList[temp]))
		temp++;
		
	size=temp+1;
}
int CPUProgram::getsize(){
	return size;
}
string CPUProgram::getfilename(){
	return filename;
}
string CPUProgram::getLine(int line){
	return inList[line];
}
