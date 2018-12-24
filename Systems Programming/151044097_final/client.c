/*!
 * Simple chat program (client side).cpp - http://github.com/hassanyf
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
#include <semaphore.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <fcntl.h>

static sem_t sharedsem;
static sem_t sharedsem2;
static sem_t sharedsem3;
static volatile sig_atomic_t finish=0;
int *establishedPort;
int *getConnect;
int size;
double totalTime;


int mainPID;
int portNum =0;
int establish (unsigned short portnum);
int getConnection(int s);


int callSocket( unsigned short portnum);

typedef struct{
	int threadNumber;
	int row;
	int col;


}threadStruct;///used by thread function

void bitir(int sinyalNo){
	finish=1;
	int i=0;
	printf("finish signal\n");
	for(i=0;i<size;i++){

		if(establishedPort[i]!=0)
			close(establishedPort[i]);
		if(getConnect[i]!=0)
			close(getConnect[i]);
	}

	/*
	printf("currentThread  %d  client pid %d\n", currentThread,clientPID);
	while(currentThread>0);
printf("currentThread  %d\n", currentThread);*/

	free(getConnect);
    free(establishedPort);
    sleep(1);
	exit(1);
	


}


void * threadFonk(void * arg){

clock_t begin = clock();

/* here, do your time-consuming job */




	while(sem_init(&sharedsem,0,1) == -1){///////////SEMAPHORE INITILİSATİON
 		perror("Failed to initialize semaphore");
 
 		return 0;
 }

	pid_t tid = syscall(__NR_gettid);

	threadStruct* STR;
	STR=(threadStruct *) arg;




	if(finish==1){
		sem_post(&sharedsem) ;
		return 0;

	}


	printf("%d  client number\n", STR->threadNumber);

	int client;
   
 	int bufsize = 50;
    char buffer[bufsize];


    client=callSocket(portNum);


clock_t end = clock();
double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    sprintf(buffer,"%d",tid);


    sprintf(buffer,"%d %d %d %d",tid,STR->row,STR->col,mainPID);

    printf("Socket called  %d \n", STR->threadNumber);

   
    int fd;

    
    
    

    printf("=> Connection confirmed, you are good to go...\n" );
    
    
    printf("%s will send\n", buffer);

    send(client, buffer,bufsize, 0);
    recv(client, buffer , bufsize, MSG_WAITALL);

    
    close(client);///////////////////////////

    sem_post(&sharedsem) ;


	int  server;/*s,t*/

    
 	if ((client= establish(tid)) < 0) {
		perror("establishh");
		exit(1);
	}

	establishedPort[STR->threadNumber]=client;

printf("getconnection bekliyor  %d\n",tid );
	if ((server= getConnection(client)) < 0) {
			if (errno == EINTR){
				
			}
				
			else{
				perror("accept");
				exit(1);
			}
			
	}
	getConnect[STR->threadNumber]=server;



   float arr[25][25];
    float b[25];
    float x1[25];
    float x2[25];
    float x3[25];
    float e1;
    float e2;
    float e3;
 

	recv(server, arr , sizeof(arr), MSG_WAITALL);
	recv(server, b , sizeof(b), MSG_WAITALL);
	recv(server, x1 , sizeof(x1), MSG_WAITALL);
	recv(server, x2 , sizeof(x2), MSG_WAITALL);
	recv(server, x3 , sizeof(x3), MSG_WAITALL);
	recv(server, &e1 , sizeof(e1), MSG_WAITALL);
	recv(server, &e2 , sizeof(e2), MSG_WAITALL);
	recv(server, &e3 , sizeof(e3), MSG_WAITALL);
	send(server, buffer,bufsize, 0);


	int i=0,j=0;
	char str[20];

	sprintf(str, "%d", tid);

	FILE *logFile;
    logFile = fopen(str, "a");

 

	for(i=0;i<STR->row;i++){
    	for(j=0;j<STR->col;j++){

    		fprintf(logFile,"%f   ", arr[i][j]);
    		
    	}
    		
    	fprintf(logFile,"\n");
    }
    printf("\n");

    fprintf(logFile,"b matrix = ");
    for(i=0;i<STR->row;i++){
    	fprintf(logFile,"%f   ", b[i]);
    }
    fprintf(logFile,"\n");
	fprintf(logFile,"x1 values = ");
    for(i=0;i<3;i++){
    		fprintf(logFile,"%f   ", x1[i]);
    }
    fprintf(logFile,"\n");
	fprintf(logFile,"x2 values = ");
    for(i=0;i<3;i++){
    		fprintf(logFile,"%f   ", x2[i]);
    }
    fprintf(logFile,"\n");
	fprintf(logFile,"x3 values = ");
    for(i=0;i<3;i++){
    		fprintf(logFile,"%f   ", x3[i]);
    }

    fprintf(logFile," e1=%f  \n ", e1);
    fprintf(logFile," e2=%f  \n ", e2);
    fprintf(logFile," e3=%f  \n ", e3);

    fprintf(logFile," Connection time=%lf  \n ", time_spent);
    totalTime+=time_spent;


	
    fclose(logFile);

   	printf("\n=> Connection terminated.  Goodbye...  %d\n", tid);
   	close(client);
   	close(server);
   	establishedPort[STR->threadNumber]=0;
   	getConnect[STR->threadNumber]=0;

   printf("thread exit  %d\n",tid);


    return 0;


}


int main(int argc, char** argv)
{







  	if (argc < 5) {
        printf ("Usage: testprog <dirname>\n");
        return 1;
    }




mainPID=getpid();
while(sem_init(&sharedsem,0,1) == -1){///////////SEMAPHORE INITILİSATİON
 		perror("Failed to initialize semaphore");
 
 		return 0;
 }


   int threadSize=atoi(argv[3]);
  	int row=atoi(argv[2]);
  	int col=atoi(argv[1]);
  	portNum=atoi(argv[4]);
  	establishedPort=(int *)malloc(sizeof(int)*threadSize);
  	getConnect=(int *)malloc(sizeof(int)*threadSize);
	int i=0;
	for(i=0;i<threadSize;++i){
		establishedPort[i]=0;
		getConnect[i]=0;
	}

    pthread_t TID;
    pthread_t TIDS[threadSize];/*directory deki dosya sayısı*/
    threadStruct strArr[threadSize];/*directory deki dosya sayısı*/


    signal(SIGINT, bitir);

  

	
    for(i=0;i<threadSize;++i){
    	if(finish==1)
    		break;
    	strArr[i].threadNumber=i;
    	strArr[i].row=row;
    	strArr[i].col=col;
	
		printf("%d pid\n",getpid() );
		

		pthread_create(&TID,NULL,threadFonk,(void *) (strArr+i) );
	
		TIDS[i]=TID;


    }

    threadSize=i;
    for(i=0;i<threadSize;i++){
    	
    	pthread_join(TIDS[i],NULL );
    	printf("%d  joined\n",i );
    
 

    }
    char str[20];

	sprintf(str, "%d.averageTime", getpid());

	FILE *logFile;
    logFile = fopen(str, "a");

 
    double ave=totalTime/threadSize;
    fprintf(logFile,"average time=%lf\nTotal time=%lf",ave,totalTime);

    fclose(logFile);


    free(getConnect);
    free(establishedPort);
    printf("return 0\n");



    return 0;
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
