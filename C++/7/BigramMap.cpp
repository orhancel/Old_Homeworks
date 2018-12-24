/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */



#include <map>
#include <utility>
#include <iostream>
#include "BigramMap.h"
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <vector>

using namespace std;
template <class T>

BigramMap<T>::BigramMap(int data){//////////CONSTRUCTOR 
    dataType=data;///////////////DATA HOLD THE DATATYPE
}

template <class T>
void BigramMap<T>::readFile( string filename){
    
    
    
    T token1;//////////OPENS A VARIABLE OF TYPE T
    
    T token2;/////////////SAME HERE

    
    ifstream dosya;//////////DOSYA ATANACAK VARIABLE
    
    dosya.open(filename);//////DOSYA ACMA
	if(!dosya.is_open()){///////////////////////////////DOSYA ACMA KONTROLU
		
		throw myException("File not opened");//////EXCEPTION FIRLATMA
	}
{/////////////////////////////////DOSYADAKI ELEMENTLERIN KONTROL SCOPU
	string temp;
	getline(dosya,temp);
	bool flag=false;
	if(temp.size()==0 ){///////////DOSYA BOS MU
	
		throw myException("Empty File");
	}
	for(int i=0;i<temp.size();++i)
	{
		if(temp[i]==' ')/////////////SADECE BOSLUKLA MI DOLU 
			continue;
		else{
			flag=true;
			break;
			}
	}
	if(!flag){

			throw myException("Empty File");	//////////SADECE BOSLUK VAR ISE EMTY FILE HATASI VERIR
	}
	
}	/////////////////////////////////////////HATA KONTROL SCOP SONU
	dosya.close();
	dosya.open(filename);
	if(!(dosya>>token1)){//////////////DATA TURUNU KONTROL ETME VE DATAYI TOKEN1 E ATAMA
		
		throw myException("inconsistent datatype");
    }
    for(int i=0;dosya.good();++i){
        if(dosya>>token2){///////////////DATA TURUNU KONTROL ETME VE DATAYI TOKEN2'YE ATAMA
			keys.push_back(pair<T,T> (token1,token2));/////////PAIR TURUNDE ACTIGIMIZ VEKTORE PAIR EKLERIZ
            seqMap[pair<T,T> (token1,token2)]=0;//////PAIR VE INT TURUNDE ACTIGIMIZ MAP E EKLEME
            token1=token2;/////SWAP
        }
		
        else if(!dosya.eof()){///////////DOSYA SONUNA GELMEDEN TOKEN2 ELEMENT ALAMAZ ISE DATATYPE FARKLIDIR
			
            throw myException("inconsistent datatype");
        }
		
    }
  
    
   
}


template <class T>

int BigramMap<T>::numGrams(){////////////KEYS VECTORUMUZ PAIR TUTAR////BOYUTUNU RETURN ETMEMIZ YETER
    
   
    return keys.size();
     
}

template <class T>
int BigramMap<T>::numOfGrams(T p1,T p2){
    pair<T,T> key(p1,p2);////////////////ALINAN DEGERLER KEY ADINDA BIR PAIR YAPILIR
  
   
    int count=0;
    
    
    for(int i=0;i<keys.size();++i)////////PAIR VEKTORUNDEKI ELEMENTLERLE KARSILASTIRMA YAPILIR
    {
         
         if(keys[i]==key)////KEYS VECTOR KEY ALDIGIMIZ DEGERLERIN PAIR'I
         {
             count+=1;
         }
    }
    
    return count;
   
    
}

template <class T>
pair<T,T> BigramMap<T>::maxGrams(){
    pair<T,T> maxpair;//////mAXIMUM OLAN PAIRI TUTAR
    int max;//////////////MAXIMUM OLAN PAIR'DEN KAC TANE OLDUGUNU TUTAR
    typename map<pair<T,T>,int> :: iterator p1;///MAP ITERATORUMUZ
    
    
    for(p1=seqMap.begin();p1!=seqMap.end();++p1)//MAP'IN ICINDE DONME
    {   p1->second=0;////MAPTEKI HER PAIR'IN DEGERI 0'A INITIALIZE EDILIR
		
        for(int i=0;i<keys.size();++i)/////VEKTORUN ICINDE GEZME
        {
         
            if(p1->first==keys[i])//VEKTORDEKI PAIR LER ILE KARSILASTIRMA
            {
                p1->second+=1;///VAR ISE ARTTIRMA
            }
        }
    }
	p1=seqMap.begin();///ITERATORU BASA ALMA

    max=p1->second;////MAX DEGERINI INITIALIZE ETME
	maxpair=p1->first;///MAXPAIR DEGERINI INITIALIZE ETME
	++p1;

    for(p1=seqMap.begin();p1!=seqMap.end();++p1)
    {
        if(max<p1->second)///EGER DEGERI FAZLA OLAN MAP VAR ISE 
        {
            max=p1->second;//MAPTEKI INT DEGERI ATANIR
            maxpair=p1->first;//MAPTEKI PAIR ATANIR
        }
    }
    return maxpair;//MAXPAIR GONDERILIR
    
    
}

template <class T>

void BigramMap<T>::print(ostream& output){//////PRINT OVERLOAD YARDIMCI FONKSIYONU INHERIT EDILIR 
	int mapsize=0;
	typename map<pair<T,T>,int> :: iterator p1=seqMap.begin();///MAP ITERATORUMUZ
	for(p1=seqMap.begin();p1!=seqMap.end();++p1)//MAP'IN ICINDE DONME
    {   p1->second=0;////MAPTEKI HER PAIR'IN DEGERI 0'A INITIALIZE EDILIR
		mapsize+=1;
        for(int i=0;i<keys.size();++i)/////VEKTORUN ICINDE GEZME
        {
         
            if(p1->first==keys[i])//VEKTORDEKI PAIR LER ILE KARSILASTIRMA
            {
                p1->second+=1;//VAR ISE ARTTIRMA
            }
        }
    }
	
	pair <pair<T,T>,int> switched[mapsize];//PAIR VE INT TUTAN YENI BIR PAIR ACMA
	
	
	p1=seqMap.begin();
	for(int i=0;i<mapsize;++i){///MAP TEKI DEGERLERI BU SWITCH PAIR'INE ATAMA
		switched[i].first=p1->first;
		switched[i].second=p1->second;
		++p1;
	}
	for(int i=1;i<mapsize;++i){//////////BUBBLE SORT
		for(int j=0;j<mapsize-i;++j){
			
			if(switched[j].second<switched[j+1].second){
				
				pair <pair<T,T>,int> temp;
				temp=switched[j];
				switched[j]=switched[j+1];
				switched[j+1]=temp;
			}
		}
	}
			

	
	
	for(int i=0;i<mapsize;++i){///DUZENLENMIS SWITCH PAIRLERINI BUYUKTEN KUCUGE SIRAYLA BASMA
	
		
		output<<" ( "<<switched[i].first.first<<" , "<<switched[i].first.second<<" )"<<" = "<<switched[i].second<<endl;
		
	}
	
	
}






