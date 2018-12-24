/**
 * Created by ORHAN on 9.12.2018.
 */
public class ModernAdapter implements TurboPayment {
    ModernPayment modern;

    ModernAdapter(ModernPayment m){
        modern=m;
    }
    @Override
    public int payInTurbo(String turboCardNo, float turboAmount, String destinationTurboOfCourse, String installmentsButInTurbo) {
        modern.pay(turboCardNo,turboAmount,destinationTurboOfCourse,installmentsButInTurbo);
        return 0;
    }
}
