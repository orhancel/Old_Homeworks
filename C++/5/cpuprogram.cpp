
#include <string>
#include <iostream>
#include <fstream>
#include "cpuprogram.h"
#include "cpu.h"
#include <vector>
CPUProgram::CPUProgram(int op){
	option=op;
	}

CPUProgram::CPUProgram(){}

void CPUProgram::setfilename(string name){
	filename=name;
}
void CPUProgram::ReadFile(string name){
	setfilename(name);
	ifstream dosya;
	string line;
	int temp=0;
	dosya.open(filename);
	while(getline(dosya,line)){
		inList.push_back(line);
		temp++;
	}
	sze=temp;
}


const string CPUProgram::operator[](const int index) const{
	if(index>=sze){
		cout<<"Index too big"<<endl;
		return "";
	}
	return inList[index];

}
void CPUProgram::addline(string line){
	inList.push_back(line);
}

const CPUProgram CPUProgram::operator+(string line)const{
	CPUProgram newcp;
	
	newcp=*this;
	newcp.addline(line);
	newcp.setsize(sze+1);
	
	return newcp;
}

const CPUProgram CPUProgram::operator+(const CPUProgram &rtside)const{
	CPUProgram newcp;
	for(int i=0;i<inList.size();i++)
		newcp.inList.push_back(inList[i]);
	for(int i=0;i<rtside.inList.size();i++)
		newcp.inList.push_back(rtside.inList[i]);
	newcp.setsize(newcp.inList.size());
	return newcp;
}
	


const CPUProgram& CPUProgram::operator+=(string line){
	if(line==""){
		cout << "Can't add an empty line"<<endl;
		return *this;
	}
	inList.push_back(line);
	sze+=1;
	return *this;
}

CPUProgram& CPUProgram::operator--(){
	inList.pop_back();
	return *this;
}

CPUProgram CPUProgram::operator--(int){
	CPUProgram newcp;
	newcp=*this;
	inList.pop_back();
	return newcp;
}

bool CPUProgram::operator==(const CPUProgram& rtside)const{
	return (sze==rtside.size());
}

bool CPUProgram::operator<=(const CPUProgram& rtside)const{
	return (sze<=rtside.size());
}

bool CPUProgram::operator>(const CPUProgram& rtside)const{
	return (sze>rtside.size());
}

bool CPUProgram::operator<(const CPUProgram& rtside)const{
	return (sze<rtside.size());
}

bool CPUProgram::operator!=(const CPUProgram& rtside)const{
	return (sze!=rtside.size());
}
bool CPUProgram::operator>=(const CPUProgram& rtside)const{
	return (sze>=rtside.size());
}
ostream & operator<<(ostream &output , const CPUProgram &nesne2){
	
	

	for(int i=0;i<nesne2.inList.size();i++)
		output <<nesne2.getLine(i)<<endl;
	
		return output;
}	

const CPUProgram CPUProgram::operator()(int start,int end)const{
	CPUProgram newcp;
	if(start<0){
		cout<<"error:Index cannot be lower than 1"<<endl;
		newcp.inList.push_back("");
		return newcp;}
	if(end>sze){
		cout<<"Array size has been passed"<<endl;
		newcp.inList.push_back("");
		return newcp;}
	for(int i=start-1;i<end;++i)
		newcp.inList.push_back(inList[i]);
	return newcp;
}
	


	
const int CPUProgram::size()const{
	return sze;
}

string CPUProgram::getfilename(){
	return filename;
}

const string CPUProgram::getLine(int index)const{
	return inList[index];
}


void CPUProgram::setsize(int size){
	sze=size;
}





