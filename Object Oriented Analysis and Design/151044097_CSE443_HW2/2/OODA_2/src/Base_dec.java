/**
 * Created by ORHAN on 15.11.2018.
 */
public class Base_dec implements Base_suit {
    @Override
    public String get_Description() {
        return "Dec suit";
    }

    @Override
    public double get_Cost() {
        return 500;
    }

    @Override
    public double get_weight() {
        return 25;
    }
}
