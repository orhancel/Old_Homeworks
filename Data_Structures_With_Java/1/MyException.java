

/**
 *
 * @author ORHAN
 */
public class MyException extends Exception{
    String errorMessege;
    /**
     *
     */
    public MyException(){
        errorMessege="An error has occurred";
    }

    /**
     *
     * @param error
	error message of our choice.Whatever string we send.
     */
    public MyException(String error){
        errorMessege=error;
    }

    @Override
    public String getMessage() {
        return errorMessege; //To change body of generated methods, choose Tools | Templates.
    }
    
    
    
}
