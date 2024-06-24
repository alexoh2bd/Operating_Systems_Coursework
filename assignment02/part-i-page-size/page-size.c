/*
 *
 * page-size.c
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>


void wait_for_input(void);
	
int
main(int argc, char * argv[])
{
  wait_for_input();
  size_t size = 16384;

  char * p;
  p = malloc(size);

  memset(p, 'p', size);
  printf("Mapped Addresses: %p \n", p);

 
}

void
wait_for_input(void)
{
    char buf[2];
    read(0, buf, 2);

}

