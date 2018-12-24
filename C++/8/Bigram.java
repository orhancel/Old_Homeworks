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
interface Bigram<T>{
    void readFile(String line)throws myException;
    int numGrams();

    int numOfGrams (T x,T y);
    
        
     
}
