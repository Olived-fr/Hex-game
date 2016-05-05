#include "regles.h"

void nouvelle_partie(Plateau p)
{
	initialiser_plateau(p);
	reinitialise_case_checked(p);
	creation_config();
	board_save(p);
}

void reinitialise_case_checked(Plateau p)
{
	int i,j;

	for(i=0; i<11; i++)
	{
		for(j=0; j<11; j++)
		{
            p[i][j].check=0;
		}
	}
}

bool bord_bleu(Type_Case c)
/* Si la case est bleue, si c'est un bord ses voisins OUEST et SUD-OUEST OU ses voisins NORD-EST et EST seront égal à NULL */
{
	return (c.O==NULL && c.SO==NULL) || (c.NE==NULL && c.E==NULL);
}

bool bord_rouge(Type_Case c)
/* Si la case est rouge, si c'est un bord ses voisins NORD-OUEST et NORD-EST OU ses voisins SUD-OUEST et SUD-EST seront égal à NULL */
{
	return (c.NO==NULL && c.NE==NULL) || (c.SO==NULL && c.SE==NULL);
}

bool bord_oppose_bleu(Type_Case deb, Type_Case comp)
/* Retourne vrai si la case comp est un bord opposé à la case deb */
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

	return false;
}

bool bord_oppose_rouge(Type_Case deb, Type_Case comp)
/* Retourne vrai si la case comp est un bord opposé à la case deb */
{
	if(deb.NO==NULL && deb.NE==NULL)
	/* Compare case bord haut à case bord bas */
	{
		return (comp.SO==NULL && comp.SE==NULL);
	}
	else if(deb.SO==NULL && deb.SE==NULL)
	/* Compare case bord bas à case bord haut */
	{
		return (comp.NO==NULL && comp.NE==NULL);
	}

	return false;
}

bool verify_bord(Type_Case *cur, Type_Case *ret)
/* Vérification si en partant d'une case posée on peut atteindre un bord */
{
	int i=0;
	bool b=false;

	while(!b && i!=6)
	/* On continue tant que tous les voisins n'ont pas été checkés ou tant que le bord n'a pas été trouvé */
	{
		if(cur->coul==bleu)
		{
			if(bord_bleu(*cur))
			{
				b=true;
				*ret=*cur;
			}
		}
		else
		{
			if(bord_rouge(*cur))
			{
				b=true;
				*ret=*cur;
			}
		}
		switch (i)
		{
			case 0:
				if(cur->SE==NULL || cur->SE->check==1 || cur->SE->coul!=cur->coul)
				{
					i++;
					if(cur->SE!=NULL)
						cur->SE->check=1;
				}
				else
				{
					cur->SE->check=1;
					b=verify_bord(cur->SE,ret);
				}
			break;

			case 1:
				if(cur->SO==NULL || cur->SO->check==1 || cur->SO->coul!=cur->coul)
				{
					i++;
					if(cur->SO!=NULL)
						cur->SO->check=1;
				}
				else
				{
					cur->SO->check=1;
					b=verify_bord(cur->SO,ret);
				}
			break;

			case 2:
				if(cur->O==NULL || cur->O->check==1 || cur->O->coul!=cur->coul)
				{
					i++;
					if(cur->O!=NULL)
						cur->O->check=1;
				}
				else
				{
					cur->O->check=1;
					b=verify_bord(cur->O,ret);
				}
			break;

			case 3:
				if(cur->NO==NULL || cur->NO->check==1 || cur->NO->coul!=cur->coul)
				{
					i++;
					if(cur->NO!=NULL)
						cur->NO->check=1;
				}
				else
				{
					cur->NO->check=1;
					b=verify_bord(cur->NO,ret);
				}
			break;

			case 4:
				if(cur->NE==NULL || cur->NE->check==1 || cur->NE->coul!=cur->coul)
				{
					i++;
					if(cur->NE!=NULL)
						cur->NE->check=1;
				}
				else
				{
					cur->NE->check=1;
					b=verify_bord(cur->NE,ret);
				}
			break;

			default:
				if(cur->E==NULL || cur->E->check==1 || cur->E->coul!=cur->coul)
				{
					i++;
					if(cur->E!=NULL)
						cur->E->check=1;
				}
				else
				{
					cur->E->check=1;
					b=verify_bord(cur->E,ret);
				}
			break;
		}
	}

	return b;
}

bool verify_bord_oppose(Type_Case *cur, Type_Case deb)
/* Vérification du bord opposé selon une case donnée */
{
	int i=0;
	bool b=false;

	while(!b && i!=6)
	/* On continue tant que tous les voisins n'ont pas été checkés ou tant que le bord opposé n'a pas été trouvé */
	{
		if(deb.coul==bleu)
		{
			if(bord_oppose_bleu(deb,*cur))
			{
				b=true;
			}
		}
		else
		{
			if(bord_oppose_rouge(deb,*cur))
			{
				b=true;
			}
		}

		switch (i)
		{
			case 0:
				if(cur->SE==NULL || cur->SE->check==1 || cur->SE->coul!=cur->coul)
				{
					i++;
					if(cur->SE!=NULL)
						cur->SE->check=1;
				}
				else
				{
					cur->SE->check=1;
					b=verify_bord_oppose(cur->SE,deb);
				}
			break;

			case 1:
				if(cur->SO==NULL || cur->SO->check==1 || cur->SO->coul!=cur->coul)
				{
					i++;
					if(cur->SO!=NULL)
						cur->SO->check=1;
				}
				else
				{
					cur->SO->check=1;
					b=verify_bord_oppose(cur->SO,deb);
				}
			break;

			case 2:
				if(cur->O==NULL || cur->O->check==1 || cur->O->coul!=cur->coul)
				{
					i++;
					if(cur->O!=NULL)
						cur->O->check=1;
				}
				else
				{
					cur->O->check=1;
					b=verify_bord_oppose(cur->O,deb);
				}
			break;

			case 3:
				if(cur->NO==NULL || cur->NO->check==1 || cur->NO->coul!=cur->coul)
				{
					i++;
					if(cur->NO!=NULL)
						cur->NO->check=1;
				}
				else
				{
					cur->NO->check=1;
					b=verify_bord_oppose(cur->NO,deb);
				}
			break;

			case 4:
				if(cur->NE==NULL || cur->NE->check==1 || cur->NE->coul!=cur->coul)
				{
					i++;
					if(cur->NE!=NULL)
						cur->NE->check=1;
				}
				else
				{
					cur->NE->check=1;
					b=verify_bord_oppose(cur->NE,deb);
				}
			break;

			default:
				if(cur->E==NULL || cur->E->check==1 || cur->E->coul!=cur->coul)
				{
					i++;
					if(cur->E!=NULL)
						cur->E->check=1;
				}
				else
				{
					cur->E->check=1;
					b=verify_bord_oppose(cur->E,deb);
				}
			break;
		}
	}

	return b;
}

bool verify_win(Type_Case cur, Plateau p)
{
	Type_Case ret;

	if(verify_bord(&cur,&ret))
	{
		reinitialise_case_checked(p);

		if(verify_bord_oppose(&cur,ret))
		{
			return true;
        }
	}
    
    return false;
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
