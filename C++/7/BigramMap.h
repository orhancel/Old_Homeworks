/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BigramMap.h
 * Author: user
 *
 * Created on December 23, 2016, 4:22 PM
 */
#include <iostream>
#include <fstream>
#include <utility>
#include "Bigram.h"
#include "myException.h"
#include <vector>
#include <map>
using namespace std;

#ifndef BIGRAMMAP_H
#define BIGRAMMAP_H


template <class T>

class BigramMap:public Bigram<T>{
    public:
        BigramMap(){dataType=1;};
        BigramMap(int);
        void readFile( string) override ;
        int numGrams() override ;
        int numOfGrams(T,T) override  ;
        pair <T,T> maxGrams() override ;
        void print(ostream&) override;
	
    private:
       
        vector<pair<T,T>> keys;
        int dataType;
       
        map<pair<T,T>,int> seqMap;
        
        
};


#endif /* BIGRAMMAP_H */

