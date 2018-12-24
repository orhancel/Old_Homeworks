import java.util.ArrayList;

/**
 * Created by ORHAN on 15.05.2017.
 */
public class dividedDifferences {



    void Formula(ArrayList<Double> x, ArrayList<Double> y, double eva){
        StringBuilder formula=new StringBuilder();
        double [] b=new double[x.size()];
        double f,temp1=1,temp2=0;
        int j=1;
        int n=x.size();
        f= y.get(0);

        int counter=0;
        do
        {
            for (int i=0;i<n-1;i++)
            {
                b[i] = ((y.get(i + 1) - y.get(i))/(x.get(i + j) - x.get(i)));
                y.set(i, b[i]);
            }
            temp1=1;
            if(counter!=0){
                formula.append("+");
                formula.append(y.get(0));
                for (int i=0;i<counter;i++){
                    formula.append("*");
                    formula.append("(x-"+x.get(i)+")");
                }

            }

            else{
                formula.append(y.get(0));
            }

            counter++;
            for(int i=0;i<j;i++)
            {
                temp1*=(eva- x.get(i));
            }
            temp2+=(y.get(0) *temp1);
            n--;
            j++;
        }
        while(n!=1);
        f+=temp2;
        System.out.println("f("+eva+")"+"="+f);
        System.out.println(formula);



    }




}
