/**
 * Created by ORHAN on 15.11.2018.
 */
public class Linen implements Seating_cover {

    private String name = null;

    public Linen(){
        name="Linen";
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
