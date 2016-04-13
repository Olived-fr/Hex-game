#include "prototypes.h"

Plateau initialiser_plateau()
{
	int i;
	Plateau p;
	p=malloc(LIGNE_MAX*sizeof(Type_Case));
	for(i=0;i<LIGNE_MAX;i++)
		p[i]=malloc(COLONNE_MAX*sizeof(Type_Case));
	int x,y;
	for(x=0;x<LIGNE_MAX;x++)//parcourt de toutes les lignes
	{
		for(y=0;y<COLONNE_MAX;y++)//et de toutes les colonnes
		{
			p[x][y].co.abscisse=x;
			p[x][y].co.ordonnee=y;
			p[x][y].coul=neutre;//initialisation de toutes les cases avec la couleur 'neutre'
			switch(y)
			{
				case 0 : //si la case courante est à l'extrémité ouest
					p[x][y].O=NULL;//on ne lui affecte pas de voisin ouest
					p[x][y].NO=NULL;//on ne lui affecte pas de voisin nord ouest
					p[x][y].E=&p[x][y+1];//on lui affecte la case à sa droite comme voisin de droite
					switch(x)
					{
						case 0 : //si la case courante est à l'extrémité nord
							p[x][y].NE=NULL;//on ne lui affecte pas de voisin nord est
							p[x][y].SE=&p[x+1][y+1];
							p[x][y].SO=&p[x+1][y];
							break;
						case LIGNE_MAX-1 ://si la case courante est à l'extrémité sud
							p[x][y].NE=&p[x-1][y];
							p[x][y].SE=NULL;//on ne lui affecte pas de voisin sud est
							p[x][y].SO=NULL;//on ne lui affecte pas de voisin sud est
							break;
						default :
							p[x][y].NE=&p[x-1][y];
							p[x][y].SE=&p[x+1][y+1];
							p[x][y].SO=&p[x+1][y];
							break;
					}
					break;
				case COLONNE_MAX-1 : //si la case courante est à l'extrémité est
					p[x][y].E=NULL;//on ne lui affecte pas de voisin est
					p[x][y].SE=NULL;//on ne lui affecte pas de voisin sud est
					p[x][y].O=&p[x][y-1];//on lui affecte la case à sa gauche comme voisin de gauche
					switch(x)
					{
						case 0 : //si la case courante est à l'extrémité nord
							p[x][y].NE=NULL;//on ne lui affecte pas de voisin nord ouest
							p[x][y].NO=NULL;//on ne lui affecte pas de voisin nord ouest
							p[x][y].SO=&p[x+1][y];
							break;
						case LIGNE_MAX-1 : //si la case courante est à l'extrémité sud
							p[x][y].NE=&p[x-1][y];
							p[x][y].NO=&p[x-1][y-1];
							p[x][y].SO=NULL;//on ne lui affecte pas de voisin sudd ouest
							break;
						default :
							p[x][y].NE=&p[x-1][y];
							p[x][y].NO=&p[x-1][y-1];
							p[x][y].SO=&p[x+1][y];
							break;
					}
					break;
				default : //sinon
					p[x][y].E=&p[x][y+1];//on ne lui affecte pas de voisin est
					p[x][y].O=&p[x][y-1];//on lui affecte la case à sa gauche comme voisin de gauche
					switch(x)
					{
						case 0 : //si la case courante est à l'extrémité nord
							p[x][y].NO=NULL;//on ne lui affecte pas de voisin nord ouest
							p[x][y].NE=NULL;//on ne lui affecte pas de voisin nord est
							p[x][y].SO=&p[x+1][y];
							p[x][y].SE=&p[x+1][y+1];
							break;
						case LIGNE_MAX-1 : //si la case courante est à l'extrémité sud
							p[x][y].NO=&p[x-1][y-1];
							p[x][y].NE=&p[x-1][y];
							p[x][y].SO=NULL;//on ne lui affecte pas de voisin sud ouest
							p[x][y].SE=NULL;//on ne lui affecte pas de voisin sud est
							break;
						default :
							p[x][y].NO=&p[x-1][y-1];
							p[x][y].NE=&p[x-1][y];
							p[x][y].SO=&p[x+1][y];
							p[x][y].SE=&p[x+1][y+1];
							break;
					}
					break;
			}
		}
	}
	return p;
}

Joueur changer_joueur(Joueur joueur_courant)
{
	if(joueur_courant==joueur1)
		return joueur2;
	else
		return joueur1;
}

bool sont_voisines(Type_Case c1,Type_Case c2)
{
		bool abs_voisines=(c1.co.abscisse==c2.co.abscisse) || (c1.co.abscisse==c2.co.abscisse+1) || (c1.co.abscisse==c2.co.abscisse-1);
		bool ord_voisines=(c1.co.ordonnee==c2.co.ordonnee) || (c1.co.ordonnee==c2.co.ordonnee+1) || (c1.co.ordonnee==c2.co.ordonnee-1);
		return (abs_voisines && ord_voisines);
}

bool est_vide(Plateau p)
{
	int x=0;
	int y=0;
	while(x<LIGNE_MAX && p[x][y].coul==neutre)
	{
		y=0;
		while(y<COLONNE_MAX && p[x][y].coul==neutre)
			y++;
		if(p[x][y].coul==neutre)x++;
	}
	return (p[x]);
}

bool dans_plateau(Coordonnees c)
{
	bool abs_correcte=(0<=c.abscisse) && (c.abscisse<LIGNE_MAX);
	bool ord_correcte=(0<=c.ordonnee) && (c.ordonnee<LIGNE_MAX);
	return (abs_correcte && ord_correcte);
}

int nb_voisin(Coordonnees coor,Type_Case c)
{
	int nb_voisins=0;
	if(c.NE!=NULL)
		if(c.NE->coul==c.coul)
			nb_voisins++;
	if(c.NO!=NULL)
		if(c.NO->coul==c.coul)
			nb_voisins++;
	if(c.E!=NULL)
		if(c.E->coul==c.coul)
			nb_voisins++;
	if(c.O!=NULL)
		if(c.O->coul==c.coul)
			nb_voisins++;
	if(c.SE!=NULL)
		if(c.NE->coul==c.coul)
			nb_voisins++;
	if(c.SO!=NULL)
		if(c.NE->coul==c.coul)
			nb_voisins++;
	return nb_voisins;
}

Couleur couleur_joueur(Joueur j)
{
	if(j==joueur1)
		return rouge;
	else
		return bleu;
}

bool coup_valide(Plateau p,Coordonnees c)
{
	return dans_plateau(c) && p[c.abscisse][c.ordonnee].coul==neutre;
}
