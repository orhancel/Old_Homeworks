import java.io.*;
import java.util.LinkedList;
import java.util.ListIterator;
import java.util.Queue;

public class Main {

    public static void main(String[] args) {

        myQueue <String> liste;
        liste=new myQueue<>();
        BufferedReader read;


        try  {


            read = new BufferedReader(new FileReader("test.csv"));

            File file =new File("testResult_2.csv");

            FileWriter fw = new FileWriter(file,false);
            //BufferedWriter writer give better performance
            BufferedWriter bw = new BufferedWriter(fw);


            String line;

            while((line=read.readLine())!=null){

                String[] parca = line.split(",");
                for(int j=0;j<parca.length;++j){

                    liste.addLast(parca[j]);

                }


            }

            ListIterator <String> it=liste.listIterator();

            while (it.hasNext()){
                String temp=it.next();

                System.out.println(temp);
            }

            liste.reverser();

            ListIterator <String> iter=liste.listIterator();

            while (iter.hasNext()){
                String temp=iter.next();

                bw.write(temp.toString());
                bw.write(",");
                System.out.println(temp);
            }




            bw.flush();
            bw.close();
            fw.flush();
            fw.close();


            read.close();


        }
        catch (Exception e){
            System.out.println(e.getMessage());
        }


    }



}
