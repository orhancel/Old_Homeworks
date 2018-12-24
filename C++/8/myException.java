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
public class myException extends Exception  {
       String error;
        myException(String line){
            error=line;
        }
        
        
        @Override
        public String toString() {
            return error;
        }
     
}
