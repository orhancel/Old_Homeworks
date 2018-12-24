//
// Created by ORHAN on 12.12.2017.
//

#ifndef HW6_GTUSET_H
#define HW6_GTUSET_H

#include <stdexcept>
#include "GTUSetBase.h"
#include <vector>
using namespace std;
template <class T>
class GTUSet:public GTUSetBase<T>{
public:

    GTUSet();
    bool empty() override;

    int max_size() override ;

    void insert(T element) override;

    void erase(T element) override;

    void clear() override;

    GTUIterator<T> find(const T& element ) const override ;

    int count(const T& element) const override ;

    GTUIterator<T>  begin() const override;

    GTUIterator<T> end() const override;

    int size() override;

protected:
    shared_ptr<T> SetArray;
    int Container=10;
    int Size=0;

};

#endif //HW6_GTUSET_H
