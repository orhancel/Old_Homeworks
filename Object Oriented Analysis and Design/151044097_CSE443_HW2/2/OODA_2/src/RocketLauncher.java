/**
 * Created by ORHAN on 15.11.2018.
 */

public class RocketLauncher extends Suit_Mods  {
    public RocketLauncher(Base_suit new_suit) {
        super(new_suit);

        System.out.println("Adding RocketLauncher");
    }

    public String get_Description(){

        return suit.get_Description()+" RocketLauncher";
    }

    public double get_Cost(){
        return suit.get_Cost()+150;
    }

    public double get_weight() {
        return suit.get_weight() + 7.5;
    }

}
