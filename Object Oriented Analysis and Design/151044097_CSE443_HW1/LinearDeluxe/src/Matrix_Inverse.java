/**
 * Created by ORHAN on 25.10.2018.
 */
public class Matrix_Inverse implements LinearSolverDeluxe{


    /**
     *
     * @param tempMatrix  Given matrix to swap 2 of it's rows.For pivoting.
     * @param a  Index of one of the rows to swap
     * @param b  Index of one of the rows to swap
     */
    private void swap(double[][] tempMatrix,int a,int b){
        double temp;
        for (int i=0;i<tempMatrix.length*2;i++){

            temp=tempMatrix[a][i];

            tempMatrix[a][i]=tempMatrix[b][i];

            tempMatrix[b][i]=temp;

        }

    }

    /**
     *
     * @param A   It is a double matrix.It contains the constants of unknown variables.Like 2x+3y+5z is 2 , 3 ,5
    and so on.
     * @return  Inverse of given matrix.
     */
    private   double[][] Gauss_Jordan_inverse(double[][] A) {
        int n = A.length;


        double [][]tempMatrix=new double[n][n*2];

        for(int i=0 ;i < n ; i++){
            for(int j=0 ; j<n*2 ; j++){
                if(j<n)
                    tempMatrix[i][j]=A[i][j];
                else
                    tempMatrix[i][j]=0;
            }
        }
        for(int i=n; i<n*2 ; i++){
            tempMatrix[i-n][i]=1;
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

                for (int k = i; k < n*2; k++) {
                    tempMatrix[j][k] -= alpha * tempMatrix[i][k];
                }
            }
        }

        double temp;
        for (int i = 0; i < n; i++) {
            if(tempMatrix[i][i]==0)
                System.out.println("Error");
            temp =tempMatrix[i][i];
            tempMatrix[i][i]=1;
            for (int j = 0; j < n*2; j++) {
                tempMatrix[i][j]/=temp;
            }
        }

        for (int i = n-1; i >=0; i--) {

            for (int j = i - 1; j >=0; j--) {
                double alpha = tempMatrix[j][i];

                for (int k = i; k < n*2; k++) {
                    tempMatrix[j][k] -= alpha * tempMatrix[i][k];
                }
            }
        }

        double [][] Matrix_Inverse=new double[n][n];

        for (int i=0;i<n;i++){
            for (int j=0;j<n;j++){
                Matrix_Inverse[i][j]=tempMatrix[i][j+n];
                Matrix_Inverse[i][j] = Matrix_Inverse[i][j]*100;
                Matrix_Inverse[i][j] = Math.round(Matrix_Inverse[i][j]);
                Matrix_Inverse[i][j] = Matrix_Inverse[i][j] /100;
            }
        }


        return  Matrix_Inverse;
    }

    /**
     *
     * @param A It is the inverse matrix.We multiply it with results vector to find the unknown variables.
     * @param B  It is the results vector of linear equations.
     * @return   It returns the values of unknown variables.
     */
    private   double[] multiply(double[][] A, double[] B) {

        int aRows = A.length;
        int aColumns = A[0].length;
        int bRows = B.length;


        if (aColumns != bRows) {
            throw new IllegalArgumentException("A:Rows: " + aColumns + " did not match B:Columns " + bRows + ".");
        }

        double[] C = new double[aRows];
        for (int i = 0; i < aRows; i++) {
            C[i] = 0.0;
        }

        for (int i = 0; i < aRows; i++) { // aRow
            for (int j = 0; j < 1; j++) { // bColumn
                for (int k = 0; k < aColumns; k++) { // aColumn
                    C[i] += A[i][k] * B[k];
                }
                C[i] = C[i]*100;
                C[i] = Math.round(C[i]);
                C[i] = C[i] /100;
            }
        }

        return C;
    }


    /**
     *
     * @param A  It is a double matrix.It contains the constants of unknown variables.Exapmle 2x+3y+5z is 2 , 3 ,5
     *           and so on.
     * @param b  It is the results vector of linear equations.
     * @return   It returns the values of unknown variables.Like the x,y,z of above example.
     */
    @Override
    public double[] getResult(double[][] A, double[] b) {

        double[][] inverse_Matrix = Gauss_Jordan_inverse(A);
        System.out.println("Inverse Matrix");
        for (int i = 0; i < A.length; i++) {
            for (int j=0; j<A.length;j++)
                System.out.print(inverse_Matrix[i][j] + " ");
            System.out.println();
        }


        return multiply(inverse_Matrix,b);
    }
}
