import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

/**
 * Created by ORHAN on 23.03.2017.
 */
public class StackD <E> implements StackInterface <E> {

    int size;
    Queue <E> liste;

    StackD(){
        size=0;
        liste=new LinkedList<>();
    }


    @Override
    public boolean isEmpty() {
        if(size<=0){
            return true;
        }
        return false;
    }

    @Override
    public E push(E obj) {
        liste.add(obj);
        ++size;
        return obj;
    }
    @Override
    public E pop() throws Exception {



        if(size<=0)
            throw new Exception("No elements left");

        ArrayList<E> temp=new ArrayList<>();
        while(size>0){
            temp.add(liste.remove());
            --size;

        }
        E data=temp.get(temp.size()-1);
        temp.remove(temp.size()-1);
        for(int i=0;i<temp.size();++i){
            ++size;
            liste.add(temp.get(i));
        }



        return data;
    }

    @Override
    public int size() {
        return size;
    }
}
