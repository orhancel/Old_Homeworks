/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

/**
 *
 * @author ORHAN
 */
public class Admin extends Staff{
    private final String userName;
    private final String passWord;
    private final String dataBase;
    protected boolean running;
    /**
     *
     * @param username
     		user's username
     * @param password
     		users password
     * @param database
     		file we want to access for the usernames and passwords
     * @throws MyException
     		My custom exception class,inherited from Exception class
     */
    public Admin(String username, String password, String database) throws MyException {
        super(username,password,database);
        this.userName=super.userName;
        this.passWord=super.passWord;
        this.dataBase=super.dataBase;
        running=true;
        Menu();
    }
    
    @Override
    public void Menu() throws MyException{
        
        while(running){
            
            
            System.out.println("Enter one of the below");
            System.out.println("1-Borrow Book");
            System.out.println("2-Return Book");
            System.out.println("3-Get the borrowed books list");
            System.out.println("4-Assign new staff");
	System.out.println("5-Assign new user");
            System.out.println("0-Exit");
            Scanner reader = new Scanner(System.in);
            String number=reader.next();
            
            switch (Integer.parseInt(number) ){
                case 1: menuBorrow();
                        break;
                case 2: menuReturn();
                        break;
                case 3: getBorrowedBooks();
                        break;
                case 4: assignUser("StaffMembers.csv");///ASSIGN STAFF MEMBERS
                        break;
				case 5: assignUser("RegularUsers.csv");///ASSIGN REGULAR USERS
						break;
                case 0:running=false;
                		super.running=false;//BECAUSE SOME METHOD'S ARE CALLED FROM SUPER CLASSES
                				//WE NEED TO SET THEIR BOOL TOO TO EXIT FROM THIS LOOP
                				//OTHERWISE WE HAVE PRESS 0 MULTIPLE TIMES
                		break;
                default:System.out.println("Wrong number.Type 1 or 2 or 0");  
                        break;
            }
        }
        
    }
   
 
    
    
}
