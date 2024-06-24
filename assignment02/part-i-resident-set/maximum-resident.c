/*
 *
 * part-i-resident-set
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>

void wait_for_input(void);

int 
main(int argc, char*argv[])
{
	pid_t mypid;
	mypid = getpid();
	printf("Process ID: %d\n\n", mypid);

	char vmcmd [32];
	snprintf(vmcmd, 32, "procstat vm %d", mypid);

	size_t mem_size = 409600;
	size_t page_size = getpagesize();

	system(vmcmd);

	char * p = malloc(mem_size* sizeof(char));
	for(size_t i = 0; i<mem_size ; i+=page_size){
		memset(p+i, '$',1);
	}


	printf("AFTER MALLOC at %p: \n\n", p);
	system(vmcmd);
	free(p);

}

void 
wait_for_input(void)
{
	char buf[2];
	read(0, buf, 2);

}
