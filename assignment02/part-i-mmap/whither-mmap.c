/*
 *
 * Whither mmap
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
char * map;
int fd, offset = 0;
struct stat fileInfo;
size_t size = 4096;


const char *fp = "./sample-output.txt";

if((fd = open(fp, O_RDONLY))== -1){
perror("open");
exit(1);
}

// process id
pid_t mypid;
mypid = getpid();
printf("mypid is %d\n", mypid);

char vmcmd[32];
snprintf(vmcmd, 32, "procstat vm %d", mypid);

// display procstat before 
printf("Before mmap:\n");
system(vmcmd);
wait_for_input();


// then mmap memory
map = mmap(0, size, PROT_READ, MAP_ANONYMOUS, -1, 0);
if(map == MAP_FAILED){
  perror("mmap");
  exit(1);
}

// print mapped memory address
printf("Mapped memory address :%p\n", map);


// display procstat again
printf("After mmap:\n");
system(vmcmd);

// free(map);

if(munmap(map,size) == -1){
	perror("Error un-mapping file");
	exit(1);
}

printf("After un-map:\n");
system(vmcmd);

// display 
close(fd);
}

void 
wait_for_input(void)
{
	char buf[2];
	read(0, buf, 2);

}
