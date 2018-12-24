/**
 * Created by ORHAN on 15.11.2018.
 */
public class Base_ora implements Base_suit {

    public String get_Description() {
        return "Ora suit";
    }

    @Override
    public double get_Cost() {
        return 1500;
    }

    @Override
    public double get_weight() {
        return 30;
    }
}
