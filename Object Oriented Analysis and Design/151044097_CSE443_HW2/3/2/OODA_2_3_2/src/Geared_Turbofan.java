/**
 * Created by ORHAN on 15.11.2018.
 */
public class Geared_Turbofan implements Engine_injection {

    private String name = null;
    public Geared_Turbofan(){
        name="Geared Turbofan";
    }

    @Override
    public void setName(String set) {
        name=set;
    }

    @Override
    public String getName() {
        return name;
    }


}
