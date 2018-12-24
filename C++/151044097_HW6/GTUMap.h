//
// Created by ORHAN on 12.12.2017.
//

#ifndef HW6_GTUMAP_H
#define HW6_GTUMAP_H

#include "GTUSet.h"
#include <utility>
template <class K,class V>
class GTUMap: public GTUSet<std::pair<K,V>>{

public:


     V& operator[] (const K& k);


};


#endif //HW6_GTUMAP_H
