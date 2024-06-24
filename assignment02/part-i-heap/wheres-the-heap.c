/*
 * wheres-the-heap.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void wait_for_input(void);

int
main(int argc, char *argv[])
{
    pid_t mypid;
    mypid = getpid();
    printf("my pid is %d\n", mypid);

    FILE *fp; 

    fp = fopen("sample-output.txt", "w+");



    char vmcmd[32];
    snprintf(vmcmd, 32, "procstat vm %d", mypid);

    printf("Before malloc:\n");
    system(vmcmd);
    wait_for_input();


    size_t n = 200000000;
    char *p = malloc(n);
    memset(p, 'p', n);
   // char *p2 = malloc(n);

    if(p == NULL) {
        perror("malloc");
        exit(1);
    }
    printf("Malloced Addresses: %p should end here: %p, or %p\n\n", p, p-n, p+n);
    printf("After malloc:\n");
    system(vmcmd);
    wait_for_input();
    //free(p2);
    free(p);
    printf("After free:\n");
    system(vmcmd);
    fclose(fp);
}

void
wait_for_input(void)
{
    char buf[2];
    read(0, buf, 2);
}

