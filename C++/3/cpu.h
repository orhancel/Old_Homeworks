#ifndef CPU_H
#define CPU_H

#include <string>
#include <iostream>
#include <fstream>
using namespace std;


class CPU{
	public:
		CPU(int);//contructor to set option number//
		int execute(string);//executes the instruction in the string//
		int sqrt(int,int);//power functıon//
		int move(string);//instruction function//
		int add(string);//instruction function//
		int sub(string);//instruction function//
		int jump(int,string);//instruction function//
		int print(string); //instruction function//
		int checksyntax(string);//syntax checking function//	
		int checkcommand(string);//syntax function//
		int checkreg(string);//syntax  function//
		int checkcoma(string );//syntax  function//
		int checkcons(string);//syntax function//
		int checkdotcoma(string);//syntax  function//
		bool HLT();//instruction function//
		int getlineNumber();
		int getoption(){return option;};
		string Uppercase(string,int);//makes the chars in a string uppercase//
	private:
		void setlineNumber(int);
		void sethaltfalse(){halt=false;};
		void sethalttru(){halt=true;};
		void setindex(int index){i=index;};
		void setoption(int set){option=set;};
		bool halt;
		int i;//index number of lines//
		int r[5];
		int currLine;
		int option;
};

#endif
