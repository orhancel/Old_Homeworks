import java.io.*;
import java.util.Iterator;
import java.util.LinkedList;

/**
 * Created by ORHAN on 6.04.2017.
 */
public class FamilyTree <E> extends BinaryTree{

    LinkedList<Node<E>> liste=new LinkedList<>();

    protected void RecursiveTraversal(Node < E > rootNode){

        if(rootNode !=  null) {
            //Visit the node by Printing the node data
            //System.out.printf("%d ",root.data);
            liste.add(rootNode);

            RecursiveTraversal(rootNode.left);
            RecursiveTraversal(rootNode.right);
        }

    }


    public void Add(E person,E Parent ,String nick) throws Exception {
        Boolean right=false;
        Node < E > newNode = new Node <> (person) ;
        Node<E> current = root;
        Node<E> parent = null;

        if(root==null){
            root = newNode;
            liste.clear();
            return;
        }
        String nickParent=nick.substring(4);


        Boolean ebu;
        System.out.println(nick.substring(0,3));
        if(nick.substring(0,3).equals("ebu")){
            ebu=true;
        }
        else{
            ebu=false;
        }




        RecursiveTraversal(root);
        Iterator<Node<E>> it=liste.iterator();

        while(true){

            if(!ebu){
                if(current.toString().equals(nickParent.toString())){
                    Node<E> temp=current;
                    current=current.left;
                    while (current!=null){
                        if(current.toString().equals(Parent.toString())){
                            break;
                        }
                        else {
                            current=current.right;
                        }

                    }
                    if(current==null){
                        current=temp;
                        current=current.left;
                        continue;
                    }


                }
            }
            if(current.data.equals(Parent))
            {
                if(ebu){

                    if(!person.toString().equals(nickParent.toString())){///ayşe,hasan,ebu-ayşe icin
                        Node<E> temp=current;
                        current=current.left;
                        while (current!=null){
                            if(current.data.equals(nickParent)){
                                break;
                            }
                            else{
                                current=current.right;
                            }
                        }
                        if (current==null){
                            current=temp;
                            parent = current;
                            current=current.left;
                            continue;
                        }
                        else {
                            current=temp;
                        }
                    }

                }


                if(current.left==null){
                    current.left = newNode;
                    liste.clear();
                    return;
                }
                else{
                    current = current.left;
                    while (true){

                        if(current.right==null){
                            current.right=newNode;
                            liste.clear();
                            return;

                        }
                        current=current.right;
                    }

                }
            }
            else {
                if(it.hasNext())
                    current=it.next();
                else {
                    throw new Exception("Error.Parent or Grandparent doesn't found");
                }
            }


            /*
            else
            {
                if(current.right!=null){
                    current=current.right;
                    right=true;
                }

                else {
                    if(right){
                        current=parent.left;
                        right=false;
                    }

                    parent = current;
                    current=current.left;
                }

            }*/
        }



    }

}
