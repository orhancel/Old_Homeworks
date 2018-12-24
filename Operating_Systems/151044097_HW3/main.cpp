#include <iostream>
#include "8080emuCPP.h"
#include "gtuos.h"
#include "memory.h"

// This is just a sample main function, you should rewrite this file to handle problems
// with new multitasking and virtual memory additions.
int main (int argc, char**argv)
{	srand(time(NULL));
    if (argc != 3){
        std::cerr << "Usage: prog exeFile debugOption\n";
        exit(1);
    }
    int DEBUG = atoi(argv[2]);

    memory mem;
    CPU8080 theCPU(&mem);
    GTUOS	theOS;
    Thread mainThread;


    uint64_t cycleToplam=0;
	uint8_t round_robin=0;
    uint8_t cycle=0;
    theCPU.ReadFileIntoMemoryAt(argv[1], 0x0000);


    FILE *infile;

    Dosya yeni;
     
    // Open person.dat for reading
    infile = fopen ("example.dat", "r");
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }

    while(fread(&yeni, sizeof(struct dosya), 1, infile)){

        theOS.Dosyalar.push_back(yeni);
    }
     

    fclose(infile);


    theOS.thread_ids[0]=true;
    theOS.thread_joined_ids[0]=false;
    for(int i=1;i<10;i++){
        theOS.thread_joined_ids[i]=true;
        theOS.thread_ids[i]=false;
    }
  
     
    theOS.main_thread(mainThread,theCPU);
    theOS.cpu_cycle_sum=0;
   
    theOS.i=0;
    
    theOS.DEBUG=DEBUG;

    theOS.current_thread=&mainThread;

    do
    {
        
    
        theOS.switch_thread(theOS.i,theCPU);


        while(round_robin<100  && theOS.current_thread->thread_state!=1  && !theCPU.isHalted()){

    
      

            cycle=theCPU.Emulate8080p();

            //printf(" pc counter in robin  %d  id=%d\n",theCPU.state->pc,theOS.current_thread->thread_id );
       
            if(theCPU.isSystemCall())
                cycle+=theOS.handleCall(theCPU);

        

          
            cycleToplam+=cycle;
            round_robin+=cycle;
            theOS.cpu_cycle_sum+=cycle;

            theOS.current_thread->thread_cycle_used+=cycle;

            //std::cout<<"is halted  "<<theCPU.isHalted()<<std::endl;
            ///theOS.Threadler[i].thread_cycle_used+=cycle;

            //printf("round robin size  %d\n", round_robin);

        }

        
        if(!theCPU.isHalted()){

            if( theOS.Threadler.at(theOS.i).thread_state==2)
                 theOS.Threadler.at(theOS.i).thread_state=0;
            if(theOS.exit_flag==false){
               
                theOS.Save_Thread(theOS.i,theCPU);

            }
            else
                theOS.exit_flag=false;


            /*if(theOS.join_flag==true){
                printf("join flag\n");
                printf("join pc  %d\n",theOS.join_pc);
                printf("join sp  %d\n",theOS.join_sp);
                theOS.Threadler.at(theOS.i).thread_register.pc=theOS.join_pc;
                theOS.Threadler.at(theOS.i).thread_register.sp=theOS.join_sp;

                theOS.join_flag=false;
            }*/

            //std::cin.get();


            theOS.i++;
            if(theOS.i>=theOS.Threadler.size())
                theOS.i=0;

            round_robin=0;
        }
        

        
    }	while (!theCPU.isHalted());

    theOS.printFile(theCPU);

    FILE *outfile;

    outfile = fopen ("example.dat", "w");

    if (outfile == NULL)
    {

        fprintf(stderr, "\nError opend file\n");

        exit (1);

    }
 
    for(int i=0;i<theOS.Dosyalar.size();i++){

        fwrite (&theOS.Dosyalar.at(i), sizeof(struct dosya), 1, outfile);

    } 

    // write struct to file

    std::cout << "Total Of Cycles: " <<(int) cycleToplam << std::endl;

    return 0;

}

