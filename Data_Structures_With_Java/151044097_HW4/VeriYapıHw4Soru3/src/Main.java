import java.io.*;

public class Main {

    public static void main(String[] args) {

        priorityQueueA <String> A=new priorityQueueA<>() ;
        priorityQueueB <String > B=new priorityQueueB<>();

        try{
            BufferedReader read = new BufferedReader(new FileReader("test.csv"));

            String line;
            while ((line=read.readLine())!=null){

                String [] parts=line.split(",");
                for (int i=0;i<parts.length;++i){
                    A.add(parts[i]);
                    B.add(parts[i]);
                }


            }

            File file =new File("testResult_3.csv");

            FileWriter fw = new FileWriter(file,false);

            BufferedWriter bw = new BufferedWriter(fw);


            while(A.size()>0){
                bw.write(A.deleteMin());
                bw.write(",");
            }

            bw.newLine();

            while (B.size()>0){
                bw.write(B.deleteMin());
                bw.write(",");
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
