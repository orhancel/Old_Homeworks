

import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author ORHAN
 */
public class main {

    /**
     * @param args the command line arguments
	no terminal arguments
     */
    public static void main(String[] args) {
       
        
        Scanner reader = new Scanner(System.in);
        String type="a";
        int UserOrStaff=0;
        Boolean running=true;
        
        while(running){
            while(!"2".equals(type) && !"1".equals(type) && !"3".equals(type)){
            System.out.println("Pick your Log in type");
            System.out.println("1-Regular user");
            System.out.println("2-Staff member");
            System.out.println("3-Admin");
            System.out.println("0-Exit");
            type=reader.next();
           
            switch (type) {
                case "1":UserOrStaff=1;
                    break;
                case "2":UserOrStaff=2;
                    break;
                case "3":UserOrStaff=3;
                    break;
                case "0":System.out.println("System closed");
                    return;
                    
            }
        }
            type="";
            System.out.println("Enter your Username");
        
            String userName=reader.next();
            System.out.println("Enter your password");
            String passWord=reader.next();
            try{
                if(UserOrStaff==1){
                    LibraryInterface library;
                    library = new user(userName,passWord,"RegularUsers.csv");
                }
                else if(UserOrStaff==2){
                    LibraryInterface library;
                    library = new Staff(userName,passWord,"StaffMembers.csv");
                }
                else if(UserOrStaff==3){
                    LibraryInterface library;
                    library = new Admin(userName,passWord,"admin.csv");
                }
                
            }
            catch(Exception error){
                System.out.println(error.getMessage());
                System.out.println(" Do you want to exit Y/N");
                if(reader.next().equals("Y")){
                    System.out.println("Bye!!!!!");
                    return;
                }
                        
            }
             
        }
        
        // TODO code application logic here
    }
    
}
