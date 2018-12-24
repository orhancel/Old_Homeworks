/**
 * Created by ORHAN on 10.12.2018.
 */
public class clockWise implements Iterator {
    int positionX;
    int positionY;
    int size;
    int distance;
    Integer  [][]matrix;
    boolean up;
    boolean down;
    boolean right;
    boolean left;
    int verticalPad;
    int horizontalPad;
    clockWise(Integer  [][]m){
        matrix=m;
        positionX=0;
        positionY=-1;
        size=matrix.length*matrix[0].length;
        distance=0;
        down=false;
        right=true;
        up=false;
        left=true;
        verticalPad=0;
        horizontalPad=0;
    }
    @Override
    public boolean hasNext() {

        if(distance<size)
            return true;
        return false;
    }

    @Override
    public Object next() {
        distance++;
        if(right && positionY<matrix[0].length){
            positionY++;
            if(matrix[0].length-verticalPad-1<=positionY){
                right=false;
                down=true;
                horizontalPad++;

            }

            return matrix[positionX][positionY];
        }
        else if(down && matrix.length>positionX){
            positionX++;
            if(matrix.length-horizontalPad <=positionX){
                down=false;
                left=true;
                verticalPad++;

            }

            return matrix[positionX][positionY];
        }
        else if(left && 0<=positionY){
            positionY--;
            if(positionY<=verticalPad-1){
                up=true;
                left=false;
                horizontalPad++;
            }

            return matrix[positionX][positionY];
        }
        else if(up && positionX>=0){
            positionX--;
            if(positionX<=horizontalPad-1){
                up=false;
                right=true;
                //verticalPad++;

            }

            return matrix[positionX][positionY];
        }
        return null;
    }
}
