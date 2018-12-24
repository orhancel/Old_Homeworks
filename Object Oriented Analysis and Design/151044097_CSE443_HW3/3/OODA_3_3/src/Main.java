public class Main {

    public static void main(String[] args) {
        System.out.println("Hello World!");
        Integer [][]matrix={{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};

        clockWise clock=new clockWise(matrix);

        while (clock.hasNext())
            System.out.print(clock.next()+" ");
        System.out.println();
        System.out.println("///////////////////////////");
        counterClockWise counter=new counterClockWise(matrix);
        while (counter.hasNext())
            System.out.print(counter.next()+" ");
    }
}
