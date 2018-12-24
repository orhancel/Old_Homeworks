#include <iostream>

#include "requiredIncs.h"

using namespace std;



int main(int argc, char** argv) {
	const char* filename = argv[1]; 
	int option = atoi(argv[2]);
	
	Memory myMemory(option);
	myMemory.setMem(0, 100); 
	cout<< myMemory.getMem(0) << endl; 
	myMemory.printAll();
	
	CPU myCPU(option);
	myCPU.execute("MOV #0, R1", myMemory); 
	myCPU.execute("MOV R1, #1", myMemory);
	
	CPUProgram myCPUProgram(option);
	myCPUProgram.ReadFile(filename); 
	cout <<myCPUProgram.getLine(0) << endl; 
	cout <<myCPUProgram.getLine(myCPUProgram.size() - 1) << endl;
	
	Computer myComputer1(myCPU, myCPUProgram, myMemory, option);
	Computer myComputer2(option); myComputer2.setCPU(myComputer1.getCPU() );
	myComputer2.setCPUProgram(myComputer1.getCPUProgram() );
	myComputer2.setMemory(myComputer1.getMemory() ); 
	myComputer2.execute();
	
	
	return 0;
}	
	
	
	
