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

	size_t mem_size = 3000000000;
	
	char * p = malloc(mem_size* sizeof(char));
	memset(p, 'p',mem_size);

	printf("AFTER MALLOC at %p: \n\n", p);
	system(vmcmd);
	free(p);

}

