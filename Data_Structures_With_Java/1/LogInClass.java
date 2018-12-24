

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author ORHAN
 */
public abstract class LogInClass implements LibraryInterface{

    /**
     *
     */
    protected String userName;

    /**
     *
     */
    protected String passWord;

    /**
     *
     */
    protected String dataBase;
    
    /**
     *
     * @param Username
     		user's username
     * @param password
     		users password
     * @param database
     		file we want to access for the usernames and passwords
     		RegulerUsers.cvs  StaffMembers.cvs Admin.cvs
     * @throws MyException
     		My custom exception class,inherited from Exception class
     */

    public LogInClass(String Username,String password,String database) throws MyException{
        LogIn(Username,password,database);
    }
    
    @Override
    public final void LogIn(String Username,String password,String database)throws MyException{
        try {
            FileReader reader;
            reader = new FileReader(database);
            BufferedReader staffMember;
            staffMember = new BufferedReader(reader);
            
            String line="";
            while(( line=staffMember.readLine() )!=null){
                
                String[] parts=line.split(",");//PART THE LINE
                if(parts[0].equals(Username)){///FIRST PART IS FOR USERNAME
                    
                    if(parts[1].equals(password)){//SECOND PART IS FOR PASSWORD
                        this.userName=Username;
                        this.passWord=password;
                        this.dataBase=database;
                        System.out.println("Access Granted");
                        reader.close();
                        staffMember.close();
                       
                        return;
                    }
                    else{
                        throw new MyException("Wrong Password");
                    }
                    
                }
                
                
                
            }
         
         
            throw new MyException("Username does not found");
                 
        } catch (FileNotFoundException ex) {
            throw new MyException("File not found");
        } catch (IOException ex) {
            throw new MyException("IO error");
        }
    }
    
}
