#include "regles.h"

bool premier_joueur(Joueur choix_premier)
{
	return choix_premier==joueur1;
}

Plateau nouvelle_partie()
{
	Plateau p;
	p=initialiser_plateau();
	creation_config();

	return p;
}

bool bord(Type_Case c)
/* On vérifie si la case est un bord */
{
	bool b=false;

	if(c.coul=bleu)
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

}

bool verify_win(Type_Case cur, Type_Case prev, Type_Case deb)
/* Vérification de la victoire d'un des deux joueurs */
{
	int i=0;

	while(!bord_oppose(deb,cur) && i!=6)
	/* On continue tant que tous les voisins n'ont pas été checkés et tant que le bord opposé n'a pas été trouvé */
	{
		switch (i)
		{
			case 0:
				else if(cur.SE==prev || cur.SE->coul!=cur.coul || cur.SE==NULL)
				{
					i++;
				}
				else
				{
					verify_win(cur.SE,cur);
				}
			break;

			case 1:
				if(cur.SO==prev || cur.SO->coul!=cur.coul || cur.SO==NULL)
				{
					i++;
				}
				else
				{
					verify_win(cur.SO,cur);
				}
			break;

			case 2:
				if(cur.O==prev || cur.O->coul!=cur.coul || cur.O==NULL)
				{
					i++;
				}
				else
				{
					verify_win(cur.O,cur);
				}
			break;

			case 3:
				if(cur.NO==prev || cur.NO->coul!=cur.coul || cur.NO==NULL)
				{
					i++;
				}
				else
				{
					verify_win(cur.NO,cur);
				}
			break;

			case 4:
				if(cur.NE==prev || cur.NE->coul!=cur.coul || cur.NE==NULL)
				{
					i++;
				}
				else
				{
					verify_win(cur.NE,cur);
				}
			break;

			default:
				if(cur.E==prev || cur.E->coul!=cur.coul || cur.E==NULL)
				{
					i++;
				}
				else
				{
					verify_win(cur.E,cur);
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

int main()
{

    return 0;
}

Joueur changer_joueur(Joueur joueur_courant) 
{
	if (joueur_courant==joueur1)
		return joueur2;
	else
		return joueur1;
}


Couleur couleur_joueur(Joueur j)
{
	if(j==joueur1)
		return rouge;
	else
		return bleu;
}



Plateau choix_coup(Plateau p,Coup c)
{
	if(coup_valide(p,c.coord))
		p[c.coord.abscisse][c.coord.ordonnee].coul=c.couleur;
	return p;
}

bool coup_valide(Plateau p,Coordonnees_tab c)
{
	return dans_plateau(c) && p[c.abscisse][c.ordonnee].coul==neutre;
}

