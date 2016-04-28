#include "persistance.h"

bool verif_file(char *name)
/* Fonction de vérification de la validité de l'existence du fichier */
{
  	FILE *fichier;
  	fichier=fopen(name,"r");
    
    return fichier;
        
  	fclose(fichier);
}

void creation_config()
/* Fonction de création du fichier config avec le repère /hex */
{
	FILE *fichier;
	fichier=fopen("config.txt","w+");

	fprintf(fichier,"%s\n\n%s\n\n","\\hex","\\board");

	fclose(fichier);
}

void board_save(Plateau p)
/* Fonction de sauvegarde de tout le plateau, on l'écrit dans le fichier config entre les repères : /board /endboard */
{
	if(!verif_file("config.txt"))
	{
		perror("Impossible de lire config.txt");
		exit(1);
	}

	char board[10];
	int i,j;
	FILE *fichier;
	fichier=fopen("config.txt","r+");

	/* Placement du curseur au début du fichier */
	rewind(fichier);

	/* On place le curseur juste après le repère \board */
	while(strcmp(board,"\\board")!=0)
	{
		fscanf(fichier,"%s",board);
	}

	/* On décale le curseur de 2 caractère pour aller à la ligne */
	fseek(fichier,sizeof(char)*2,SEEK_CUR);

	/* On copie la description du plateau de jeu */
	for(i=0; i<11; i++)
	{
		for(j=0; j<11; j++)
		{
			if(p[i][j].coul==rouge)
			/* Si la case contient un pion rouge on écrit ses coordonnées et le repère 'R' dans le fichier */
			{
				fprintf(fichier,"%d %d R\n",i,j);
			}
			else if(p[i][j].coul==bleu)
			/* Si la case contient un pion bleu on écrit ses coordonnées et le repère 'B' dans le fichier */
			{
				fprintf(fichier,"%d %d B\n",i,j);
			} 
			else
			/* Si la case est vide on écrit ses coordonnées et le repère '.' */
			{ 
				fprintf(fichier,"%d %d .\n",i,j);
			}
		}
	}
	
	fprintf(fichier,"\n\\endboard\n\n");

	fclose(fichier);
}

void historique(bool b, Coordonnees_tab cor, Couleur co)
{
	if(!verif_file("config.txt"))
	{
		perror("Impossible de lire config.txt");
		exit(1);
	}

	char cur[10];
	FILE *fichier;
	fichier=fopen("config.txt","r+");

	/* Placement du curseur au début du fichier */
	rewind(fichier);

	if(b)
	{
		/* Si c'est le premier tour de jeu on place le curseur juste après le repère \endboard */
		while(strcmp(cur,"\\endboard")!=0)
		{
			fscanf(fichier,"%s",cur);
		}

		fprintf(fichier,"\\game\n\n");

		/* On écrit les coordonnées du premier coup placé dans le fichier */
		if(co==rouge)
		{
			fprintf(fichier,"\\play R %d %d\n",cor.abscisse,cor.ordonnee);
		}
		else
		{
			fprintf(fichier,"\\play B %d %d\n",cor.abscisse,cor.ordonnee);
		}

		/* ceci est un test : fprintf(fichier,"\\play R 1 3\n"); */

		fprintf(fichier,"\n\\endgame\n");

		fprintf(fichier,"\n\\endhex\n");
	}
	else
	{
		/* Sinon on place le curseur juste après le dernier repère \play */
		while(strcmp(cur,"\\endgame")!=0)
		{
			fscanf(fichier,"%s",cur);
		}

		fseek(fichier,-(sizeof(char)*9),SEEK_CUR);

		/* ceci est un test : fprintf(fichier,"\\play B 2 3\n"); */

		/* On écrit les coordonnées du dernier coup placé dans le fichier */
		if(co==rouge)
		{
			fprintf(fichier,"\\play R %d %d\n",cor.abscisse,cor.ordonnee);
		}
		else
		{
			fprintf(fichier,"\\play B %d %d\n",cor.abscisse,cor.ordonnee);
		}

		/* Comme l'écriture dans le fichier écrase les anciennes données, on ré-écrit \endgame et \endhex */
		fprintf(fichier,"\n\\endgame\n");

		fprintf(fichier,"\n\\endhex\n"); 
	}

	fclose(fichier);
}

void dernier_coup(char couleur[], int *abscisse, int *ordonnee)
{
	char cur[10];
	FILE *config;
	config=fopen("config.txt","r");

	/* Recherche du dernier coup joué */
	fscanf(config,"%s",cur);

	while(strcmp(cur,"\\endgame")!=0)
	{
		fscanf(config,"%s",cur);
	}
	/* Décalage du curseur jusqu'aux dernières coordonnées avant le endgame */
	fseek(config,-(sizeof(char)*15),SEEK_CUR);

	fscanf(config,"%c %d %d",couleur,abscisse,ordonnee);

	fclose(config);
}


/*int main()
{
	int absi,ordo;
	char lel[1];
	creation_config();
	board_save();
	historique(0);

	dernier_coup(lel,&absi,&ordo);

	printf("NIXAMER : %s %d %d\n",lel,absi,ordo);

	return 0;
}*/




