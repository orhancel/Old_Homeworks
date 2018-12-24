public class Main {

    public static void main(String[] args) {


        Base_suit dec_suit=new Base_dec();
        dec_suit=new Flamethrower(dec_suit);
        dec_suit=new AutoRifle(dec_suit);

        System.out.println(dec_suit.get_Description());
        System.out.println(dec_suit.get_Cost()+"k");
        System.out.println(dec_suit.get_weight()+"kg");
        System.out.println();

        Base_suit tor_suit=new Flamethrower(new RocketLauncher(new Base_tor()));

        System.out.println(tor_suit.get_Description());
        System.out.println(tor_suit.get_Cost()+"k");
        System.out.println(tor_suit.get_weight()+"kg");
        System.out.println();

        Base_suit ora_suit=new Flamethrower(new AutoRifle(new RocketLauncher(new Base_ora())));

        System.out.println(ora_suit.get_Description());
        System.out.println(ora_suit.get_Cost()+"k");
        System.out.println(ora_suit.get_weight()+"kg");


    }
}
