public class Main {

    public static void main(String[] args) {

    PlaneFactory plane_factory=new PlaneFactory();
    Plane plane=plane_factory.makePlane("Domestic flights");
    System.out.println();
    plane_factory=new PlaneFactory();
    plane=plane_factory.makePlane("Domestic and short international flights");
    System.out.println();
    plane_factory=new PlaneFactory();
    plane=plane_factory.makePlane("Transatlantic flights");


    }
}
