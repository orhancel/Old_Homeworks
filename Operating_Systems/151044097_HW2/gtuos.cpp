#include <iostream>
#include "8080emuCPP.h"
#include "gtuos.h"
#include <ctime>


using namespace std;


void GTUOS::main_thread(Thread & mainThread,const CPU8080 & cpu){



	mainThread.thread_register=*(cpu.state);

    mainThread.thread_id=0;

    mainThread.thread_start=0;

    mainThread.thread_cycle_used=0;

    mainThread.start_address=cpu.state->pc;

    mainThread.thread_state=2;

    Threadler.insert(Threadler.begin()+mainThread.thread_id,mainThread);

    thread_ids[mainThread.thread_id]=true;




}

void GTUOS::Save_Thread(uint8_t j,const CPU8080 & cpu){

	//printf("save thread  cpu   j=%d  pc=%d  \n",j ,cpu.state->pc);
	//printf("save thread  cpu   j=%d  sp=%d  \n",j ,cpu.state->sp);

	//printf("save B %d\n", cpu.state->b);

	Threadler.at(j).thread_register=*(cpu.state);



}


void GTUOS::switch_thread(uint8_t j, CPU8080 & cpu){

		if(DEBUG==2){
			printf("\n");
			printf("Cycle spent for  %d  is   %d  \n",current_thread->thread_id,current_thread->thread_cycle_used );
			printf("Thread switch  to  %d",Threadler.at(j).thread_id);
			printf("   from %d\n", current_thread->thread_id);
		}
		
		
		
		//printf("thread111 pc  and stack111   id111  %d    %d   %d \n", cpu.state->pc,cpu.state->sp,current_thread->thread_id);

		*(cpu.state) = Threadler.at(j).thread_register;

		
		
		current_thread = &Threadler.at(j);

		current_thread->thread_state=2;
		if(DEBUG==3)
			print_thread_table();

	

		//printf("thread222 pc  and stack2222    id222  %d    %d   %d\n", current_thread->thread_register.pc,current_thread->thread_register.sp,current_thread->thread_id);
}


uint64_t GTUOS::handleCall(const CPU8080 & cpu){


	uint16_t address = ((uint16_t)cpu.state->b << 8) | cpu.state->c;

    uint64_t cycleCount=0;
	if(cpu.state->a == (uint8_t)1){

		cout<<endl;
		cout << "Call: PRINT_B" << endl;
		cout << "Content of B: " << (int)cpu.state->b <<"  of  thread id: "<< current_thread->thread_id<< endl;
		//printf("thred id  %d\n",Threadler.at(i).thread_id);
		//printf("iiiiii  %d\n",i);
		cout<<endl;

	
		cycleCount = 10;	
	}
	
	else if(cpu.state->a == (uint8_t)2){
		cout << "Call: PRINT_MEM" << endl;
		cout << "Content of Memory: " << cpu.memory->at(address) << endl; 
		cycleCount = 10;	
	}
	// Read an integer. 
	else if(cpu.state->a == (uint8_t)3){
		
		int temp;
		cin >> temp;
		cpu.state->b = (uint8_t)temp;
        cout << "Call: READ_B  :  " << temp <<" value readed into B"<< endl;
		cin.clear();
		cycleCount = 10;
	}
	// Read memory content
	else if(cpu.state->a == (uint8_t)4){
		
		uint8_t temp;
		cin >> temp;
		
		cpu.memory->at(address) = temp;
        	cout << "Call: READ_MEM  :  " << cpu.memory->at(address) <<" value readed into memory" << endl;
		cin.clear();
		cycleCount = 10;
	}
	// Print string
	else if(cpu.state->a == (uint8_t)5){
		cout << "Call: PRINT_STR" << endl;
		char ch ='x';
		for(int i=0; ch != '\0'; ++i){
               		ch = (char)cpu.memory->at(address+i);
                	cout << ch;
            	}
            	
		
		cycleCount = 100;
	}
	// Read a string.
	else if(cpu.state->a == (uint8_t)6){
		cout << "Call: READ_STR" << endl;
		char ch ;
		
		int count=0;
		do{
			ch = getchar();
			cpu.memory->at(address+count) = ch;
			++count;
		}while(ch != '\n');
		cpu.memory->at(address+count)= (uint8_t)'\0';
		
		cycleCount = 100;
	}
	// Get a random integer.
	else if(cpu.state->a == (uint8_t)7){
		cout << "Call: GET_RND" << endl;
	
    	int r = (rand() % 255) + 1;
    	cpu.state->b = (uint8_t)r;
		cout<<"Random number is  :  "<<(int)cpu.state->b<<endl;
		cycleCount = 5;
	}
	else if(cpu.state->a == (uint8_t)11){

		cout << "Call: TCreate" << endl;
		//printf("ii    %d\n",i);
		printf("  thread id %d    pc  %d\n",current_thread->thread_id ,cpu.state->pc);
		//printf("  adress  %d \n",address );
		
		Thread yeni;

		yeni.thread_register.b=0;

		yeni.thread_register.a=0;

		yeni.thread_register.pc=address;

		yeni.start_address=address;

		yeni.thread_id=check_thread_id();

	
		yeni.thread_register.sp=cpu.state->sp-(1024*yeni.thread_id);

		

		//printf("yeni thread id  %d\n", yeni.thread_id);

		//printf("current thread id  %d \n",current_thread->thread_id);

		yeni.thread_start=this->cpu_cycle_sum;

		yeni.thread_cycle_used=0;

		yeni.thread_state=0;
	

		Threadler.push_back(yeni);
		//printf("threadler size %d\n", Threadler.size());

		

		//printf("array cıkıs\n" );

		thread_ids[yeni.thread_id]=true;
		thread_joined_ids[yeni.thread_id]=false;

	

		cpu.state->b =(uint8_t) yeni.thread_id;

		cycleCount=80;

	}
	else if(cpu.state->a == (uint8_t)8){

		cout << "Call: TExit  from  thread " << current_thread->thread_id<<endl;
		//std::cin.get();
		
		
		thread_ids[current_thread->thread_id]=false;
		Threadler.erase(Threadler.begin()+i);

		current_thread->thread_state=1;
		i--;
		exit_flag=true;
		cycleCount=50;
		//std::cin.get();

	}
	else if(cpu.state->a == (uint8_t)9){
		uint8_t Wait_id=(uint8_t)cpu.state->b;
		cout << "Call: TJoin  with thread "<< (int)Wait_id << endl;

		//printf("current  pc %d\n",cpu.state->pc);
		//printf("old  pc %d\n",current_thread->thread_register.pc);

		if( thread_ids[Wait_id]==true){
			/*printf("cpu  pc %d\n",cpu.state->pc );
			printf("current pc %d\n",current_thread->thread_register.pc );
			printf("cpu  sp %d\n",cpu.state->sp );
			printf("current sp %d\n",current_thread->thread_register.sp );*/

			*(cpu.state)=current_thread->thread_register;

			current_thread->thread_state=1;


			//printf("Join failes with  thread:%d\n",(int)Wait_id  );
			

			
		}
		if(thread_ids[Wait_id]==false && thread_joined_ids[Wait_id]==false){
			printf("Join succesfull with  thread:%d\n",(int)Wait_id  );
			thread_joined_ids[Wait_id]=true;
		}
		/*else{
			current_thread->thread_state=2;
			//printf("Join succes current  pc %d\n",cpu.state->pc);
			//printf("Join succes current  sp %d\n",cpu.state->sp);
			//printf("wait id  %d \n",(int)Wait_id  );
			join_flag=true;
			join_pc=cpu.state->pc;
			join_sp=cpu.state->sp;
		}*/
	

		cycleCount=40;

	}
	else if(cpu.state->a == (uint8_t)10){
		

		cout << "Call: TYield   Thread  id:"<< current_thread->thread_id << endl;

		current_thread->thread_state=1;


		cycleCount=40;

	}
	

	// Case of Undefined call.
	else{

    cout <<  "Undefined OS Call";
    cout << "Content of B: " << (int)cpu.state->b << endl;
    cout << "Content of A: " << (int)cpu.state->a  << endl;
    
    throw -1;
	} 
	
	
	return cycleCount;
}

uint8_t GTUOS::check_thread_id(){

	for(int i=0;i<10;i++){
		if(thread_ids[i]==false  &&  thread_joined_ids[i]==true)
			return i;
	}

}

// Write memory to  "exe.mem" file 
void GTUOS::printFile(const CPU8080 & cpu){

	FILE *File_ptr;
	File_ptr = fopen("exe.mem" , "w");	

	if(File_ptr == NULL){ 
		fprintf(stderr, "File couldn't opened to write.\n");
		exit(1);
	}	


    	for(int i=0; i < 65536; i += 16){////65536=256*256
		fprintf(File_ptr, "%04x:   ", i);
		for(int j =0; j < 16; ++j){
			fprintf(File_ptr, "%02x ", cpu.memory->at(uint16_t (i+j)));
		}
		fprintf(File_ptr, "\n");
	}

	
	fclose(File_ptr);
	return;
}

void  GTUOS::print_thread_table(){


	for(int j=0;j<Threadler.size();j++){
		printf("\n");
		printf("Thread id=%d  ",Threadler.at(j).thread_id );
		printf("Thread start cycle=%d   ",(int)Threadler.at(j).thread_start );
		printf("Thread cycle used=%d   ",Threadler.at(j).thread_cycle_used );

		switch (Threadler.at(j).thread_state){

			case 0:
				printf("Thread state=READY   ");
				break;
			case 1:
				printf("Thread state=BLOCKED   ");
				break;
			case 2:
				printf("Thread state=RUNNING   ");
				break;

		}
		printf("Thread start address=%d   ",Threadler.at(j).start_address );




	}
	printf("\n");



}

