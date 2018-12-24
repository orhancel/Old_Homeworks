/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javaapplication3;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.Map;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Locale;
import java.util.Map.Entry;

/**
 *
 * @author ORHAN
 * @param <T>
 */
@SuppressWarnings("unchecked")
public class BigramMap<T> implements Bigram<T> {
    private final int dataType;
    private ArrayList<pair<T,T>> bigrams = new ArrayList<>();
    private HashMap<pair<T,T>,Integer> bigMap;
    
    
    public BigramMap(int data){
        this.bigMap = new HashMap<>();
        
        dataType=data;
    }
    @Override
    public void readFile (String filename) throws myException{
            

        
        try {
            Scanner scan;
            scan = new Scanner(new File(filename));
            scan.useLocale(Locale.US);
            
            if(dataType==1){
                int token1=0;
                int token2=0;
                if(scan.hasNextInt())
                    token1=scan.nextInt();
                
                while(scan.hasNextInt()){
                    token2=scan.nextInt();
                    bigrams.add(new pair(token1,token2));
                    bigMap.put(new pair(token1,token2),1);
                    token1=token2;
                }
                if(scan.hasNext()){
                    throw new myException("Element integer degil");
                }
                
                
            }
            else if(dataType==2){
                String token1="";
                String token2="";
                if(scan.hasNext())
                    token1=scan.next();
                while(scan.hasNext()){
                    token2=scan.next();
                    
                    bigrams.add(new pair(token1,token2));
                    bigMap.put(new pair(token1,token2),1);
                    token1=token2;
                }
                /* if(scan.hasNext()){
                
                }*/
            }
            else if(dataType==3){
                double token1=0;
                double token2=0;
                if(scan.hasNextDouble()){
                    token1=scan.nextDouble();
                }
                while(scan.hasNextDouble()){
                    token2=scan.nextDouble();
                    
                    bigrams.add(new pair(token1,token2));
                    bigMap.put(new pair(token1,token2),1);
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
       return bigrams.size();
    }

    @Override
    public int numOfGrams(T x, T y) {
        int count=0;
        for(pair<T,T> PairToken:bigMap.keySet()){
            
            if(PairToken.first==x && PairToken.second==y){
                count+=1;
            }
        }
        return count;
    }
    

    @Override
    public String toString() {
        String AllLine="";
        HashMap<pair<T,T>,Integer> Temp=new HashMap<>() ;
        
        for(Map.Entry<pair<T,T>,Integer> MapEntry:bigMap.entrySet()){////CALCULATE THE AMOUNT BİGRAMS OF A MAP
            MapEntry.setValue(0);
            for(pair<T,T> AllPairs:bigrams){
                if(MapEntry.getKey().first==AllPairs.first){
                    if (MapEntry.getKey().second==AllPairs.second) {
                        MapEntry.setValue(MapEntry.getValue()+1);
                    }

                }

            }
        }/////////////////
        
        
        Temp.putAll(bigMap);
        
        
        Map.Entry<pair<T,T>,Integer> max;/////TEMPORARY MAP TO HOLD A SINGLE KEY,VALUE PAIR
        max = Temp.entrySet().iterator().next();
       
        
        while(!Temp.isEmpty()){
            
            for(Map.Entry<pair<T,T>,Integer> tempEntry:Temp.entrySet()){

                if(max.getValue()<=tempEntry.getValue()){
                    max=tempEntry;
                }

            }
            AllLine+="(";
            AllLine+=String.valueOf(max.getKey().first);
            AllLine+=",";
            AllLine+=String.valueOf(max.getKey().second);
            AllLine+=")";
            AllLine+="=";
            AllLine+=String.valueOf(max.getValue());
            AllLine+=System.lineSeparator();
            
            Temp.remove(max.getKey());
            if(!Temp.isEmpty())
                max = Temp.entrySet().iterator().next();
        }
        return AllLine;
    }
}
