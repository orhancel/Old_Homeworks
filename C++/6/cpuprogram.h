#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;



class CPUProgram{
	public:
		CPUProgram(string);
		CPUProgram(int);
		CPUProgram();
		void addline(string);
		void setfilename(string);
		const int size()const;
		void setsize(int);
		const string getLine(int)const;
		void ReadFile(string);
		
		string getfilename();
		const string operator[](const int)const;

		const CPUProgram operator+(string)const;

		
		const CPUProgram& operator+=(string);
		const CPUProgram operator+(const CPUProgram&)const;
		CPUProgram& operator--();
		CPUProgram operator--(int);
		friend ostream & operator<<(ostream &output , const CPUProgram&);
		bool operator==(const CPUProgram&)const;
		bool operator<=(const CPUProgram& rtside)const;
		bool operator>(const CPUProgram& rtside)const;
		bool operator!=(const CPUProgram& rtside)const;
		bool operator>=(const CPUProgram& rtside)const;
		bool operator<(const CPUProgram& rtside)const;
		const CPUProgram operator()(int,int )const;
	private:
		string filename;
		vector<string> inList;
		
		int sze;
		int option;
		
	};
	
#endif
