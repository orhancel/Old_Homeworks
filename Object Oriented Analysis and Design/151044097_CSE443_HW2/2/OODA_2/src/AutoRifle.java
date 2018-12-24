/**
 * Created by ORHAN on 15.11.2018.
 */
public class AutoRifle extends Suit_Mods  {
    public AutoRifle(Base_suit new_suit) {
        super(new_suit);

        System.out.println("Adding AutoRifle");
    }

    public String get_Description(){

        return suit.get_Description()+" AutoRifle";
    }

    public double get_Cost(){
        return suit.get_Cost()+30;
    }

    public double get_weight() {
        return suit.get_weight() + 1.5;
    }

}
