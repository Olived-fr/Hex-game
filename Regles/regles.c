#include "regles.h"



void nouvelle_partie(Plateau p)
{
	initialiser_plateau(p);
	creation_config();
	board_save(p);
}

bool bord(Type_Case c)
/* On vérifie si la case est un bord */
{
	bool b=false;

	if(c.coul==bleu)
	/* Si la case est bleu alors si c'est un bord ses voisins NORD-OUEST et NORD-EST OU ses voisins SUD-OUEST et SUD-EST seront égal à NULL */
	{
		if((c.NO==NULL && c.NE==NULL) || (c.SO==NULL && c.SE==NULL))
		{
			b=true;
		}
	}
	else
	/* Sinon la case est rouge, si c'est un bord ses voisins OUEST et SUD-OUEST OU ses voisins NORD-EST et EST seront égal à NULL */
	{
		if((c.O==NULL && c.SE==NULL) || (c.NE==NULL && c.E==NULL))
		{
			b=true;
		}
	}
	return b;
}

bool bord_oppose(Type_Case deb, Type_Case comp)
/* Retourne vrai si la case comp (comparaison) est le bord opposé de la case deb (début) */
{
	bool b=false;

	if(deb.NE==NULL && deb.E==NULL)
	/* Compare case bord droit à case bord gauche */
	{
		if(comp.O==NULL && comp.SO==NULL)
		{
			b=true;
		}
	}
	else if(deb.O==NULL && deb.SO==NULL)
	/* Compare case bord gauche à case bord droit */
	{
		if(comp.NE==NULL && comp.E==NULL)
		{
			b=true;
		}
	}
	else if(deb.NO==NULL && deb.NE==NULL)
	/* Compare case bord haut à case bord bas */
	{
		if(comp.SO==NULL && comp.SE==NULL)
		{
			b=true;
		}
	}
	else if(deb.SO==NULL && deb.SE==NULL)
	/* Compare case bord bas à case bord haut */
	{
		if(comp.NO==NULL && comp.NE==NULL)
		{
			b=true;
		}
	}
	
	return b;
}

bool verify_win(Type_Case cur, Type_Case prev, Type_Case deb)
/* Vérification de la victoire d'un des deux joueurs */
{
	int i=0;
	bool b=false;
	bool tab[6];

	if(!bord(deb))
	{
		i=6;
	}

	while(!b && i!=6)
	/* On continue tant que tous les voisins n'ont pas été checkés et tant que le bord opposé n'a pas été trouvé */
	{
		if(bord_oppose(deb,cur))
		{
			b=true;
		}

		switch (i)
		{
			case 0:
				if(tab[0]==1)
				{
					i++;
				}
				else if(cur.SE==NULL || cur.SE==&prev || cur.SE->coul!=cur.coul)
				{
					i++;
					tab[0]=1;
				}
				else
				{
					tab[0]=1;
					b=verify_win(*cur.SE,cur,deb);
				}
			break;

			case 1:
				if(tab[1]==1)
				{
					i++;
				}
				else if(cur.SO==NULL || cur.SO==&prev || cur.SO->coul!=cur.coul)
				{
					i++;
					tab[1]=1;
				}
				else
				{
					tab[0]=1;
					b=verify_win(*cur.SO,cur,deb);
				}
			break;

			case 2:
				if(tab[2]==1)
				{
					i++;
				}
				else if(cur.O==NULL || cur.O==&prev || cur.O->coul!=cur.coul)
				{
					i++;
					tab[2]=1;
				}
				else
				{
					tab[2]=1;
					b=verify_win(*cur.O,cur,deb);
				}
			break;

			case 3:
				if(tab[3]==1)
				{
					i++;
				}
				else if(cur.NO==NULL || cur.NO==&prev || cur.NO->coul!=cur.coul)
				{
					i++;
					tab[3]=1;
				}
				else
				{
					tab[3]=1;
					b=verify_win(*cur.NO,cur,deb);
				}
			break;

			case 4:
				if(tab[4]==1)
				{
					i++;
				}
				else if(cur.NE==NULL || cur.NE==&prev || cur.NE->coul!=cur.coul)
				{
					i++;
					tab[4]=1;
				}
				else
				{
					tab[4]=1;
					b=verify_win(*cur.NE,cur,deb);
				}
			break;

			default:
				if(tab[5]==1)
				{
					i++;
				}
				else if(cur.E==NULL || cur.E==&prev || cur.E->coul!=cur.coul)
				{
					i++;
					tab[5]=1;
				}
				else
				{
					tab[5]=1;
					b=verify_win(*cur.E,cur,deb);
				}
			break;
		}
	}

	return b;
}


Couleur changer_joueur(Couleur couleur_courante) 
{
	if (couleur_courante==bleu)
		return rouge;
	else
		return bleu;
}


void choix_coup(Plateau p,Coordonnees_tab c,Couleur couleur_courante)
{
		p[c.abscisse][c.ordonnee].coul=couleur_courante;
}


bool coup_valide(Plateau p,Coordonnees_tab c)
{
	return dans_plateau(c) && p[c.abscisse][c.ordonnee].coul==neutre;
}
