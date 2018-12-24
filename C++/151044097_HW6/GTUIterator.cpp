//
// Created by ORHAN on 14.12.2017.
//
#include "GTUIterator.h"
template <class T>
T& GTUIterator<T>::operator *()  {

    return *itIndex;

}


template <class T>
bool GTUIterator<T>::operator==(const GTUIterator &other) const {
    return itIndex == other.itIndex;
}


template <class T>
GTUIterator<T>& GTUIterator<T>:: operator++()
{
    this->itIndex=itIndex+1;
    return *this;
}
template <class T>
GTUIterator<T> GTUIterator<T>::operator++(int)
{
    GTUIterator<T> tmp  =*this;
    this->itIndex=itIndex+1;
    return tmp;
}

template <class T>
bool GTUIterator<T>::operator!=(const GTUIterator &other) const {
    return !(other == *this);
}

template <class T>
T* GTUIterator<T>:: getItIndex() const {
    return itIndex;
}

template <class T>
void GTUIterator<T>:: setItIndex(T *itIndex) {
    GTUIterator::itIndex = itIndex;
}

template <class T>
GTUIterator<T>& GTUIterator<T>:: operator=(const GTUIterator<T>& other)
{
    if (this == &other){
        return *this;
    }

    this->itIndex =other.itIndex;

    return *this;
}

template <class T>
GTUIterator<T>* GTUIterator<T>:: operator->(){

    return this;
}