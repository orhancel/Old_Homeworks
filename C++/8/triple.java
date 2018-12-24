/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javaapplication3;

/**
 *
 * @author ORHAN
 */
public class triple <T> {
    T [] first;
    T [] second;
    int [] value;
    int index;
    int Size;
    
    triple(int size){
        first=(T[])new Object[size];
        second=(T[])new Object[size];
        value=new int [size];
        index=0;
        Size=size;
    }
    public void add(T f,T s,int val){
        
        if(index<Size){
            
            first[index]=f;
            second[index]=s;
            value[index]=val;
            index+=1;
            
        }
    }
    public T getFirst(int i){
        return first[i];
    }
    public T getSecond(int i){
        return second[i];
    }
    public int getValue(int i){
        return value[i];
    }
    
    
}
