import java.io.*;
import java.util.Iterator;
import java.util.LinkedList;

/**
 * Created by ORHAN on 6.04.2017.
 */
public class BinarySearchTree < E extends Comparable> extends BinaryTree< E > {

    protected LinkedList <E> levelList  = new LinkedList<>();


    public BinarySearchTree(){
        super.root=null;
    }

    protected BinarySearchTree(Node < E > root) {
        super.root = root;
    }

    public BinarySearchTree(E data, BinarySearchTree < E > leftTree,
                            BinarySearchTree < E > rightTree) {
        root = new Node < E > (data);
        if (leftTree != null) {
            super.root.left = leftTree.root;
        }
        else {
            super.root.left = null;
        }
        if (rightTree != null) {
            super.root.right = rightTree.root;
        }
        else {
            super.root.right = null;
        }
    }


    private void LevelTraversal(Node root){
        LinkedList<Node> level  = new LinkedList<>();
        level.add(root);
        while(!level.isEmpty()){
            Node node = level.poll();

            levelList.add((E) node.data);

            if(node.left!= null)
                level.add(node.left);
            if(node.right!= null)
                level.add(node.right);
        }
    }

    public void LevelOrderTraversal(){

        LevelTraversal(super.root);

        Iterator<E> it=levelList.iterator();

        while (it.hasNext())
            System.out.println(it.next());

        levelList.clear();
    }

}
