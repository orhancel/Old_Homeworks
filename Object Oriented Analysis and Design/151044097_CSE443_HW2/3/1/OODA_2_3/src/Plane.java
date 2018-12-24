/**
 * Created by ORHAN on 15.11.2018.
 */
public abstract class Plane {
    private String name;
    private String engine;
    private String skeleton;
    private Integer seats;

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

    protected String getEngine(){return engine;}
    protected String getSkeleton(){return skeleton;}
    protected Integer getSeats(){return seats;}
    protected String getName(){return name;}

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
