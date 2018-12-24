//
// Created by ORHAN on 12.12.2017.
//

#ifndef HW6_GTUSETBASE_H
#define HW6_GTUSETBASE_H
#include <iostream>
#include <cstdio>
#include <memory>
#include "GTUIterator.h"
using namespace std;



template <class T>
class GTUSetBase{

public:

    virtual bool empty()=0;

    virtual int size()=0;

    virtual int max_size()=0;

    virtual void insert(T)=0;
    virtual void erase(T)=0;
    virtual void clear()=0;

    virtual GTUIterator<T>  find(const T&) const =0 ;



    virtual int count(const T&) const =0 ;

    virtual  GTUIterator<T>  begin() const =0 ;


    virtual  GTUIterator<T>  end() const =0 ;






};

#endif //HW6_GTUSETBASE_H
