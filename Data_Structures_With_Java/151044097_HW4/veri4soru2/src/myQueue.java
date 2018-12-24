
import java.util.ListIterator;
import java.util.Queue;

/**
 * Created by ORHAN on 23.03.2017.
 */

public class myQueue <E> extends KWLinkedList <E> {
    private ListIterator <E> iterStart;
    private ListIterator <E> iterEnd;




    public void reverser() {
        iterStart=listIterator();
        iterEnd=listIterator();
        E tempE=null;
        E tempS;
        int size=0;
        while (iterEnd.hasNext()){
            size+=1;
            tempE=iterEnd.next();
        }
        iterEnd.previous();
        size*=0.5;
        while(size>0){
            tempS=iterStart.next();
            iterStart.set(tempE);
            iterEnd.set(tempS);
            tempE=iterEnd.previous();
            --size;
        }


    }

    public void reverseQueue (Queue<E> list){

        E data;

        if(list.size() ==0){
            return ;
        }
        else{
            data=list.remove();
            reverseQueue(list);
            list.add(data);

        }


    }




}
