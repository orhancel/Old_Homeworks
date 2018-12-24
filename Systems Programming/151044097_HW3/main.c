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
        
        if (argc < 2) {
            printf ("Usage: testprog <dirname>\n");
            return 1;
        }

        
        int toplam;////////////toplam aranan sayısı olacak
        toplam=ForkAt(dosyaYolu,Ara);////////////Ana process i cagırma
       
       
		/*if(getpid()==mainProcces){
			printf("Fclose logFile\n");
    	fclose(file);
   		}*/
        
        if(mainProcces==getpid()){
            if (unlink("myfifo") == -1)
                perror("Failed to remove myfifo");


            FILE *logFile;
           /* logFile = fopen("log.txt", "r");

            while(fscanf(logFile,"%c",&ch)!=EOF){
                if(ch=='\n'){
                    ++bulunan;
                }
                
                
            }
            fclose(logFile);*/
            logFile = fopen("log.txt", "a");
            fprintf(logFile,"%d %s were found in total.\n",toplam,Ara);///////Log dosyasına toplam sayıyı yazdırma//////
            fprintf(stderr, "%d %s were found in total.\n",toplam,Ara);
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
    int SubDirectories=0;



 	int parentPID;
 	pid_t childPID;

 	if (pDir == NULL) {
        printf ("Cannot open directory '%s'\n", directory);
        return 0;
    }

    int fdp[2];

    if (pipe(fdp) < 0)/////////////////////PIPE/////////////
        err_sys("pipe");

    if(mkfifo("myfifo",S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)){//////////fifo////////////
        if(errno!=EEXIST){
            fprintf(stderr, "failed to make a fifo in pid=[%ld]\n",(long)getpid() );
        }
    }

    FILE* myF=fopen("myfifo","a+");


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
 				if(getpid()==parentPID){

                childPID=fork();
                SubDirectories=+1;
                if(childPID < 0){
                    printf("Fork failed\n");
                    
                    
                }
                
                else if(getpid()==parentPID)
                    len++;
                else if(childPID==0){
                    int toplam;
                    
                    toplam=ForkAt(path,ara);//////////////RECURSIVE////
                    
                    /*fprintf(stderr, "return FORK AT\n");*/
                    int fifoDir;

                    fifoDir = open("myfifo",O_WRONLY|O_NONBLOCK);

                    if(write(fifoDir,&toplam,sizeof(int))<0)///////////////////fifoya yaz//////////
                        printf("Failed write fifo [%s] -- %s\n",directory,strerror(errno));
                    free(path);
                    close(fifoDir);

                    /*printf("sum at [%s]  [%d]\n",path,toplam );*/

                    
                    
                    exit(0);
                    
                    
                }
          
                

                

            }
	 			
	 			
	 			
 			}
 			
 				
 		}
        else if((pDirent->d_name[strlen(pDirent->d_name)-1]!='~') && (strcmp(pDirent->d_name,"log.txt")!=0 && strcmp(pDirent->d_name,"myfifo")!=0 )) {
        	
	        

	        if(getpid()==parentPID){
	    		childPID=fork();
	    		if(childPID < 0){

	    			printf("Fork failed\n");
	    			
	    			
	    		}
	    		else if(getpid()==parentPID){
                    
	    			len++;
                    
                }
	    		else if(childPID==0){
	    			
	    		    int bulunan=0;
                    close(fdp[0]);

                    /*fprintf(stderr, "%s yardımcı fonksiyonu\n", path);*/
	    			bulunan=readFile(path,ara);
                    free(path);
                    /*fprintf(stderr, "%s yardımcı fonksiyonu cıktı\n", path);*/
                    

	    			if(write(fdp[1], &bulunan, sizeof(int))<0)/////////pipe 'a yaz////////'
                        printf("Failed write %s -- %s\n",path,strerror(errno));
                    
                    close(fdp[1]);
                    

	    			
	    			
	    			exit(0);
	    			
	    			
	    		}

	    	}
	    	
	    	
        }
        free(path);
  
   
        
        
    }
    int val=0;
    int result;
    int sum=0;
/*
    while((result=read(fdp,&val,sizeof(int))>=0)){

        printf("result while\n");
        
    }*/

    /*printf("close fdp len=%d\n", len);*/

    
  
    	
   
     /*printf("waitten %s\n",directory);*/
    	while(wait(NULL)!=-1)
        {
            /*fprintf(stderr, " len  %d path [%s]\n",len,directory );*/
        
    		--len;
    	}
      
        close(fdp[1]);
        

        
        while ((result = read(fdp[0], &val, sizeof(int))) > 0){///////////pipe oku////

            /*printf("value %d\n", val);*/

            sum+=val;

        }
      /*  printf("pipe leave   %s\n",directory);*/
        int fifoDir;
     
        while((fifoDir = open("myfifo",O_RDONLY))==-1) {

        }
      /* printf("fifo open\n");*/
        
        while(SubDirectories>0){
            /*printf("read fifo at %s\n", directory);*/
            read(fifoDir, &val, sizeof(int));/////fifoyu oku//////////

            /*printf("value fifo %d at %s\n", val,directory);*/

            sum+=val;
            --SubDirectories;
            
            /*printf("\nFIFO readed at %s \n", directory);*/

        }
       
        
        /*printf("fifo leave val [%d]\n",val);*/
        


        /*
        if(write(fifoDir,&sum,sizeof(int))<0)
            printf("Failed write %s -- %s\n",path,strerror(errno));
        printf("sum at [%s]  [%d]\n",directory,sum );
        */
      

        closedir(pDir);

        close(fifoDir);

        fclose(myF);

        close(fdp[0]);

     
    return sum;

    
    

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
                    fprintf(stderr,  "%s=[%d,%d] %s first character is found.\n",dosyaAdi,satir,sutun,Ara );
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
