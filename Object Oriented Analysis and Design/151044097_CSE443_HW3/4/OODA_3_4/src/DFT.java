/**
 * Created by ORHAN on 10.12.2018.
 */
public class DFT extends Discreate_Transform{

    @Override
    void Transform() {
        System.out.println("DFT transform");
    }
    void Display_Time(){
        System.out.println("Execution time");
    }

    @Override
    void hook() {
        Display_Time();
    }
}
