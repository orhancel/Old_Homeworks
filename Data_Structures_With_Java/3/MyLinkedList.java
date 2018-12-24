


import java.util.Iterator;

/**
 *
 * @author ORHAN
 * @param <T>
 */
public class  MyLinkedList <T>  {
    node<T> head;///START OF NORMAL LINKED LIST
    node<T> Dhead;//START OF DELETED NODES
    int size=0;//SIZE OF NORMAL LINKED LIST
    int Dsize=0;//SIZE OF DELETED NODES LIST
    node<T> tail;//END OF NORMAL LINKED LIST
    
    node <T> ItCurrent;//JUST TO USE IT AS TEMPORARY NODE FOR SWAP OPERATIONS
    
    /**
     *
     * @return
     */
    public Iterator<T> iterator(){///RETURNS CUSTOM ITERATORS SUBCLASS
        
        return new MyIterator <>();
    }
    
    /**
     *
     * @param <T>
     */
    public class MyIterator <T> implements Iterator<T>{/////CUSTOM ITERATOR
        private int index;
        private boolean removed;
        MyIterator (){
            index=0;
            removed=false;
        }
        
        /**
         *
         * @return
         */
        @Override
        public boolean hasNext() {///CUSTOM ITERATORS HASNEXT METHOD
            
            if(removed){/////IF REMOVE HAS BEEN CALLED,REITERATE THE LIST TO GET
               // TO THE NODE BEFORE THE DELETED ONE
                node<T> temp;
                temp= (node<T>) ItCurrent;
                ItCurrent=head;
                while(ItCurrent.next!=temp){///RE ITERATE THE LIST TO GO BACK TO THE WHERE
                    ItCurrent=ItCurrent.next;
                    
                removed=false;
                }
            }
            if(index==0){
                return head!=null;
            }
            else if(index==1)
                return head.next!=null;
            else
                return ItCurrent.next.next!=null;
        }

        /**
         *CURRENT NODE IS ALWAYS THE ONE BEFORE WE RETURNED
         * @return
         */
        @Override
        public T next() {////CUSTOM ITERATORS NEXT METHOD
            
            if(removed){/////IF REMOVE HAS BEEN CALLED,REITERATE THE LIST TO GET
               // TO THE NODE BEFORE THE DELETED ONE
                node<T> temp;
                temp= (node<T>) ItCurrent;
                ItCurrent=head;
                while(ItCurrent.next!=temp){///RE ITERATE THE LIST TO GO BACK TO THE WHERE
                    ItCurrent=ItCurrent.next;
                    
                removed=false;
                }
            }
            
            if(index==0){
                if(head!=null){
                    ++index;
                    ItCurrent= head;
                    return (T) ItCurrent.data;
                }
                else{
                    System.out.println("There is no next at  "+index);//CAN'T THROW EXCEPTİON TO THE MAIN CLASS
                    return null;
                }
                    
            }
            else if(index==1){
                if(ItCurrent.next!=null){
                    ++index;
                    
                    return (T) head.next.data;
                }
                    
                else
                    System.out.println("There is no next at  "+index);////
            }
            
            
            else{
                if(index==2){
                    ++index;
                    
                    
                    return (T) (ItCurrent=ItCurrent.next).next.data;
                }
                
                else if(ItCurrent.next!=null){
                    ++index;
                    
                    
                    return (T) (ItCurrent=ItCurrent.next).next.data;
                }
                else
                    System.out.println("There is no next at  "+index);
            }
            return null;
                
        }

        /**
         *CURRENT NODE IS ALWAYS THE ONE BEFORE WE RETURNED
         */
        @Override
        public void remove() {///ITERATORS REMOVE METHOD
            node<T> temp;
            if(index==1){
                temp=(node<T>) head;
                head=head.next;
                delete(temp);//SEND IT TO DELETED NODES LIST
               
                ItCurrent=head;
                return;
            }
            else if(ItCurrent.next!=null){
                temp=(node<T>) ItCurrent.next;
                if(ItCurrent.next.next!=null)
                    ItCurrent.next=ItCurrent.next.next;
                else{
                    tail=ItCurrent;
                }
                delete(temp);/////SEND IT TO DELETED NODES LIST
                
              
            }
            else
                System.out.println("Hasn't been iterating the list yet");
            
            
            
            --index;
            
        }
   
    }
    /*
    /**
     *
     * @return
     */
    public String reverseToString(){////
        return reverser(this.toString());

    }
    
    public String reverser(String str){//////RECURSIVE METHOD TO REVERSE A STRING
        if (str.length() <= 1) {
            return str;
        }
        else{
            
            return reverser(str.substring(1)) + str.charAt(0);
        }
        
    
    } 
    
    
    private node<T> reUse(Object data){///REUSE THE DELETED NODES FOR NEW NODES
        node<T> current;
        current = Dhead;
        if(Dsize>1){
            for(int i=0; i<Dsize-2 ;++i){
                current=current.next;
            }
            node<T> temp;
            temp=current.next;
            current.next=null;
            Dsize--;
            temp.data=(T) data;
            return temp;
        }
        else if(Dsize==1){
            Dsize--;
            node<T> temp;
            temp=Dhead;
            Dhead=null;
            return temp;
        }
        else{
            return null;
        }
            
     
    }
    
    private void delete(Object del){////DELETE METHOD TO STORE DELETED NODES TO USE IT AGAIN
        
        if(Dhead==null){
            
            Dsize++;
            Dhead=(node<T>) del;
            Dhead.next=null;
            
        }
        else{
            node<T> current;
            current = Dhead;
            while(current.next!=null){
                current=current.next;
            }
            Dsize++;
            
            current.next=(node<T>) del;
            current.next.next=null;
        }
        
    }

    
    
    /**
     *
     * @return 
     */
    public String deletedToString(){/////////////RETURNS STRING OF DELETED ELEMENTS
        node<T> current;
        if(Dsize<1){
            System.out.println("No deleted nodes left.All of them used");
            return null;
        }
        current=Dhead;
        String temp;
        temp=current.data.toString();
        for(int i=0;i<Dsize-1 ;++i){
            current=current.next;
            temp+=current.data.toString();
            temp+=" ";
            
            
        }
        return temp;
    }
    /**
     *
     * @param data
     */
    public void add(Object data){/////////////APPENDS ELEMENTS TO THE LIST
        
        if(head==null){
            ++size;
            head=new node(data);
            tail=head;     
        }
        else{
            if(Dsize>0){
                ++size;
                tail.next=reUse(data);
                tail=tail.next;  
            }
            else{
                ++size;
                tail.next=new node<>(data);
                tail=tail.next;  
            }
                   
        }          
    }
    
    
    T get(int index) throws Exception{
        
        if(index>size-1)
            throw new Exception("Index out of bound"); 
        int i=0;
        node<T> current;
        current=head;
        while(i!=index){
            ++i;
            current=current.next;
        }
        return current.data;
        
    }
    
    
    void remove(int index) throws Exception{////REMOVES NODE BY INDEX NUMBER
        
        if(index>size-1)
            throw new Exception("Index out of bound"); 
        
        int i=0;
        node<T> current;
        current=head;
        while(i<index-1){
           
            ++i;
            current=current.next;
        }
        
        node<T> temp;
        temp=current.next;
        if(current.next.next!=null){
            current.next=current.next.next;
            size--;
            delete(temp);      
        }
        else{
            current.next=null;
            tail=current;
            --size;
            delete(temp);    
        }
        
        
    }
    void remove(T element) throws Exception{//REMOVES NODE BY IT'S NAME
        
        
        int i=0;
        node<T> current;
        node<T> temp=null;
        current=head;
        while(!element.equals(current.data)){
            ++i;
            temp=current;
            current=current.next;
        }
        
        if(temp==null)
            throw new Exception("Index out of bound"); 
        
        temp=current.next;
        current.next=current.next.next;
        temp=null;
             
    }

    
          
        
    private class node<T>{///NODE  SUBCLASS OF SINGLE LINKED LIST.
        T data;
        node<T> next;
        node(Object o){
            data=(T) o;
        }
              
    }
    /**
     *
     * @return
     */
    @Override
    public String toString()
    {
        node<T> current;
        current=head;
        
        T temp;
        temp = (T) current.data;
        if(size==1){
            return temp.toString();
        }
        current=current.next;
        while(!current.equals(tail)){
            temp+=" ";
            temp+=current.data.toString();
            
            current=current.next;
        }
        temp+=" ";
        temp+=tail.data.toString();
        return (String) temp;
            
    }
    
      
}
