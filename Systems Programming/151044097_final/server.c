/*!
 * Simple chat program (server side).cpp - http://github.com/hassanyf
 * Version - 2.0.1
 *
 * Copyright (c) 2016 Hassan M. Yousuf
 */


#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/syscall.h>
#include "nrutil.h"
#include <math.h>


static sem_t sharedsem;

static sem_t sharedsem1;
static sem_t sharedsem2;
static sem_t sharedsem3;

static volatile sig_atomic_t finish=0;
static volatile sig_atomic_t currentThread=0;
static int mainPID=0;
int clientEstablish;
int clientPID=0;


typedef struct{
    
   float arr[25][25];


   int row;
   int col;

   float x1[25];
   float x2[25];
   float x3[25];

   float e1;
   float e2;
   float e3;

   float b[25];

   sem_t SAM;
   sem_t SAM2;

   int sem[3];


}SharedStruct;///used as a shared memory


typedef struct{
	int threadNumber;
	int server;
	int client;
	struct sockaddr_in server_addr;
	SharedStruct *sharedMem;

}threadStruct;///used by thread function


int establish (unsigned short portnum);
int getConnection(int s);
int detachandremove(int shmid,void *shmaddr);
void generateMatrix(int row,int col,SharedStruct *Shared);
float determinant(float m[25][25],int n);
int callSocket( unsigned short portnum);
int pseudoInverse(SharedStruct *Shared ,int row,int col,int thread );
void transpose(float num[25][25], float fac[25][25], float r,float in[25][25]);
void cofactor(float num[25][25], float f,float in[25][25]);
void verify(SharedStruct *Shared,int row,int col);


typedef struct{
	

	int i;
	SharedStruct *sharedMem;
	int row;
	int col;

}threadStruct2;///used by thread function



void * threadForkFonk(void * arg){


	threadStruct2* STR;
	STR=(threadStruct2 *) arg;


	pseudoInverse(STR->sharedMem,STR->row,STR->col,STR->i);

	return 0;


}



void * threadFonk(void * arg){

	int server=*(int *) arg;

	sem_post(&sharedsem3) ;

	while(kill(mainPID,SIGUSR1)==-1){
  			fprintf(stderr, "SIGUSR1 sinyali gönderilemedi\n" );
  			fprintf(stderr, "%d pid\n",getpid() );
  			exit(0);

  	}





	pid_t tidThread = syscall(__NR_gettid);

	int bufsize = 50;
    char buffer[bufsize];

	 int i,j;
	 pid_t  wpid;
	  int id;


  	key_t key=(int)tidThread;
/*
printf("key=%d  tid=%d \n", key,(int)tidThread);
*/
  	SharedStruct *Shared;

    if((id=shmget(key ,sizeof(Shared),IPC_CREAT | 0666))==-1){
        perror("Failed to create shared memory");
        return 0;
    }


    if((Shared=(SharedStruct*)shmat(id,NULL,0))==(void*)-1){
        perror("Failed to attach shared memory segment");
        if(detachandremove(id,Shared)==-1)
            perror("Failed to remove shared memory segment");
        return 0;
    }


	
	int client=0;

	
	

	recv(server, buffer , bufsize, MSG_WAITALL);
	send(server, buffer,bufsize, 0);
	
	

	int row;
	int col;
	int tid;

	sscanf(buffer,"%d %d %d %d",&tid,&row,&col,&clientPID);
	


    pid_t childPID[3];

    Shared->sem[0]=0;
    Shared->sem[1]=0;
    Shared->sem[2]=0;


    while(sem_init(&Shared->SAM,0,1) == -1){///////////SEMAPHORE INITILİSATİON
 		perror("Failed to initialize semaphore");
 
 		return 0;
 }
/* 
  while(sem_init(&Shared->SAM2,0,1) == -1){///////////SEMAPHORE INITILİSATİON
 		perror("Failed to initialize semaphore");
 
 		return 0;
 }

while(sem_wait(&Shared->SAM)==-1)///Kritik bölge için Semaphore 
				if(errno!=EINTR)
					return 0;	

while(sem_wait(&Shared->SAM2)==-1)///Kritik bölge için Semaphore 
				if(errno!=EINTR)
					return 0;				
*/
    for(i=0;i<3;i++){
    	childPID[i]=fork();

	    if(childPID[0]==0 && i==0){

	    	
			//printf("generate girdi %d\n",tid );

	    	generateMatrix(row,col,Shared);
/*
	    	sem_post(&Shared->SAM) ;
*/


	    	Shared->sem[0]=1;
	    //	printf("generate bitti %d\n",tid );
	    	exit(0);


	    }
	    else if(childPID[1]==0 && i==1){

	  		

	  		/*
	    	while(sem_wait(&Shared->SAM)==-1)///Kritik bölge için Semaphore 
				if(errno!=EINTR)
					return 0;
*/			threadStruct2 strArr[3];
	    	pthread_t TIDS[3];
	    	pthread_t TID;
	  		while(Shared->sem[0]==0);
			printf("pseuo girdi %d\n",tid );



            strArr[0].sharedMem=Shared;
        	strArr[0].i=0;
        	strArr[0].row=row;
        	strArr[0].col=col;

    		pthread_create(&TID,NULL,threadForkFonk,(void *) (strArr) );

    		pthread_join(TIDS[0],NULL );


			

			/*

			sem_post(&Shared->SAM) ;
			sem_post(&Shared->SAM2) ;
					

printf("pseuo bitti %d\n",tid );*/

Shared->sem[1]=1;
	    	exit(0);


	    }
	    else if(childPID[2]==0 && i==2){

/*
printf("verify bekliyor %d\n",tid );


	    	while(sem_wait(&Shared->SAM2)==-1)///Kritik bölge için Semaphore 
				if(errno!=EINTR)
					return 0;


				printf("verify girdi %d\n",tid );*/

			while(Shared->sem[1]==0);

			
				verify(Shared,row,col);
		/*	
			
			

			sem_post(&Shared->SAM2) ;


printf("verify bitti %d\n",tid );*/
	    	exit(0);


	    }



    }

 
    for(i=0;i<3;i++){
    	wait(NULL);
    }


    client=callSocket(tid);

	for(i=0;i<row;i++){
    	for(j=0;j<col;j++)
    		printf("%f ", Shared->arr[i][j]);
    	printf("\n");
    }

    for(i=0;i<row;i++){
    	printf("%f ",Shared->b[i]);
    }

    printf("\n");

   
	send(client, Shared->arr,sizeof(Shared->arr), 0);

	send(client, Shared->b,sizeof(Shared->b), 0);

	send(client, Shared->x1,sizeof(Shared->x1), 0);

	send(client, Shared->x2,sizeof(Shared->x2), 0);

	send(client, Shared->x3,sizeof(Shared->x3), 0);

	send(client, &Shared->e1,sizeof(Shared->e1), 0);

	send(client, &Shared->e2,sizeof(Shared->e2), 0);

	send(client, &Shared->e3,sizeof(Shared->e3), 0);

	recv(client, buffer , bufsize, MSG_WAITALL);


    
    printf("%s  \n",buffer );



   close(server);


    if(detachandremove(id,Shared)==-1)
            perror("Failed to remove shared memory segment");
     
	
	close(client);
	while(kill(mainPID,SIGUSR2)==-1){
  			fprintf(stderr, "SIGUSR2 sinyali gönderilemedi\n" );
  			fprintf(stderr, "%d pid\n",getpid() );
  			exit(0);

  	}
 printf("exiting... %d\n",tid);
    return 0;

}




void bitir(int sinyalNo){
	finish=1;
	kill(clientPID,SIGINT);

	printf("client pid %d\n",clientPID);
	sleep(1);

	close(clientEstablish);
	exit(1);
	


}

void yakala(int sinyalNo){////Sinyal fonksiyonu

	
	if(sinyalNo==SIGUSR1){///SIGUSR1 geldiğing ,currentThread değişkeni arttırılır
		
		IncShared();//////currentThread değişkeni aynı anda çalışan thread sayısını bulmak için kullanılır
		
	}
	else if(sinyalNo==SIGUSR2){///SIGUSR geldiğing ,currentThread değişkeni azaltılır
		
		DecrShared();
	}


              
}


int IncShared(){///currentThread değişkenini  arttırmak için kullanılır
	/*while(sem_wait(&sharedsem)==-1)///Kritik bölge için Semaphore 
		if(errno!=EINTR)
			return -1;
*/
	++currentThread;

	
	return 0;//sem_post(&sharedsem);


}
int DecrShared(){//currentThread değişkenini  azaltmak için kullanılır
	/*while(sem_wait(&sharedsem)==-1)///Kritik bölge için Semaphore 
		if(errno!=EINTR)
			return -1;*/

	--currentThread;
	return 0;//sem_post(&sharedsem);

}


int main(int argc, char** argv)
{
	int client, server;/*s,t*/
	int PORTNUM=atoi(argv[1]);
	
	pthread_t TID;

	int strArr[1];
	mainPID=getpid();
	int thPool=0;

	if (argc == 3) {
		thPool=atoi(argv[2]);
		printf("thread pool\n");
		
	}
	else if(argc==2){
		thPool=0;
	}
	else{
		printf ("Usage: testprog %d\n",argc);
		return 1;
	}

	pthread_t TIDS[thPool];



	while(sem_init(&sharedsem,0,1) == -1){///////////SEMAPHORE INITILİSATİON
 		perror("Failed to initialize semaphore");
 
 		return 0;
 }

 while(sem_init(&sharedsem2,0,1) == -1){///////////SEMAPHORE INITILİSATİON
 		perror("Failed to initialize semaphore");
 
 		return 0;
 }

  while(sem_init(&sharedsem3,0,1) == -1){///////////SEMAPHORE INITILİSATİON
 		perror("Failed to initialize semaphore");
 
 		return 0;
 }


 signal(SIGUSR1,yakala);
 signal(SIGUSR2,yakala);
 
    signal(SIGINT, bitir);

   
    srand(time(NULL));
    int i=0;
    

 	if ((client= establish(PORTNUM)) < 0) {
		perror("establishh");
		exit(1);
	}
	clientEstablish=client;

int currentThreadCount=0;
int counter=0;
if(thPool!=0){


	while(finish==0){

		
		if(currentThreadCount>thPool){
	    	counter=i;
	    	pthread_join(TIDS[i],NULL );
	    	printf("%d  joined\n",i );

 			++i;
 			--currentThreadCount;
  		}
  		if(i>thPool){
  			i=0;
  		}

	 	if ((server= getConnection(client)) < 0) {
				if (errno == EINTR)
					continue;
				perror("accept");
				exit(1);
			}

			while(sem_wait(&sharedsem3)==-1)///Kritik bölge için Semaphore 
					if(errno!=EINTR)
						return 0;	

	    	currentThreadCount++;
	    	
	    	strArr[0]=server;
		
			printf("theread acılacak  %d\n",i);
		

			pthread_create(&TID,NULL,threadFonk,(void *) (strArr) );
			TIDS[counter]=TID;
			counter++;

	}
}


else{

	 while(finish==0){

	 
	 	if ((server= getConnection(client)) < 0) {
				if (errno == EINTR)
					continue;
				perror("accept");
				exit(1);
			}

			while(sem_wait(&sharedsem3)==-1)///Kritik bölge için Semaphore 
					if(errno!=EINTR)
						return 0;	

	    	
	    	strArr[0]=server;
		
			printf("theread acılacak  %d\n",i);
		

			pthread_create(&TID,NULL,threadFonk,(void *) (strArr) );



	}

}

    for(;;){

    }

  /*  for(i=0;i<threadSize;i++){
    	
    	pthread_join(TIDS[i],NULL );
    	printf("%d  joined\n",i );
 
  }

	close(client);
	return 0;*/

}


int establish (unsigned short portnum)
{
	
	int s;
	struct sockaddr_in sa;



	memset(&sa, 0, sizeof(struct sockaddr_in));


	sa.sin_family= AF_INET;
	sa.sin_port= htons(portnum);

	if ((s= socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return(-1);
	if (bind(s,(struct sockaddr *)&sa,sizeof(struct sockaddr_in)) < 0) {
		close(s);
		return(-1);
	}

	listen(s, 20);
	return(s);
}


int getConnection(int s)
{	
	int t;
	if ((t = accept(s,NULL,NULL)) < 0)
		return(-1);


	return(t);
}


int callSocket( unsigned short portnum)
{
	struct sockaddr_in sa;

	int a, s;

	memset(&sa,0,sizeof(sa));


	sa.sin_family= AF_INET;

	sa.sin_port= htons((u_short)portnum);

	if ((s= socket(AF_INET,SOCK_STREAM,0)) < 0)
	
		return(-1);
	if (connect(s,(struct sockaddr *)&sa,sizeof sa) < 0) { /* connect */
		close(s);
		return(-1);
	} 

	return(s);
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

void generateMatrix(int row,int col,SharedStruct *Shared){

	float sign=-1;
	int i=0,j=0;
	float d;
	float multiply[25][25];

		for(i=0;i<row;i++){
			sign*=sign;
	    	for(j=0;j<col;j++)
	    		Shared->arr[i][j]=(((float)rand()/(float)(RAND_MAX)) * 50.0)-(10*sign);

	    		/*
	    		arr[row][col]= ((float)rand()/(float)(RAND_MAX)) * 20.0;*/
	    }


	


	    
     for(i=0;i<row;i++){
    	
    		Shared->b[i]=((float)rand()/(float)(RAND_MAX)) * 20.0;

    }



  

}


int pseudoInverse(SharedStruct *Shared ,int row,int col,int thread ){

	
	float transpose[col][row];

	float multiply[col][col];

	float pseudoIn[col][row];

	int i=0,j=0,k=0;



	for(i=0; i<row; ++i)
        for(j=0; j<col; ++j)
        {
            transpose[j][i] = Shared->arr[i][j];
        }


      for(i=0;i<col;i++){
    	for(j=0;j<row;j++)
    		printf("%2f tr  ",transpose[i][j]);

    	printf("\n");	
    }

    for(i=0; i<col; ++i)
        for(j=0; j<col; ++j)
        {
            multiply[i][j] = 0;
        }


    for(i=0; i<col; ++i)
        for(j=0; j<col; ++j)
            for(k=0; k<row; ++k)
            {
                multiply[i][j]+=transpose[i][k]*Shared->arr[k][j];
            }

 for(i=0;i<col;i++){
    	for(j=0;j<col;j++)
    		printf("%f mltp %d  ",multiply[i][j],col);

    	printf("\n");	
    }

   float in[25][25];

   	float d;

	d = determinant(multiply, col);
 
	printf("\nTHE DETERMINANT IS=%2f\n", d);
 
	if (d == 0){
		 printf("\nMATRIX IS NOT INVERSIBLE\n"); 
		 return 0;

			
    }
	else
 		cofactor(multiply, col,in);


printf("cofactorden cıktı\n");

 for(i=0; i<col; ++i)
        for(j=0; j<row; ++j)
        {
            pseudoIn[i][j] = 0;
        }


 for(i=0;i<col;i++){
    	for(j=0;j<col;j++)
    		printf("%2f inverse  ",in[i][j]);

    	printf("\n");	
    }

	for(i=0; i<col; ++i)
        for(j=0; j<row; ++j)
            for(k=0; k<col; ++k)
            {
                pseudoIn[i][j]+=in[i][k]*transpose[k][j];
            }

for(i=0;i<col;i++){
    	for(j=0;j<col;j++)
    		printf("%2f psudo  ",pseudoIn[i][j]);

    	printf("\n");	
    }



	if(thread==0){

	  	for(i=0; i<col; ++i)
	        for(j=0; j<row; ++j)
	           Shared->x1[i]+=pseudoIn[i][j]*Shared->b[j];
	}
	else if(thread==1){
		for(i=0; i<col; ++i)
	        for(j=0; j<row; ++j)
	           Shared->x2[i]+=pseudoIn[i][j]*Shared->b[j];
	}
	else if(thread==2){
		for(i=0; i<col; ++i)
	        for(j=0; j<row; ++j)
	           Shared->x3[i]+=pseudoIn[i][j]*Shared->b[j];
	}
          
            

	return 1;


}


void verify(SharedStruct *Shared,int row,int col){

	float multiply[row];
	int i=0,j=0;
	float e1[row];
	float e2[row];
	float e3[row];

	for(i=0; i<row; ++i)
   		multiply[i]= 0;



	for(i=0; i<row; ++i)
        for(j=0; j<col; ++j)
           multiply[i]+=Shared->arr[i][j]*Shared->x1[j];


	for(i=0; i<row; ++i)
   		e1[i]= 0;


    for(i=0; i<row; ++i)
   		e1[i]= multiply[i]-Shared->b[i];

   	float tempE=0;

   	for(i=0;i<row;++i)
   		tempE+=e1[i]*e1[i];

    Shared->e1=sqrt(tempE);

    for(i=0; i<row; ++i)
   		multiply[i]= 0;



	for(i=0; i<row; ++i)
        for(j=0; j<col; ++j)
           multiply[i]+=Shared->arr[i][j]*Shared->x2[j];


	for(i=0; i<row; ++i)
   		e2[i]= 0;


    for(i=0; i<row; ++i)
   		e2[i]= multiply[i]-Shared->b[i];

   	 tempE=0;

   	for(i=0;i<row;++i)
   		tempE+=e2[i]*e2[i];

    Shared->e2=sqrt(tempE);


for(i=0; i<row; ++i)
   		multiply[i]= 0;



	for(i=0; i<row; ++i)
        for(j=0; j<col; ++j)
           multiply[i]+=Shared->arr[i][j]*Shared->x3[j];


	for(i=0; i<row; ++i)
   		e3[i]= 0;


    for(i=0; i<row; ++i)
   		e3[i]= multiply[i]-Shared->b[i];

   	 tempE=0;

   	for(i=0;i<row;++i)
   		tempE+=e3[i]*e3[i];

    Shared->e3=sqrt(tempE);



}


float determinant(float m[25][25],int n)
{

    float matrix[n][n],ratio, det;



    int i, j, k;

    for(i=0;i<n;i++)
    	for(j=0;j<n;j++)
    		matrix[i][j]=m[i][j];

    /* Conversion of matrix to upper triangular */

    for(i = 0; i < n; i++){

        for(j = 0; j < n; j++){

            if(j>i){

                ratio = matrix[j][i]/matrix[i][i];

                for(k = 0; k < n; k++){

                    matrix[j][k] -= ratio * matrix[i][k];

                }

            }

        }

    }

    det = 1; //storage for determinant

    for(i = 0; i < n; i++)

        det *= matrix[i][i];

    printf("The determinant of matrix is: %.2f\n\n", det);

    return det;

}

/*
float determinant(float matrix[25][25],float size)
{
    float s=1,det=0,m_minor[25][25];
    int i,j,m,n,c;
    if (size==1)
    {
        return (matrix[0][0]);
    }
    else
    {
        det=0;
        for (c=0;c<size;c++)
        {
            m=0;
            n=0;
            for (i=0;i<size;i++)
            {
                for (j=0;j<size;j++)
                {
                    m_minor[i][j]=0;
                    if (i != 0 && j != c)
                    {
                       m_minor[m][n]=matrix[i][j];
                       if (n<(size-2))
                          n++;
                       else
                       {
                           n=0;
                           m++;
                       }
                    }
                }
            }
            det=det + s * (matrix[0][c] * determinant(m_minor,size-1));
            s=-1 * s;
        }
    }
 
    return (det);
}

 
*/
void cofactor(float num[25][25], float f,float in[25][25])

{

 float b[25][25], fac[25][25];

 int p, q, m, n, i, j;

 for (q = 0;q < f; q++)

 {

   for (p = 0;p < f; p++)

    {

     m = 0;

     n = 0;

     for (i = 0;i < f; i++)

     {

       for (j = 0;j < f; j++)

        {

          if (i != q && j != p)

          {

            b[m][n] = num[i][j];

            if (n < (f - 2))

             n++;

            else

             {

               n = 0;

               m++;

               }

            }

        }

      }

      fac[q][p] = pow(-1, q + p) * determinant(b, f - 1);

    }

  }

  transpose(num, fac, f,in);

}



void transpose(float num[25][25], float fac[25][25], float r,float in[25][25])

{

  int i, j;

  float b[25][25], inverse[25][25], d;

 

  for (i = 0;i < r; i++)

    {

     for (j = 0;j < r; j++)

       {

         b[i][j] = fac[j][i];

        }

    }

  d = determinant(num, r);

  for (i = 0;i < r; i++)

    {

     for (j = 0;j < r; j++)

       {

        inverse[i][j] = b[i][j] / d;

        }

    }

   printf("\n\n\nThe inverse of matrix is : \n");

 

   for (i = 0;i < r; i++)

    {

     for (j = 0;j < r; j++)

       {

         printf("\t%f  a ", inverse[i][j]);
         in[i][j]=inverse[i][j];

        }

    printf("\n");

     }

}
