import java.util.ArrayList;

/**
 * Created by ORHAN on 21.03.2017.
 */
public class  StackA <E> extends  ArrayList <E> implements StackInterface <E> {
    private int size=0;

    @Override
    public boolean isEmpty() {
        if(size<0)
            return true;
        return false;
    }

    @Override
    public E push(E obj) {
        ++size;
        add(obj);
        return  obj;
    }

    @Override
    public E pop() throws Exception {
        E temp;
        if(size<=0)
            throw new Exception("No elements left");

        else{
            temp=get(size-1);

            remove(size-1);
            --size;
            return temp;
        }

    }

    @Override
    public int size() {
        return size;
    }
}
