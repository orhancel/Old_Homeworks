/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */








#include <iostream>
#include "BigramDyn.h"
#include <fstream>

#include <stdlib.h>


using namespace std;

template <class T>

BigramDyn<T>::BigramDyn(int data){
	dataType=data;
	
	pairAllPtr=new pairClass<T>[10];////////
	pairMapPtr=new pairClass<T>[10];/////
	pairSize=10;
	pairIndex=0;
	pairMapSize=10;
	pairMapIndex=0;
}
template <class T>
BigramDyn<T>::BigramDyn(){
	dataType=1;
	
	pairAllPtr=new pairClass<T>[10];
	pairMapPtr=new pairClass<T>[10];
	pairSize=10;
	pairIndex=0;
	pairMapSize=10;
	pairMapIndex=0;

}
template <class T>
BigramDyn<T>::~BigramDyn(){////DESTRUCTOR

	delete [] pairMapPtr;
	delete [] pairAllPtr;
	

}

template <class T>
BigramDyn<T>::BigramDyn(const BigramDyn<T>& other){////COPY CONSTRUCTOR

	
		
		pairSize=other.pairSize;
		pairIndex=0;
		pairMapSize=other.pairMapSize;
		pairMapIndex=0;
		for(int i=0;i<pairSize;++i){
			pairAll(other.pairAllPtr[i].getLeft(),other.pairAllPtr[i].getRight(),other.pairAllPtr[i].getValue());
		}
		for(int i=0;i<pairMapSize;++i){
			pairAll(other.pairMapPtr[i].getLeft(),other.pairMapPtr[i].getRight(),other.pairMapPtr[i].getValue());
		}




}


template <class T>
const BigramDyn<T>& BigramDyn<T>::operator=(const BigramDyn<T>& other){////ASSIGNMENT OVERLOAD
	
	if(this!=&other){
		delete [] pairMapPtr;
		delete [] pairAllPtr;
		pairSize=other.pairSize;
		pairIndex=other.pairIndex;
		pairMapSize=other.pairMapSize;
		pairMapIndex=other.pairMapIndex;
		for(int i=0;i<pairIndex;++i){
			pairAllPtr[i]=other.pairAllPtr[i];
		}
		for(int i=0;i<pairMapIndex;++i){
			pairMapPtr[i]=other.pairMapPtr[i];
		}


	}
	return *this;

}






template <class T>
void BigramDyn<T>::readFile( string filename){
	T token1;
    
    T token2;

    
    ifstream dosya;
    
    dosya.open(filename);
	if(!dosya.is_open()){
		
		throw myException("File not opened");
	}
{
	string temp;
	getline(dosya,temp);
	bool flag=false;
	if(temp.size()==0 ){

		throw myException("Empty File");
	}
	for(int i=0;i<temp.size();++i)
	{
		if(temp[i]==' ')
			continue;
		else{
			flag=true;
			break;
			}
	}
	if(!flag){
	
			throw myException("Empty File");	
	}
	
}	
	dosya.close();
	dosya.open(filename);
	if(!(dosya>>token1)){
	
		throw myException("inconsistent datatype");
	}
	for(int i=0;dosya.good();++i){//////////////BU KISMA KADAR BIGRAMMAP ILE AYNI
        if(dosya>>token2){
			pairAll(token1,token2,0);////BUTUN CIFTLER TUTULUR
            pairMap(token1,token2,0);///AYNI OLAN CIFTLER TUTULMAZ
            token1=token2;
        }
		
        else if(!dosya.eof()){
			
            throw myException("inconsistent datatype");
        }
		
    }


}





template <class T>


void BigramDyn<T>::pairAll(T a1,T a2,int a3){
	
	if(pairIndex>=pairSize){////////////////EGER ARRAY BOYUTU GECILIR ISE 
		pairClass<T> temp[pairSize];
		for(int i=0;i<pairSize;++i){
			temp[i]=pairAllPtr[i];/////////////GECICI CLASS ARRAY INE DEGERLER ATILIR
				
		}
		pairSize+=10;//BOYUT ARTTIRILIR
		delete [] pairAllPtr;////DEALLOCATE
		pairAllPtr=new pairClass<T>[pairSize];///ALLOCATE
		
		for(int i=0;i<pairSize-10;++i){///DEGERLER YENI ARRAY E DOLDURULUR
			pairAllPtr[i]=temp[i];
				
		}
	
	}

	pairAllPtr[pairIndex]=pairClass<T>(a1,a2,a3);////YENI DEGER ATAMSI
	pairIndex+=1;///INDEX GUNCELLENIR



}

template <class T>


void BigramDyn<T>::pairMap(T a1,T a2,int a3){/////paırAll FONKSIYONU ILE AYNI
	
	if(pairMapIndex>=pairMapSize){
			pairClass<T> temp[pairMapSize];
			for(int i=0;i<pairMapSize;++i){
				temp[i]=pairMapPtr[i];
				
			}
			pairMapSize+=10;
			delete [] pairMapPtr;
			pairMapPtr=new pairClass<T>[pairMapSize];
			for(int i=0;i<pairMapSize-10;++i){
						pairMapPtr[i]=temp[i];
				
		}
	
	}

	for(int i=0;i<pairMapIndex;++i){///////EGER YENI BIGRAM ZATEN BIZDE VAR ISE ATAMA YAPMAZ
		if(a1==pairMapPtr[i].getLeft() && a2==pairMapPtr[i].getRight()){
			return;

		} 
	}
		
		pairMapPtr[pairMapIndex]=pairClass<T>(a1,a2,a3);
		
		pairMapIndex+=1;


}

template <class T>

int BigramDyn<T>::numGrams(){///////////////////////////
    
    
    return pairIndex;///////////////////
     
}



template <class T>
int BigramDyn<T>::numOfGrams(T p1,T p2){
    pairClass<T> key(p1,p2,0);///YENI paırCLASS OBJESI KEY
  
   
    int count=0;
    
    
    for(int i=0;i<pairIndex;++i)///BUTUN BIGRAMLARIN SAYISI
    {
         
         if((pairAllPtr[i].getLeft()==key.getLeft()) &&////////////////KEY OBJESI BUTUN BIGRAM DEGERLERI ILE KARSILASTIRILIR
				(pairAllPtr[i].getRight()==key.getRight()))
         {
             count+=1;
         }
    }
    
    return count;
   
    
}




template <class T>
pair<T,T> BigramDyn<T>::maxGrams(){
    pair<T,T> maxpair;
    int max;
    
    
    
    for(int i=0;i<pairMapIndex;++i)///////paırMapPtr ARRAYI DNGUYE GIRER
    {   pairMapPtr[i].setValue(0);
        for(int j=0;j<pairIndex;++j)////BUTUN BIGRAMLARIN TUTULDUGU ARRAY DONGUYE GIRER
        {
         
            if((pairMapPtr[i].getLeft()==pairAllPtr[j].getLeft()) && ////////paırMapPtr ve paırAllPtr KARSILASTIRILIR
					(pairMapPtr[i].getRight()==pairAllPtr[j].getRight()))
            {
                pairMapPtr[i].setValue(pairMapPtr[i].getValue()+1);////SADECE TEK TUR BIGRAM TUTULAN ARRAYDEKI
///////////////////////////////////////////////////////////////////////OBJELERIN VALUE KISMI ARTIRILIR
            }
        }
    }
	
    max=pairMapPtr[0].getValue();
	maxpair.first=pairMapPtr[0].getLeft();
	maxpair.second=pairMapPtr[0].getRight();
	
    for(int i=1;i<pairMapIndex;++i)//////paırMapPtr VALUE KISIMLARI KARSILASTIRILIR
    {
        if(max<pairMapPtr[i].getValue())///VALUE KISMI BIGRAMDAN KAC TANE OLDUGUNU TUTAR
        {
            max=pairMapPtr[i].getValue();
            maxpair.first=pairMapPtr[i].getLeft();
			maxpair.second=pairMapPtr[i].getRight();
        }
    }
    return maxpair;
    
    
}



template <class T>

void BigramDyn<T>::print(ostream& output){
	 
    for(int i=0;i<pairMapIndex;++i)////////////////MAP TUTAN ARRAY
    {   pairMapPtr[i].setValue(0);
        for(int j=0;j<pairIndex;++j)///BUTUN BIGRAMLARI TUTAN ARRAY
        {
         
            if((pairMapPtr[i].getLeft()==pairAllPtr[j].getLeft()) && (pairMapPtr[i].getRight()==pairAllPtr[j].getRight()))
            {/////////////////////////////////////////////////////////EGER MAP TUTAN ARRAYDEKI BIGRAMDAN VAR ISE
                pairMapPtr[i].setValue(pairMapPtr[i].getValue()+1);////MAP TUTAN ARRAYDEKI VALUE KISMI ARTTIRILIR
            }
        }
    }
	
	for(int i=1;i<pairMapIndex;++i){///////////////////BUBBLE SORT
		for(int j=0;j<pairMapIndex-i;++j){
			
			if(pairMapPtr[j].getValue()<pairMapPtr[j+1].getValue()){
				
				pairClass<T> temp;
				temp=pairMapPtr[j];
				pairMapPtr[j]=pairMapPtr[j+1];
				pairMapPtr[j+1]=temp;
			}
		}
	}
			
	for(int i=0;i<pairMapIndex;++i){///DUZENLENMIS PAIRCLASS OBJELERININ BASKISI
	
		
		output<<" ( "<<pairMapPtr[i].getLeft()<<" , "<<pairMapPtr[i].getRight()<<" )"<<" = "<<pairMapPtr[i].getValue()<<endl;
		
	}
	
	
}













