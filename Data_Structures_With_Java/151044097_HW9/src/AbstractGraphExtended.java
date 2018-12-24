import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.*;

/**
 * Created by ORHAN on 19.05.2017.
 */
public  abstract class AbstractGraphExtended extends AbstractGraph {


    public AbstractGraphExtended(int numV, boolean directed) {
        super(numV,directed);
    }

    public int [] breadthFirstSearch (int start){

        Queue <Integer> theQueue= new LinkedList<>();
        int[] parent = new int[getNumV()];
        for(int i=0;i<getNumV();++i){
            parent[i]=-1;
        }
        boolean [] identified = new boolean[getNumV()];
        identified[start]=true;
        theQueue.offer(start);

        while (!theQueue.isEmpty()){
            int current=theQueue.remove();
            Iterator<Edge> itr=edgeIterator(current);
            while (itr.hasNext()){
                Edge edge=itr.next();
                int neighbor = edge.getDest();
                if(!identified[neighbor]){
                    identified[neighbor]=true;
                    theQueue.offer(neighbor);
                    parent[neighbor]=current;
                }
            }
        }
        return parent;

    }

    public void writeGraphToFile (String fileName) throws IOException {
        File file = new File(fileName);
        FileWriter fw = new FileWriter(file.getAbsoluteFile());
        BufferedWriter bw = new BufferedWriter(fw);

        Queue <Integer> theQueue= new LinkedList<>();

        boolean [] identified = new boolean[getNumV()];

        ArrayList<String> edgesFound= new ArrayList<>();
        bw.write(String.valueOf(getNumV()));
        bw.newLine();


        int i=0;
        while (i<getNumV()) {

            while (i < getNumV() && identified[i]) {
                ++i;

            }
            if (i == getNumV())
                break;
            theQueue.offer(i);
            identified[i] = true;
            while (!theQueue.isEmpty()) {
                int current = theQueue.remove();
                Iterator<Edge> itr = edgeIterator(current);
                while (itr.hasNext()) {
                    Edge edge = itr.next();

                    int neighbor = edge.getDest();

                    if (edgesFound.contains(edge.getDest() + " " + edge.getSource())) {

                        bw.write(edge.getSource() + " " + edge.getDest());
                        bw.newLine();
                    } else
                        edgesFound.add(edge.getSource() + " " + edge.getDest());

                    if (!identified[neighbor]) {

                        identified[neighbor] = true;
                        theQueue.offer(neighbor);

                    }
                }
            }
        }
        bw.flush();




    }

    public Graph[] getConnectedComponentUndirectedGraph () throws IOException {

        Queue <Integer> theQueue= new LinkedList<>();

        boolean [] identified = new boolean[getNumV()];
        ArrayList<String> edgesFound= new ArrayList<>();
        ArrayList<Graph> graphList=new ArrayList<>();
        StringBuilder stb=new StringBuilder();

        int max=0;
        int i=0;
        while (i<getNumV()){

            while (i<getNumV() && identified[i] ){
                ++i;

            }
            if(i==getNumV())
                break;
            theQueue.offer(i);
            identified[i]=true;
            while (!theQueue.isEmpty()){
                int current=theQueue.remove();
                Iterator<Edge> itr=edgeIterator(current);
                while (itr.hasNext()){

                    Edge edge=itr.next();

                    int neighbor = edge.getDest();
                    if(edge.getSource()>max)
                        max=edge.getSource();
                    if(edge.getDest()>max)
                        max=edge.getDest();
                    if(edgesFound.contains(edge.getDest()+" "+edge.getSource())){


                    }
                    else{

                        edgesFound.add(edge.getSource()+" "+edge.getDest());
                    }




                    if(!identified[neighbor]){

                        identified[neighbor]=true;

                        theQueue.offer(neighbor);

                    }
                }
            }
            stb.append(max+1);
            stb.append(System.lineSeparator());
            for(int k=0;k<edgesFound.size();k++){
                stb.append(edgesFound.get(k));
                stb.append(System.lineSeparator());
            }
            Scanner sc=new Scanner(stb.toString());
            String typeOfGraph;
            if(this.getClass().getName().equals("ListGraph")){
                typeOfGraph="List";
            }
            else
                typeOfGraph="Matrix";
            graphList.add(AbstractGraph.createGraph(sc,isDirected(),typeOfGraph));
            stb=new StringBuilder();
            edgesFound=new ArrayList<>();

        }
        Graph [] rtr=new Graph[graphList.size()];

        for( i=0;i<rtr.length;i++){
            rtr[i]=graphList.get(i);
        }
        return rtr;



    }

    public boolean isBipartiteUndirectedGraph () {

        Queue<Integer> theQueue = new LinkedList<>();

        boolean[] identified = new boolean[getNumV()];
        int[] color = new int[getNumV()];
        for (int i = 0; i < color.length; i++)
            color[i] = -1;

        int i = 0;
        while (i < getNumV()) {

            while (i < getNumV() && identified[i]) {
                ++i;

            }
            if (i == getNumV())
                break;
            theQueue.offer(i);

            color[i] = 1;
            identified[i] = true;
            while (!theQueue.isEmpty()) {
                int current = theQueue.remove();
                if (color[current] == -1) {
                    color[current] = 0;
                }
                Iterator<Edge> itr = edgeIterator(current);
                while (itr.hasNext()) {

                    Edge edge = itr.next();

                    int neighbor = edge.getDest();
                    if (color[neighbor] != color[current])
                        color[neighbor] = 1 - color[current];
                    else
                        return false;

                    if (!identified[neighbor]) {

                        identified[neighbor] = true;

                        theQueue.offer(neighbor);

                    }
                }
            }

        }
        return true;


    }



    public int addRandomEdgesToGraph (int edgeLimit) throws IOException {
        boolean directed=isDirected();


        Random random=new Random();

        int count=0;
        int insertedEdges=0;
        for (int i=0;i<edgeLimit;i++){

            int edgeSource=random.nextInt(edgeLimit);
            int edgeDest=random.nextInt(edgeLimit);


            if(!isEdge(edgeSource,edgeDest)){
                Edge temp=new Edge(edgeSource,edgeDest);
                insert(temp);
                insertedEdges++;
                count=0;
            }
            else{
                --i;
                count++;
            }
            if(count>10){
                return insertedEdges;
            }


        }




        return insertedEdges;

    }





}
