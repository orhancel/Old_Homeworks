
/**
 *
 * @author ORHAN

 */
public interface LibraryInterface {
    
    /**
     *
     * @param Username
			user's username
     * @param password
			user's password
     * @param database
	which file to access
     * @throws MyException
			my custom exception class,inherited from Exception class
     */
    public void LogIn(String Username,String password,String database)throws MyException;

    
    public String getUsername();

    
    

    /**
     *
     * @param book
			book to return
   	* @throws MyException
			My custom exception class,inherited from Exception class
     */
    public void returnBook(String book)throws MyException;

    /**
     *
     * @param book
	book to borrow
 	* @throws MyException
			My custom exception class,inherited from Exception class
     */
    public void borrowBook(String book)throws MyException;

    
    public void getBorrowedBooks()throws MyException;

    
    void Menu()throws MyException;
}
