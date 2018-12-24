/**
 * Created by ORHAN on 15.11.2018.
 */
public class Velvet implements Seating_cover {

    private String name = null;

    public Velvet(){
        name="Velvet";
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
