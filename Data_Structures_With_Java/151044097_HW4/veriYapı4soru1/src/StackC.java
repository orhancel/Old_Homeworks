/**
 * Created by ORHAN on 21.03.2017.
 */
public class StackC <E> implements StackInterface<E> {
    private node<E> head;
    private node<E> tail;
    private int size=0;



    @Override
    public boolean isEmpty() {

        return size <= 0;
    }

    @Override
    public E push(E obj) {
        if(head==null){
            ++size;
            head=new node<>(obj);

            tail=head;
        }
        else{

            ++size;
            tail.next=new node<>(obj);
            tail=tail.next;
        }
        return obj;

    }



    @Override
    public E pop() throws Exception {

        if(size==0){
            throw new Exception("No elements left");
        }
        if(size==1){
            E temp=head.data;
            head=null;
            --size;
            return temp;



        }

        node <E> current=head;
        while(current.next!=tail && current.next!=null)
        {
            current=current.next;
        }

        node <E> temp=current.next;
        current.next=null;
        tail=current;
        --size;
        return   temp.data;

    }

    @Override
    public int size() {
        return size;
    }

    private class node<T>{///NODE  SUBCLASS OF SINGLE LINKED LIST.
        T data;
        node<T> next;
        node(Object o){
            data=(T) o;
        }

    }


}
