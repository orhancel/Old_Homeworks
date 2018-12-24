
#include <string>
#include <iostream>
#include <fstream>
#include "cpuprogramdyn.h"
#include "cpu.h"

namespace odev{


CPUProgramDyn::CPUProgramDyn(int op){
	option=op;
	inList=new string[cap];
	}

CPUProgramDyn::CPUProgramDyn(){
	inList=new string[cap];
}


void CPUProgramDyn::setfilename(string name){
	filename=name;
}
void CPUProgramDyn::ReadFile(string name){
	setfilename(name);
	ifstream dosya;
	string line;

	dosya.open(filename);

	while(getline(dosya,line)){
		
		addline(line);
	}
	
}

CPUProgramDyn::CPUProgramDyn(const CPUProgramDyn &other){//COPY CONSTRUCTOR
	
	sze=other.sze;
	cap=other.cap;
	filename=other.filename;
	option=other.option;
	inList=new string[cap];
	for(int in=0;in<sze;++in)
		inList[in]=other.inList[in];
	

}


CPUProgramDyn& CPUProgramDyn::operator=(const CPUProgramDyn& other){//ASİGNMENT
	
	if(&other==this)
		return *this;

	sze=other.sze;
	cap=other.cap;
	filename=other.filename;
	option=other.option;
	delete [] inList;
	inList=new string[cap];
	for(int in=0;in<sze;++in)
		inList[in]=other.inList[in];
	return *this;

}

CPUProgramDyn::~CPUProgramDyn(){////DESTRUCTOR
	delete [] inList;
}


void CPUProgramDyn::addline(string line){
	if(sze == cap ){
		string arr[sze];
		for(int in=0;in<sze;++in)
			arr[in]=inList[in];
		delete [] inList;
		cap*=2;
		inList=new string[cap];
		for(int in=0;in<sze;++in)
			inList[in]=arr[in];
	}	
	
	inList[sze]=line;
	++sze;
}

const string CPUProgramDyn::operator[](const int index) const{
	
	if(index>=sze){
		cout<<"Index too big"<<endl;
		return "";
	}
	return inList[index];

}


const CPUProgramDyn CPUProgramDyn::operator+(string line)const{
	CPUProgramDyn newcp;
	
	newcp=*this;
	newcp.addline(line);
	
	
	return newcp;
}

const CPUProgramDyn CPUProgramDyn::operator+(const CPUProgramDyn &rtside)const{
	CPUProgramDyn newcp;
	for(int i=0;i<sze;i++)
		newcp.addline(inList[i]);
	for(int i=0;i<rtside.sze;i++)
		newcp.addline(rtside.inList[i]);
	
	return newcp;
}
	


const CPUProgramDyn& CPUProgramDyn::operator+=(string line){
	if(line==""){
		cout << "Can't add an empty line"<<endl;
		return *this;
	}
	addline(line);
	
	return *this;
}

void CPUProgramDyn::popback(){
	
	string arr[1];
	inList[sze-1]=arr[0];

}
CPUProgramDyn& CPUProgramDyn::operator--(){
	popback();
	return *this;
}

CPUProgramDyn CPUProgramDyn::operator--(int){
	CPUProgramDyn newcp;
	newcp=*this;
	popback();
	return newcp;
}

bool CPUProgramDyn::operator==(const CPUProgramDyn& rtside)const{
	return (sze==rtside.size());
}

bool CPUProgramDyn::operator<=(const CPUProgramDyn& rtside)const{
	return (sze<=rtside.size());
}

bool CPUProgramDyn::operator>(const CPUProgramDyn& rtside)const{
	return (sze>rtside.size());
}

bool CPUProgramDyn::operator<(const CPUProgramDyn& rtside)const{
	return (sze<rtside.size());
}

bool CPUProgramDyn::operator!=(const CPUProgramDyn& rtside)const{
	return (sze!=rtside.size());
}
bool CPUProgramDyn::operator>=(const CPUProgramDyn& rtside)const{
	return (sze>=rtside.size());
}
ostream & operator<<(ostream &output , const CPUProgramDyn &nesne2){
	
	

	for(int i=0;i<nesne2.size();i++)
		output <<nesne2.getLine(i)<<endl;
	
		return output;
}	

const CPUProgramDyn CPUProgramDyn::operator()(int start,int end)const{
	CPUProgramDyn newcp;
	if(start<0){
		cout<<"error:Index cannot be lower than 1"<<endl;
		newcp.addline("");
		return newcp;}
	if(end>sze){
		cout<<"Array size has been passed"<<endl;
		newcp.addline("");
		return newcp;}
	for(int i=start-1;i<end;++i)
		newcp.addline(inList[i]);
	return newcp;
}
	


	
int CPUProgramDyn::size()const{
	return sze;
}

string CPUProgramDyn::getfilename()const{
	return filename;
}

const string CPUProgramDyn::getLine(int index)const{
	return inList[index];
}


void CPUProgramDyn::setsize(int size){
	sze=size;
}




}
