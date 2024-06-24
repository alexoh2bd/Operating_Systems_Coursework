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


	char vmcmd2 [32];
	snprintf(vmcmd2, 32, "vmstat -w 1 " );
	system(vmcmd2);


}

