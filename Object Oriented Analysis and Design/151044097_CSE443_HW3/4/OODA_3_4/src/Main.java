public class Main {

    public static void main(String[] args) {
        //System.out.println("Hello World!");

        Discreate_Transform dft=new DFT();
        Discreate_Transform dct=new DCT();

        dft.Procedure();
        System.out.println("///////////////////");
        dct.Procedure();

    }
}
