/**
 * Created by ORHAN on 21.03.2017.
 */
public interface StackInterface  <E>  {

    public boolean isEmpty();
    public E push(E obj);
    public E pop() throws Exception;
    public int size();
}
