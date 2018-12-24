/**
 * Created by ORHAN on 15.11.2018.
 */
public abstract class PlaneFactory {


    protected Plane makePlane(String type){

        Plane plane;
        plane=createPlane(type);
        plane.constructSkeleton();
        plane.placeEngines();
        plane.placeSeats();
       // plane.placeMods();

        return plane;
    }


    abstract Plane createPlane(String type);


}
