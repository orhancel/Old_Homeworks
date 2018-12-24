import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class Main {

    public static void main(String[] args) {

        FamilyTree<String> family= new FamilyTree<>();

        try {
            FileReader fr = new FileReader("family.txt");
            BufferedReader br = new BufferedReader(fr);
            String line="";
            while ((line=br.readLine())!=null){
                line=line.replaceAll("\\s+","");
                String [] parts=line.split(",");
                if (parts.length==3){
                    family.Add(parts[0],parts[1],parts[2]);
                }
                else {
                    family.Add(parts[0],null,null);
                }

            }

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        catch (Exception e) {
            System.out.println(e.getMessage());
        }

        System.out.println("Family tree");
        family.preOrderTraversal();

        BinaryTree < Integer > binTree=new BinaryTree<>();
        BinarySearchTree binSearchTree=new BinarySearchTree<>();

        try {
            FileReader fr = new FileReader("test.txt");
            BufferedReader br = new BufferedReader(fr);
            String line="";
            while ((line=br.readLine())!=null){

                String [] parts=line.split(" ");
                for (int i=0;i<parts.length;i++){
                    binSearchTree.Add(Integer.valueOf( parts[i]));
                    binTree.Add(Integer.valueOf( parts[i]));
                }


            }

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        catch (Exception e) {
            System.out.println(e.getMessage());
        }
        System.out.println("pre Order Traversal");
        binTree.preOrderTraversal();
        System.out.println("Level Order Traversal");
        binSearchTree.LevelOrderTraversal();


    }
}
