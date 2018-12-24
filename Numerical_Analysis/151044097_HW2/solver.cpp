

#include <cstdlib>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <sstream>

#include <cmath> 
#include <math.h> 

double getMax(double x[],int size);
double getMaxDiff(double x[],double xTemp[],int size);
void gauss();

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    
    if((argv[2]=="GESP") || (argv[2]=="gesp")){
        gauss();
        return 0;
    }
    else if((argv[2]=="JCB") || argv[2]=="jcb"){
        ifstream file;
    file.open(argv[4]);
    int satir=0;
    int sutun=0;
    string line;
    
    
    while(getline(file,line)){
        
        satir++;
       
        istringstream str(line);
        string parts;
        sutun=0;
        while(getline(str,parts,',')){
            sutun++;
            
        }
            
    }
    double matris[satir][sutun];
    file.close();
    file.open("system.txt");
    satir=0;
    sutun=0;
    while(getline(file,line)){
        
        cout<<"line "<<line<<endl;
        
        istringstream str(line);
        string parts;
        sutun=0;
        while(getline(str,parts,',')){
            matris[satir][sutun]=stoi(parts);
            
            cout<<"out "<<parts<<" "<<satir<<" "<<sutun<<endl;
            sutun++;
        }
        satir++;
            
    }
    
    cout<<"satir  "<<satir<<endl;
    cout<<"sutun "<<sutun<<endl;
    double x[satir];
    double xTemp[satir];
    int t=sutun-1;
    while(t>=0){
        x[t]=0;
        xTemp[t]=0;
        --t;
    }
    int iterasyon=0;
    cout<<"while"<<endl;
    while(true){
        for(int i=0;i<satir;i++){
            for(int j=0;j<sutun-1;j++){
                if(i!=j)
                    x[i]-=(xTemp[j]*matris[i][j])/matris[i][i];
                

            }
            x[i]+=(matris[i][sutun-1]/matris[i][i]);
            
            
        }
        

        if((getMaxDiff(x,xTemp,sutun-1)/getMax(x,sutun-1))<0.001)
            break;
        cout<<"-------------"<<endl;
        for(int i=0;i<satir;i++)
            cout<<"x["<<i<<"] = "<<x[i]<<endl;
        for(t=0;t<satir;++t){
            xTemp[t]=x[t];
            x[t]=0;
        }
        
        iterasyon++;
        if(iterasyon>100)
            break;
    }
    cout<<"-------------"<<endl;
    for(int i=0;i<satir;i++)
            cout<<"x["<<i<<"] = "<<x[i]<<endl;
    
    cout<<"itersyon = "<<iterasyon<<endl;
    
 
 
    }   
    
    
    
    file.close();

    return 0;
}

double getMax(double x[],int size){
    double max=abs(x[size-1]);
    
    while(size>0){
        if(abs(x[size-1])>max){
            max=abs(x[size-1]);
        }
        size--;
    }
    return max;
    
}

double getMaxDiff(double x[],double xTemp[],int size){
    
    double temp;
    double max;
    
    temp=x[size-1]-xTemp[size-1];
    max=abs(temp);
    size--;
    while(size>0){
        temp=x[size-1]-xTemp[size-1];
        if(abs(temp)>max)
            max=abs(temp);
        size--;
    }
    return max;
    
    
    
}

void gauss(){

    ifstream file;
    file.open("system.txt");
    int satir=0;
    int sutun=0;
    string line;
    
    
    while(getline(file,line)){
        
        satir++;
       
        istringstream str(line);
        string parts;
        sutun=0;
        while(getline(str,parts,',')){
            sutun++;
            
        }
            
    }
    double matris[satir][sutun];
    file.close();
    file.open("system.txt");
    satir=0;
    sutun=0;
    while(getline(file,line)){
        
        cout<<"line "<<line<<endl;
        
        istringstream str(line);
        string parts;
        sutun=0;
        while(getline(str,parts,',')){
            matris[satir][sutun]=stod(parts);
            
            cout<<"out "<<matris[satir][sutun]<<" "<<satir<<" "<<sutun<<endl;
            sutun++;
        }
        satir++;
            
    }
    
    cout<<"satir  "<<satir<<endl;
    cout<<"sutun "<<sutun<<endl;
    
    double max[satir];
    for(int i=0;i<satir;i++){
        max[i]=getMax(matris[i],satir);
        cout<<max[i]<<endl;
    }
    
    for(int i=0;i<satir-1;i++){
        int index=0;
        
        if(i!=satir-1){
            double maxDivision;
           
            maxDivision=matris[i][i]/max[i];
            cout<<"asd  "<<matris[i][i]<<"  adsa"<<endl;
            cout<<"asd  "<<max[i]<<"  adsa"<<endl;
            cout<<"asdas  "<<maxDivision*10<<"  adas"<<endl;
            for(int t=i+1;t<satir;t++){

                if((matris[t][i]/max[t])>maxDivision){
                    maxDivision=matris[t][0]/max[t];
                    index=t;
                }
            
            }
        }
           
        if(index!=i){
            double temp[sutun];
            for(int t=0;t<sutun;t++){
                temp[t]=matris[i][t];
                cout<<"temp  "<<temp[t]<<endl;
                matris[i][t]=matris[index][t];
                matris[index][t]=temp[t];
            }
        }
        
        for(int j=i+1;j<satir;j++){
            double divide=matris[j][i]/matris[i][i];
            cout<<"divide   "<<divide<<endl;
            cout<<"divide2  "<<matris[j][i]<<endl;
            cout<<"divide3  "<<matris[i][i]<<endl;
            
            for(int t=0;t<sutun;t++){
                cout<<"divide4 b "<<matris[j][t]<<endl;
                cout<<"divide4 b "<<matris[i][t]*divide<<endl;
                matris[j][t]=matris[j][t]-(matris[i][t]*divide);
                if(matris[j][t]<0.00001)
                    matris[j][t]=0;
                cout<<"divide4 a "<<matris[j][t]<<endl;
            }
            
        }
    }
    
    double x[satir];
    
    x[satir-1]=(matris[satir-1][sutun-1])/matris[satir-1][sutun-2];
    int count=1;
    for(int i=satir-2;i>=0;i--){
        for(int j=0;j<count;j++){
            x[i]-=(x[i+1+j]*matris[i][i+1+j])/matris[i][i];
        }
        x[i]+=(matris[i][sutun-1])/matris[i][i];
        count++;
     
        
    }
    for(int i=0;i<satir;i++)
        cout<<"x["<<i<<"] = "<<x[i]<<endl;
    
    file.close();
   
    
    
        
    


}



   /*
    while(satir>=0){
        while(sutun>=0){
            cout<<" matris "<<matris[satir][sutun]<<endl;
            sutun--;
        }
        sutun=4;
        satir--;
    }*/
