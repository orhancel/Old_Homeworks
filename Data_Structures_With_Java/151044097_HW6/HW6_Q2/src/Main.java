import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class Main {

    public static void main(String[] args) {

        ArrayList<HuffmanTree.HuffData> hufpuf=new ArrayList<>();
        HuffmanTree customHufPuf=new HuffmanTree();
        String line="";
        try (BufferedReader br = new BufferedReader(new FileReader("freq.txt"))) {

            while ((line = br.readLine()) != null){
                String [] parts=line.split(" ");
                HuffmanTree.HuffData temp=new HuffmanTree.HuffData(Double.parseDouble(parts[1]) ,parts[0].charAt(0));
                hufpuf.add(temp);


            }


        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        HuffmanTree.HuffData[] hufdataArray=new HuffmanTree.HuffData[hufpuf.size()];

        for(int i=0;i<hufpuf.size();++i){
            hufdataArray[i]=hufpuf.get(i);
        }


        customHufPuf.buildTree(hufdataArray);

        String en = customHufPuf.encode("cadde");

        String de=customHufPuf.decode(en);
        System.out.println(de);




    }
}

