/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


import java.util.AbstractCollection;
import java.util.Iterator;

/**
 *
 * @author ORHAN
 * @param <E>
 */
public abstract class myAbstractCollection<E> extends AbstractCollection<E> {
    
    
    
    
    
    /**
     *
     * @param base
     * @param ekle
     * @return
     */
    public AbstractCollection <E> appendAnything(AbstractCollection <E> base,AbstractCollection <E> ekle){
        Iterator<E> iter;
        
        iter = ekle.iterator();
        E temp;
        
        while(iter.hasNext()){
            if( base.add( iter.next() ) ) {
                
            }
            
        }
        return base;
    }

    
}
