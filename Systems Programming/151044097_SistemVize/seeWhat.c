#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>
#include <fcntl.h>

static volatile sig_atomic_t signalSent=0;
static volatile sig_atomic_t readMatrix=0;
static volatile sig_atomic_t closing=0;




void yakala(int sinyalNo){

  
    switch(sinyalNo){
      case SIGUSR1:signalSent=1;
                break;
      case SIGUSR2:readMatrix=1;
      			break;
    case SIGINT:closing=1;
    break;

     /*fprintf(stderr, "sinyal geldi %ld\n" ,(long) getpid());*/
    }


    
   
  }


int main(int argc, char const *argv[])
{
 


	/* if(mkfifo("myfifo",S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)){//////////fifo////////////
        if(errno!=EEXIST){
            fprintf(stderr, "failed to make a fifo in pid=[%ld]\n",(long)getpid() );
        }
    }

    FILE* myF=fopen("myfifo","a+");*/
    int fifoWrite;
    int ServerPid=0;
    int matrixSize=0;
    int i=0,j=0;
    struct sigaction sinyal;
    int DosyaBool=0;

    sinyal.sa_flags=0;
  	sinyal.sa_handler=yakala;
 	int parentPid;
 

     if(sigaction(SIGUSR1,&sinyal,NULL)==-1 || sigemptyset(&sinyal.sa_mask)){
      
       fprintf(stderr, "sinyal set değil\n");
      }

   if(sigaction(SIGUSR2,&sinyal,NULL)==-1 || sigemptyset(&sinyal.sa_mask)){
    
     fprintf(stderr, "sinyal set değil \n");
    }

   if(sigaction(SIGINT,&sinyal,NULL)==-1 || sigemptyset(&sinyal.sa_mask)){
    
     fprintf(stderr, "sinyal set değil \n");
    }
 
                    
    parentPid=getpid();
  
     int fifoDir;
   
    while((fifoDir = open(   argv[1] ,O_RDONLY))==-1) {
          fprintf(stderr, " Server is not up.Exiting\n");
          exit(0);
    }
  printf("asd2\n");
    read(fifoDir, &ServerPid, sizeof(int));/////fifoyu 

	read(fifoDir, &matrixSize, sizeof(int));/////fifoyu 
	
	printf("pid  %d\n",getpid());
    
   
    printf("asd3\n");

    close(fifoDir);

    printf("%d server\n", ServerPid);
    printf("%d size\n", matrixSize);


    char seeWhatFifo[6];
	sprintf(seeWhatFifo, "%d", parentPid);


    if(mkfifo(seeWhatFifo,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)==-1){//////////fifo////////////
      if(errno!=EEXIST){
          fprintf(stderr, "failed to make a fifo in pid=[%ld]\n",(long)getpid() );
      }
  	}
    FILE* myF=fopen(seeWhatFifo,"a+");

  
    if(kill(ServerPid,SIGUSR1)==-1){
				
				fprintf(stderr, "%d pid\n",ServerPid );

	}
 

    while((fifoDir = open(seeWhatFifo,O_RDONLY))==-1) {
    		printf("Failed open fifo  -- %s\n",strerror(errno));
    }

    i=getpid();

    int a[matrixSize][matrixSize];
    int x=0;
    while(1){
    	
    	signalSent=0;
    	
    	while(!signalSent){
        if(closing==1){
              unlink(seeWhatFifo);
              printf("kill aldım.Unlink yapıldı\n");     
          exit(1);

        }
    		
    		if(kill(ServerPid,SIGUSR2)==-1){
				fprintf(stderr, "hatalı kill111\n" );
				fprintf(stderr, "%d pid\n",ServerPid );

			}
    	}
    	printf("signalSent 0\n");
    	

  		
	    while(readMatrix==0 ){
	    	
	       if(closing==1){

              unlink(seeWhatFifo);   
              printf("kill aldım.Unlink yapıldı\n");    
          exit(1);
        }
	    	
	    }
	    
	    readMatrix=0;
	    for(i=1;i<=matrixSize;i++)
	   {
	        printf("\n");
	        for(j=1;j<=matrixSize;j++)
	        {  
	            if(read(fifoDir,&a[i][j],sizeof(int))<0)///////////////////fifoya yaz//////////
	              {
                    printf("Failed read fifo matrix %s\n",strerror(errno));

                  if(closing==1){
                    printf("kill aldım.Unlink yapıldı\n");  
                        unlink(seeWhatFifo);     
                           exit(1);
          
                     }
                }
	  
	             printf("\t%d \t",a[i][j]);
	        }
	   }
      if(closing==1){
                 unlink(seeWhatFifo);   
                 printf("kill aldım.Unlink yapıldı\n");    
          exit(1);
       }
	   printf("\n");
		

    }



   


   

	
	return 0;


}




