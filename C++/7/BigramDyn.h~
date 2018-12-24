/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BigramDyn.h
 * Author: user
 *
 * Created on December 23, 2016, 4:23 PM
 */
#include <iostream>
#include <fstream>
#include <utility>
#include "Bigram.h"
#include "myException.h"
#include "pairClass.h"//////////KENDI YARDIMCI CLASS'IM


using namespace std;
#ifndef BIGRAMDYN_H
#define BIGRAMDYN_H

template <class T>
class BigramDyn:public Bigram<T>{
	public:
		BigramDyn();
        BigramDyn(int);
		BigramDyn(const BigramDyn<T>&);////COPY CONSTRUCTOR
		const BigramDyn& operator=(const BigramDyn<T>& );///////////ASSIGNMENT OVERLOAD
        void readFile( string) override ;
        int numGrams() override ;
        int numOfGrams(T,T) override  ;
        pair <T,T> maxGrams() override ;
        void print(ostream&) override;
		void pairAll(T a1,T a2,int a3);/////HERSEYI ALIP PAIRCLASS IN ICINE ATAR
		void pairMap(T a1,T a2,int a3);////AYNI BIGRAM DEGERLERINI ALMAZ
		~BigramDyn();//////DESTRUCTOR
	private:
		int dataType;
		pairClass<T> *pairAllPtr;////HER BIGRAM VARDIR
		pairClass<T> *pairMapPtr;///AYNI BIGRAM DEGERLERINI ALMAZ
		int pairSize;/////pairAllPtr ICIN SIZE
		int pairIndex;////pairAllPtr ICIN INDEX YANI DOLU OLAN ALAN
		int pairMapSize;/////pairMapPtr ICIN SIZE
		int pairMapIndex;////pairMapPtr ICIN INDEX YANI DOLU OLAN ALAN


};

#endif /* BIGRAMDYN_H */

