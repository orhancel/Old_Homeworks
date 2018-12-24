import java.util.LinkedList;
import java.lang.String;
/**
 * Created by ORHAN on 23.03.2017.
 */
public class priorityQueueA <E> extends LinkedList <E> {








    public  String deleteMin(){

        E min = get(0);

        for(int i=1;i<size();++i){
            if(min.toString().compareTo(get(i).toString())>0   ) {
                min = get(i);
            }
        }
        remove(min);

        return min.toString();


    }


}
