import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        dividedDifferences q2=new dividedDifferences();
        leastSquares q3=new leastSquares();
        zoom q1=new zoom();

        ArrayList<Double> x=new ArrayList<>();
        ArrayList<Double> y=new ArrayList<>();





        x.add((double) 0);
        x.add((double) 0.25);
        x.add((double) 0.5);
        x.add(0.75);
        x.add((double) 1);

        y.add(1.0);
        y.add(1.284);
        y.add(1.6487);
        y.add(2.117);
        y.add(2.7183);

        q3.Formula(x,y,3);


    }
}


/*
        Scanner sc = new Scanner(System.in);

        String line=sc.nextLine();
        String [] parts1=line.split(" ");
        for (int i=0;i<parts1.length;++i){
            x.add(Double.parseDouble(parts1[i]));
        }

        line=sc.nextLine();
        String [] parts2=line.split(" ");
        for (int i=0;i<parts2.length;++i){
            y.add(Double.parseDouble(parts2[i]));
        }
*/

