#ifndef H_GTUOS
#define H_GTUOS

#include "8080emuCPP.h"
#include <vector>
#include <stdbool.h>
#include <ctime>

using namespace std;

typedef struct thread
{
	State8080 thread_register;
	uint16_t thread_id;
	uint64_t thread_start;
	uint16_t thread_cycle_used;
	uint8_t thread_state;
	uint16_t start_address;
	uint16_t	sp;
	uint16_t	pc;

	
}Thread;

typedef struct dosya
{
	char name[256];
	time_t creation_time;
	time_t last_modification;
	time_t last_access;
	int file_size;
    vector <char> content;
	int cursor;

	int file_id;

	bool is_open;

}Dosya;


class GTUOS{
	public:
		uint64_t handleCall(const CPU8080 & cpu); // handles call which comes from the hw
		void printFile(const CPU8080 & cpu); // writes memory content to file "exe.mem"
		uint8_t check_thread_id();

		void print_thread_table();

		void main_thread(Thread & mainThread,const CPU8080 & cpu);
		void switch_thread(uint8_t i,CPU8080 & cpu);
		void Save_Thread(uint8_t i,const CPU8080 & cpu);

		std::vector<Thread> Threadler;
		bool thread_ids[10];
		bool thread_joined_ids[10];

		uint8_t i;
		int DEBUG;

		bool exit_flag;

		Thread *current_thread;

		uint64_t cpu_cycle_sum;

		std::vector<Dosya> Dosyalar;
	
		
};	

#endif
