#ifndef CPUPROGRAMDYN_H
#define CPUPROGRAMDYN_H

#include <string>
#include <iostream>
#include <fstream>


using namespace std;


namespace odev{

	class CPUProgramDyn{
		public:
			CPUProgramDyn(const CPUProgramDyn &other);
			CPUProgramDyn(int);
			CPUProgramDyn();
			void addline(string);
			void setfilename(string);
			int size()const;
			void setsize(int);
			const string getLine(int)const;
			void ReadFile(string);
		
			string getfilename()const;
			const string operator[](const int)const;
			CPUProgramDyn& operator=(const CPUProgramDyn& other);
			const CPUProgramDyn operator+(string)const;
			void popback();
		
			const CPUProgramDyn& operator+=(string);
			const CPUProgramDyn operator+(const CPUProgramDyn&)const;
			CPUProgramDyn& operator--();
			CPUProgramDyn operator--(int);
			friend ostream & operator<<(ostream &output , const CPUProgramDyn&);
			
			bool operator==(const CPUProgramDyn&)const;
			bool operator<=(const CPUProgramDyn& rtside)const;
			bool operator>(const CPUProgramDyn& rtside)const;
			bool operator!=(const CPUProgramDyn& rtside)const;
			bool operator>=(const CPUProgramDyn& rtside)const;
			bool operator<(const CPUProgramDyn& rtside)const;
			const CPUProgramDyn operator()(int,int )const;
			~CPUProgramDyn();
		private:
			string filename;
			string *inList;
		
			int sze=0;
			int cap=10;
			int option;
		
		};

}
	
#endif
