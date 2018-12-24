package hw7;
import javafx.util.Pair;

/**
 *
 * @author ORHAN
 */
public class Main {

    /**
     *For terminal inputs.
     * @param args
     */
    public static void main(String[] args) {

        GTUSet<Integer> temp=new GTUSet<Integer>();
        System.out.println("First Set");
        //System.out.println("-------------");

        temp.insert(10);
        temp.insert(20);
        temp.insert(30);
        temp.insert(40);
        temp.insert(40);
        temp.insert(40);
        temp.insert(30);
        System.out.println("-------------");
        GTUIterator iter=temp.begin();

        while (iter.hasNext()){
            System.out.println(iter.next());
        }
        System.out.println("-------------");
        GTUSet<Integer> temp2=new GTUSet<>();
        System.out.println("Second Set");
        temp2.insert(10);
        temp2.insert(30);
        temp2.insert(50);
        temp2.insert(60);

        iter=temp2.begin();

        while (iter.hasNext()){
            System.out.println(iter.next());
        }
        System.out.println("-------------");
        GTUSet<Integer> inter= (GTUSet<Integer>) temp.intersection(temp2);//Intersect
        iter=inter.end();                                              //iterator end
        System.out.println("Print Intersection reverse");

        while (iter.hasPrevious()){
            System.out.println(iter.previous());
        }
        System.out.println("Print intersection");
        while (iter.hasNext()){
            System.out.println(iter.next());
        }
        System.out.println("-------------");




        GTUMap<Integer,String > mapTemp=new GTUMap<>();

        mapTemp.insert( new Pair<Integer,String>( 1,"a") );
        mapTemp.insert( new Pair<Integer,String>( 1,"h") );
        mapTemp.insert( new Pair<Integer,String>( 1,"x") );
        mapTemp.insert( new Pair<Integer,String>( 1,"a") );
        mapTemp.insert( new Pair<Integer,String>( 1,"a") );

        mapTemp.insert( new Pair<Integer,String>( 2,"b") );
        mapTemp.insert( new Pair<Integer,String>( 3,"c") );
        mapTemp.insert( new Pair<Integer,String>( 4,"d") );




        GTUIterator it=mapTemp.begin();

        while (it.hasNext())
            System.out.println(it.next());

        System.out.println("Find the value at key 3");

        System.out.println(mapTemp.at(3));

        System.out.println("Clear and check empty");
        temp.clear();

        System.out.println(temp.empty());

        temp.insert(1000);
        temp.insert(200);

        iter=temp.begin();

        System.out.println(iter.next());

        System.out.println("erase 1000");

        temp.erase(1000);
        iter=temp.begin();
        System.out.println(iter.next());




    }
}
