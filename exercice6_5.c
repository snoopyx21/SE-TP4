#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>

int main(int argc, char ** argv)
{
    if (argc < 2)
    {
        printf("je veux un ls -l rep \n");
        exit(1);
    }
    struct timeval tv, tv2;
    pid_t pid=fork();
    int raison;
    if((gettimeofday(&tv, NULL)) == -1)
    {
        perror("gettimeofday(&tv, NULL)");
        exit(0);
    }
    printf("heure en secondes : %ld secondes\n",tv.tv_sec);
    printf("heure en micro secondes : %ld ms \n", tv.tv_usec);
    switch(pid)
    {
        case -1 : 
        {
            perror("fork()");
            exit(1);
        }
        case 0 :   
        {
            execlp("ls","ls","-l",argv[1], NULL);
        }
        default :
        {
            if(wait(&raison) == -1)
            {
                perror("gettimeofday");
                exit(1);
            }
            if(gettimeofday(&tv2, NULL) == -1)
            {
                perror("gettimeofday");
                exit(1);
            }
            else 
            {
                printf("heure en secondes : %ld secondes\n",tv2.tv_sec);
                printf("heure en micro secondes : %ld ms \n", tv2.tv_usec);
                printf("processus termine en %ld secondes \n", tv2.tv_sec-tv.tv_sec);
                printf("processus termine en %ld ms \n",tv2.tv_usec-tv.tv_usec);
                
            }
        }
    }
    return 0;
}


