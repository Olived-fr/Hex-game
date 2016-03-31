#include "persistance.h"

bool verif_file(char *name)
{
  	FILE *fichier;
  	fichier=fopen(name, "r");
    
    return fichier;
        
  	fclose(fichier);
}

void creation_config()
{
	FILE *fichier;
	fichier=fopen("configuration.txt","w+");

	fprintf(fichier,"%s\n\n%s","/hex","/endhex");

	fclose(fichier);
}
