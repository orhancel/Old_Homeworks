#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <pthread.h>



typedef struct{
	char  filename[256];
	char  aranan[256];
	int total;
	int lineNumber;
	int searchThreads;
	int searchFile;
	int searchDirectory;


}threadStruct;

threadStruct ForkAt(char* directory,char* ara);

void * threadFonk(void * arg){
	threadStruct* STR;
	STR=(threadStruct *) arg;
	printf(" [%s]  threadFonk  [%s] aranan\n", STR->filename,STR->aranan);
	STR->total=readFile(STR->filename,STR->aranan);
	STR->lineNumber=findLineNumber(STR->filename,STR->aranan);
	printf("%s  total  %d aranan\n", STR->filename,STR->total);
	pthread_exit(NULL);


}

void err_sys(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}





int main (int argc, char** argv) {
       
        char* Ara=argv[1];
        char* dosyaYolu=argv[2];
	    FILE *logFile;
        logFile = fopen("log.txt", "w");
        fclose(logFile);
		int mainProcces=getpid();
		/*struct sigaction sinyal;

	    sinyal.sa_flags=0;
	    sinyal.sa_handler=yakala;*/
        
        if (argc < 2) {
            printf ("Usage: testprog <dirname>\n");
            return 1;
        }

/*
	     if(sigemptyset(&sinyal.sa_mask)  || sigaction(SIGUSR1,&sinyal,NULL)==-1 ){
	      
	       fprintf(stderr, "sinyal gelmedi  Client'ın okumasını bekliyor111\n");
	      }

	   if( sigemptyset(&sinyal.sa_mask)   || sigaction(SIGUSR2,&sinyal,NULL)==-1 ){
	    
	     fprintf(stderr, "sinyal gelmedi  Client'ın okumasını bekliyor111\n");
	    }
*/
        
        threadStruct toplam;////////////toplam aranan sayısı olacak
        toplam=ForkAt(dosyaYolu,Ara);////////////Ana process i cagırma
       
       
		/*if(getpid()==mainProcces){
			printf("Fclose logFile\n");
    	fclose(file);
   		}*/
        
        if(mainProcces==getpid()){
           


            FILE *logFile;
           /* logFile = fopen("log.txt", "r");

            while(fscanf(logFile,"%c",&ch)!=EOF){
                if(ch=='\n'){
                    ++bulunan;
                }
                
                
            }
            fclose(logFile);*/
            logFile = fopen("log.txt", "a");
            fprintf(logFile,"%d %s were found in total.\n",toplam.total,Ara);///////Log dosyasına toplam sayıyı yazdırma//////
            fprintf(stderr, "%d %s were found in total.\n",toplam.total,Ara);
            fprintf(stderr, "%d  line in total.\n",toplam.lineNumber);
            fclose(logFile);
        }
     
        
        
        return 0;
		
}


threadStruct ForkAt(char* directory,char* ara){
	int len=0;
	int i=0;
	int * temp;
	struct dirent *pDirent;
    DIR *pDir;
    threadStruct sum;
    sum.total=0;
    sum.lineNumber=0;
    sum.searchDirectory=0;
    sum.searchFile=0;
    sum.searchThreads=0;


    pthread_t TID;
    pthread_t TIDS[100];/*directory deki dosya sayısı*/

    threadStruct strArr[100];/*directory deki dosya sayısı*/

    struct stat statbuf;
 	pDir = opendir (directory);
    int SubDirectories=0;



 	int parentPID;
 	pid_t childPID;

 	if (pDir == NULL) {
        printf ("Cannot open directory '%s'\n", directory);
        return sum;
    }

    int fdp[2];

    if (pipe(fdp) < 0)/////////////////////PIPE/////////////
        err_sys("pipe");

    
 


    parentPID=getpid();
    int structCounter=0;

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
 				if(getpid()==parentPID){

                childPID=fork();
                SubDirectories=+1;
                if(childPID < 0){
                    printf("Fork failed\n");
                    
                    
                }
                
                else if(getpid()==parentPID)
                    len++;
                else if(childPID==0){
                    threadStruct toplam;

                    
                    toplam=ForkAt(path,ara);//////////////RECURSIVE////
                    
                    /*fprintf(stderr, "return FORK AT\n");*/
                  
                    close(fdp[0]);

         
              

	    			if(write(fdp[1], &toplam, sizeof(threadStruct))<0)/////////pipe 'a yaz////////'
                        printf("Failed write %s -- %s\n",path,strerror(errno));
                    
                    close(fdp[1]);
                  

                    free(path);
              

                    /*printf("sum at [%s]  [%d]\n",path,toplam );*/

                    
                    
                    exit(0);
                    
                    
                }
          
                

                

            }
	 			
	 			
	 			
 			}
 			
 				
 		}
        else if((pDirent->d_name[strlen(pDirent->d_name)-1]!='~') && (strcmp(pDirent->d_name,"log.txt")!=0 && strcmp(pDirent->d_name,"myfifo")!=0 && 
        	strcmp(&pDirent->d_name[strlen(pDirent->d_name)-4],".txt")==0  )) {
        	
	        

	   
        		printf("strcpy %s\n",path);
	        	strcpy(strArr[structCounter].filename,path);
	        	strcpy(strArr[structCounter].aranan,ara);
	        	printf("%d struct counter artıs %s \n",structCounter,strArr[structCounter].filename );

	    		pthread_create(&TID,NULL,threadFonk,(void *) (strArr+structCounter) );

	    		TIDS[structCounter]=TID;

	    		
	    		++structCounter;


	    	
        }
        free(path);
  
   
        
        
    }


    threadStruct val;

    int result;
    

    
    val.total=0;
    val.lineNumber=0;

    val.searchDirectory=0;
    val.searchFile=0;
    val.searchThreads=0;
   
    


    for(i=0;i<structCounter;i++){
    	printf("join %d i %d\n",structCounter ,i);
    	pthread_join(TIDS[i],(void ** )&temp  );
    	
    	sum.total+=strArr[i].total;
    	sum.lineNumber+=strArr[i].lineNumber;
    	printf(" %d sum %d total %s name\n",sum.total ,strArr[i].total,strArr[i].filename);
    	printf("%d  sum line lineNumber\n", sum.lineNumber);

    }
    	
      
        close(fdp[1]);
        
        while ((result = read(fdp[0], &val, sizeof(threadStruct))) > 0){///////////pipe oku////

            /*printf("value %d\n", val);*/

           
            sum.total+=val.total;
    		sum.lineNumber+=val.lineNumber;
    		sum.searchDirectory=val.searchDirectory+1;

        }
      
       
        
       
      

        closedir(pDir);



        close(fdp[0]);

     
    return sum;

    
    

}

int findLineNumber(char* dosyaAdi,char* Ara){
	FILE* dosya;
	char ch;
	int lineNumber=0;;
	dosya=fopen(dosyaAdi,"r");			/*Dosya açma*/
	if(dosya==NULL){					/*Dosya açma kontrolü*/
		printf("Dosya bulunamadı [%s]\n",dosyaAdi);
		return 0;
	}
	while((ch=fgetc(dosya))!=EOF){
		if(ch=='\n')
			lineNumber++;

	}
	printf("returned line number %d \n",lineNumber );
	return lineNumber;



}


int readFile(char* dosyaAdi,char* Ara){/*Dosya okuma fonksiyonu.Bulunan sayısını return eder.*/

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
		printf("Dosya bulunamadı [%s]\n",dosyaAdi);
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
                        
                        
                        fclose(logFile);
                        /*fprintf(stderr, "%d bulunan readFile path [%s]\n", Bulunan,dosyaAdi);*/
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
                    fprintf(stderr,  " %d - %ld  %s=[%d,%d] %s first character is found.\n",(int)getpid(),(long) pthread_self(),dosyaAdi,satir,sutun,Ara );
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
   /* free(dosyaAdi);
    free(Ara);*/
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
