

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

public class user extends LogInClass{
    protected final String userName;
    protected final String passWord;
    protected final String dataBase;
    protected boolean running;  ///For Menu() method's running while loop
    /**
     *
     * @param Username
     		username
     * @param password
     		password
     * @param database
     		File that contains usernames and password we want
     * @throws MyException
     		my custom exception class,inherited from Exception class
     */
    public user(String Username, String password,String database) throws MyException{
        super(Username,password,database);/////////////CALLS LOGIN METHOD TO GET PERMISSION
        
        this.userName=super.userName;///
        this.passWord=super.passWord;
        this.dataBase=super.dataBase;
        running=true;////
        Menu();
    }
   
   
    @Override
    public String getUsername() {////////////
        return userName;
    }

   
    public String getPassword() {//////////////
        return passWord;
    }


/**
     *

     * 
	* @throws MyException
     		my custom exception class,inherited from Exception class
     */


    @Override
    public void returnBook(String book) throws MyException {////BOOK RETURN PROCCES HAPPENS
        String line="";                                     //THIS METHOD OPENS AND CLOSES FILES
        Boolean found=false;
        try {
            FileReader reader;
            reader = new FileReader("bookDatabase.csv");
            BufferedReader bookRead;
            bookRead = new BufferedReader(reader);
            
            ArrayList<String> bookList=new ArrayList<>();///A LIST TO GET THE BOOKS 
            
                                                        ///BECAUSE WE WİLL EDİT THEİR NUMBERS
            while((line=bookRead.readLine())!=null){
                
                bookList.add(line);                 /////ADD THE BOOKS TO THE LIST
            }
            
            FileReader userReader;
            userReader = new FileReader(userName+".csv");/////
            BufferedReader userRead;
            userRead = new BufferedReader(userReader);////EVERY USER HAS A .CVS FILE.
            ArrayList<String> usersList;            ///WE WRITE THE BOOKS THEY BORROWED.
            usersList = new ArrayList<>();////WE WILL EDIT THEIR FILE SO WE DO THE SAME HERE WITH THIS LIST ARRAY
            
            while((line=userRead.readLine())!=null){
                String [] parted=line.split(",");/////FIRST PART IS BOOK NAME,
                if(parted[0].equals(book)){       ///SECOND PART IS NOTHING BUT WE CAN ADD STUFF LATER ON,
                                                ///LIKE THE DATE THEY HAVE BORROWED
                }
                else
                    usersList.add(line);///ADDS ONLY THE BOOKS WE HAVE NOT RETURNED
            }/////////                      EVERY USER CAN GET ONLY 1 COPY OF A BOOK
            
           
            
           
            
            for(int i=0;i<bookList.size();++i){
                line=bookList.get(i);       //
                
                
                String [] parted=line.split(",");
                if(parted[0].equals(book)){////WE FIND THE BOOK FROM THE bookDATABASE AND
                    
                    line=parted[0]+",";
                    line+=String.valueOf(Integer.parseInt(parted[1])+1); //INCREMENT THE NUMBER OF COPIES
                    
                }
                
                bookList.set(i, line);///SET THE BOOK LIST
              
            }
            
            
            
            FileWriter fw = new FileWriter("bookDatabase.csv");//WHERE WE KEEP THE BOOKS
            FileWriter userFW;
            BufferedWriter userWriter;
            try  {
                BufferedWriter bookWriter = new BufferedWriter(fw);
                userFW = new FileWriter(userName+".csv");///USER'S PERSONEL CVS FILE
                userWriter = new BufferedWriter(userFW);//THEY HAVE THE SAME NAME AS USERNAME
                for(String x:bookList){
                    bookWriter.write(x);///WRITE THE BOOKDATABASE
                    bookWriter.newLine();
                }
                bookWriter.close();
                for(String x:usersList){
                    userWriter.write(x);//WRITE THE USER'S DATA FILE
                    userWriter.newLine();
                }   
                userWriter.close();//CLOSE EVERYTHING
                
                fw.close();
                
                bookRead.close();
                reader.close();
                
                userFW.close();
                
                userRead.close();
                userReader.close();
            }catch (IOException ex) {
                throw new MyException("IO error");
            }
        
        
        
    }   catch (IOException ex) {
            throw new MyException("IO error");
        }
    }


/**
     *

     * 
	* @throws MyException
     		my custom exception class,inherited from Exception class
     */


    @Override
    public void borrowBook(String book) throws MyException {
        String line="";
        String allLines="";
        Boolean found=false;
        try {
            FileReader reader;
            reader = new FileReader("bookDatabase.csv");
            BufferedReader bookRead;
            bookRead = new BufferedReader(reader);
            
            ArrayList<String> bookList=new ArrayList<>();//TO EDIT BOOKDATABASE
           
            while((line=bookRead.readLine())!=null){///ADD BOOKS TO LIST
                
                bookList.add(line);
            }
            
          
            
            FileReader userReader;
            userReader = new FileReader(userName+".csv");//USER'S PERSONEL CVS FILE
            BufferedReader userRead;                //SAME NAME AS USERNAME
            userRead = new BufferedReader(userReader);//CONTAINS BOOK'S HE/SHE BORROWED
            
          
            
            while((line=userRead.readLine())!=null) {
                
                String [] parted =line.split(",");///A USER CANNOT HAVE MORE THEAN ONE COPY
                if(book.equals(parted[0])){///CHECK IF WE ALREAD HAVE A COPY.
                    System.out.println("You already have a copy of this book");
                    userRead.close();
                    userReader.close();
                    reader.close();
                    bookRead.close();
                    return;
                }
                
                
            }
            
            
            for(int i=0;i<bookList.size();++i){//BOOK'S LIST
                line=bookList.get(i);
                String [] parted=line.split(",");//FIRS PART BOOKNAME SECOND PART NUMBER OF COPIES
                if(parted[0].equals(book)){
                    if(Integer.parseInt(parted[1])>0){//CHECK IF WE HAVE ANY COPY LEFT
                        found=true;
                        line=parted[0]+",";
                        line+=String.valueOf(Integer.parseInt(parted[1])-1);//DECREMENT THE NUMBER OF COPIES
                    }
                    else{
                        System.out.println("No more copies left");
                        userReader.close();
                        bookRead.close();
                        return;
                    }
                }
                bookList.set(i, line);
                
            }
     
            if(!found){//TO CHECK IF WE HAVE THE BOOK BUT IT'S REDUNDANT.USER CANNOT ENTER
                System.out.println("Book has not found");//RANDOM BOOK NAMES
                userRead.close();
                userReader.close();
                bookRead.close();
                reader.close();
    
                return;
            }
            else{
                
                FileWriter fw = new FileWriter("bookDatabase.csv");//WRITE BOOKDATABASE
                try
                    {
                    BufferedWriter bookWriter = new BufferedWriter(fw); 
                    FileWriter userFW = new FileWriter(userName+".csv",true);//WRITE USER'S DATA FILE
                    BufferedWriter userBR;
                    userBR = new BufferedWriter(userFW);
                    
                    for(String x:bookList){///REWRITE THE BOOKS BACK
                        bookWriter.write(x);
                        bookWriter.newLine();
                    }
                    
                    userBR.append(book);//APPEND THE NEW BOOK TO USER'S DATA FILE
                    userBR.append(",");
                    userBR.newLine();
                    
                    userBR.close();///COLE EVERYTHING
                    bookWriter.close();
                    bookRead.close();
                    reader.close();
                    
                    
                    userRead.close();
                    userReader.close();
                    }
                catch (IOException ex) {
                    throw new MyException("IO error");
                }
                
                
            }   
            userRead.close();
            userReader.close();
            bookRead.close();
            reader.close();
     
        }
            
        catch (FileNotFoundException ex) {
            throw new MyException("File not found error");
        }
        catch (IOException ex) {
            throw new MyException("IO  error");
        }
        
       
    }
  
/**
     *

     * 
	* @throws MyException
     		my custom exception class,inherited from Exception class
     */



    @Override
    public void getBorrowedBooks()throws MyException {/////LIST OF BORROWED BOOKS
        try {
            FileReader userReader;
            userReader = new FileReader(userName+".csv");
            BufferedReader userRead;
            userRead = new BufferedReader(userReader);
            String line="";
            
            while((line=userRead.readLine())!=null){
                System.out.println(line);
            }
                
            
            
            
            
        } catch (FileNotFoundException ex) {
            throw new MyException("File not found");
        } catch (IOException ex) {
            throw new MyException("IO error");
        }
        
        
        
    }

    /**
     *
     * 
	* @throws MyException
     		my custom exception class,inherited from Exception class
     */
    @Override
    public void Menu() throws MyException {///////////////MAIN MENU
        
        
        while(running){//RUNNING IS SET AT CONSTRUCTOR
            
            
            System.out.println("Enter one of the below");
            System.out.println("1-Borrow Book");
            System.out.println("2-Return Book");
            System.out.println("3-Get the borrowed books list");
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
		          case 0:running=false;//WHRE WE BREAK THE LOOP

                        break;
                default:System.out.println("Wrong number.Type 1 or 2 or 0 user");  
                        break;
            }
        }
    }
            
    /**
     *
     * 

     * @throws MyException
     		my custom exception class,inherited from Exception class
     */
    public void menuBorrow() throws MyException{///////BORROW MENU
        try {
            System.out.println("Type the index of the book you want");
            System.out.println("or type 0 to go back to main menu");
            
            FileReader reader;
            reader = new FileReader("bookDatabase.csv");
            BufferedReader bookRead;
            bookRead = new BufferedReader(reader);
            
            ArrayList<String> books=new ArrayList<>();///BOOKS LIST
            int i=0;
            String line="";
            while((line=bookRead.readLine())!=null){///USERS DOES NOT ENTER THE BOOK NAMES
                                            //////WE GIVE THEM THE LIST OF WHAT WE HAVE
                String[] parts=line.split(",");
                books.add(parts[0]);
                ++i;
                System.out.println(i+"-"+books.get(i-1));//GIVE THE USER LIST OF BOOKS
                
            }
            Scanner IndexReader = new Scanner(System.in);
            String bookIndex=IndexReader.next();////INDEX IS FOR THE BOOK NAME.WE GET THE FROM books ARRAY
            if(bookIndex.equals("0")){///TO LEAVE THE BORROW MENU
                
                reader.close();//CLOSE FILE
                bookRead.close();
                return;
            }
            reader.close();///CLOSE FILE
            bookRead.close();   
            borrowBook(books.get(Integer.parseInt(bookIndex)-1));//CALL THE METHOD TO BORROW BOOK
        } catch (FileNotFoundException ex) {
            throw new MyException("File not found");
        } catch (IOException ex) {
            throw new MyException("IO error");
        }
    }
    
    /**
     *
     *

     * @throws MyException
     			my custom exception class
     */
    public void menuReturn() throws MyException{///////RETURN BOOKS MENU
        try {                                   ///ALMOST SAME AS BORROW BOOK MENU
            System.out.println("Type the index of the book you want to return");
            System.out.println("or type 0 to go back to main menu");
            
            FileReader reader;
            reader = new FileReader(userName+".csv");//EVERY USER HAS A CVS FILE FOR BORROWED BOOKS
            BufferedReader bookRead;
            bookRead = new BufferedReader(reader);
            ArrayList<String> books=new ArrayList<>();//ADD BOOKS TO ARRAY LIST
            int i=0;
            String line="";
            while((line=bookRead.readLine())!=null){///USERS DOES NOT ENTER THE BOOK NAMES
                                            //////WE GIVE THEM THE LIST OF WHAT WE HAVE
                
                String[] parts=line.split(",");
                books.add(parts[0]);////GET THE BORROWED BOOKS FROM USER'S PERSONEL FILE
                ++i;
                System.out.println(i+"-"+books.get(i-1));
                
            }
            reader.close();//CLOSE FILE
            bookRead.close();
            Scanner IndexReader = new Scanner(System.in);
            String bookIndex=IndexReader.next();/// +1 INDEX OF THE BOOK FROM THE LIST
            if(bookIndex.equals("0"))///LEAVE RETURN BOOKS MENU
                return;
            returnBook(books.get(Integer.parseInt(bookIndex)-1));
        } catch (FileNotFoundException ex) {
            throw new MyException("File not found");
        } catch (IOException ex) {
            throw new MyException("IO error");
        }
    }
}
