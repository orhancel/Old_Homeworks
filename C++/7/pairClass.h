/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pairClass.h
 * Author: user
 *
 * Created on December 24, 2016, 7:39 AM
 */

#ifndef PAIRCLASS_H
#define PAIRCLASS_H
template <class T>

class pairClass{

	public:
		pairClass(){
		
		};
		pairClass(T a1,T a2,int a3){
		left=a1;
		right=a2;
		value=a3;		
		};
		
		T  getLeft()const{
			return left;
		};
		T getRight()const{
			return right;		
		};
		int getValue()const{
			return value;
		};
		void setValue(int set){
			value=set;
		}
	private:
		
		T left;
		T right;
		int value;/////KAC TANE BIGRAM OLDUGUNU TUTMAK ICIN


};


#endif /* PAIRCLASS_H */

