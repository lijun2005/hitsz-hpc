#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        sleep(2);
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        printf("chile progress sleep for 2\n");
    } else {
        // parent goes down this path (original process)
        sleep(1);
        printf("hello, I am parent of %d (pid:%d)\n",
	       rc, (int) getpid());
        printf("parent progress sleep for 1\n");
    }
    return 0;
}