/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javaapplication3;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Locale;

import java.util.Scanner;

/**
 *
 * @author ORHAN
 * @param <T>
 */
@SuppressWarnings("unchecked")
public class BigramDyn <T> implements Bigram<T> {
    
    private int dataType;
    private triple <T>  AllBigr;
    private triple <T> MapBgr;
    private int allIndex=0;
    private int mapIndex=0;
    private int capacity=0;//NUMBER OF ELEMENTS IN A FILE
    
    public BigramDyn(int data) {///CONSTRUCTOR
        
        
        dataType=data;
    }

    /**
     *
     * @param filename
     * @throws myException
     */
    @Override
    public void readFile(String filename) throws myException {
        
   
        
        try {
            Scanner scan;
            scan = new Scanner(new File(filename));
            while(scan.hasNext()){
                String next = scan.next();
                capacity+=1;
            }
        } catch (FileNotFoundException ex) {
            throw new myException("Dosya bulunamadı");
        }
        
        AllBigr=new triple<>(capacity);
        
        MapBgr=new triple<>(capacity);
        try {
            Scanner scan;
            scan = new Scanner(new File(filename));
            scan.useLocale(Locale.US);
            
            if(dataType==1){
                T token1 = null;
                T token2;
                if(scan.hasNextInt())
                    token1=(T) (Object)  scan.nextInt();
                    
                while(scan.hasNextInt()){
                    token2=(T) (Object) scan.nextInt();
                    tripleAll(token1,token2,0);
                    tripleMap(token1,token2,0);
                    
                    token1=token2;
                }
                if(scan.hasNext()){
                    throw new myException("Element integer degil");
                }
                
                
            }
            else if(dataType==2){
                T token1=(T) (Object) "";
                T token2=(T) (Object) "";
                if(scan.hasNext())
                    token1=(T) (Object) scan.next();
                while(scan.hasNext()){
                    token2=(T) (Object) scan.next();
                    
                    tripleAll(token1,token2,0);
                    tripleMap( token1,token2,0);
                    token1=token2;
                }
                /* if(scan.hasNext()){
                
                }*/
            }
            else if(dataType==3){
                T token1=(T) (Object) 0;
                T token2=(T) (Object) 0;
                if(scan.hasNextDouble()){
                    token1=(T) (Object) scan.nextDouble();
                }
                while(scan.hasNextDouble()){
                    token2=(T) (Object) scan.nextDouble();
                    
                    tripleAll(token1,token2,0);
                    tripleMap(token1,token2,0);
                    token1=token2;
                }
                if(scan.hasNext()){
                    throw new myException("Element double degil");
                }
                        
                        }
        } catch (FileNotFoundException ex) {
            throw new myException("Dosya bulunamadı");
        }
        
        
        
        
        
    }

    @Override
    public int numGrams() {
        return capacity-1;
    }

    @Override
    public int numOfGrams(T x, T y) {
        int count=0;
        for(int i=0;i<allIndex;++i){
            if(AllBigr.first[i]==x && AllBigr.second[i]==y)
                count+=1;
        }
        return count;
    }
    
    
    @Override
    public String toString(){
        String AllLine="";
        
        for(int i=0;i<mapIndex;++i)////////////////MAP TUTAN ARRAY
        {   MapBgr.value[i]=0;
            for(int j=0;j<allIndex;++j)///BUTUN BIGRAMLARI TUTAN ARRAY
            {

                if((AllBigr.first[j]==MapBgr.first[i]) && (AllBigr.second[j]==MapBgr.second[i]))
                {/////////////////////////////////////////////////////////EGER MAP TUTAN ARRAYDEKI BIGRAMDAN VAR ISE
                    MapBgr.value[i]+=1;////MAP TUTAN ARRAYDEKI VALUE KISMI ARTTIRILIR
                }
            }
        }
	
        
        
        
        for(int i=1;i<mapIndex;++i){///////////////////BUBBLE SORT
		for(int j=0;j<mapIndex-i;++j){
			
			if(MapBgr.value[j]<MapBgr.value[j+1]){
				
				triple<T> temp;
                                temp = new triple<>(1);
                                
				temp.first[0]=MapBgr.first[j];
                                temp.second[0]=MapBgr.second[j];
                                temp.value[0]=MapBgr.value[j];
                                
				MapBgr.first[j]=MapBgr.first[j+1];
                                MapBgr.second[j]=MapBgr.second[j+1];
                                MapBgr.value[j]=MapBgr.value[j+1];
                                
				MapBgr.first[j+1]=temp.first[0];
			        MapBgr.second[j+1]=temp.second[0];
                                MapBgr.value[j+1]=temp.value[0];
                        }
		}
	}///////////////////////////////////////////////////////
        for(int i=0;i<mapIndex;++i){
            AllLine+="(";
            AllLine+=String.valueOf( MapBgr.first[i]);
            AllLine+=",";
            AllLine+=String.valueOf(MapBgr.second[i]);
            AllLine+=")";
            AllLine+="=";
            AllLine+=String.valueOf(MapBgr.value[i]);
            AllLine+=System.lineSeparator();
        }
        return AllLine;
    }
    /**
     *
     * @param first
     * @param second
     * @param val
     */
    public void tripleAll(T  first,T second,int val){
       
        AllBigr.first[allIndex]= first;
        AllBigr.second[allIndex]=second;
        AllBigr.value[allIndex]= val;
        allIndex+=1;
     
    }
    public void tripleMap(T first,T second,int val){
        
        for(int i=0;i<=mapIndex;++i){
            if(MapBgr.first[i]==first && MapBgr.second[i]==second)
            {
                return;
            }
        }
        MapBgr.first[mapIndex]=(T) first;
        MapBgr.second[mapIndex]=(T) second;
        MapBgr.value[mapIndex]=val;
        mapIndex+=1;
    }
    
    
    
}
