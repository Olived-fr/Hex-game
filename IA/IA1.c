#include "IA.h"

Coordonnees_tab coup_IA1(Plateau p)
{	
	int x,y,d1,d2;
	int distance_min=LIGNE_MAX+2;
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
	verif[c.co.abscisse][c.co.ordonnee]=true;
	int distance=0;
	bool verif_b[LIGNE_MAX][COLONNE_MAX];
	initialiser_verif(verif_b);
	if(relie_bord_nord(p,c,voisin,verif_b))return LIGNE_MAX+1;
	if(voisin==NULL)
		return 0;
	else
	{
		if(impasse(c,verif))return LIGNE_MAX+1;
		else
		{
			Type_Case* temp;
			do
				temp=voisin_suivant(&c,voisin);
			while(temp==NULL);
			distance=1+distance_bord_nord(p,*temp,temp->NO,verif);
		}
	}
	return distance;
}

int distance_bord_sud(Plateau p,Type_Case c,bool verif[LIGNE_MAX][COLONNE_MAX])
{
	verif[c.co.abscisse][c.co.ordonnee]=true;
	int distance=0;
	bool verif_b[LIGNE_MAX][COLONNE_MAX];
	initialiser_verif(verif_b);
	if(relie_bord_nord(p,c,voisin,verif_b))return LIGNE_MAX+1;
	if(voisin==NULL)
		return 0;
	else
	{
		if(impasse(c,verif))return LIGNE_MAX+1;
		else
		{
			Type_Case* temp;
			do
				temp=voisin_suivant(&c,voisin);
			while(temp==NULL);
			distance=1+distance_bord_nord(p,*temp,temp->SE,verif);
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

bool relie_bord_nord(Plateau p,Type_Case c,Type_Case* voisin,bool verif[LIGNE_MAX][COLONNE_MAX])
{
	verif[c.co.abscisse][c.co.ordonnee]=true;
	bool relie=true;
	if(voisin==NULL)
		return true;
	else
	{
		if(voisin->coul==rouge && !impasse_bord(*c.NO,verif))
			relie=relie_bord_nord(p,*voisin,voisin->NO,verif);
		else
		{
			Type_Case* temp;
			do
				temp=voisin_suivant(&c,c.NO);
			while(temp==NULL);
			relie=relie_bord_nord(p,*temp,temp->NO,verif);
		}
	}
	return relie;
}

bool relie_bord_sud(Plateau p,Type_Case c,Type_Case* voisin,bool verif[LIGNE_MAX][COLONNE_MAX])
{
	verif[c.co.abscisse][c.co.ordonnee]=true;
	bool relie=true;
	if(voisin==NULL)
		return true;
	else
	{
		if(voisin->coul==rouge && !impasse_bord(*c.SE,verif))
			relie=relie_bord_nord(p,*voisin,voisin->SE,verif);
		else
		{
			Type_Case* temp;
			do
				temp=voisin_suivant(&c,c.SE);
			while(temp==NULL);
			relie=relie_bord_nord(p,*temp,temp->SE,verif);
		}
	}
	return relie;
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