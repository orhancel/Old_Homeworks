/**
 * Created by ORHAN on 9.12.2018.
 */
public interface ModernPayment {
    int pay(String cardNo, float amount, String destination, String installments);
}
