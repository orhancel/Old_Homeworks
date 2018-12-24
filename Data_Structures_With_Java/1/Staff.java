


import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author ORHAN
 */
public class Staff extends user{
    protected final String userName;
    protected final String passWord;
    protected final String dataBase;
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
    public Staff(String username,String password,String database) throws MyException{
        super(username,password,database);////CALLS LOGIN METHOD TO GET PERMISSION
        this.userName=super.userName;
        this.passWord=super.passWord;
        this.dataBase=super.dataBase;
       	running=true;///FOR THE MENU() METHOD'S WHILE LOOP
        Menu();
    }
    
    
    @Override
    public String getUsername() {
        return userName;
    }

  
    
    public String getPassword() {
        return passWord;
    }


/**
     *
     * @throws MyException
		My custom exception class,inherited from Exception class
     */
 
    public void addBook()throws MyException{////ADD BOOKS TO THE DATABASE
        
        System.out.println("Name of the book you want to add");
        Scanner readInput=new Scanner(System.in);
        String book=readInput.next();
   
        boolean copy=false;
        try {
            String line="";
            FileReader reader;
            reader = new FileReader("bookDatabase.csv");
            BufferedReader bookRead;
            bookRead = new BufferedReader(reader);
            
            ArrayList<String> bookList=new ArrayList<>();
            
            
            while((line=bookRead.readLine())!=null){
                
                bookList.add(line);
            }
            
            
            for(int i=0;i<bookList.size();++i){
                line=bookList.get(i);
                
                
                String [] parted=line.split(",");
                if(parted[0].equals(book)){
                    
                    line=parted[0]+",";
                    line+=String.valueOf(Integer.parseInt(parted[1])+1);
                    copy=true;
                }
                
                bookList.set(i, line);
                
            }
            if(!copy){
                bookList.add(book+",1");
            }
            
           
            
           
               FileWriter fw = new FileWriter("bookDatabase.csv");
                BufferedWriter bookWriter = new BufferedWriter(fw);
                
                for(String x:bookList){
                    bookWriter.write(x);
                    bookWriter.newLine();
                }
                bookWriter.close();
                bookRead.close();
                fw.close();
                reader.close();
            
       
        } catch (FileNotFoundException ex) {
            throw new MyException("File not found");
        } catch (IOException ex) {
            throw new MyException("IO error");
        }
        

    }
  
   
    /**
     *
     * @throws MyException
     	My custom exception class
     */
    @Override
    public void Menu() throws MyException{////////MAIN MENU
        
        while(running){//SET AT CONSTRUCTOR
            
            
            System.out.println("Enter one of the below");
            System.out.println("1-Borrow Book");
            System.out.println("2-Return Book");
            System.out.println("3-Get the borrowed books list");
            System.out.println("4-Assign new user");
            System.out.println("5-Add new books");
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
                case 4: assignUser("RegularUsers.csv");
                        break;
                    
                case 5:addBook();
                case 0: running=false;
                		super.running=false;//BECAUSE SOME METHOD'S ARE CALLED FROM SUPER CLASSES
                				//WE NEED TO SET THEIR BOOL TOO TO EXIT FROM THIS LOOP
                				//OTHERWISE WE HAVE PRESS 0 MULTIPLE TIMES
                		break;
                default:System.out.println("Wrong number.Type 1 or 2 or 0");  
                        break;
            }
        }
    }
    
  
    
    /**
     * @param databaseType
     		Name of file we want to access.RegulerUsers.cvs  or StaffMembers.cvs
     * @throws MyException
		My custom exception class,inherited from Exception class

     */
    public void assignUser(String databaseType) throws MyException {///////ASSIGNS NEW USERS or STAFF
    try{															///ONLY ADMIN CAN ASSIG NEW STAFF
        System.out.println("Enter the username you want to assign");
        FileReader readerforBuffer;
            readerforBuffer = new FileReader(databaseType);
            BufferedReader userDatabase;
            userDatabase = new BufferedReader(readerforBuffer);;///WHERE WE KEEP USER'S NAME AND PASSWORDS
        
        
        boolean nameSet=false;
        while(!nameSet){
            
            boolean tryAgain=false;
            Scanner reader;
    		reader = new Scanner(System.in);
    		String user =reader.next();///GET THE USERNAME FROM USER/////////////////
            String line="";
            while((line=userDatabase.readLine())!=null){
        		
            								//THERE IS NO SECOND PART
            	String [] parted=line.split(",");///BUT WE CAN USE IT IN THE FUTURE FOR ADDITINAL INFO
            						///LIKE BLOCKING USER FOR SOME TIME

            	System.out.println(parted[0]);
                if(parted[0].equals(user)){///CHECK IF WE ALREAD HAVE SET SOMEONE
                    System.out.println("Username has already assigned.");//WITH THE SAME USERNAME.
                    System.out.println("Try a different name");
                    userDatabase.close();
            		readerforBuffer.close();
                    return;
                    
                }
            }
            userDatabase.close();
            readerforBuffer.close();
            if(!tryAgain){//IF WE DON'T ALREADY HAVE THE SAME USERNAME
                FileWriter userFile;
                try {
                    userFile = new FileWriter(databaseType,true);//WRITE FILE
                    try (BufferedWriter userWriter = new BufferedWriter(userFile)) {
                        
                        userWriter.append(user);//APPEND USERNAME TO 
                        userWriter.append(",");
                        System.out.println("Enter the password you want to use");
                        userWriter.append(reader.next());
                        userWriter.newLine();
                        userWriter.close();
                    }
                    userFile.close();
                    FileWriter file=new FileWriter(user+".csv");//CREATE NEW FILE FOR USER
                    System.out.println("New user has been set");
                    nameSet=true;
                } catch (IOException ex) {
                    throw new MyException("IO error");
                }
               
            }
        	
            
        }
        
    }catch (FileNotFoundException ex) {
    	
            throw new MyException("File not found");
        } catch (IOException ex) {
        	
            throw new MyException("IO error");
        }
}	
    
}
