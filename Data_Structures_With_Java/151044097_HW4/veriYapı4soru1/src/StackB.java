import java.util.ArrayList;

/**
 * Created by ORHAN on 21.03.2017.
 */
public class StackB <E> implements StackInterface <E> {

    private ArrayList<E> liste;
    private int size;
    StackB(){
        liste=new ArrayList<E>();
        size=0;
    }

    @Override
    public boolean isEmpty() {
        return liste.isEmpty();
    }

    @Override
    public E push(E obj) {
        liste.add(obj);
        ++size;
        return  obj;
    }

    @Override
    public E pop() throws Exception {
        E temp;
        if(size>0){

            temp=liste.get(size-1);
            liste.remove(size-1);
            --size;
            return temp;
        }
        throw new Exception("No elements left");


    }

    @Override
    public int size() {
        return size;
    }
}
