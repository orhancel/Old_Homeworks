import java.io.File;
import java.io.IOException;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {






        try {
            File graphFile = new File("graph.txt");

            //Creating Scanner instnace to read File in Java
            Scanner sc = new Scanner(graphFile);
            ListGraph GrList= (ListGraph) ListGraph.createGraph(sc,false,"List");

           GrList.writeGraphToFile("x.txt");


/*
            Graph [] graphs=GrList.getConnectedComponentUndirectedGraph();
            System.out.println(graphs[0].getNumV());
            System.out.println(graphs[1].getNumV());
*/

        } catch (IOException e) {
            e.printStackTrace();
        }


    }
}
