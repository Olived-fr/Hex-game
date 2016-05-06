#include "IA.h"

Coordonnees_tab coup_IA1(Plateau p, Couleur couleur_courante)
{	
	int x,y,d1,d2;
	int distance_min=LIGNE_MAX+1;
	//afin de s'assurer que la première itération génerera une distance min
	int(*distance_extremite1)(Plateau,Type_Case,bool verif1[LIGNE_MAX][COLONNE_MAX],Couleur);
	int(*distance_extremite2)(Plateau,Type_Case,bool verif2[LIGNE_MAX][COLONNE_MAX],Couleur);
	int(*distance_choisie)(Plateau,Type_Case,bool verif2[LIGNE_MAX][COLONNE_MAX],Couleur)=&distance_bord_ouest;
	Type_Case*(*voisin_elu)(Type_Case)=&voisin_NO;
	Type_Case* case_choisie=&p[5][5];
	if(case_choisie->coul==changer_joueur(couleur_courante))case_choisie=case_choisie->O;
	Type_Case case_courante;
	Type_Case case_proche=p[5][5];
	bool verif1[LIGNE_MAX][COLONNE_MAX];
	bool verif2[LIGNE_MAX][COLONNE_MAX];
	initialiser_verif(verif1);
	initialiser_verif(verif2);
	if(couleur_courante==bleu)
	{
		distance_extremite1=&distance_bord_ouest;
		distance_extremite2=&distance_bord_est;
	}
	else
	{
		distance_extremite1=&distance_bord_nord;
		distance_extremite2=&distance_bord_sud;
	}
	//si le plateau est de taille 11 par exemple la distance maximale qu'une case peut avoir à un bord est égal à 10
	bool horizontal=(couleur_courante==bleu);
	if(horizontal)
		distance_min=LIGNE_MAX-1;
	else
		distance_min=COLONNE_MAX-2;
	//Note : cette instruction conditionnelle est facultative car on admet que LIGNE_MAX est toujours égal à COLONNE_MAX
	for(x=0;x<LIGNE_MAX;x++)
	{
		for(y=0;y<COLONNE_MAX;y++)
		{
			case_courante=p[x][y];
			if(case_courante.coul==couleur_courante)
			{
				initialiser_verif(verif1);
				d1=distance_extremite1(p,case_courante,verif1,couleur_courante);
				initialiser_verif(verif2);
				d2=distance_extremite2(p,case_courante,verif2,couleur_courante);
				/*le troisième argument n'a aucun interêt ici, il n'est utile que dans le cas d'un appel récursif pour éviter de tourner en rond*/
				if(d1 < distance_min && d1!=0)
				{
					case_proche=case_courante;
					initialiser_verif(verif1);
					distance_choisie=distance_extremite1;
					distance_min=d1;
				}
				if(d2 < distance_min && d2!=0)
				{
					case_proche=case_courante;
					initialiser_verif(verif2);
					distance_choisie=distance_extremite2;
					distance_min=d2;
				}
				/*Ainsi, on retient la distance la plus courte et on retient également la direction la plus courte avec la variable "distance_choisie"*/
			}
		}
	}
	/* case_proche contient la case la plus proche d'un bord parmi ses voisins neutres on regarde celui qui est
	le plus proche du bord concerné*/
	
	int distance_courante;
	initialiser_verif(verif1);
	if(case_proche.NO!=NULL && case_proche.NO->coul==neutre)
	{
		distance_courante=distance_choisie(p,*case_proche.NO,verif1,couleur_courante);
		if(distance_courante < distance_min && case_proche.NO->coul==neutre)
		{
			distance_min=distance_courante;
			voisin_elu=&voisin_NO;
		}
	}
	initialiser_verif(verif1);
	if(case_proche.NE!=NULL && case_proche.NE->coul==neutre)
	{
		distance_courante=distance_choisie(p,*case_proche.NE,verif1,couleur_courante);
		if(distance_courante < distance_min && case_proche.NE->coul==neutre)
		{
			distance_min=distance_courante;
			voisin_elu=&voisin_NE;
		}
	}
	initialiser_verif(verif1);
	if(case_proche.O!=NULL && case_proche.O->coul==neutre)
	{
		distance_courante=distance_choisie(p,*case_proche.O,verif1,couleur_courante);
		if(distance_courante < distance_min && case_proche.O->coul==neutre)
		{
			distance_min=distance_courante;
			voisin_elu=&voisin_O;
		}
	}
	initialiser_verif(verif1);
	if(case_proche.SO!=NULL && case_proche.SO->coul==neutre)
	{
		distance_courante=distance_choisie(p,*case_proche.SO,verif1,couleur_courante);
		if(distance_courante < distance_min && case_proche.SO->coul==neutre)
		{
			distance_min=distance_courante;
			voisin_elu=&voisin_SO;
		}
	}
	initialiser_verif(verif1);
	if(case_proche.SE!=NULL && case_proche.SE->coul==neutre)
	{
		distance_courante=distance_choisie(p,*case_proche.SE,verif1,couleur_courante);
		if(distance_courante < distance_min && case_proche.SE->coul==neutre)
		{
			distance_min=distance_courante;
			voisin_elu=&voisin_SE;
		}
	}
	initialiser_verif(verif1);
	if(case_proche.E!=NULL && case_proche.E->coul==neutre)
	{
		distance_courante=distance_choisie(p,*case_proche.E,verif1,couleur_courante);
		if(distance_courante < distance_min && case_proche.E->coul==neutre)
		{
			distance_min=distance_courante;
			voisin_elu=&voisin_E;
		}
	}
	initialiser_verif(verif1);
	case_choisie=voisin_elu(case_proche); 
	/*et on pose le pion à cet endroit là*/
	Type_Case* temp=case_choisie;
	
	if(!horizontal)
	{
		case_choisie=temp->SE;
		while(case_choisie!=NULL && case_choisie->coul!=neutre)
			case_choisie=case_choisie->SE;
		if(case_choisie==NULL)
		{
			case_choisie=temp;
			while(case_choisie!=NULL && case_choisie->coul!=neutre)
				case_choisie=case_choisie->NO;
		}
		if(case_choisie==NULL)
		{
			case_choisie=temp;
			while(case_choisie!=NULL && case_choisie->coul!=neutre)
				case_choisie=case_choisie->SO;
		}
		if(case_choisie==NULL)
		{
			case_choisie=temp;
			while(case_choisie!=NULL && case_choisie->coul!=neutre)
				case_choisie=case_choisie->NE;
		}
		if(case_choisie==NULL)
		{
			case_choisie=temp;
			while(case_choisie!=NULL && case_choisie->coul!=neutre)
				case_choisie=case_choisie->O;
		}
		if(case_choisie==NULL)
		{
			case_choisie=temp;
			while(case_choisie!=NULL && case_choisie->coul!=neutre)
				case_choisie=case_choisie->E;
		}
	}
	else
	{
		while(case_choisie->coul!=neutre && case_choisie!=NULL)
		{	
			case_choisie=case_choisie->O;
			if(case_choisie==NULL)
				break;
		}
		if(case_choisie==NULL)
		{
			temp=case_choisie;
			while(case_choisie->coul!=neutre && case_choisie!=NULL)
			{	
				case_choisie=case_choisie->E;
				if(case_choisie==NULL)
					break;
			}
		}
		if(case_choisie==NULL)
		{
			case_choisie=temp;
			while(case_choisie->coul!=neutre && case_choisie!=NULL)
			{	
				case_choisie=case_choisie->NO;
				if(case_choisie==NULL)
					break;
			}
		}
		if(case_choisie==NULL)
		{
			case_choisie=temp;
			while(case_choisie->coul!=neutre && case_choisie!=NULL)
			{	
				case_choisie=case_choisie->NE;
				if(case_choisie==NULL)
					break;
			}
		}
		if(case_choisie==NULL)
		{
			case_choisie=temp;
			while(case_choisie->coul!=neutre && case_choisie!=NULL)
			{	
				case_choisie=case_choisie->SO;
				if(case_choisie==NULL)
					break;
			}
		}
		if(case_choisie==NULL)
		{
			case_choisie=temp;
			while(case_choisie->coul!=neutre && case_choisie!=NULL)
			{	
				case_choisie=case_choisie->SE;
				if(case_choisie==NULL)
					break;
			}
		}
	}
	return case_choisie->co;
}

void initialiser_verif(bool verif[LIGNE_MAX][COLONNE_MAX])
{
	int x,y;
	for(x=0;x<COLONNE_MAX;x++)
		for(y=0;y<LIGNE_MAX;y++)
			verif[x][y]=false;
}

bool impasse(Type_Case c,Couleur cou,bool verif[LIGNE_MAX][COLONNE_MAX])
{
	bool NE,NO,O,E,SO,SE; //chaque booleen indique true si la case concernée est libre
	/* une case est dite libre si elle n'a pas déjà été vérifiée et si elle n'est pas de la couleur de l'adversaire */
	if(c.NE!=NULL)
		NE=(c.NE->coul!=changer_joueur(cou) && !verif[c.co.abscisse+1][c.co.ordonnee-1]);
	else
		NE=true;
	if(c.NO!=NULL)
		NO=(c.NO->coul!=changer_joueur(cou) && !verif[c.co.abscisse-1][c.co.ordonnee-1]);
	else
		NO=true;
	if(c.E!=NULL)
		E=(c.E->coul!=changer_joueur(cou) && !verif[c.co.abscisse+1][c.co.ordonnee]);
	else
		E=true;
	if(c.O!=NULL)
		O=(c.O->coul!=changer_joueur(cou) && !verif[c.co.abscisse-1][c.co.ordonnee]);
	else
		O=true;
	if(c.SE!=NULL)
		SE=(c.SE->coul!=changer_joueur(cou) && !verif[c.co.abscisse+1][c.co.ordonnee+1]);
	else
		SE=true;
	if(c.SO!=NULL)
		SO=(c.SO->coul!=changer_joueur(cou) && !verif[c.co.abscisse-1][c.co.ordonnee+1]);
	else
		SO=true;
	return (NE && NO && E && O && SE && SO);
}

int distance_bord_ouest(Plateau p,Type_Case c,bool verif[LIGNE_MAX][COLONNE_MAX],Couleur cou)
{
	verif[c.co.abscisse][c.co.ordonnee]=true;
	int distance=0;
	bool verif_b[LIGNE_MAX][COLONNE_MAX]
	initialiser_verif(verif_b);
	if(impasse_bord(c,cou,verif_b)return LIGNE_MAX+1;
	if(c.O==NULL)
		return 0;
	else
	{
		if(impasse(c,cou,verif))return LIGNE_MAX+1;
		else
		{
			if(c.O->coul!=changer_joueur(cou) && !verif[c.co.abscisse-1][c.co.ordonnee])
				distance=1+distance_bord_ouest(p,*(c.O),verif,cou);
			else
			{
				if(c.NO!=NULL && c.NO->coul!=changer_joueur(cou) && !verif[c.co.abscisse][c.co.ordonnee-1])
					distance=1+distance_bord_ouest(p,*(c.NO),verif,cou);
				else 
				{
					if(c.NE!=NULL && c.NE->coul!=changer_joueur(cou) && !verif[c.co.abscisse+1][c.co.ordonnee-1])
						distance=1+distance_bord_ouest(p,*(c.NE),verif,cou);
					else
					{
						if(c.E!=NULL && c.E->coul!=changer_joueur(cou) && !verif[c.co.abscisse+1][c.co.ordonnee])
							distance=1+distance_bord_ouest(p,*(c.E),verif,cou);
						else
						{
							if(c.SE!=NULL && c.SE->coul!=changer_joueur(cou) && !verif[c.co.abscisse][c.co.ordonnee+1])
								distance=1+distance_bord_ouest(p,*(c.SE),verif,cou);
							else
							{
								if(c.SO!=NULL && c.SO->coul!=changer_joueur(cou) && !verif[c.co.abscisse-1][c.co.ordonnee+1])
									distance=1+distance_bord_ouest(p,*(c.SO),verif,cou);
							}
						}
					}
				}
			}
		}
	}
	return distance;
}	

int distance_bord_est(Plateau p,Type_Case c,bool verif[LIGNE_MAX][COLONNE_MAX],Couleur cou)
{
	verif[c.co.abscisse][c.co.ordonnee]=true;
	int distance=0;
	bool verif_b[LIGNE_MAX][COLONNE_MAX]
	initialiser_verif(verif_b);
	if(impasse_bord(c,cou,verif_b)return LIGNE_MAX+1;
	if(c.E==NULL)
		return 0;
	else
	{
		if(impasse(c,cou,verif))return LIGNE_MAX+1;
		else
		{
			if(c.E->coul!=changer_joueur(cou) && !verif[c.co.abscisse+1][c.co.ordonnee])
				distance=1+distance_bord_est(p,*(c.E),verif,cou);
			else
			{
				if(c.SE!=NULL && c.SE->coul!=changer_joueur(cou) && !verif[c.co.abscisse][c.co.ordonnee+1])
					distance=1+distance_bord_est(p,*(c.SE),verif,cou);
				else 
				{
					if(c.SO!=NULL && c.SO->coul!=changer_joueur(cou) && !verif[c.co.abscisse-1][c.co.ordonnee+1])
						distance=1+distance_bord_est(p,*(c.SO),verif,cou);
					else
					{
						if(c.O!=NULL && c.O->coul!=changer_joueur(cou) && !verif[c.co.abscisse-1][c.co.ordonnee])
							distance=1+distance_bord_est(p,*(c.O),verif,cou);
						else
						{
							if(c.NO!=NULL && c.NO->coul!=changer_joueur(cou) && !verif[c.co.abscisse][c.co.ordonnee-1])
								distance=1+distance_bord_est(p,*(c.NO),verif,cou);
							else
							{
								if(c.NE!=NULL && c.NE->coul!=changer_joueur(cou) && !verif[c.co.abscisse+1][c.co.ordonnee-1])
									distance=1+distance_bord_est(p,*(c.NE),verif,cou);
							}
						}
					}
				}
			}
		}
	}
	return distance;
}	

int distance_bord_nord(Plateau p,Type_Case c,bool verif[LIGNE_MAX][COLONNE_MAX],Couleur cou)
{
	verif[c.co.abscisse][c.co.ordonnee]=true;
	int distance=0;
	bool verif_b[LIGNE_MAX][COLONNE_MAX]
	initialiser_verif(verif_b);
	if(impasse_bord(c,cou,verif_b)return LIGNE_MAX+1;
	if(c.NO==NULL)
		return 0;
	else
	{
		if(impasse(c,cou,verif))return LIGNE_MAX+1;
		else
		{
			if(c.NO->coul!=changer_joueur(cou) && !verif[c.co.abscisse][c.co.ordonnee-1])
				distance=1+distance_bord_nord(p,*(c.NO),verif,cou);
			else
			{
				if(c.NE!=NULL && c.NE->coul!=changer_joueur(cou) && !verif[c.co.abscisse+1][c.co.ordonnee-1])
					distance=1+distance_bord_nord(p,*(c.NE),verif,cou);
				else 
				{
					if(c.E!=NULL && c.E->coul!=changer_joueur(cou) && !verif[c.co.abscisse+1][c.co.ordonnee])
						distance=1+distance_bord_nord(p,*(c.E),verif,cou);
					else
					{
						if(c.SE!=NULL && c.SE->coul!=changer_joueur(cou) && !verif[c.co.abscisse][c.co.ordonnee+1])
							distance=1+distance_bord_nord(p,*(c.SE),verif,cou);
						else
						{
							if(c.SO!=NULL && c.SO->coul!=changer_joueur(cou) && !verif[c.co.abscisse-1][c.co.ordonnee+1])
								distance=1+distance_bord_nord(p,*(c.SO),verif,cou);
							else
							{
								if(c.O!=NULL && c.O->coul!=changer_joueur(cou) && !verif[c.co.abscisse-1][c.co.ordonnee])
									distance=1+distance_bord_nord(p,*(c.O),verif,cou);
							}
						}
					}
				}
			}
		}
	}
	return distance;
}

int distance_bord_sud(Plateau p,Type_Case c,bool verif[LIGNE_MAX][COLONNE_MAX],Couleur cou)
{
	verif[c.co.abscisse][c.co.ordonnee]=true;
	int distance=0;
	bool verif_b[LIGNE_MAX][COLONNE_MAX]
	initialiser_verif(verif_b);
	if(impasse_bord(c,cou,verif_b)return LIGNE_MAX+1;
	if(c.SE==NULL)
		return 0;
	else
	{
		if(impasse(c,cou,verif))return LIGNE_MAX+1;
		else
		{
			if(c.SE->coul!=changer_joueur(cou) && !verif[c.co.abscisse][c.co.ordonnee+1])
				distance=1+distance_bord_sud(p,*(c.SE),verif,cou);
			else
			{
				if(c.SO!=NULL && c.SO->coul!=changer_joueur(cou) && !verif[c.co.abscisse-1][c.co.ordonnee+1])
					distance=1+distance_bord_sud(p,*(c.SO),verif,cou);
				else 
				{
					if(c.O!=NULL && c.O->coul!=changer_joueur(cou) && !verif[c.co.abscisse-1][c.co.ordonnee])
						distance=1+distance_bord_sud(p,*(c.O),verif,cou);
					else
					{
						if(c.NO!=NULL && c.NO->coul!=changer_joueur(cou) && !verif[c.co.abscisse][c.co.ordonnee-1])
							distance=1+distance_bord_sud(p,*(c.NO),verif,cou);
						else
						{
							if(c.NE!=NULL && c.NE->coul!=changer_joueur(cou) && !verif[c.co.abscisse+1][c.co.ordonnee-1])
								distance=1+distance_bord_sud(p,*(c.NE),verif,cou);
							else
							{
								if(c.E!=NULL && c.E->coul!=changer_joueur(cou) && !verif[c.co.abscisse+1][c.co.ordonnee-1])
									distance=1+distance_bord_sud(p,*(c.E),verif,cou);
							}
						}
					}
				}
			}
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

bool impasse_bord(Type_Case c,Couleur cou,bool verif[LIGNE_MAX][COLONNE_MAX])
{
	bool NE,NO,O,E,SO,SE; //chaque booleen indique true si la case concernée est libre
	/* une case est dite libre si elle n'a pas déjà été vérifiée et si elle n'est pas de la couleur de l'adversaire */
	if(c.NE!=NULL)
		NE=(c.NE->coul==cou && !verif[c.co.abscisse+1][c.co.ordonnee-1]);
	else
		NE=true;
	if(c.NO!=NULL)
		NO=(c.NO->coul==cou && !verif[c.co.abscisse-1][c.co.ordonnee-1]);
	else
		NO=true;
	if(c.E!=NULL)
		E=(c.E->coul==cou) && !verif[c.co.abscisse+1][c.co.ordonnee]);
	else
		E=true;
	if(c.O!=NULL)
		O=(c.O->coul==cou && !verif[c.co.abscisse-1][c.co.ordonnee]);
	else
		O=true;
	if(c.SE!=NULL)
		SE=(c.SE->coul==cou && !verif[c.co.abscisse+1][c.co.ordonnee+1]);
	else
		SE=true;
	if(c.SO!=NULL)
		SO=(c.SO->coul==cou && !verif[c.co.abscisse-1][c.co.ordonnee+1]);
	else
		SO=true;
	return (NE && NO && E && O && SE && SO);
}

bool relie_bord_ouest(Plateau p,Type_Case c,bool verif[LIGNE_MAX][COLONNE_MAX],Couleur cou)
{
	verif[c.co.abscisse][c.co.ordonnee]=true;
	bool relie=true;
	if(c.O==NULL)
		return relie;
	else
	{
		if(c.O->coul!=changer_joueur(cou) && !verif[c.co.abscisse-1][c.co.ordonnee] && !impasse_bord(*c.O,cou,verif))
			relie=relie_bord_ouest(p,*(c.O),verif,cou);
		else
		{
			if(c.NO!=NULL && c.NO->coul!=changer_joueur(cou) && !verif[c.co.abscisse][c.co.ordonnee-1] && !impasse_bord(*c.NO,cou,verif))
				relie=relie_bord_ouest(p,*(c.NO),verif,cou);
			else 
			{
				if(c.NE!=NULL && c.NE->coul!=changer_joueur(cou) && !verif[c.co.abscisse+1][c.co.ordonnee-1] && !impasse_bord(*c.NE,cou,verif))
					relie=relie_bord_ouest(p,*(c.NE),verif,cou);
				else
				{
					if(c.E!=NULL && c.E->coul!=changer_joueur(cou) && !verif[c.co.abscisse+1][c.co.ordonnee] && !impasse_bord(*c.E,cou,verif))
						relie=relie_bord_ouest(p,*(c.E),verif,cou);
					else
					{
						if(c.SE!=NULL && c.SE->coul!=changer_joueur(cou) && !verif[c.co.abscisse][c.co.ordonnee+1] && !impasse_bord(*c.SE,cou,verif))
							relie=relie_bord_ouest(p,*(c.SE),verif,cou);
						else
						{
							if(c.SO!=NULL && c.SO->coul!=changer_joueur(cou) && !verif[c.co.abscisse-1][c.co.ordonnee+1] && !impasse_bord(*c.SO,cou,verif)))
								relie=relie_bord_ouest(p,*(c.SO),verif,cou);
							else
								return false;
						}
					}
				}
			}
		}
	}
	return relie;
}	

bool relie_bord_est(Plateau p,Type_Case c,bool verif[LIGNE_MAX][COLONNE_MAX],Couleur cou)
{
	verif[c.co.abscisse][c.co.ordonnee]=true;
	bool relie=true;
	if(c.E==NULL)
		return relie;
	else
	{
		if(c.E->coul!=changer_joueur(cou) && !verif[c.co.abscisse+1][c.co.ordonnee] && impasse_bord(c,cou,verif) && !impasse_bord(*c.O,cou,verif))
			relie=relie_bord_est(p,*(c.E),verif,cou);
		else
		{
			if(c.SE!=NULL && c.SE->coul!=changer_joueur(cou) && !verif[c.co.abscisse][c.co.ordonnee+1] && !impasse_bord(*c.SE,cou,verif))
				relie=relie_bord_est(p,*(c.SE),verif,cou);
			else 
			{
				if(c.SO!=NULL && c.SO->coul!=changer_joueur(cou) && !verif[c.co.abscisse-1][c.co.ordonnee+1] && !impasse_bord(*c.SO,cou,verif))
					relie=relie_bord_est(p,*(c.SO),verif,cou);
				else
				{
					if(c.O!=NULL && c.O->coul!=changer_joueur(cou) && !verif[c.co.abscisse-1][c.co.ordonnee] && !impasse_bord(*c.O,cou,verif))
						relie=relie_bord_est(p,*(c.O),verif,cou);
					else
					{
						if(c.NO!=NULL && c.NO->coul!=changer_joueur(cou) && !verif[c.co.abscisse][c.co.ordonnee-1 && !impasse_bord(*c.NO,cou,verif)])
							relie=relie_bord_est(p,*(c.NO),verif,cou);
						else
						{
							if(c.NE!=NULL && c.NE->coul!=changer_joueur(cou) && !verif[c.co.abscisse+1][c.co.ordonnee-1] && !impasse_bord(*c.NE,cou,verif))
								relie=relie_bord_est(p,*(c.NE),verif,cou);
							else
								return false;
						}
					}
				}
			}
		}
	}
	return relie;
}	

bool relie_bord_nord(Plateau p,Type_Case c,bool verif[LIGNE_MAX][COLONNE_MAX],Couleur cou)
{
	verif[c.co.abscisse][c.co.ordonnee]=true;
	bool relie=true;
	if(c.NO==NULL)
		return relie;
	else
	{
		if(c.NO->coul!=changer_joueur(cou) && !verif[c.co.abscisse][c.co.ordonnee-1] && !impasse_bord(*c.NO,cou,verif))
			relie=relie_bord_nord(p,*(c.NO),verif,cou);
		else
		{
			if(c.NE!=NULL && c.NE->coul!=changer_joueur(cou) && !verif[c.co.abscisse+1][c.co.ordonnee-1] && !impasse_bord(*c.NE,cou,verif))
				relie=relie_bord_nord(p,*(c.NE),verif,cou);
			else 
			{
				if(c.E!=NULL && c.E->coul!=changer_joueur(cou) && !verif[c.co.abscisse+1][c.co.ordonnee] && !impasse_bord(*c.E,cou,verif))
					relie=relie_bord_nord(p,*(c.E),verif,cou);
				else
				{
					if(c.SE!=NULL && c.SE->coul!=changer_joueur(cou) && !verif[c.co.abscisse][c.co.ordonnee+1] && !impasse_bord(*c.SE,cou,verif))
						relie=relie_bord_nord(p,*(c.SE),verif,cou);
					else
					{
						if(c.SO!=NULL && c.SO->coul!=changer_joueur(cou) && !verif[c.co.abscisse-1][c.co.ordonnee+1] && !impasse_bord(*c.SO,cou,verif))
							relie=relie_bord_nord(p,*(c.SO),verif,cou);
						else
						{
							if(c.O!=NULL && c.O->coul!=changer_joueur(cou) && !verif[c.co.abscisse-1][c.co.ordonnee] && !impasse_bord(*c.O,cou,verif))
								relie=relie_bord_nord(p,*(c.O),verif,cou);
							else
								return false;
						}
					}
				}
			}
		}
	}
	return relie;
}

bool relie_bord_sud(Plateau p,Type_Case c,bool verif[LIGNE_MAX][COLONNE_MAX],Couleur cou)
{
	verif[c.co.abscisse][c.co.ordonnee]=true;
	bool relie=true;
	if(c.SE==NULL)
		return relie;
	else
	{
		if(c.SE->coul!=changer_joueur(cou) && !verif[c.co.abscisse][c.co.ordonnee+1] && !impasse_bord(*c.SE,cou,verif))
			relie=relie_bord_sud(p,*(c.SE),verif,cou);
		else
		{
			if(c.SO!=NULL && c.SO->coul!=changer_joueur(cou) && !verif[c.co.abscisse-1][c.co.ordonnee+1] && !impasse_bord(*c.SO,cou,verif))
				relie=relie_bord_sud(p,*(c.SO),verif,cou);
			else 
			{
				if(c.O!=NULL && c.O->coul!=changer_joueur(cou) && !verif[c.co.abscisse-1][c.co.ordonnee] && !impasse_bord(*c.O,cou,verif))
					relie=relie_bord_sud(p,*(c.O),verif,cou);
				{
					if(c.NO!=NULL && c.NO->coul!=changer_joueur(cou) && !verif[c.co.abscisse][c.co.ordonnee-1] && !impasse_bord(*c.NO,cou,verif))
						relie=relie_bord_sud(p,*(c.NO),verif,cou);
					else
						{
						if(c.NE!=NULL && c.NE->coul!=changer_joueur(cou) && !verif[c.co.abscisse+1][c.co.ordonnee-1] && !impasse_bord(*c.NE,cou,verif))
							relie=relie_bord_sud(p,*(c.NE),verif,cou);
						else
						{
							if(c.E!=NULL && c.E->coul!=changer_joueur(cou) && !verif[c.co.abscisse+1][c.co.ordonnee-1] && !impasse_bord(*c.E,cou,verif))
								relie=relie_bord_sud(p,*(c.E),verif,cou);
							else
								return false;
						}
					}
				}
			}
		}
	}
	return relie;
}