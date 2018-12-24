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
    uint64_t cycleToplam=0;
	
    theCPU.ReadFileIntoMemoryAt(argv[1], 0x0000);

    do
    {
        cycleToplam+=theCPU.Emulate8080p(DEBUG);
        if(theCPU.isSystemCall())
            theOS.handleCall(theCPU);
        if(DEBUG == 2)
            std::cin.get();
    }	while (!theCPU.isHalted());

    theOS.printFile(theCPU);

    std::cout << "Total Of Cycles: " <<(int) cycleToplam << std::endl;

    return 0;

}


