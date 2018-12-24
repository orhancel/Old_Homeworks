/**
 * Created by ORHAN on 15.11.2018.
 */
public class Flamethrower extends Suit_Mods  {
    public Flamethrower(Base_suit new_suit) {
        super(new_suit);

        System.out.println("Adding Flamethrower");
    }

    public String get_Description(){

        return suit.get_Description()+" Flamethrower";
    }

    public double get_Cost(){
        return suit.get_Cost()+50;
    }

    public double get_weight() {
        return suit.get_weight() + 2;
    }

}
