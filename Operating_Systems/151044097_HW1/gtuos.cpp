#include <iostream>
#include "8080emuCPP.h"
#include "gtuos.h"
#include <ctime>


using namespace std;
uint64_t GTUOS::handleCall(const CPU8080 & cpu){


	uint16_t address = ((uint16_t)cpu.state->b << 8) | cpu.state->c;
    	uint64_t cycleCount=0;
	if(cpu.state->a == (uint8_t)1){
		cout << "Call: PRINT_B" << endl;
		cout << "Content of B: " << (int)cpu.state->b << endl;
		cycleCount = 10;	
	}
	
	else if(cpu.state->a == (uint8_t)2){
		cout << "Call: PRINT_MEM" << endl;
		cout << "Content of Memory: " << cpu.memory->at(address) << endl; 
		cycleCount = 10;	
	}
	// Read an integer. 
	else if(cpu.state->a == (uint8_t)3){
		
		int temp;
		cin >> temp;
		cpu.state->b = (uint8_t)temp;
        cout << "Call: READ_B  :  " << temp <<" value readed into B"<< endl;
		cin.clear();
		cycleCount = 10;
	}
	// Read memory content
	else if(cpu.state->a == (uint8_t)4){
		
		uint8_t temp;
		cin >> temp;
		
		cpu.memory->at(address) = temp;
        	cout << "Call: READ_MEM  :  " << cpu.memory->at(address) <<" value readed into memory" << endl;
		cin.clear();
		cycleCount = 10;
	}
	// Print string
	else if(cpu.state->a == (uint8_t)5){
		cout << "Call: PRINT_STR" << endl;
		char ch ='x';
		for(int i=0; ch != '\0'; ++i){
               		ch = (char)cpu.memory->at(address+i);
                	cout << ch;
            	}
            	
		
		cycleCount = 100;
	}
	// Read a string.
	else if(cpu.state->a == (uint8_t)6){
		cout << "Call: READ_STR" << endl;
		char ch ;
		
		int count=0;
		do{
			ch = getchar();
			cpu.memory->at(address+count) = ch;
			++count;
		}while(ch != '\n');
		cpu.memory->at(address+count)= (uint8_t)'\0';
		
		cycleCount = 100;
	}
	// Get a random integer.
    	else if(cpu.state->a == (uint8_t)7){
		cout << "Call: GET_RND" << endl;
		
        	int r = (rand() % 255) + 1;
        	cpu.state->b = (uint8_t)r;
		cout<<"Random number is  :  "<<(int)cpu.state->b<<endl;
		cycleCount = 5;
	}

	// Case of Undefined call.
    	else{
        cout <<  "Undefined OS Call";
	    throw -1;
    	} 
	
	
	return cycleCount;
}

// Write memory to  "exe.mem" file 
void GTUOS::printFile(const CPU8080 & cpu){

	FILE *File_ptr;
	File_ptr = fopen("exe.mem" , "w");	

	if(File_ptr == NULL){ 
		fprintf(stderr, "File couldn't opened to write.\n");
		exit(1);
	}	


    	for(int i=0; i < 65536; i += 16){////65536=256*256
		fprintf(File_ptr, "%04x:   ", i);
		for(int j =0; j < 16; ++j){
			fprintf(File_ptr, "%02x ", cpu.memory->at(uint16_t (i+j)));
		}
		fprintf(File_ptr, "\n");
	}

	
	fclose(File_ptr);
	return;
}

