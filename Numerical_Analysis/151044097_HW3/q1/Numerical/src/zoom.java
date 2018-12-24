/**
 * Created by ORHAN on 15.05.2017.
 */
public class zoom {


    Integer[][] zoomInNeighbor(int Image[][], int z){
        int count=0;

        Integer [][] zoomIn= new Integer[z * 10][z * 10];
        int i=0;
        for(int n=0;n<10;n++){
            i=n*z;
            count=0;
            while (count<z){
                for(int j=0;j<10;++j){

                        zoomIn[i+count][j*z] = Image[n][j];


                }
                count++;
            }


        }



        for(i=0;i<10*z;i++){
            for(int j=0;j<10*z;++j){
                if(zoomIn[i][j]==null){

                    zoomIn[i][j]=zoomIn[i][j-1];

                }

            }

        }




        for (i=0;i<z*10;++i){
            for (int n=0;n<z*10;++n){
                System.out.print(zoomIn[i][n]+" ");

            }
            System.out.println();
        }

        return zoomIn;
    }
}
