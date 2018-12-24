import java.util.LinkedList;

/**
 * Created by ORHAN on 23.03.2017.
 */
public class priorityQueueB <E> {

    private LinkedList <E> liste;
    private int size=0;

    priorityQueueB(){
        liste=new LinkedList<>();


    }

    public void add(E obj){
        ++size;
        liste.add(obj);

    }
    public boolean isEmpty(){


        return liste.isEmpty();
    }


    public  String deleteMin(){

        E min = liste.get(0);

        for(int i=1;i<size();++i){
            if(min.toString().compareTo(liste.get(i).toString())>0   ) {
                min = liste.get(i);
            }
        }
        liste.remove(min);
        --this.size;
        return min.toString();


    }

    public int size(){
        return size;
    }




}
