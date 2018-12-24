/**
 * Created by ORHAN on 10.12.2018.
 */
public class counterClockWise implements Iterator{

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
    counterClockWise(Integer  [][]m){
        matrix=m;
        positionX=-1;
        positionY=0;
        size=matrix.length*matrix[0].length;
        distance=0;
        down=true;
        right=false;
        up=false;
        left=false;
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

         if(down && matrix.length>positionX){
            positionX++;
            if(matrix.length-horizontalPad/2-1 <=positionX){
                down=false;
                right=true;
                verticalPad++;
            }
            return matrix[positionX][positionY];
        }
        else if(right && positionY<matrix[0].length){
            positionY++;
            if(matrix[0].length-verticalPad<=positionY){
                right=false;
                up=true;
                horizontalPad++;
            }
            return matrix[positionX][positionY];
        }

        else if(up && positionX>=0){
            positionX--;
            if(positionX<=horizontalPad-1){
                up=false;
                left=true;
            }
            return matrix[positionX][positionY];
        }
        if(left && 0<=positionY){
            positionY--;
            if(positionY<=verticalPad){
                down=true;
                left=false;
                horizontalPad++;
            }
            return matrix[positionX][positionY];
        }
        return null;
    }
}

