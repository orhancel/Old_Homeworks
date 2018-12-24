package hw7;

import java.security.cert.TrustAnchor;

/**
 * Created by ORHAN on 21.12.2017.
 * @param <T>
 */
public class GTUIterator<T> {

    T current;
    Object[] Set_Arr;
    int size;
    int index;

    /**
     *Checks if Set array has an element with bigger index number.
     * @return true if exists
     */
    public boolean hasNext(){
        if(index<size){
            return true;
        }
        return false;

    }

    /**
     *Checks if Set array has an element with lower index number.
     * @return true if exists
     */
    public boolean hasPrevious(){

        if(index>=0) {
            return true;
        }
        return false;


    }

    /**
     *Iterates to next object
     * @return a pointer to the element in the Set array.
     */
    public T next(){
        if(index==-1)
            index=0;
        index++;
        return (T) Set_Arr[index-1];
    }

    /**
     *Iterates to previous object
     * @return a pointer to the element in the Set array.
     */
    public T previous(){
        if(index==size)
            index=size-1;
        index--;
        return (T) Set_Arr[index+1];

    }
}
