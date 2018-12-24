

#include "cpuprogram.h"
#include "memory.h"
#include "cpu.h"
#include <string>
#include <iostream>
#include <fstream>
#include "computer.h"
using namespace std;

Computer::Computer(CPU& myC,CPUProgram& myCP,Memory& myM,int op){
	setCPU(myC);
	setCPUProgram(myCP);
	setMemory(myM);
	option=op;

}
Computer::Computer(int op){
	option=op;
}
Computer::Computer(){}

void Computer::execute(){
	myC.setlineNumber(0);
	for(int i=0;i<50;++i)
		myM.setMem(i,0);
	for(int i=0;i<5;++i)
		myC.setReg(i,0);
	myC.setoption(option);
	
	while(myC.HLT()){
		myC.execute(myC.Uppercase(myCP.getLine(myC.getlineNumber()),myCP.size()),myM);
		myC.setlineNumber(myC.getlineNumber()+1);//INCREMENT THE LINE NUMBER AFTER EACH LINE
	//EXECUTE CONVERT STRING UPPERCASE GETTHELINE AND LINENUMBER    SIZE OF THE ARRAY TO BE CHECKED//
	}	
}
void Computer::setCPU(CPU my){
	myC=my;
}
void Computer::setCPUProgram(CPUProgram my){
	myCP=my;
}
void Computer::setMemory(Memory my){
	myM=my;
}

CPU Computer::getCPU(){
	return myC;
}
CPUProgram Computer::getCPUProgram(){
	return myCP;
}
Memory Computer::getMemory(){
	return myM;
}





