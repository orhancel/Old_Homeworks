#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "cpu.h"
#include "cpuprogram.h"


using namespace std;



int main(int argc, char** argv) {
	CPUProgram myProg(argv[1]);//CALLS THE CONSTRUCTOR WITH THE FILENAME//
	CPU mycpu(*argv[2]);//CALLS THE CONSTRUCTOR WITH THE OPTION NUMBER//
	myProg.ReadFile();//READS THE FILE//
	while(mycpu.HLT()){//BREAK THE LOOP IF HLT IS FALSE//
		mycpu.execute(mycpu.Uppercase(myProg.getLine(mycpu.getlineNumber()),myProg.getsize()));
		//EXECUTE     TURN STRING UPPERCASE   GETTHELINE AND LINENUMBER      SIZE OF THE ARRAY TO BE CHECKED//	
	}

	return 0;
}	
	
	
	
