import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        dividedDifferences q2=new dividedDifferences();
        leastSquares q3=new leastSquares();
        zoom q1=new zoom();

        ArrayList<Double> x=new ArrayList<>();
        ArrayList<Double> y=new ArrayList<>();




        x.add((double) 10);
        x.add((double) 15);
        x.add((double) 20);
        x.add(22.5);

        y.add(227.04);
        y.add(362.78);
        y.add(517.35);
        y.add(602.97);



        q2.Formula(x,y,  16);//eva is number X to evaluate.Does not neccessery.Method will print the equation.

      /*  x.add((double) 0);
        x.add((double) 0.25);
        x.add((double) 0.5);
        x.add(0.75);
        x.add((double) 1);

        y.add(1.0);
        y.add(1.284);
        y.add(1.6487);
        y.add(2.117);
        y.add(2.7183);
        q3.Formula(x,y,3);*/


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

