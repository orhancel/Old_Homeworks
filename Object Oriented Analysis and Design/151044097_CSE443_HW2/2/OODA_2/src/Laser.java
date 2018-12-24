/**
 * Created by ORHAN on 15.11.2018.
 */

    public class Laser extends Suit_Mods  {
        public Laser(Base_suit new_suit) {
            super(new_suit);

            System.out.println("Adding Laser");
        }

        public String get_Description(){

            return suit.get_Description()+" Laser";
        }

        public double get_Cost(){
            return suit.get_Cost()+200;
        }

        public double get_weight() {
            return suit.get_weight() + 5.5;
        }

    }
