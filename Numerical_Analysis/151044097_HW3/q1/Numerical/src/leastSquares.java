import java.util.ArrayList;

/**
 * Created by ORHAN on 15.05.2017.
 */
public class leastSquares {


    void Formula(ArrayList<Double> x, ArrayList<Double> y, int m){
        if(!(m <x.size()-1)){
            System.out.println("m<size-1 does not true");
            return;
        }
        double [][] A = new double[m][m+1];
        double sum=0;

        ArrayList<Double> powersOfX=new ArrayList<>();
        double[] roots= new double[m];

        for(int n=0;n<2*m-1;++n) {
            for(int i=0;i<x.size();++i){
                sum+=Math.pow(x.get(i),n);
            }
            powersOfX.add(sum);
            sum=0;
        }


        for(int j=0;j<m;++j){
            for(int k=0;k<m;++k){
                A[j][k]=powersOfX.get(k+j);
            }
        }

        sum=0;
        for(int n=0;n<m;++n){

            for (int i=0;i<x.size();++i){
                sum+=y.get(i)*Math.pow(x.get(i),n);
            }
            A[n][m]=sum;
            sum=0;
        }






        roots=gauss(A);

       StringBuilder formula=new StringBuilder();

        for (int i=0;i<roots.length;++i){
            if(i==0)
                formula.append(roots[i]);
            else{
                formula.append(" + ");
                formula.append(roots[i]+"*"+"x^"+i);
            }


        }

        System.out.println("y = "+formula);

    }



    private double[] gauss(double[][] A){
        int n = A.length;

        for (int i=0; i<n; i++) {
            // Search for maximum in this column
            double maxEl = Math.abs(A[i][i]);
            int maxRow = i;
            for (int k=i+1; k<n; k++) {
                if (Math.abs(A[k][i]) > maxEl) {
                    maxEl = Math.abs(A[k][i]);
                    maxRow = k;
                }
            }

            // Swap maximum row with current row (column by column)
            for (int k=i; k<n+1;k++) {
                double tmp = A[maxRow][k];
                A[maxRow][k] = A[i][k];
                A[i][k] = tmp;
            }

            // Make all rows below this one 0 in current column
            for (int k=i+1; k<n; k++) {
                double c = -A[k][i]/A[i][i];
                for (int j=i; j<n+1; j++) {
                    if (i==j) {
                        A[k][j] = 0;
                    } else {
                        A[k][j] += c * A[i][j];
                    }
                }
            }
        }

        // Solve equation upper triangular matrix A
       double[] x=new double[n];


        for (int i=n-1; i>=0; i--) {
            x[i] = A[i][n]/A[i][i];
            for (int k=i-1;k>=0; k--) {
                A[k][n] -= A[k][i] * x[i];
            }
        }
        return x;



    }

}
