/**
 * Created by ORHAN on 15.11.2018.
 */
public abstract class Suit_Mods implements Base_suit{

    protected Base_suit suit;

    public Suit_Mods(Base_suit new_suit){
        suit=new_suit;
    }

    public String get_Description(){

        return suit.get_Description();
    }

    public double get_Cost(){
        return suit.get_Cost();
    }

    public double get_weight() {
        return suit.get_weight();
    }

}
