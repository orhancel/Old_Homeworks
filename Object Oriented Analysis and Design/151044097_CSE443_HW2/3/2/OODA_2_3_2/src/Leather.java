/**
 * Created by ORHAN on 15.11.2018.
 */
public class Leather implements Seating_cover {

    private String name = null;

    public Leather(){
        name="Leather";
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
