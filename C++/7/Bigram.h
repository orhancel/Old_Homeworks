/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bigram.h
 * Author: user
 *
 * Created on December 23, 2016, 4:21 PM
 */
#include <iostream>
using namespace std;
#ifndef BIGRAM_H
#define BIGRAM_H
template <class T>

class Bigram{
    public:
        virtual void readFile( string)=0;
        virtual int numGrams() =0;
        virtual int numOfGrams(T,T)=0;
        virtual pair<T,T> maxGrams() =0;
		friend ostream &operator <<(ostream& output,Bigram<T>& bigram){
		bigram.print(output);
		return output;
		};
		virtual void print(ostream&)=0;
		

};

#endif /* BIGRAM_H */

