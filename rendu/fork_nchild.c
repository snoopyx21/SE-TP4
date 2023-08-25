#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main( int argc, char ** argv )
{
    if (argc < 2)
    {
	 printf("Wrong arguments \n");
	 return 1;
    }
    printf( "[dad] pid %d\n", getpid() );
    pid_t pid;
    int status;
    for ( int i = 0; i < atoi(argv[1]); i++ )
    { 
	pid=fork();
	if(pid == -1)
	{
	    perror("fork()");	
	    exit(1);
	}
	if ( pid == 0 )
        {
            printf( "[son] pid %d number %d from pid [parent] %d\n", getpid(), i, getppid() );
            exit( 0 ); // si tout se passe bien, code de retour 0
        }
    }
    for ( int j = 0; j < atoi(argv[1]); j++ )
    {    
	if((pid=wait(&status)) == -1) perror("wait(&status)");
	printf("[son] pid %d finish / return %d \n",pid, WEXITSTATUS(status) );
	    
    }
    return 0;
}
