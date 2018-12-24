package hw7;

/**
 * Created by ORHAN on 20.12.2017.
 */
import javafx.util.Pair;

/**
 *
 * @author ORHAN
 * @param <K> Generic type for Keys.
 * @param <V> Generic type for Values.
 */
public class  GTUMap<K, V> extends GTUSet< Pair <K, V> >   {


    @Override
    public int count(Pair <K, V> e){

        if(at(e.getKey())==null){
            return 0;
        }
        return 1;

    }

    /**
     * Finds and returns value of the given Key of a Pair object.
     * @param k Key variable of a Pair object.
     * @return value of the correspondind key.
     */
    public V at(K k){

        for(int i=0;i<size;i++){

           if(((Pair<K,V>) SetArray[i]).getKey().equals(k)) {
               return ((Pair<K,V>) SetArray[i]).getValue();
           }
        }
        return null;

    }

}
