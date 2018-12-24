/**
 * Created by ORHAN on 15.11.2018.
 */
public class Turbofan implements Engine_injection {
    private String name = null;
    public Turbofan(){
        name="Turbofan";
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
