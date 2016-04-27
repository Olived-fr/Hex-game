#include "regles.h"



void nouvelle_partie(Plateau p)
{
	initialiser_plateau(p);
	creation_config();
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
	if(deb.NE==NULL && deb.E==NULL)
	/* Compare case bord droit à case bord gauche */
	{
		return (comp.O==NULL && comp.SO==NULL);
	}
	else if(deb.O==NULL && deb.SO==NULL)
	/* Compare case bord gauche à case bord droit */
	{
		return (comp.NE==NULL && comp.E==NULL);
	}
	else if(deb.NO==NULL && deb.NE==NULL)
	/* Compare case bord haut à case bord bas */
	{
		return (comp.SO==NULL && comp.SE==NULL);
	}
	else if(deb.SO==NULL && deb.SE==NULL)
	/* Compare case bord bas à case bord haut */
	{
		return (comp.NO==NULL && comp.NE==NULL);
	}
	else
	{
		return false;
	}
}

bool verify_win(Type_Case cur, Type_Case prev, Type_Case deb)
/* Vérification de la victoire d'un des deux joueurs */
{
	int i=0;
	bool b=false;
	bool tab[6];

	while(!b && i!=6)
	/* On continue tant que tous les voisins n'ont pas été checkés et tant que le bord opposé n'a pas été trouvé */
	{
		switch (i)
		{
			case 0:
				if(cur.SE==&prev || cur.SE->coul!=cur.coul || cur.SE==NULL)
				{
					i++;
					tab[0]=1;
				}
				else if(tab[0]==1)
				{
					i++;
				}
				else if(bord_oppose(deb,cur))
				{
					b=true;
				}
				else
				{
					b=verify_win(*cur.SE,cur,deb);
				}
			break;

			case 1:
				if(cur.SO==&prev || cur.SO->coul!=cur.coul || cur.SO==NULL)
				{
					i++;
					tab[1]=1;
				}
				else if(tab[1]==1)
				{
					i++;
				}
				else if(bord_oppose(deb,cur))
				{
					b=true;
				}
				else
				{
					b=verify_win(*cur.SO,cur,deb);
				}
			break;

			case 2:
				if(cur.O==&prev || cur.O->coul!=cur.coul || cur.O==NULL)
				{
					i++;
					tab[2]=1;
				}
				else if(tab[2]==1)
				{
					i++;
				}
				else if(bord_oppose(deb,cur))
				{
					b=true;
				}
				else
				{
					b=verify_win(*cur.O,cur,deb);
				}
			break;

			case 3:
				if(cur.NO==&prev || cur.NO->coul!=cur.coul || cur.NO==NULL)
				{
					i++;
					tab[3]=1;
				}
				else if(tab[3]==1)
				{
					i++;
				}
				else if(bord_oppose(deb,cur))
				{
					b=true;
				}
				else
				{
					b=verify_win(*cur.NO,cur,deb);
				}
			break;

			case 4:
				if(cur.NE==&prev || cur.NE->coul!=cur.coul || cur.NE==NULL)
				{
					i++;
					tab[4]=1;
				}
				else if(tab[4]==1)
				{
					i++;
				}
				else if(bord_oppose(deb,cur))
				{
					b=true;
				}
				else
				{
					b=verify_win(*cur.NE,cur,deb);
				}
			break;

			default:
				if(cur.E==&prev || cur.E->coul!=cur.coul || cur.E==NULL)
				{
					i++;
					tab[5]=1;
				}
				else if(tab[5]==1)
				{
					i++;
				}
				else if(bord_oppose(deb,cur))
				{
					b=true;
				}
				else
				{
					b=verify_win(*cur.E,cur,deb);
				}
			break;
		}
	}

	if(i==6)
	/* Si la boucle s'est arrêté en ayant incrémenté i jusqu'à 6 alors elle n'a pas détecté de bord */
	{
		return false;
	}
	else
	{
		return true;
	}
}


Couleur changer_joueur(Couleur couleur_courante) 
{
	if (couleur_courante==bleu)
		return rouge;
	else
		return bleu;
}

int choix_coup(Plateau p,Coordonnees_tab c,Couleur couleur_courante)
{
	if(coup_valide(p,c))
	{
		p[c.abscisse][c.ordonnee].coul=couleur_courante;
		return 0;
	}
	else 
		return -1;
}

bool coup_valide(Plateau p,Coordonnees_tab c)
{
	return dans_plateau(c) && p[c.abscisse][c.ordonnee].coul==neutre;
}
