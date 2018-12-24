/**
 * Created by ORHAN on 15.11.2018.
 */
public class PlaneFactory {


    protected Plane makePlane(String type){

        Plane plane;
        plane=createPlane(type);
        plane.constructSkeleton();
        plane.placeEngines();
        plane.placeSeats();

        return plane;
    }


    private Plane createPlane(String type){


        if(type.equals("Domestic flights"))
            return new TPX_100();
        else if(type.equals("Domestic and short international flights"))
            return new TPX_200();
        else if(type.equals("Transatlantic flights"))
            return new TPX_300();

        return null;

    }



}
