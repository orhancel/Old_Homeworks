/**
 * Created by ORHAN on 9.12.2018.
 */
public interface TurboPayment {

    int payInTurbo(String turboCardNo, float turboAmount, String destinationTurboOfCourse, String installmentsButInTurbo);
}
