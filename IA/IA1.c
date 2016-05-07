#include "IA.h"

Coordonnees_tab coup_IA1(Plateau p)
{
	srand((unsigned int)time(NULL));
	int depart=rand()%11;
	int x,y,d;
	int distance_min,nb_appels;
	int min_courant=LIGNE_MAX+2;
	bool trouve=false;
	Type_Case* case_courante;
	Type_Case* case_proche=&p[depart][0];
	distance_min=COLONNE_MAX+2;
	if(case_proche->coul!=neutre)
		case_proche=case_proche->O;
	//si le plateau est de taille 11 par exemple la distance maximale qu'une case peut avoir à un bord est égal à 10
	for(y=0;y<LIGNE_MAX;y++)
	{
		for(x=0;x<COLONNE_MAX;x++)
		{
			case_courante=&p[x][y];
			if(case_courante->coul==rouge)
			{
				trouve=true;
				reinitialise_case_checked(p);
				nb_appels=0;
				d=distance_bord_sud(case_courante,&min_courant);
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

int distance_bord_sud(Type_Case* c,int* min)
{	
	int i=0;
	int distance=0;
	Type_Case* voisin=c->SE;
	c->check=true;
	if(c->SE!=NULL)
	{
		while(i!=6)
		{
			if(voisin!=NULL && voisin->coul!=bleu && !voisin->check)
			{
				distance=1+distance_bord_sud(voisin,min);
				if(distance < *min)
					*min=distance;
			}
			voisin=voisin_suivant(c,voisin);
		}
	}
	return distance;
}

Type_Case* contourner(Type_Case* case_choisie,Type_Case* voisin)
{
	Type_Case* temp=voisin;
	int compteur;
	int min=LIGNE_MAX+2;
	int i=0;
	while(i!=6 && (temp==NULL || temp->coul!=neutre || temp->check))
	{
		if(temp!=NULL)
			temp->check=true;
			if(temp->coul==neutre)
			{
				compteur=0;
				distance_bord_sud(temp,&min);
				if(compteur < min)
				{
					min=compteur;
					elue=temp;
				}
			}
		}
		switch(i)
		{
			case 0:
				temp=case_choisie->SE;
				break;
			case 1:
				temp=case_choisie->SO;
				break;
			case 2:
				temp=case_choisie->O;
				break;
			case 3:
				temp=case_choisie->E;
				break;
			case 4:
				temp=case_choisie->NO;
				break;
			case 5:
				temp=case_choisie->NE;
				break;
		}
		i++;
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