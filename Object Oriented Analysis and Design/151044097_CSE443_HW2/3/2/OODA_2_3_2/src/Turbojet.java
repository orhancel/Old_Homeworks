/**
 * Created by ORHAN on 15.11.2018.
 */
public class Turbojet implements Engine_injection {
    private String name = null;
    public Turbojet(){
        name="Turbojet";
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
