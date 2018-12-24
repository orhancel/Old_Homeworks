import java.io.*;


public class Main {

    public static void main(String[] args) {

        StackInterface <String> A;
        StackInterface <String> B;
        StackInterface <String> C;
        StackInterface <String> D;

        A=new StackA<>();
        B=new StackB<>();
        C=new StackC<>();
        D=new StackD<>();
        BufferedReader read;


        try  {


            read = new BufferedReader(new FileReader("test.csv"));

            File file =new File("testResult_1.csv");

            FileWriter fw = new FileWriter(file,false);

            BufferedWriter bw = new BufferedWriter(fw);

            String line;

            while((line=read.readLine())!=null){

                    String[] parca = line.split(",");
                    for(int j=0;j<parca.length;++j){
                        A.push(parca[j]);
                        B.push(parca[j]);
                        C.push(parca[j]);
                        D.push(parca[j]);
                    }


            }

            long startTime = System.nanoTime();

            bw.write(String.valueOf(A.size()));
            bw.write(",");
            while(A.size()>0){
                String x=A.pop();

                bw.write(x);
                bw.write(",");
            }
            long endTime   = System.nanoTime();
            long totalTime = endTime - startTime;
            System.out.println(totalTime +"for stack A");

            bw.newLine();

            startTime = System.nanoTime();

            bw.write(String.valueOf(B.size()) );
            bw.write(",");
            while(B.size()>0){

                bw.write(B.pop());
                bw.write(",");

            }

            endTime   = System.nanoTime();
            totalTime = endTime - startTime;
            System.out.println(totalTime +"for stack B");


            startTime = System.nanoTime();


            bw.newLine();
            bw.write(String.valueOf(C.size()));
            bw.write(",");
            while(C.size()>0){
                String x=C.pop();

                bw.write(x);
                bw.write(",");
            }

            endTime   = System.nanoTime();
            totalTime = endTime - startTime;
            System.out.println(totalTime +"for stack C");

            bw.newLine();

            startTime = System.nanoTime();
            bw.write(String.valueOf(D.size()));
            bw.write(",");
            while(D.size()>0){
                bw.write(D.pop());
                bw.write(",");
            }

            endTime   = System.nanoTime();
            totalTime = endTime - startTime;
            System.out.println(totalTime +"for stack D");


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
