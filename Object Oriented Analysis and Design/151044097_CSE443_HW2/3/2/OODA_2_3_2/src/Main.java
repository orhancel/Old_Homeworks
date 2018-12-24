public class Main {

    public static void main(String[] args) {

    PlaneFactory plane_factory=new Domestic_Factory();
    Plane plane=plane_factory.makePlane("Domestic flights");
    System.out.println();
    plane_factory=new Eurasia_Factory();
    plane=plane_factory.makePlane("Domestic flights");
    System.out.println();
    plane_factory=new Other_Factory();
    plane=plane_factory.makePlane("Domestic flights");

    System.out.println();
    plane_factory=new Domestic_Factory();
    plane=plane_factory.makePlane("Domestic and short international flights");
    System.out.println();
    plane_factory=new Eurasia_Factory();
    plane=plane_factory.makePlane("Domestic and short international flights");
    System.out.println();
    plane_factory=new Other_Factory();
    plane=plane_factory.makePlane("Domestic and short international flights");

    System.out.println();
    plane_factory=new Domestic_Factory();
    plane=plane_factory.makePlane("Transatlantic flights");
    System.out.println();
    plane_factory=new Eurasia_Factory();
    plane=plane_factory.makePlane("Transatlantic flights");
    System.out.println();
    plane_factory=new Other_Factory();
    plane=plane_factory.makePlane("Transatlantic flights");

    }
}
