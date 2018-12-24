import java.util.ArrayList;

/**
 * Created by ORHAN on 15.11.2018.
 */
public abstract class Plane {
    private String name;
    private String engine;
    private String skeleton;
    private Integer seats;
    private Engine_injection injection;
    private Seating_cover seating_cover;

    protected void setEngine(String set){
        engine=set;
    }
    protected void setSkeleton(String set){
        skeleton=set;
    }
    protected void setSeats(Integer set){
        seats=set;
    }
    protected void setName(String set){
        name=set;
    }
    protected void setInjection(Engine_injection set){
        System.out.println(set.getName()+" has placed.");
        injection=set;}
    protected void setSeating_cover( Seating_cover set ){
        System.out.println(set.getName()+" covers has placed.");
        seating_cover=set; }


    protected String getEngine(){return engine;}
    protected String getSkeleton(){return skeleton;}
    protected Integer getSeats(){return seats;}
    protected String getName(){return name;}
    protected Engine_injection getInjection(){return injection;}
    protected Seating_cover getSeating_cover(){return seating_cover;}

    protected void constructSkeleton(){
        System.out.println(skeleton+" skeleton constructed.");
    }
    protected void placeEngines(){
        System.out.println(engine+" placed.") ;
    }
    protected void placeSeats(){
        System.out.println(seats.toString()+" seats placed.");
    }


}
