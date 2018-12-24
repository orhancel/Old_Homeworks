
#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include <errno.h>
#include <fcntl.h>

static volatile sig_atomic_t newSeeWhat=0;
static volatile sig_atomic_t makeMatrix=0;
static volatile sig_atomic_t closing=0;


static volatile sig_atomic_t NewseeWhatPid=0;
static volatile sig_atomic_t MatrixseeWhatPid=0;

int determinant(int f[20][20],int n);
void yakala(int sinyalNo,siginfo_t *siginfo,void * contex);


void makeMatris(int n,int seeWhatPid);





int main(int argc, char const *argv[])
{
  int i=0;
  int waitForMs=atoi(argv[1]);
  struct sigaction sinyal;
  pid_t childPid;
  int seeWhatPid;
  int seeWhatCount=0;
  int DosyaBool=0;
  int fifoDir;
  int fifoWrite;
  

  int parentPid;
                  
  parentPid=getpid();

  sinyal.sa_flags=SA_SIGINFO;
  sinyal.sa_sigaction=yakala;

  int matrixSize=atoi(argv[2])*2;





  if(mkfifo(argv[3],S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)==-1){//////////fifo////////////
      if(errno!=EEXIST){
          fprintf(stderr, "failed to make a fifo in pid=[%ld]\n",(long)getpid() );
      }
  }
  printf("done4\n");

FILE * myF=fopen("myfifo","a+");
printf("done3\n");

  while((fifoWrite = open("myfifo",O_WRONLY | O_NONBLOCK))==-1) {   /*|O_NONBLOCK*/
        printf("Failed open fifo  -- %s\n",strerror(errno));
    }
printf("done2\n");

    if(write(fifoWrite,&parentPid,sizeof(int))<0)///////////////////fifoya yaz//////////
        printf("Failed write fifo %s\n",strerror(errno));
    if(write(fifoWrite,&matrixSize,sizeof(int))<0)///////////////////fifoya yaz//////////
        printf("Failed write fifo %s\n",strerror(errno));
printf("done1\n");
 
  
   printf("done\n");



  
   

 
     if(sigaction(SIGUSR1,&sinyal,NULL)==-1 || sigemptyset(&sinyal.sa_mask)){
      
       fprintf(stderr, "sinyal gelmedi  Client'ın okumasını bekliyor111\n");
      }

   if(sigaction(SIGUSR2,&sinyal,NULL)==-1 || sigemptyset(&sinyal.sa_mask)){
    
     fprintf(stderr, "sinyal gelmedi  Client'ın okumasını bekliyor111\n");
    }
    if(sigaction(SIGINT,&sinyal,NULL)==-1){
    
     fprintf(stderr, "sinyal gelmedi  Client'ın okumasını bekliyor111\n");
    }
  

    while(true){
  

       if(newSeeWhat){
          seeWhatCount++;
         printf("%d\n",seeWhatCount );

          if(write(fifoWrite,&parentPid,sizeof(int))<0)///////////////////fifoya yaz//////////
              printf("Failed write fifo %s\n",strerror(errno));
          if(write(fifoWrite,&matrixSize,sizeof(int))<0)///////////////////fifoya yaz//////////
              printf("Failed write fifo %s\n",strerror(errno));
      
            newSeeWhat=0;

        }

        if(makeMatrix){

           if(closing==1){
                
                seeWhatCount--;
                  if(kill(MatrixseeWhatPid,SIGINT)==-1){
                        printf("couldnt sent stop signal\n");
                }
              }
            else{


              printf("make matrix %d\n",MatrixseeWhatPid);
                if(kill(MatrixseeWhatPid,SIGUSR1)==-1){
                   printf("couldnt sent stop signal\n");
                }
                    makeMatrix=0;
                childPid=fork();

                if(childPid==0){
                  makeMatris(matrixSize,MatrixseeWhatPid);
              
                
                exit(0);
            }

          }

           


            
        }
        if(closing==1 && seeWhatCount==0  ){
          unlink("myfifo");
          exit(0);
        }
        sigprocmask(SIG_BLOCK,&sinyal.sa_mask,NULL);
        usleep(1000* waitForMs);
        sigprocmask(SIG_UNBLOCK,&sinyal.sa_mask,NULL);

     


    }





 
  return 0;
}




void yakala(int sinyalNo,siginfo_t *siginfo,void * contex){
  
  
    switch(sinyalNo){
      case SIGUSR1:newSeeWhat=1;
                  NewseeWhatPid=siginfo->si_pid;
                  
                  break;

      case SIGUSR2:makeMatrix=1;

                MatrixseeWhatPid=siginfo->si_pid;

                break;
      case SIGINT:closing=1;
     /*fprintf(stderr, "sinyal geldi %ld\n" ,(long) getpid());*/
    }
    

   
  }




void makeMatris(int n,int seeWhatPid){
  int i=0,j=0;
  int a[20][20];
  int d;

  srand(time(NULL));
  do{

    for(i=1;i<=n;i++)
    {
      for(j=1;j<=n;j++)
      {
  
        a[i][j]= ((rand()+getpid())%20)-5;
         
      }
    }
     printf("done \n");

  }while(d=(determinant(a,n)==0));
  printf("determinant \n");

  char seeWhatFifo[6];
  sprintf(seeWhatFifo, "%d", seeWhatPid);
  
  int fifoWrite;

  fifoWrite = open(seeWhatFifo,O_WRONLY|O_NONBLOCK);
  

  for(i=1;i<=n;i++)
   {
        printf("\n");
        for(j=1;j<=n;j++)
        {    
            if(write(fifoWrite,&a[i][j],sizeof(int))<0)///////////////////fifoya yaz//////////
              printf("Failed write fifo matrix %s\n",strerror(errno));
  
           
            
        }
   }
   printf("%d childpid\n",getpid());
   close(fifoWrite);
   if(kill(MatrixseeWhatPid,SIGUSR2)==-1){

        fprintf(stderr, "matris bitti sinyali gönderilemedi\n" );
    }
  fprintf(stderr, "Sinyal gönderildi matris hazır\n" );

 
  
  
  
}


int determinant(int f[20][20],int n)
{
  int pr,c[20],d=0,b[20][20],j,p,q,t;
  if(n==2)
  {
    d=0;
    d=(f[1][1]*f[2][2])-(f[1][2]*f[2][1]);
    return(d);
   }
  else
  {
    for(j=1;j<=n;j++)
    {       
      int r=1,s=1;
      for(p=1;p<=n;p++)
        {
          for(q=1;q<=n;q++)
            {
              if(p!=1&&q!=j)
              {
                b[r][s]=f[p][q];
                s++;
                if(s>n-1)
                 {
                   r++;
                   s=1;
                  }
               }
             }
         }
     for(t=1,pr=1;t<=(1+j);t++)
     pr=(-1)*pr;
     c[j]=pr*determinant(b,n-1);
     }
     for(j=1,d=0;j<=n;j++)
     {
       d=d+(f[1][j]*c[j]);
      }
     return(d);
   }
}

