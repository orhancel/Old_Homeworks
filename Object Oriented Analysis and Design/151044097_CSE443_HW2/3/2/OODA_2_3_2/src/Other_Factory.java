/**
 * Created by ORHAN on 15.11.2018.
 */

public class Other_Factory extends PlaneFactory {
    @Override
    Plane createPlane(String type) {
        Plane tmp;
        if(type.equals("Domestic flights")){
            tmp=new TPX_100();
            tmp.setInjection(new Geared_Turbofan());
            tmp.setSeating_cover(new Leather());
            return tmp;
        }

        else if(type.equals("Domestic and short international flights"))
        {
            tmp=new TPX_200();
            tmp.setInjection(new Geared_Turbofan());
            tmp.setSeating_cover(new Leather());
            return tmp;
        }
        else if(type.equals("Transatlantic flights"))
        {
            tmp=new TPX_300();
            tmp.setInjection(new Geared_Turbofan());
            tmp.setSeating_cover(new Leather());
            return tmp;
        }

        return null;
    }
}
