//
// Created by ORHAN on 14.12.2017.
//

#ifndef HW6_GTUITERATOR_H
#define HW6_GTUITERATOR_H


template <class T>
class GTUIterator{

public:
     T& operator *()  ;

    bool operator==(const GTUIterator &other) const ;
    GTUIterator<T>& operator++();

    GTUIterator<T> operator++(int);


    bool operator!=(const GTUIterator &other) const ;

    T *getItIndex() const ;

    void setItIndex(T *itIndex) ;

    GTUIterator<T>& operator=(const GTUIterator<T>& other);


    GTUIterator<T> * operator->();

protected:
    T* itIndex;

};



#endif //HW6_GTUITERATOR_H
