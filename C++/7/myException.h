/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   myException.h
 * Author: user
 *
 * Created on December 24, 2016, 4:38 AM
 */
#include <exception>
#include <iostream>

using namespace std;
#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H
class myException:public exception{
	public:
		myException(){
		
		
		};
		myException(const char* error){
			line=error;
		
		};
		const char* what()const throw() override{
			return line;
		};
		
	private:
		const char* line;


};


#endif /* MYEXCEPTION_H */

