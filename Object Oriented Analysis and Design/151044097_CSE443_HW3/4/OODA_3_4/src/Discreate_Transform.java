/**
 * Created by ORHAN on 10.12.2018.
 */
public abstract class Discreate_Transform {

    final public void Procedure(){
        Read_N_Numbers();
        Transform();
        Write_To_File();
        hook();
    }

    public void Read_N_Numbers() {
        System.out.println("Reading File");
    }
    abstract void Transform();

    public void Write_To_File(){
        System.out.println("Writing to File");
    }

    void hook() {

    }

}
