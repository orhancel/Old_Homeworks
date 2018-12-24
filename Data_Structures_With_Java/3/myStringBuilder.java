/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


import java.util.Iterator;

/**
 *
 * @author ORHAN
 */
public class myStringBuilder {
    
    private MyLinkedList<String> list;
    
    /**
     *
     * @param ap 
     */
    
    myStringBuilder(){
        list=new MyLinkedList<>();//INITIALIZE THE LINKED LIST
        
        
    }

    /**
     *
     * @param ap
     */
    public void append(Object  ap){
        
        
        list.add( ap.toString() );///LIST APPENDER
        
    }
    
    /**
     *
     * @return
     */
    public String reverse(){///CALLS THE RECURSIVE STRING REVERSER METHOD
        return list.reverseToString();
    }
    
    /**
     *
     * @return
     */
    public String toStringList(){///LinkedList ToString method
        return list.toString();             
    }
    
    /**
     *
     * @return
     * @throws java.lang.Exception
     */
    public String toStringGet() throws Exception{
        String temp="";
        for(int i=0;i<list.size;++i){
            temp+=list.get(i);
            temp+=" ";
        }
            
        return temp;
        
                
    }

    /**
     *
     * @return
     */
    public String toStringIterator(){
        Iterator <String> iter=list.iterator();
        String temp="";
        while(iter.hasNext()){
            temp+=iter.next();
            temp+=" ";
        }
        return temp;
    }
    
}
