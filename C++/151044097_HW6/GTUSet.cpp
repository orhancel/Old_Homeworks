//
// Created by ORHAN on 12.12.2017.
//

#include "GTUSet.h"


template <class T>
GTUSet<T>::GTUSet(){

    shared_ptr<T> temp(new T[10], default_delete<T[]>());
    SetArray=temp;
    Container=10;
}


template <class T>
bool GTUSet<T>::empty() {

    if(Size==0)
        return true;
    else
        return false;
};

template <class T>
int GTUSet<T>::max_size()  {
    return Container;
};


template <class T>
void GTUSet<T>::insert(T element) {

    for (int i = 0; i < Size; ++i) {
        if(SetArray.get()[i]==element)
            throw invalid_argument("Element already in the set");
        return;
    }
    SetArray.get()[Size]=element;
    Size++;

    if(Size==Container){
        T* temp=new T[Size];
        for (int i =0;i<Size;i++){

            temp[i]=SetArray.get()[i];
        }
        shared_ptr<T> shareTemp (new T[Size*2], default_delete<T[]>());
        SetArray=shareTemp;
        for (int i=0;i<Size;i++){
            SetArray.get()[i]=temp[i];
        }
        delete [] temp;
        Container=Size*2;
    }
}

template <class T>
void GTUSet<T>::erase(T element)  {
    shared_ptr<T> temp(new T[Size], default_delete<T[]>());
    int count=0;
    for(int i=0;i<Size;i++){

        if(!(SetArray.get()[i]==element)){
            temp.get()[count]=SetArray.get()[i];
            count++;
        }


    }
    SetArray.reset();
    SetArray=temp;
    Size=count;

}

template <class T>
void GTUSet<T>::clear()  {
    SetArray.reset();
    Size=0;
    GTUSet();

}

template <class T>
GTUIterator<T> GTUSet<T>::find(const T& element ) const  {
    GTUIterator<T> temp;
    for (int i = 0; i < Size; ++i) {
        if(element==SetArray.get()[i]){
            temp.setItIndex(&(SetArray.get()[i]));
            return temp;
        }

    }
    temp.setItIndex(&(SetArray.get()[Size-1]));
    return temp;


}

template <class T>
int GTUSet<T>::count(const T& element) const  {

    for (int i = 0; i < Size; ++i) {
        if(element==SetArray.get()[i])
        return 1;
    }

    return 0;
}

template <class T>
GTUIterator<T>  GTUSet<T>::begin() const  {
    GTUIterator<T> temp;
    temp.setItIndex(&(SetArray.get()[0]));

    return temp;
}

template <class T>
GTUIterator<T> GTUSet<T>::end() const  {
    GTUIterator<T> temp;
    temp.setItIndex(&(SetArray.get()[Size-1]));

    return temp;
};

template <class T>
int GTUSet<T>::size() {
    return Size;
};










