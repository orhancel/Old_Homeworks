/**
 * Created by ORHAN on 15.11.2018.
 */

public class Eurasia_Factory extends PlaneFactory {
    @Override
    Plane createPlane(String type) {
        Plane tmp;
        if(type.equals("Domestic flights")){
            tmp=new TPX_100();
            tmp.setInjection(new Turbofan());
            tmp.setSeating_cover(new Linen());
            return tmp;
        }

        else if(type.equals("Domestic and short international flights"))
        {
            tmp=new TPX_200();
            tmp.setInjection(new Turbofan());
            tmp.setSeating_cover(new Linen());
            return tmp;
        }
        else if(type.equals("Transatlantic flights"))
        {
            tmp=new TPX_300();
            tmp.setInjection(new Turbofan());
            tmp.setSeating_cover(new Linen());
            return tmp;
        }

        return null;
    }
}
