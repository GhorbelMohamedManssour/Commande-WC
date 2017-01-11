#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
int my_open(const char* file, int flags, mode_t mode)
{
  int f = open(file,flags,mode);
  if (f<0) {
    fprintf(stderr,"echec d'ouverture de %s (%s)\n",file,strerror(errno));
    exit(1);
  }
  return f;
}


int nb ( const char *file)
{
char buf[65536]; 
int src;
src=my_open(file,O_RDONLY,0);
int nb_lignes, nb_caracteres, nb_mots;
char tampon[128];
nb_lignes = 0;
nb_caracteres = 0;
nb_mots = 0;
FILE *fichier;
fichier = fopen(file, "r" );

	while(fgets(tampon, 128, fichier))
	{
 	char *token ;
 	nb_lignes++;
 	nb_caracteres += strlen(tampon);
 	token = strtok(tampon, " \t" ); 
 		while(token)
 		{
 			nb_mots++;
 			token = strtok( NULL, " \t" );
 		}
	}
close(src);
fclose(fichier);
printf("lignes : %d     caractères : %d       mots : %d\n", nb_lignes, nb_caracteres, nb_mots);
return 0;
}

int main(int argc, const char** argv)
{
  int src;         

  if (argc!=2) 
	{
    fprintf(stderr,"%s: verifier le nombre d\'arguments \n",argv[0]);
    exit(1);
	}
	src=my_open(argv[1],O_RDONLY,0);
  
  	nb(argv[1]);

  	close(src);

  return 0;
}
