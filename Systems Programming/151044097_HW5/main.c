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
#include <time.h>
#include <signal.h>
#include <semaphore.h>
#include  <sys/msg.h>

#include <sys/shm.h>


static int max=0;
static int currentThread=0;
static int mainPID=0;
static sem_t sharedsem;
static int cascade=0;
static int errorNo=0;

static volatile sig_atomic_t finish=0;
static volatile sig_atomic_t errFinish=0;

int msqid;


typedef struct{
    
    int total;
    int lineNumber;
    int searchThreads;
 
    int searchDirectory;
    


}SharedStruct;///used as a shared memory




typedef struct{
	char  filename[256];
	char  aranan[256];
	int total;
	int lineNumber;
	int searchThreads;
	int searchFile;
	int searchDirectory;
    SharedStruct* sharedPointer;


}threadStruct;///used by thread function


typedef struct{
    long mtype;
    char mtxt[20];
  

}mymsg_t;//used by message queue






int detachandremove(int shmid,void *shmaddr);
threadStruct ForkAt(char* directory,char* ara);



int IncShared(){///currentThread değişkenini  arttırmak için kullanılır
	while(sem_wait(&sharedsem)==-1)///Kritik bölge için Semaphore 
		if(errno!=EINTR)
			return -1;

	++currentThread;

	if(currentThread>max){///currentThread ,Max değişkeninden fazlaysa ,currentThread değeri max olur

		max=currentThread;
		
	}
	return sem_post(&sharedsem);


}
int DecrShared(){//currentThread değişkenini  azaltmak için kullanılır
	while(sem_wait(&sharedsem)==-1)///Kritik bölge için Semaphore 
		if(errno!=EINTR)
			return -1;

	--currentThread;
	return sem_post(&sharedsem);

}

void * threadFonk(void * arg){


	while(kill(mainPID,SIGUSR1)==-1){
  			fprintf(stderr, "SIGUSR2 sinyali gönderilemedi\n" );
  			fprintf(stderr, "%d pid\n",getpid() );
  			exit(0);

  		}

  			
	threadStruct* STR;
	STR=(threadStruct *) arg;
	/*printf(" [%s]  threadFonk  [%s] aranan\n", STR->filename,STR->aranan);*/
	STR->total=readFile(STR->filename,STR->aranan);

    STR->sharedPointer->total+=STR->total;

	STR->lineNumber=findLineNumber(STR->filename,STR->aranan);

    STR->sharedPointer->lineNumber+=STR->lineNumber;


	/*printf("%s  total  %d aranan\n", STR->filename,STR->total);*/
	
	while(kill(mainPID,SIGUSR2)==-1){
  			fprintf(stderr, "SIGUSR2 sinyali gönderilemedi\n" );
  			fprintf(stderr, "%d pid\n",getpid() );
  			exit(0);

  		}
	
	return 0;
	/*pthread_exit(NULL);*/




}

void err_sys(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}


void yakala(int sinyalNo){////Sinyal fonksiyonu

	
	if(sinyalNo==SIGUSR1){///SIGUSR1 geldiğing ,currentThread değişkeni arttırılır
		signal(SIGUSR1,yakala);
		IncShared();//////currentThread değişkeni aynı anda çalışan thread sayısını bulmak için kullanılır
		
	}
	else if(sinyalNo==SIGUSR2){///SIGUSR geldiğing ,currentThread değişkeni azaltılır
		signal(SIGUSR2,yakala);
		DecrShared();
	}
	
	


              
}

void bitir(int sinyalNo){

	finish=1;
	killpg( 0, SIGINT);
    

}
void errorDurumu(int sinyalNo){

	finish=1;
	errFinish=1;
	killpg( 0, SIGINT);
    

}


int main (int argc, char** argv) {
	 max=0;
currentThread=0;
 mainPID=0;
 int i=0;

 int key=1234;


if((msqid=msgget(key,S_IRUSR|S_IWUSR|IPC_CREAT))<0){
    perror("Messege queue initialize error");
    return 1;
}



 while(sem_init(&sharedsem,0,1) == -1){///////////SEMAPHORE INITILİSATİON
 	perror("Failed to initialize semaphore");
 	errorNo=errno;
		signal(  SIGQUIT,errorDurumu);
		
		if(kill(mainPID,SIGQUIT)==-1){
  			fprintf(stderr, "SIGQUIT sinyali gönderilemedi\n" );
  			fprintf(stderr, "%d pid\n",getpid() );
  			

  		}
 }


       clock_t begin = clock();
        char* Ara=argv[1];
        char* dosyaYolu=argv[2];
	    FILE *logFile;
        logFile = fopen("log.txt", "w");
        fclose(logFile);
		int mainProcces=getpid();


		signal(SIGUSR1,yakala);
		signal(SIGUSR2,yakala);
		signal(SIGINT,bitir);
		

        if (argc < 2) {
            printf ("Usage: testprog <dirname>\n");
            return 1;
        }
        mainPID=getpid();
		
        
        threadStruct toplam;////////////toplam aranan sayısı olacak
        toplam=ForkAt(dosyaYolu,Ara);////////////Ana process i cagırma
        toplam.total=0;
        toplam.searchDirectory=0;
        toplam.lineNumber=0;
        toplam.searchThreads=0;


        
	   mymsg_t myMessegeStruct;
       int temp[4];
                
        
       for(;;){
            
            if(msgrcv(msqid,&myMessegeStruct,sizeof(myMessegeStruct)+1,1,MSG_NOERROR | IPC_NOWAIT)==-1){
                break;
                perror("Failed to read message queue");
                return 1;
            }

            sscanf(myMessegeStruct.mtxt,"%d %d %d %d ",&temp[0],&temp[1],&temp[2],&temp[3]);
         
           
            toplam.total+=temp[0];
            toplam.searchDirectory+=temp[1];
            toplam.lineNumber+=temp[2];
            toplam.searchThreads+=temp[3];
            

       }

        

  

        msgctl(msqid,IPC_RMID,NULL);

        
        if(mainProcces==getpid()){



           


            FILE *logFile;
         
            clock_t end = clock();
			double time_spent = ((double)(end - begin) / CLOCKS_PER_SEC )*1000;
            logFile = fopen("log.txt", "a");
            fprintf(logFile," %d %s were found in total. \n",toplam.total,Ara);///////Log dosyasına toplam sayıyı yazdırma//////
            fprintf(stderr,"Total number of strings found : %d \n",toplam.total);
            fprintf(stderr, "Number of directories searched:  %d (Counting the first directory) \n",toplam.searchDirectory+1);
            fprintf(stderr, "Number of files searched:  %d\n",toplam.searchThreads);
            fprintf(stderr, "Number of lines searched:  %d\n",toplam.lineNumber);
            fprintf(stderr, "Number of search threads created:   %d\n",toplam.searchThreads);
            fprintf(stderr, "Number of cascade threads created:   %d\n",cascade);
            fprintf(stderr, "Total run time, in milliseconds.   %f \n",time_spent);
            fprintf(stderr, "Max # of threads running concurrently:   %d\n",max);
            fprintf(stderr, "Shared Memory Number: %d  Size: %d\n",toplam.searchDirectory+1,sizeof(SharedStruct));

            if(errFinish==1)
            	fprintf(stderr, "Exit condition:     due to ErrorNo:%d \n",errorNo);
            else if(finish==1)
            	fprintf(stderr, "Exit condition:     due to SIGINT \n");
            else
            	fprintf(stderr, "Exit condition:     normal \n");
             
            
            fclose(logFile);
        }
     
        
        
        return 0;
		
}

int fileCount(char* directory){
	struct dirent *pDirent;
	DIR *pDir;
	pDir = opendir (directory);
	int count=0;

	if (pDir == NULL) {
        printf ("Cannot open directory '%s'\n", directory);
        errorNo=errno;
		signal(  SIGQUIT,errorDurumu);
		
		if(kill(mainPID,SIGQUIT)==-1){
  			fprintf(stderr, "SIGQUIT sinyali gönderilemedi\n" );
  			fprintf(stderr, "%d pid\n",getpid() );
  			

  		}
        return 100;
    }
    while ((pDirent = readdir(pDir)) != NULL && finish!=1){

    	if((pDirent->d_name[strlen(pDirent->d_name)-1]!='~') && (strcmp(pDirent->d_name,"log.txt")!=0 && strcmp(pDirent->d_name,"myfifo")!=0  )){

    		++count;


    	}

    }

    closedir(pDir);
    return count;


}

int detachandremove(int shmid,void *shmaddr){
    int error=0;
    if(shmdt(shmaddr)==-1){
        error=errno;
    }
    if((shmctl(shmid,IPC_RMID,NULL)==-1) && !error){
        error=errno;
    }
    if(!errno){
        return 0;
    }
    errno=error;
    return -1;
}






threadStruct ForkAt(char* directory,char* ara){
	int len=0;
	int i=0;
	
	struct dirent *pDirent;
    DIR *pDir;
    threadStruct sum;
    sum.total=0;
    sum.lineNumber=0;
    sum.searchDirectory=0;
    sum.searchFile=0;
    sum.searchThreads=0;

    int NumOfFiles=fileCount(directory);
    pthread_t TID;
    pthread_t TIDS[NumOfFiles];/*directory deki dosya sayısı*/

    threadStruct strArr[NumOfFiles];/*directory deki dosya sayısı*/

    struct stat statbuf;
 	pDir = opendir (directory);
    int SubDirectories=0;

	


 	int parentPID;
 	pid_t childPID;

 	if (pDir == NULL) {
        printf ("Cannot open directory '%s'\n", directory);
        return sum;
    }




    int id;
    SharedStruct *Shared;

    if((id=shmget(IPC_PRIVATE,sizeof(int),S_IRUSR|S_IWUSR))==-1){
        perror("Failed to create shared memory");
        return sum;
    }
    if((Shared=(SharedStruct*)shmat(id,NULL,0))==(void*)-1){
        perror("Failed to attach shared memory segment");
        if(detachandremove(id,Shared)==-1)
            perror("Failed to remove shared memory segment");
        return sum;
    }
    
 


    parentPID=getpid();
    int structCounter=0;
   

 	while ((pDirent = readdir(pDir)) != NULL && getpid()==parentPID && finish!=1) {
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
					errorNo=errno;
					signal(  SIGQUIT,errorDurumu);
					
					if(kill(mainPID,SIGQUIT)==-1){
					fprintf(stderr, "SIGQUIT sinyali gönderilemedi\n" );
					fprintf(stderr, "%d pid\n",getpid() );
  			

  					}
                    
                    
                }
                
                else if(getpid()==parentPID)
                    len++;
                else if(childPID==0){
                    threadStruct toplam;
                    
                    
                    toplam=ForkAt(path,ara);//////////////RECURSIVE////
                    
                  
          
                

                    free(path);
              

               

                    
                    
                    exit(0);
                    
                    
                }


            }
	 			
	 			
	 			
 			}
 			
 				/*&& 
        	strcmp(&pDirent->d_name[strlen(pDirent->d_name)-4],".txt"*/
 		}
        else if((pDirent->d_name[strlen(pDirent->d_name)-1]!='~') && (strcmp(pDirent->d_name,"log.txt")!=0 && strcmp(pDirent->d_name,"myfifo")!=0 )) {
        	
	    	
        	
          		

	   
        		/*printf("strcpy %s\n",path);*/
	        	strcpy(strArr[structCounter].filename,path);
	        	strcpy(strArr[structCounter].aranan,ara);

                strArr[structCounter].sharedPointer=Shared;
	        	/*printf("%d struct counter artıs %s \n",structCounter,strArr[structCounter].filename );*/

	    		pthread_create(&TID,NULL,threadFonk,(void *) (strArr+structCounter) );

	    		TIDS[structCounter]=TID;

	    		
	    		++structCounter;


	    	
        }
        free(path);
  
   
        
        
    }



   
    pid_t child_pid, wpid;
	int status = 0;


    for(i=0;i<structCounter;i++){
    	/*printf("join %d i %d\n",structCounter ,i);*/
    	pthread_join(TIDS[i],NULL );
    	
 /*   	sum.total+=strArr[i].total;
    	sum.lineNumber+=strArr[i].lineNumber;
    	/*printf(" %d sum %d total %s name\n",sum.total ,strArr[i].total,strArr[i].filename);
    	printf("%d  sum line lineNumber\n", sum.lineNumber);*/

    }






    if(structCounter>cascade)
    	cascade=structCounter;
   
   
   	while ((wpid = wait(&status)) > 0);


    sum.total=Shared->total;
    sum.searchDirectory=SubDirectories;
    sum.lineNumber=Shared->lineNumber;
    sum.searchThreads= structCounter  ;

    
    
   

    mymsg_t myMessege;////////////

   
   
    myMessege.mtype=1;
    ////Send integers as a string///
    sprintf(myMessege.mtxt,"%d %d %d %d ",sum.total,sum.searchDirectory,sum.lineNumber,sum.searchThreads);


   
    ////Send Message to Queue///
    if(msgsnd(msqid,&myMessege,sizeof(myMessege)+1,0)==-1){
        perror("message send error");
        return sum;
    }
  


	
  

    
       
      if(detachandremove(id,Shared)==-1){
        
      }
    


    closedir(pDir);

 
    return sum;

    
    

}



int findLineNumber(char* dosyaAdi,char* Ara){
	FILE* dosya;
	char ch;
	int lineNumber=0;;
	dosya=fopen(dosyaAdi,"r");			
	if(dosya==NULL  ){
		errorNo=errno;
		signal(  SIGQUIT,errorDurumu);
		printf("Dosya bulunamadı [%s]\n",dosyaAdi);
		if(kill(mainPID,SIGQUIT)==-1){
  			fprintf(stderr, "SIGQUIT sinyali gönderilemedi\n" );
  			fprintf(stderr, "%d pid\n",getpid() );
  			

  		}
		return 0;
	}
	while((ch=fgetc(dosya))!=EOF){
		if(ch=='\n')
			lineNumber++;

	}

	fclose(dosya);
	return lineNumber;

	return 0;

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
		
		errorNo=errno;
		signal(  SIGQUIT,errorDurumu);
		printf("Dosya bulunamadı [%s]\n",dosyaAdi);
		if(kill(mainPID,SIGQUIT)==-1){
  			fprintf(stderr, "SIGQUIT sinyali gönderilemedi\n" );
  			fprintf(stderr, "%d pid\n",getpid() );
  			

  		}
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
                     fprintf(logFile,  " %d - %ld  %s=[%d,%d] %s first character is found.\n",(int)getpid(),(long) pthread_self(),dosyaAdi,satir,sutun,Ara );
                    
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








	
              	


