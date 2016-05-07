#include "IA.h"

Coordonnees_tab coup_IA1(Plateau p)
{	
	int x,y,d1,d2;
	int distance_min;
	bool trouve=false;
	//afin de s'assurer que la première itération génerera une distance min
	int(*distance_choisie)(Plateau,Type_Case,Type_Case*,bool verif2[LIGNE_MAX][COLONNE_MAX])=&distance_bord_sud;
	Type_Case case_courante;
	Type_Case case_proche=p[5][5];
	if(case_proche.coul!=neutre)case_proche=*case_proche.O;
	bool verif1[LIGNE_MAX][COLONNE_MAX];
	bool verif2[LIGNE_MAX][COLONNE_MAX];
	initialiser_verif(verif1);
	initialiser_verif(verif2);
	//si le plateau est de taille 11 par exemple la distance maximale qu'une case peut avoir à un bord est égal à 10
	for(x=0;x<LIGNE_MAX;x++)
	{
		for(y=0;y<COLONNE_MAX;y++)
		{
			distance_min=LIGNE_MAX+2;
			case_courante=p[x][y];
			if(case_courante.coul==rouge)
			{
				trouve=true;
				initialiser_verif(verif1);
				d1=distance_bord_nord(p,case_courante,case_courante.NO,verif1);
				initialiser_verif(verif2);
				d2=distance_bord_sud(p,case_courante,case_courante.SE,verif2);
				/*le troisième argument n'a aucun interêt ici, il n'est utile que dans le cas d'un appel récursif pour éviter de tourner en rond*/
				if(d1 < distance_min && d1!=0)
				{
					case_proche=case_courante;
					distance_choisie=&distance_bord_nord;
					distance_min=d1;
				}
				if(d2 < distance_min && d2!=0)
				{
					case_proche=case_courante;
					distance_choisie=distance_bord_sud;
					distance_min=d2;
				}
				/*Ainsi, on retient la distance la plus courte et on retient également la direction la plus courte avec la variable "distance_choisie"*/
			}
		}
	}
	/* case_proche contient la case la plus proche d'un bord parmi ses voisins neutres on regarde celui qui est
	le plus proche du bord concerné*/
	
	if(trouve)
	{
		if(distance_choisie==&distance_bord_nord)
			case_proche=*contourner(&case_proche,case_proche.NO);
		else
			case_proche=*contourner(&case_proche,case_proche.SE);
	}
	return case_proche.co;
}

void initialiser_verif(bool verif[LIGNE_MAX][COLONNE_MAX])
{
	int x,y;
	for(x=0;x<COLONNE_MAX;x++)
		for(y=0;y<LIGNE_MAX;y++)
			verif[x][y]=false;
}

bool impasse(Type_Case c,bool verif[LIGNE_MAX][COLONNE_MAX])
{
	bool NE,NO,O,E,SO,SE; //chaque booleen indique true si la case concernée est libre
	/* une case est dite libre si elle n'a pas déjà été vérifiée et si elle n'est pas de la couleur de l'adversaire */
	if(c.NE!=NULL)
		NE=(c.NE->coul!=bleu && !verif[c.co.abscisse+1][c.co.ordonnee-1]);
	else
		NE=true;
	if(c.NO!=NULL)
		NO=(c.NO->coul!=bleu && !verif[c.co.abscisse][c.co.ordonnee-1]);
	else
		NO=true;
	if(c.E!=NULL)
		E=(c.E->coul!=bleu && !verif[c.co.abscisse+1][c.co.ordonnee]);
	else
		E=true;
	if(c.O!=NULL)
		O=(c.O->coul!=bleu && !verif[c.co.abscisse-1][c.co.ordonnee]);
	else
		O=true;
	if(c.SE!=NULL)
		SE=(c.SE->coul!=bleu && !verif[c.co.abscisse][c.co.ordonnee+1]);
	else
		SE=true;
	if(c.SO!=NULL)
		SO=(c.SO->coul!=bleu && !verif[c.co.abscisse-1][c.co.ordonnee+1]);
	else
		SO=true;
	return (NE && NO && E && O && SE && SO);
}

int distance_bord_nord(Plateau p,Type_Case c,Type_Case* voisin,bool verif[LIGNE_MAX][COLONNE_MAX])
{
	int i;
	verif[c.co.abscisse][c.co.ordonnee]=true;
	int distance=0;
	bool verif_b[LIGNE_MAX][COLONNE_MAX];
	initialiser_verif(verif_b);
	Type_Case* poubelle=&c;
	reinitialise_case_checked(p);
	if(relie_bord_nord(&c,poubelle))
		return LIGNE_MAX+1;
	if(voisin==NULL)
		return 0;
	else
	{
		if(impasse(c,verif))
			return LIGNE_MAX+1;
		else
		{
			Type_Case* temp;
			i=0;
			do
			{
				temp=voisin_suivant(&c,voisin);
				i++;
				if(temp==NULL || temp->coul==bleu)
					distance=1+distance_bord_nord(p,*temp,temp->NO,verif);
			}
			while(i!=6);
		}
	}
	return distance;
}

int distance_bord_sud(Plateau p,Type_Case c,Type_Case* voisin,bool verif[LIGNE_MAX][COLONNE_MAX])
{
	int i;
	verif[c.co.abscisse][c.co.ordonnee]=true;
	int distance=0;
	bool verif_b[LIGNE_MAX][COLONNE_MAX];
	initialiser_verif(verif_b);
	Type_Case* poubelle=&c;
	reinitialise_case_checked(p);
	if(relie_bord_nord(&c,poubelle))
		return LIGNE_MAX+1;
	if(voisin==NULL)
		return 0;
	else
	{
		if(impasse(c,verif))
			return LIGNE_MAX+1;
		else
		{
			Type_Case* temp;
			i=0;
			do
			{
				temp=voisin_suivant(&c,voisin);
				i++;
				if(temp==NULL || temp->coul==bleu)
					distance=1+distance_bord_nord(p,*temp,temp->SE,verif);
			}
			while(i!=6);
		}
	}
	return distance;
}

Type_Case* voisin_NO(Type_Case c)
{
	return c.NO;
}

Type_Case* voisin_NE(Type_Case c)
{
	return c.NE;
}

Type_Case* voisin_O(Type_Case c)
{
	return c.O;
}

Type_Case* voisin_E(Type_Case c)
{
	return c.E;
}

Type_Case* voisin_SO(Type_Case c)
{
	return c.SO;
}

Type_Case* voisin_SE(Type_Case c)
{
	return c.SE;
}

bool impasse_bord(Type_Case c,bool verif[LIGNE_MAX][COLONNE_MAX])
{
	bool NE,NO,O,E,SO,SE; //chaque booleen indique true si la case concernée est libre
	/* une case est dite libre si elle n'a pas déjà été vérifiée et si elle n'est pas de la couleur de l'adversaire */
	if(c.NE!=NULL)
		NE=(c.NE->coul==rouge && !verif[c.co.abscisse+1][c.co.ordonnee-1]);
	else
		NE=true;
	if(c.NO!=NULL)
		NO=(c.NO->coul==rouge && !verif[c.co.abscisse][c.co.ordonnee-1]);
	else
		NO=true;
	if(c.E!=NULL)
		E=(c.E->coul==rouge && !verif[c.co.abscisse+1][c.co.ordonnee]);
	else
		E=true;
	if(c.O!=NULL)
		O=(c.O->coul==rouge && !verif[c.co.abscisse-1][c.co.ordonnee]);
	else
		O=true;
	if(c.SE!=NULL)
		SE=(c.SE->coul==rouge && !verif[c.co.abscisse][c.co.ordonnee+1]);
	else
		SE=true;
	if(c.SO!=NULL)
		SO=(c.SO->coul==rouge && !verif[c.co.abscisse-1][c.co.ordonnee+1]);
	else
		SO=true;
	return (NE && NO && E && O && SE && SO);
}

bool relie_bord_nord(Type_Case* cur, Type_Case* ret)
{
	int i=0;
	bool b=false;

	while(!b && i!=6)
	/* On continue tant que tous les voisins n'ont pas été checkés ou tant que le bord n'a pas été trouvé */
	{
		if(cur->NO==NULL)
		{
			b=true;
			*ret=*cur;
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

bool relie_bord_sud(Type_Case* cur, Type_Case* ret)
{
	int i=0;
	bool b=false;

	while(!b && i!=6)
	/* On continue tant que tous les voisins n'ont pas été checkés ou tant que le bord n'a pas été trouvé */
	{
		if(cur->SE==NULL)
		{
			b=true;
			*ret=*cur;
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

Type_Case* contourner(Type_Case* case_choisie,Type_Case* voisin)
{
	if(voisin!=NULL)
	{
		if(voisin->coul==rouge)
			return contourner(voisin,voisin->SE);
		if(voisin->coul==neutre)
				return voisin;
		if(voisin->coul==bleu)
				return contourner(voisin,voisin_suivant(case_choisie,voisin));
	}
	/*else
	{
		return
	}*/
	return case_choisie;
}

Type_Case* voisin_suivant(Type_Case* depart,Type_Case* voisin)
{
	if(voisin==depart->SO) 
		return depart->O;
	if(voisin==depart->O) 
		return depart->NO;
	if(voisin==depart->NO) 
		return depart->NE;
	if(voisin==depart->NE) 
		return depart->E;
	if(voisin==depart->E) 
		return depart->SE;
	if(voisin==depart->SE) 
		return depart->SO;
	return depart;
}