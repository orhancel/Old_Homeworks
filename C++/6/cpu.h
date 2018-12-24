#ifndef CPU_H
#define CPU_H
#include "memory.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;


class CPU{
	public:
		CPU(int);//contructor to set option number//
		CPU();
		void print();
		void execute(string,Memory& mymem);//executes the instruction in the string//
		int sqrt(int,int);//power functıon//
		int constconversion(string);
		void move(string,Memory&);//instruction function//
		void add(string,Memory&);//instruction function//
		void sub(string,Memory&);//instruction function//
		void jump(string);//instruction function//
		void jpn(string line);
		void print(string,Memory&); //instruction function//
		int checksyntax(string);//syntax checking function//	
		int checkcommand(string);//syntax function//
		int checkreg(string);//syntax  function//
		int checkcoma(string );//syntax  function//
		int checkcons(string);//syntax function//
		int checkdotcoma(string);//syntax  function//
		bool HLT();//instruction function//
		int getlineNumber();
		int getoption(){return option;};
		void setoption(int set){option=set;};
		string Uppercase(string,int);//makes the chars in a string uppercase//
		void setReg(int index,int value){r[index]=value;};
		void firstregister(string);
		int checkhash(string line);
		void setlineNumber(int);
	private:
		
		void sethaltfalse(){halt=false;};
		void sethalttru(){halt=true;};
		void setindex(int index){i=index;};
		
		bool halt=true;
		int i=0;//index number of lines//
		int r[5];
		int currLine=0;
		int option=0;
		int *first=0;
};

#endif
