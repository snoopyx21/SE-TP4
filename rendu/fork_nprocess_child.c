#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int n)
{
    pid_t pid;
    int raison;
    pid=fork();
    pid_t pid_fils;
    pid_t pid_pere;
    for(int i=0;i<n;i++)
    {
    	switch(pid)
    	{
        	case -1 : 
        	{
            		// cas d'erreur
            		perror("fork()");
            		exit(1);
        	}
        	case 0 :    
        	{
            		pid_fils=getpid();
            		pid_pere=getppid();    
            		printf("pid du fils : %d \n pid du pere : %d \n",pid_fils,pid_pere);
            		exit(0);
        	}
        	default :
        	{
            		if(wait(&raison) == -1) perror("wait(&raison)");
            		if( WIFEXITED(raison) )
                		printf("processus fils termine avec %d avec code de retour %d",pid,WEXITSTATUS(raison));
            	else
            	{	 
                	printf("fils %d termine pour une raison bizarre \n",pid);
            	}
        	}
    	}
    }
    return 0;
}




