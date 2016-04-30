#include "regles.h"

void nouvelle_partie(Plateau p)
{
	initialiser_plateau(p);
	creation_config();
	board_save(p);
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

bool verify_bord(Type_Case cur, Type_Case prev, Type_Case *ret)
/* Vérification si en partant d'une case posée on peut atteindre un bord */
{
	int i=0;
	bool b=false;
	bool tab[6]={0,0,0,0,0,0};

	while(!b && i!=6)
	/* On continue tant que tous les voisins n'ont pas été checkés ou tant que le bord n'a pas été trouvé */
	{
		if(cur.coul==bleu)
		{
			if(bord_bleu(cur))
			{
				b=true;
				ret=&cur;
			}
		}
		else
		{
			if(bord_rouge(cur))
			{
				b=true;
				ret=&cur;
			}
		}

		switch (i)
		{
			case 0:
				if(tab[0]==1)
				{
					i++;
				} 
				else if(cur.SE==NULL || (cur.SE->co.abscisse==prev.co.abscisse && cur.SE->co.ordonnee==prev.co.ordonnee) || cur.SE->coul!=cur.coul)
				{
					i++;
					tab[0]=1;
				}
				else
				{
					tab[0]=1;
					b=verify_bord(*cur.SE,cur,ret);
				}
			break;

			case 1:
				if(tab[1]==1)
				{
					i++;
				}
				else if(cur.SO==NULL || (cur.SO->co.abscisse==prev.co.abscisse && cur.SO->co.ordonnee==prev.co.ordonnee) || cur.SO->coul!=cur.coul)
				{
					i++;
					tab[1]=1;
				}
				else
				{
					tab[1]=1;
					b=verify_bord(*cur.SO,cur,ret);
				}
			break;

			case 2:
				if(tab[2]==1)
				{
					i++;
				}
				else if(cur.O==NULL || (cur.O->co.abscisse==prev.co.abscisse && cur.O->co.ordonnee==prev.co.ordonnee) || cur.O->coul!=cur.coul)
				{
					i++;
					tab[2]=1;
				}
				else
				{
					tab[2]=1;
					b=verify_bord(*cur.O,cur,ret);
				}
			break;

			case 3:
				if(tab[3]==1)
				{
					i++;
				} 
				else if(cur.NO==NULL || (cur.NO->co.abscisse==prev.co.abscisse && cur.NO->co.ordonnee==prev.co.ordonnee) || cur.NO->coul!=cur.coul)
				{
					i++;
					tab[3]=1;
				}
				else
				{
					tab[3]=1;
					b=verify_bord(*cur.NO,cur,ret);
				}
			break;

			case 4:
				if(tab[4]==1)
				{
					i++;
				}
				else if(cur.NE==NULL || (cur.NE->co.abscisse==prev.co.abscisse && cur.NE->co.ordonnee==prev.co.ordonnee) || cur.NE->coul!=cur.coul)
				{
					i++;
					tab[4]=1;
				}
				else
				{
					tab[4]=1;
					b=verify_bord(*cur.NE,cur,ret);
				}
			break;

			default:
				if(tab[5]==1)
				{
					i++;
				}
				else if(cur.E==NULL || (cur.E->co.abscisse==prev.co.abscisse && cur.E->co.ordonnee==prev.co.ordonnee) || cur.E->coul!=cur.coul)
				{
					i++;
					tab[5]=1;
				}
				else
				{
					tab[5]=1;
					b=verify_bord(*cur.E,cur,ret);
				}
			break;
		}
	}

	return b;
}

bool verify_bord_oppose(Type_Case cur, Type_Case prev, Type_Case deb)
/* Vérification du bord opposé selon une case donnée */
{
	{
	int i=0;
	bool b=false;
	bool tab[6]={0,0,0,0,0,0};

	while(!b && i!=6)
	/* On continue tant que tous les voisins n'ont pas été checkés ou tant que le bord opposé n'a pas été trouvé */
	{
		if(deb.coul==bleu)
		{
			if(bord_oppose_bleu(deb,cur))
			{
				b=true;
			}
		}
		else
		{
			if(bord_oppose_rouge(deb,cur))
			{
				b=true;
			}
		}

		switch (i)
		{
			case 0:
				if(tab[0]==1)
				{
					i++;
				} 
				else if(cur.SE==NULL || (cur.SE->co.abscisse==prev.co.abscisse && cur.SE->co.ordonnee==prev.co.ordonnee) || cur.SE->coul!=cur.coul)
				{
					i++;
					tab[0]=1;
				}
				else
				{
					tab[0]=1;
					b=verify_bord_oppose(*cur.SE,cur,deb);
				}
			break;

			case 1:
				if(tab[1]==1)
				{
					i++;
				}
				else if(cur.SO==NULL || (cur.SO->co.abscisse==prev.co.abscisse && cur.SO->co.ordonnee==prev.co.ordonnee) || cur.SO->coul!=cur.coul)
				{
					i++;
					tab[1]=1;
				}
				else
				{
					tab[1]=1;
					b=verify_bord_oppose(*cur.SO,cur,deb);
				}
			break;

			case 2:
				if(tab[2]==1)
				{
					i++;
				}
				else if(cur.O==NULL || (cur.O->co.abscisse==prev.co.abscisse && cur.O->co.ordonnee==prev.co.ordonnee) || cur.O->coul!=cur.coul)
				{
					i++;
					tab[2]=1;
				}
				else
				{
					tab[2]=1;
					b=verify_bord_oppose(*cur.O,cur,deb);
				}
			break;

			case 3:
				if(tab[3]==1)
				{
					i++;
				} 
				else if(cur.NO==NULL || (cur.NO->co.abscisse==prev.co.abscisse && cur.NO->co.ordonnee==prev.co.ordonnee) || cur.NO->coul!=cur.coul)
				{
					i++;
					tab[3]=1;
				}
				else
				{
					tab[3]=1;
					b=verify_bord_oppose(*cur.NO,cur,deb);
				}
			break;

			case 4:
				if(tab[4]==1)
				{
					i++;
				}
				else if(cur.NE==NULL || (cur.NE->co.abscisse==prev.co.abscisse && cur.NE->co.ordonnee==prev.co.ordonnee) || cur.NE->coul!=cur.coul)
				{
					i++;
					tab[4]=1;
				}
				else
				{
					tab[4]=1;
					b=verify_bord_oppose(*cur.NE,cur,deb);
				}
			break;

			default:
				if(tab[5]==1)
				{
					i++;
				}
				else if(cur.E==NULL || (cur.E->co.abscisse==prev.co.abscisse && cur.E->co.ordonnee==prev.co.ordonnee) || cur.E->coul!=cur.coul)
				{
					i++;
					tab[5]=1;
				}
				else
				{
					tab[5]=1;
					b=verify_bord_oppose(*cur.E,cur,deb);
				}
			break;
		}
	}

	return b;
}
}

bool verify_win(Type_Case cur, Type_Case prev)
{
	Type_Case ret;

	if(verify_bord(cur,prev,&ret))
	{
		if(verify_bord_oppose(cur,prev,ret))
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
