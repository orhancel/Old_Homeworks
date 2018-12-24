//
// Created by ORHAN on 14.12.2017.
//
#include "GTUMap.h"

template <class K,class V>

V& GTUMap<K,V>::operator[] (const K& k){

    for (int i = 0; i <GTUSet<pair<K,V>>::Size ; ++i) {
        if(GTUSet<pair<K,V>>::SetArray.get()[i].first==k)
            return GTUSet<pair<K,V>>::SetArray.get()[i].second;

    }


};

