package hw7;

/**
 * Created by ORHAN on 18.12.2017.
 * @param <T>
 */

public class GTUSet<T> implements GTUSetInt<T> {

    /**
     *An Array of object where we hold all elements of the Set.
     * We cast it to generic data type we are given when class is constructed.
     */
    protected Object[] SetArray;

    /**
     *Current size of the Set Array.Where it's last index at.
     */
    protected int size;

    /**
     *Current capacity.If size reaches capacity we resize it by deleting and 
     * reallocating the Set array.
     */
    protected int max_Size;
    
    
    @Override
    public GTUSetInt<T> intersection(GTUSetInt<T> other){

        GTUIterator it=other.begin();
        GTUSet<T> intersect=new GTUSet<>();
        for(int i=0;i<size;i++){
            while (it.hasNext()) {
                if(SetArray[i].equals( it.next() )){
                    intersect.insert((T) SetArray[i]);

                    break;
                }
            }
            it=other.begin();
        }

        return intersect;

    }



    GTUSet(){
        SetArray= (T[]) new Object[10];
        size=0;
        max_Size=10;

    }

    @Override
    public boolean empty() {
        if(size==0)
            return true;

        return false;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public int max_size() {
        return max_Size;
    }

    @Override
    public void insert(T e) {

        if(count(e)==1)
            return;

        if(max_Size==0){
            max_Size=10;
            SetArray=(T[]) new Object[max_Size];
        }

        SetArray[size]=e;
        size++;


        if(size >= max_Size){
            Object[] temp = (T[]) new Object[size];
            for(int i=0;i<size;i++)
                temp[i]=SetArray[i];

            max_Size*=2;
            SetArray=null;
            SetArray=(T[]) new Object[max_Size];

            for(int i=0;i<size;i++)
                SetArray[i]=temp[i];

        }


    }



    @Override
    public void erase(T e) {

        Object[] temp = (T[]) new Object[size];
        int count=0;
        for(int i=0;i<size;i++){
            if(!e.equals(SetArray[i])){

                temp[count]=SetArray[i];
                count++;
            }
        }

        if(count!=size){
            for(int i=0;i<count;i++){
                SetArray[i]=temp[i];
            }
            size--;
        }


    }

    @Override
    public void clear() {
        size=0;
        max_Size=0;
        SetArray=null;
    }

    @Override
    public GTUIterator<T> find(T e) {
        GTUIterator<T> temp =new GTUIterator<>();
        temp.Set_Arr=  SetArray;

        temp.size=size;



        for(int i=0;i<size;i++){
            if(e.equals(SetArray[i])){
                temp.current= (T) SetArray[i];
                temp.index=i;
                return temp;
            }
        }
        return null;
    }

    @Override
    public int count(T e) {

        for (int i=0;i<size;i++){

            if(e.equals(SetArray[i])){
                return 1;
            }
        }


        return 0;
    }

    @Override
    public GTUIterator<T> begin() {

        GTUIterator<T> temp =new GTUIterator<>();
        temp.Set_Arr=  SetArray;
        temp.current= (T) SetArray[0];
        temp.size=size;
        temp.index=0;
        return temp;

    }

    @Override
    public GTUIterator<T> end() {

        GTUIterator<T> temp =new GTUIterator<>();
        temp.Set_Arr=  SetArray;
        temp.current= (T) SetArray[0];
        temp.size=size;
        temp.index=size-1;
        return temp;

    }
}

