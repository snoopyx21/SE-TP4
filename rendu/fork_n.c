#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void forkChildren (int nChildren) 
{
    int i;
    pid_t pid;
    for (i = 1; i <= nChildren; i++) 
    {
        pid = fork();
        if (pid == -1) 
	{
            perror("fork()");
            return;
        }
        if (pid == 0) {
            printf("Processus fils numero %d avec le PID: %d\n",i, getpid());
            sleep (5);
            return;
        }
    }
}

int main (int argc, char *argv[]) 
{
    if (argc < 2) 
    {
        forkChildren (2);
    } else 
    {
        forkChildren (atoi (argv[1]));
    }
    return 0;
}
