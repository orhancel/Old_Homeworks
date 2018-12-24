/**
 * Created by ORHAN on 15.11.2018.
 */
public class Base_tor implements Base_suit{

    public String get_Description() {
        return "Tor suit";
    }

    @Override
    public double get_Cost() {
        return 5000;
    }

    @Override
    public double get_weight() {
        return 50;
    }
}
