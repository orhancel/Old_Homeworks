#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 


int main (int argc, char** argv) {
       
        char* Ara=argv[1];
        char* dosyaYolu=argv[2];
	    FILE *logFile;
        logFile = fopen("log.txt", "w");
        fclose(logFile);
		int mainProcces=getpid();
        
        if (argc < 2) {
            printf ("Usage: testprog <dirname>\n");
            return 1;
        }
        ForkAt(dosyaYolu,Ara);
       
        
		/*if(getpid()==mainProcces){
			printf("Fclose logFile\n");
    	fclose(file);
   		}*/
        
        if(mainProcces==getpid()){
            char ch;
            int bulunan=0;
            FILE *logFile;
            logFile = fopen("log.txt", "r");

            while(fscanf(logFile,"%c",&ch)!=EOF){
                if(ch=='\n'){
                    ++bulunan;
                }
                
                
            }
            fclose(logFile);
            logFile = fopen("log.txt", "a");
            fprintf(logFile,"%d %s were found in total.\n",bulunan,Ara);
            fclose(logFile);
        }
     
        
        
        return 0;
		
}


int ForkAt(char* directory,char* ara){
	int len=0;
	struct dirent *pDirent;
    DIR *pDir;
    struct stat statbuf;
 	pDir = opendir (directory);

 	int parentPID;
 	pid_t childPID;

 	if (pDir == NULL) {
        printf ("Cannot open directory '%s'\n", directory);
        return 0;
    }


    parentPID=getpid();
 	while ((pDirent = readdir(pDir)) != NULL && getpid()==parentPID) {
 		char* path;
	    path=malloc((strlen(pDirent->d_name)+2+strlen(directory))*sizeof(char));
        
        strcpy(path,directory);
        strcat(path,"/");
        strcat(path,pDirent->d_name);

 		stat(path, &statbuf);

 		if(S_ISDIR(statbuf.st_mode))
 		{
 			if(strcmp(pDirent->d_name,"..")!=0 && strcmp(pDirent->d_name,".")!=0){
 				
	 			ForkAt(path,ara);
	 			
	 			
 			}
 			
 				
 		}
        else if((pDirent->d_name[strlen(pDirent->d_name)-1]!='~') && (strcmp(pDirent->d_name,"log.txt")!=0)){
        	
	        

	        if(getpid()==parentPID){
	    		childPID=fork();
	    		if(childPID < 0){
	    			printf("Fork failed\n");
	    			
	    			
	    		}
	    		else if(getpid()==parentPID)
	    			len++;
	    		else if(childPID==0){
	    			
	    		
	    			read(path,ara);
	    			
	    			free(path);
	    			
	    			exit(0);
	    			
	    			
	    		}
	    		/*
	    		else if(getpid()==parentPID){
	    			wait(NULL);
	    			printf("freeee path  %s pid %d \n",path,getpid());
	    			

	    		}*/
	    		

	    		

	    	}
	    	
	    	
        }
        free(path);
        
        
    }
    
    if(getpid()==parentPID){
    	
    	close(pDir);
        
    	while(wait(NULL) && len>0){
    		--len;
    	}
       

    }
   
    
    return 1;

    
    

}



int read(char* dosyaAdi,char* Ara){/*Dosya okuma fonksiyonu.Bulunan sayısını return eder.*/

	FILE* dosya;
	FILE *logFile;
    logFile = fopen("log.txt", "a");
    
    						/*Dosya pointerı*/
    /*char * dosyaPath=malloc(strlen(dosyaAdi)+strlen(directory)+2);
    strcpy(dosyaPath,directory);
    strcat(dosyaPath,"/");
    strcat(dosyaPath,dosyaAdi);*/
    dosya=fopen(dosyaAdi,"r");			/*Dosya açma*/
	if(dosya==NULL){					/*Dosya açma kontrolü*/
		printf("Dosya bulunamadı\n");
		return 0;
	}



	int stringLen=0,satir=1,sutun=0,i=0,Bulunan=0,counter=0;
    char ch;
    bool emtyFile;
    emtyFile=true;
	for(i=0; Ara[i] !='\0' ;++i){/*Aranacak stringin uzunluğunu bulma*/
            stringLen+=1;
    }
   	while((ch=fgetc(dosya))!=EOF){/*Dosyayı karakter karakter oku ve kontrol et*/
        emtyFile=false;
        ++sutun;			/*kelimenin ilk karakteri alınır ve sutun 1 arttırılır*/
        if(ch=='\n')		/*Satır sonuna gelince satır 1 arttırılır ve sutun sıfırlanır*/
        {   
            sutun=0;
            ++satir;
        }
        else if(ch==' '){/*ilk karakter boşluk olamaz.Ama karakterler arasında yok sayılır*/
            continue;
        }
        else if(ch==Ara[0])
        {
            for(i=0;i<stringLen;++i)/*aranacak kelimenin boyunda dosyadan karakter okunur*/
            {
                counter+=1;/*Dosyadan okunan karakter sayısı.Her yeni String kontrolünde sıfırlanır*/
               	while(ch==' ' || ch=='\n' || ch=='\t'){/*ilk karakter boşluk olamaz.Ama karakterler arasında yok sayılır*/
					ch=fgetc(dosya);
                   	counter+=1;/*Counter ,FOR döngüsüne girdikten sonra dosyadan kaç tane karakter okunduğunu tutar*/
                }                
                if(ch!=Ara[i] && ch!=' ' && ch!='\n' && ch!='\t'){/*Eğer farklı bir karakter bulunursa ,FOR döngüsünden çıkılır*/
                    if((ch=fgetc(dosya))!=EOF){/*Eğer sıradaki karakter aranan kelimedeki karaktere eşit değilse "COUNTER" kadar dosyada geri gidilir*/
                     	fseek(dosya,-(counter),SEEK_CUR);/*Aslında COUNTER-1 kadar gidilir ama IF statement'ında dosya sonu kontrolü yapılırken karakter okunur*/
                    }
                    else{

						fclose(dosya);/*Dosya sonuna geldiysek dosya kapatılır*/
                        printf("%d  bulunan\n", Bulunan);
                        
                        fclose(logFile);
						return Bulunan;
					}                        
                	counter=0;
                    break;
                }              
                if(i<stringLen-1){/*Yeterince karakter okumadıysak ve hata yoksa tekrar okunur ve döngü devam eder*/
                    ch=fgetc(dosya);                   
                }
                else if(i==stringLen-1){/*Yeterince okuma yapıldıysa ve döngü bozulmadıysa kelimeyi bulduk*/
                    fseek(dosya,-(counter-1),SEEK_CUR);/*Dosya COUNTER-1 kadar başa sarılır*/
                    Bulunan++;/*Bulunan aranan kelime sayısı*/
                    printf("%s=[%d,%d] %s first character is found.  \n",dosyaAdi,satir,sutun,Ara);
                    fprintf(logFile, "%s=[%d,%d] %s first character is found.\n",dosyaAdi,satir,sutun,Ara);
                    counter=0;/*Counter sıfırlanır*/
                }
			}
        }
	}
    if(emtyFile){
        printf("Dosya Bos %s \n",dosyaAdi);
        
        
    }
    
    
    fclose(logFile);
    fclose(dosya);
    free(dosyaAdi);
    free(Ara);
    return Bulunan;
}















/*


void checkFile(){

	char* fileType=&pDirent->d_name[strlen(pDirent->d_name)-4];


	if(strcmp(fileType,".txt")==0)
    {
    	printf("%s text\n", pDirent->d_name);
    }





}





int checkFileOrDirectory(){
	struct dirent *pDirent;
    DIR *pDir;
    struct stat statbuf;
    pDir = opendir (v[1]);

   

    
                

        closedir (pDir);


}*/
