#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    pid_t  child_pid;
    //fork process
    child_pid = fork();

    //check for fork error
    if (child_pid < 0) {
        fprintf(stderr, "Fork failed.");
        exit(-1);
    }

    //CHILD PROCESS
    else if (child_pid == 0) {
        fprintf(stderr, "This is child process %d\n", getpid());
        //fork process
        pid_t grandchild_pid;
        grandchild_pid = fork();

        //check for fork error
        if(grandchild_pid < 0){
            fprintf(stderr, "Fork failed.");
            exit(-1);
        }

        //GRANDCHILD PROCESS
        else if(grandchild_pid == 0){
            fprintf(stderr, "This is grand child process %d\n", getpid());
            //start firefox
            execlp("/usr/bin/firefox", "ls", NULL);
        }
        //wait for grand child
        else {
            printf("Child waiting for the grand child to complete. \n");
            wait(NULL);
            printf("\nGrand child complete.\n");
            exit(0);
        }
    }

    //PARENT PROCESS
    else {
        //wait for child process
        fprintf(stderr, "This is parent process %d\n", getpid());
        printf("Parent waiting for the child to complete.\n");
        wait(NULL);
        printf("\nChild complete.\n");
        exit(0);
    }
}
