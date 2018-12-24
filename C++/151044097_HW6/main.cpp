#include <iostream>

#include "GTUMap.h"
#include "GTUSet.cpp"
#include "GTUMap.cpp"
#include "GTUIterator.cpp"
#include <iostream>
using namespace std;


template <class T >
shared_ptr< GTUSetBase<T> > setIntersection (const GTUSetBase <T>&  first, const GTUSetBase <T>& second){

    shared_ptr< GTUSetBase<T> > temp(new GTUSet<T> );

    for (auto iter_first=first.begin() ; iter_first!=first.end()  ; ++iter_first)
    {

        if(second.count((*iter_first))!= 0)
        {
            temp.get()->insert((*iter_first));
        }
    }
    auto iter_first=first.end();
    if(second.count((*iter_first))!= 0)
    {
        temp.get()->insert((*iter_first));
    }

    return temp;

}



int main() {

    GTUSet<int> x;

    try {
        x.insert(5);
        x.insert(1);
        x.insert(2);
        x.insert(3);

    }
    catch (const exception& e){
        cout<<e.what()<<endl;

    }


    GTUSet<int> z;

    z.insert(1);
    z.insert(3);
    z.insert(10);
    z.insert(20);
    z.insert(30);




    for (auto it=x.begin(); it!= x.end() ; it++) {///  SON ELEMAN PRİNT EDİLMEYECEK
        cout << *it << endl;
    }
    cout << *(x.end()) << endl;

    auto it=x.end();//SON ELEMAN

    cout<<"iter end "<<*it<<endl;

    it=x.begin();///İLK ELEMAN

    cout<<"iter begin "<<*it<<endl;

    it=x.find(2);///ELEMAN BULMA //Bulamazsa son elemanı return eder.
    cout<<"iter find  2  :"<<*it<<endl;

    cout<<"----------"<<endl;

    for (auto itZ=z.begin(); itZ!= z.end() ; itZ++) {///  SON ELEMAN PRİNT EDİLMEYECEK
        cout << *itZ << endl;
    }
    cout << *(z.end()) << endl;

    auto itZ=z.end();//SON ELEMAN

    cout<<"iter end "<<*itZ<<endl;

    itZ=z.begin();///İLK ELEMAN

    cout<<"iter begin "<<*itZ<<endl;

    itZ=z.find(1000);///ELEMAN BULMA //Bulamazsa son elemanı return eder.
    cout<<"iter find  1000  :"<<*itZ<<endl;
    cout<<"Bulunmaz ise son eleman return edilir"<<endl;

    cout<<"----------"<<endl;

    shared_ptr< GTUSetBase<int> > temp =setIntersection(x,z);///INTERSECTION SET

    auto iterator=temp.get()->begin();
    cout<<"intersection list" <<endl;
    for (int i = 0; i <temp.get()->size() ; ++i) {
        cout << (*iterator) <<  endl;
        iterator++;
    }

    cout<<"----------"<<endl;


    GTUMap<int,char> y;
    y.insert(pair<int,char>(5,'a'));
    y.insert(pair<int,char>(4,'b'));
    y.insert(pair<int,char>(3,'c'));
    y.insert(pair<int,char>(2,'d'));
    y.insert(pair<int,char>(1,'e'));

    for(auto iter=y.begin();iter!=y.end();iter++){
        cout <<"iter map key "<< (*iter).first ;
        cout<<"  iter map value "<<(*iter).second<<endl;
    }

    cout<<"----------"<<endl;

    auto iter=y.end();
    cout<<"iter END key "<<(*iter).first;
    cout<<"  iter END value "<<(*iter).second<<endl;

    iter=y.begin();

    cout<<"iter BEGIN map key "<<(*iter).first;
    cout<<"  iter BEGIN map value "<<(*iter).second<<endl;



    iter=y.find(pair<int,char>(2,'d'));

    cout<<"iter find key "<<(*iter).first;
    cout<<"  iter find value  "<<(*iter).second<<endl;
    cout<<"----------"<<endl;
    x.clear();
    y.clear();
    z.clear();
    if(!(x.begin().getItIndex()))
        cout<<"Set cleared"<<endl;







    return 0;
}