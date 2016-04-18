#include "persistance.h"

bool verif_file(char *name)
/* Fonction de vérification de la validité de l'existence du fichier */
{
  	FILE *fichier;
  	fichier=fopen(name, "r");
    
    return fichier;
        
  	fclose(fichier);
}

void creation_config()
/* Fonction de création du fichier config avec le repère /hex */
{
	FILE *fichier;
	fichier=fopen("configuration.txt","w+");

	fprintf(fichier,"%s\n\n%s\n\n","\\hex","\\board");

	fclose(fichier);
}

void board_save(char Nom[])
/* Fonction de sauvegarde de tout le plateau, on l'écrit dans le fichier config entre les repères : /board /endboard */
{
	if(!verif_file(Nom))
	{
		perror(Nom);
		exit(1);
	}

	char board[10];
	int i,j;
	FILE *fichier;
	fichier=fopen(Nom,"r+");

	rewind(fichier);

	/* On place le curseur juste après le repère \board */
	while(strcmp(board,"\\board")!=0)
	{
		fscanf(fichier,"%s",board);
	}

	/* On copie la description du plateau de jeu */
	for(i=0; i<11; i++)
	{
		for(j=0; j<11; j++)
		{
			/* if(p[i][j].coul==rouge)
			{
				fprintf(fichier,"%d %d R\n",i,j);
			}
			else if(p[i][j].coul==bleu)
			{
				fprintf(fichier,"%d %d B\n",i,j);
			} 
			else
			{ */
				fprintf(fichier,"%d %d .\n",i,j);
			

		}
	}

	fprintf(fichier,"\n\\endboard\n");

	fclose(fichier);
}



int main()
{
	creation_config();
	board_save("configuration.txt");

	return 0;
}
