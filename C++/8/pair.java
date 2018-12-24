/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javaapplication3;

//import java.util.Objects;

import java.util.Objects;


/**
 *
 * @author ORHAN
 * @param <T>
 * @param <K>
 */
public class pair<T,K>  {
    public final T first;
    public final K second;
    public  pair( T t, K k ) {
        first=t;
        second=k;
    }



    @Override
    public String toString() {
        return "["+first+","+second+"]";
    }

    @Override
    public int hashCode() {
        int hash = 5;
        hash = 97 * hash + Objects.hashCode(this.first);
        hash = 97 * hash + Objects.hashCode(this.second);
        return hash;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        final pair<?, ?> other = (pair<?, ?>) obj;
        if (!Objects.equals(this.first, other.first)) {
            return false;
        }
        return Objects.equals(this.second, other.second);
    }
     
}
