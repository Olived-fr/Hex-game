#include "IA.h"

Coordonnees_tab coup_IA1(Plateau p)
{
	int x,y,d;
	int distance_min;
	int dis;
	bool trouve=false;
	Type_Case* case_courante;
	Type_Case* case_proche=&p[5][0];
	if(case_proche->coul!=neutre)case_proche=case_proche->O;
	//si le plateau est de taille 11 par exemple la distance maximale qu'une case peut avoir à un bord est égal à 10
	for(x=0;x<LIGNE_MAX;x++)
	{
		for(y=0;y<COLONNE_MAX;y++)
		{
			distance_min=COLONNE_MAX+2;
			case_courante=&p[x][y];
			if(case_courante->coul==rouge)
			{
				trouve=true;
				reinitialise_case_checked(p);
				dis=0;
				d=distance_bord_sud(p,case_courante,case_courante->SE,&dis);
				if(d <= distance_min && d!=0)
				{
					case_proche=case_courante;
					distance_min=d;
				}
				/*Ainsi, on retient la distance la plus courte et on retient également la direction la plus courte avec la variable "distance_choisie"*/
			}
		}
	}
	/* case_proche contient la case la plus proche d'un bord parmi ses voisins neutres on regarde celui qui est
	le plus proche du bord concerné*/
	if(trouve)
	{
		reinitialise_case_checked(p);
		case_proche=contourner(case_proche,case_proche->SE);
	}
	return case_proche->co;
}

int distance_bord_sud(Plateau p,Type_Case* c,Type_Case* voisin,int* d)
{
	d++;
	int i;
	int min_interne=LIGNE_MAX+2;
	c->check=true;
	if(voisin==NULL)
		return 0;
	else
	{
		Type_Case* nouveau_voisin=voisin;
		int i=0;
		while(i!=6)
		{
			if(nouveau_voisin!=NULL && !nouveau_voisin->check && nouveau_voisin->coul==neutre)
			{
				distance_bord_sud(p,nouveau_voisin,nouveau_voisin->SE,d);
				if(nouveau_voisin->coul==neutre && d < min_interne)
					min_interne=d;
			}
			i++;
			nouveau_voisin=voisin_suivant(c,nouveau_voisin);
		}
		return d;
	}
}

Type_Case* contourner(Type_Case* case_choisie,Type_Case* voisin)
{
	Type_Case* temp=voisin;
	int i=0;
	while(i!=6 && (temp==NULL || temp->coul!=neutre || temp->check))
	{
		if(temp!=NULL)
			temp->check=true;
		i++;
		temp=voisin_suivant(case_choisie,temp);
	}
	return temp;
}

Type_Case* voisin_suivant(Type_Case* depart,Type_Case* voisin)
{
	if(voisin==depart->SE) 
		return depart->SO;
	if(voisin==depart->SO) 
		return depart->O;
	if(voisin==depart->O) 
		return depart->E;
	if(voisin==depart->E) 
		return depart->NO;
	if(voisin==depart->NO) 
		return depart->NE;
	if(voisin==depart->NE) 
		return depart->NO;
	return depart;
}