

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.Random;
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
     */
    public static void main(String[] args) {
        myStringBuilder builder=new myStringBuilder();
        
        try {/////INTEGER TEXT FILE CREATOR. 10.000 RANDOM NUMBERS
            PrintWriter out = new PrintWriter("numbers.txt");
            Random generator = new Random(); 
            for(int j=0;j<10000;++j){
                int i = generator.nextInt(100) + 1;
                out.print(String.valueOf(i)+" ");
                if(j%10==0 && j!=0){
                    out.println();
                }
                    
            }
            
 
        } catch (Exception ex) {
            System.out.println("NUMBERS.TXT FILE READ ERROR");
        }
        
        
       
        try {///////////////////////////////////////////////////////////QUESTION 1
            Scanner scanner = new Scanner(new File("numbers.txt"));
            while(scanner.hasNextInt()){
                
                builder.append(scanner.nextInt() );  ////READS THE NUMBERS FILE AND ADD IT TO STRING BUILDER
            }
            File file1 = new File("result1.txt");
            FileWriter writer1 = new FileWriter(file1); 
            
            File file2 = new File("result2.txt");
            FileWriter writer2 = new FileWriter(file2); 
            
            File file3 = new File("result3.txt");
            FileWriter writer3; 
            writer3 = new FileWriter(file3);
            
             
            
            writer1.write(builder.toStringGet());
            
            writer2.write(builder.toStringIterator());
            
            writer3.write(builder.toStringList());
   
            
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        
        System.out.println(builder.toStringIterator()); 
        
        MyLinkedList<Integer> liste=new MyLinkedList<>();
        
        
        Scanner scanner;
        try {///////////////////////////////////QUESTION 4
            scanner = new Scanner(new File("numbers.txt"));
            int i=0;
            while(scanner.hasNextInt() && i<100){
                ++i;
                liste.add(scanner.nextInt() );  ////READS 100 NUMBERS FROM FILE AND ADD IT TO LIST
            } 
            
            i=50;
            
            while(i>0){///////////////////////REMOVE INTEGERS
                liste.remove(50);
                --i;
            }
            
            System.out.println(liste.deletedToString());   //////////////////////////STRING OF DELETED NUMBERS
            
            while(scanner.hasNextInt() && i<100){/////ADD 100 MORE INTEGERS
                ++i;
                liste.add(scanner.nextInt() );  ////READS THE NUMBERS FILE AND ADD IT TO STRING BUILDER
            }
            System.out.println(liste.toString());
            
            
            
            
        } 
        catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
            
        MyLinkedList<Integer> list1=new MyLinkedList<>();
        
        list1.add("123456789");
	System.out.println("123456789   will be reversed");
        System.out.println(list1.reverseToString()); 
       
        

    
}
    
}
