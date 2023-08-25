#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>

// define à choisir (main/pas main)
#define DEBUG
//#undef DEBUG

/** fonction qui sépare la chaine de caractères 'chaine'
 *  avec tous les séparateurs présents dans 'separateurs'
 *  renvoie un tableau NULL-terminated de mots
 *  utilise la mémoire de chaine pour cela (modifie la chaine) !
 */
char **separe( char *chaine, const char *separateurs )
{
	char **tab;
	int i, s, m, size=10;
	
	tab = malloc( size * sizeof(char*) );
	m = 0;
	i = 0;
	while( chaine[i] != 0 )
	{
		// saute un séparateur
		for( s=0 ; separateurs[s]!=0 ; s++ )
			if( chaine[i] == separateurs[s] )
				break;
		if( separateurs[s]!=0 )
		{
			chaine[i++] = 0;	// met un fin de chaine à la place du séparateur et avance
			continue;	// les séparateurs n'ont pas été épuisés
		}

		if( chaine[i] != 0 )
			tab[m++] = chaine+i;
		if( m == size )
		{
			// si j'atteinds la limite de la taille de mon tableau, je l'agrandis.
			size += 10;
			tab = realloc( tab, size * sizeof(char*) );
		}
		// saute les caractères non séparateurs
		for( ; chaine[i]!=0 ; i++ )
		{
			for( s=0 ; separateurs[s]!=0 ; s++ )
				if( chaine[i] == separateurs[s] )
					break;
			if( separateurs[s]!=0 )
				break;	// trouvé un caractère séparateur, j'arrête d'avancer et je passe au mot suivant
		}
	}
	tab[m] = NULL;
	return( tab );
}

#ifdef DEBUG
int main(int argc, char ** argv)
{
    if(argc !=2)
    {
        printf("nombre d'arguments incorrects \n");
        return -1;
    }
	int i ;
    int s_cl;
	char *ge_path, *path, **tab;
    DIR * dp;
    struct dirent *d;	


	// récupère la valeur de $PATH
	ge_path = getenv ("PATH");
	// crée une copie locale modifiable
	// (on ne doit pas modifier la zone mémoire renvoyée par getenv)
	path = malloc( strlen(ge_path)+1 );
	strcpy( path, ge_path );
	
	tab = separe( path, ":" ) ;
	
	for( i=0 ; tab[i] != NULL ; i++ )
	{
		//printf ("%s\n", tab [i]) ;
        if ((dp=opendir(tab[i])) == NULL)
        {
            free( tab );
	        free( path );
            return -1;
        }
        while((d=readdir(dp)) != NULL)
        {
            if(strcmp(d->d_name,argv[1]) ==0)
            {
                
                printf("%s/%s \n",tab[i],argv[1]);
                free( tab );
	            free( path );
                s_cl=closedir(dp);
                if(s_cl==-1) perror("closedir(dp)");
                exit(0);
            }
        }
        s_cl=closedir(dp);
        if(s_cl==-1) perror("closedir(dp)");
        
	}
	free( tab );
	free( path );
	
	exit (0) ;
}
#endif


