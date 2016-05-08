#include "plateau.h"
#include "regles.h"
#include <string.h>

int main()
{
	Plateau p;
	int t=0;

	/* TEST INITIALISATION PLATEAU */

	printf("**INITIALISATION DU PLATEAU**\n");

	initialiser_plateau(p);

	printf("\n**VERIFICATION DES COTES**\n");

	printf("\n**COTE GAUCHE HAUT**\n\n");

	if(p[0][0].NE==NULL && p[0][0].NO==NULL && p[0][0].O==NULL && p[0][0].SO==NULL && p[0][0].SE!=NULL && p[0][0].E!=NULL)
	{
		t++;
		if(p[0][0].coul==neutre)
			t++;

		if(t==2)
			printf("OK\n");
	}

	printf("\n**COTE DROIT HAUT**\n\n");

	if(p[10][0].NE==NULL && p[10][0].NO==NULL && p[10][0].O!=NULL && p[10][0].SO!=NULL && p[10][0].SE!=NULL && p[10][0].E==NULL)
	{
		t++;
		if(p[10][0].coul==neutre)
			t++;

		if(t==4)
			printf("OK\n");
	}

	printf("\n**COTE GAUCHE BAS**\n\n");

	if(p[0][10].NE!=NULL && p[0][10].NO!=NULL && p[0][10].O==NULL && p[0][10].SO==NULL && p[0][10].SE==NULL && p[0][10].E!=NULL)
	{
		t++;
		if(p[0][10].coul==neutre)
			t++;

		if(t==6)
			printf("OK\n");
	}

	printf("\n**COTE DROIT BAS**\n\n");

	if(p[10][10].NE==NULL && p[10][10].NO!=NULL && p[10][10].O!=NULL && p[10][10].SO==NULL && p[10][10].SE==NULL && p[10][10].E==NULL)
	{
		t++;
		if(p[10][10].coul==neutre)
			t++;

		if(t==8)
			printf("OK\n");
	}

	printf("\n**VERIFICATION DES BORDS**\n");

	printf("\n**BORDS HAUT ET BAS**\n");

	int i;

	for(i=1; i<10; i++)
	{
		if(p[i][0].NE==NULL && p[i][0].NO==NULL && p[i][0].O!=NULL && p[i][0].SO!=NULL && p[i][0].SE!=NULL && p[i][0].E!=NULL)
		{
			t++;
			if(p[i][0].coul==neutre)
				t++;

			if(i==9 && t==42)
				printf("\nOK\n");
		}

		if(p[i][10].NE!=NULL && p[i][10].NO!=NULL && p[i][10].O!=NULL && p[i][10].SO==NULL && p[i][10].SE==NULL && p[i][10].E!=NULL)
		{
			t++;
			if(p[i][10].coul==neutre)
				t++;

			if(i==9 && t==44)
				printf("OK\n");
		}
	}

	printf("\n**BORDS GAUCHE ET DROIT**\n\n");

	for(i=1; i<10; i++)
	{
		if(p[0][i].NE!=NULL && p[0][i].NO!=NULL && p[0][i].O==NULL && p[0][i].SO==NULL && p[0][i].SE!=NULL && p[0][i].E!=NULL)
		{
			t++;
			if(p[0][i].coul==neutre)
				t++;

			if(i==9 && t==78)
				printf("OK\n");
		}

		if(p[10][i].NE==NULL && p[10][i].NO!=NULL && p[10][i].O!=NULL && p[10][i].SO!=NULL && p[10][i].SE!=NULL && p[10][i].E==NULL)
		{
			t++;
			if(p[10][10].coul==neutre)
				t++;

			if(i==9 && t==80)
				printf("OK\n");
		}
	}

	printf("\n**RESTE DU PLATEAU**\n");

	int j;

	for(i=1; i<10; i++)
	{
		for(j=1; j<10; j++)
		{
			if(p[i][j].NE!=NULL && p[i][j].NO!=NULL && p[i][j].O!=NULL && p[i][j].SO!=NULL && p[i][j].SE!=NULL && p[i][j].E!=NULL)
			{
				t++;
				if(p[i][j].coul==neutre)
					t++;
			}

			if(j==9 && i==9 && t==242)
				printf("\nOK\n");
		}
	}

	printf("\n**FIN DU TEST D'INITIALISATION**\n\n");

	/* TEST PLACEMENT D'UN PION */

	printf("\n**TEST PLACEMENT D'UN PION**\n\n");

	p[5][5].coul=rouge;
	
	if(p[5][5].coul==rouge)
		t++;printf("OK\n");

	/* TEST VALIDITE COUP */

	printf("\n**TEST VALIDITE D'UN COUP**\n\n");

	Type_Case c;
	c.co.abscisse=80;
	c.co.ordonnee=80;

	if(!dans_plateau(c.co))
		t++;printf("OK\n");

	/* TEST VAINQUEUR */

	printf("\n**TEST VAINQUEUR**\n\n");

	p[1][0].coul=rouge;
	p[1][1].coul=rouge;
	p[1][2].coul=rouge;
	p[1][3].coul=rouge;
	p[1][4].coul=rouge;
	p[1][5].coul=rouge;
	p[1][6].coul=rouge;
	p[1][7].coul=rouge;
	p[1][8].coul=rouge;
	p[1][9].coul=rouge;
	p[1][10].coul=rouge;

	if(verify_win(p[1][5],p))
		t++;printf("OK\n");

	/* TEST CHANGEMENT DE JOUEUR */

	printf("\n**TEST CHANGEMENT DE JOUEUR**\n\n");

	if(changer_joueur(bleu)==rouge)
		t++;printf("OK\n");

	/* TEST CREATION ET LECTURE FICHIER CONFIG */

	printf("\n**TEST CREATION ET LECTURE FICHIER CONFIG**\n\n");

	creation_config();

	FILE *read;
	read=fopen("config.txt","r");
	if(read)
		t++;printf("OK\n");
	fclose(read);

	/* TEST ANNULER UN COUP */

	printf("\n**TEST ANNULER UN COUP**\n\n");

	initialiser_plateau(p);
	board_save(p);
	p[1][0].coul=rouge;
	historique(1,p[1][0].co,p[1][0].coul);
	p[1][1].coul=rouge;
	historique(0,p[1][1].co,p[1][1].coul);
	annuler(p);

	if(p[1][1].coul!=rouge)
		t++;printf("OK\n");

	/* TEST CHARGEMENT */

	printf("\n**TEST CHARGEMENT**\n\n");

	initialiser_plateau(p);
	chargement(p);

	if(p[1][0].coul==rouge)
		t++;printf("OK\n");


	printf("\nNb de tests passés : %d/248\n",t);

	return 0;
}