/**
 * Created by ORHAN on 25.10.2018.
 */
public class Gaus_Elimination implements LinearSolverDeluxe{

    /**
     *
     * @param tempMatrix  Given matrix to swap 2 of it's rows.For pivoting.
     * @param a  Index of one of the rows to swap
     * @param b  Index of one of the rows to swap
     */
    private void swap(double[][] tempMatrix,int a,int b){
        double temp;
        for (int i=0;i<tempMatrix.length+1;i++){

                temp=tempMatrix[a][i];

                tempMatrix[a][i]=tempMatrix[b][i];

                tempMatrix[b][i]=temp;

        }

    }

    /**
     *
     * @param A  It is a double matrix.It contains the constants of unknown variables.Like 2x+3y+5z is 2 , 3 ,5
     *           and so on.
     * @param b  It is the results vector of linear equations.
     * @return  It returns the values of unknown variables.
     */
    private double[] Gaussian_Elim(double[][] A,double [] b) {

        int n = A.length;


        double [][]tempMatrix=new double[n][n+1];

        for(int i=0 ;i < n ; i++){
            for(int j=0 ; j<n+1 ; j++){
                if(j<n)
                    tempMatrix[i][j]=A[i][j];
                else
                    tempMatrix[i][j]=b[i];
            }
        }


        for (int i = 0; i < n; i++) {

            if(tempMatrix[i][i]==0){
                for (int j=i;j<n;j++){
                    if(tempMatrix[j][i]!=0){
                        swap(tempMatrix,i,j);
                        break;
                    }

                }
            }



            for (int j = i + 1; j < n; j++) {
                double alpha = tempMatrix[j][i] / tempMatrix[i][i];

                for (int k = i; k < n+1; k++) {
                    tempMatrix[j][k] -= alpha * tempMatrix[i][k];
                }
            }
        }

        double temp;
        for (int i = 0; i < n; i++) {
            if(tempMatrix[i][i]==0)
                System.out.println("Error");
            temp =tempMatrix[i][i];

            for (int j = 0; j < n+1; j++) {
                tempMatrix[i][j]/=temp;
            }
        }

        for (int i = n-1; i >=0; i--) {

            for (int j = i - 1; j >=0; j--) {
                double alpha = tempMatrix[j][i];

                for (int k = i; k < n+1; k++) {
                    tempMatrix[j][k] -= alpha * tempMatrix[i][k];
                }
            }
        }

        double [] results=new double[n];

        for (int i=0;i<n;i++){
            results[i]=tempMatrix[i][n];

            results[i] = results[i]*100;
            results[i] = Math.round(results[i]);
            results[i] = results[i] /100;
        }

        return  results;


    }

    /**
     *
     * @param A   It is a double matrix.It contains the constants of unknown variables.Example 2x+3y+5z is 2 , 3 ,5
    and so on.
     * @param b  It is the results vector of linear equations.
     * @return  It returns the values of unknown variables.Like x,y,z of above example.
     */
    @Override
    public double[] getResult(double[][] A, double[] b) {
        return Gaussian_Elim(A,b);
    }



}
