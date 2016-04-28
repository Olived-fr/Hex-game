#include "plateau.h"

void initialiser_plateau(Plateau p)
{
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
					p[x][y].SO=NULL;//on ne lui affecte pas de voisin sud ouest
					p[x][y].O=NULL;//on ne lui affecte pas de voisin ouest
					p[x][y].E=&p[x+1][y];//elle a forcément un voisin est
					switch(x)
					{
						case 0 : //si la case courante est à l'extrémité nord
							p[x][y].NO=NULL;//on ne lui affecte pas de voisin nord est
							p[x][y].NE=NULL;//on ne lui affecte pas de voisin nord ouest
							p[x][y].SE=&p[x][y+1];
							break;
						case LIGNE_MAX-1 ://si la case courante est à l'extrémité sud
							p[x][y].NO=&p[x][y-1];
							p[x][y].NE=&p[x+1][y-1];
							p[x][y].SE=NULL;//on ne lui affecte pas de voisin sud est
							break;
						default :
							p[x][y].NO=&p[x][y-1];
							p[x][y].NE=&p[x+1][y-1];
							p[x][y].SE=&p[x][y+1];
							break;
					}
					break;
				case COLONNE_MAX-1 : //si la case courante est à l'extrémité est
					p[x][y].E=NULL;//on ne lui affecte pas de voisin est
					p[x][y].NE=NULL;//on ne lui affecte pas de voisin nord est
					p[x][y].O=&p[x-1][y];//elle a forcément un voisin ouest
					switch(x)
					{
						case 0 : //si la case courante est à l'extrémité nord
							p[x][y].SE=&p[x][y+1];
							p[x][y].NO=NULL;//on ne lui affecte pas de voisin nord ouest
							p[x][y].SO=&p[x-1][y+1];
							break;
						case LIGNE_MAX-1 : //si la case courante est à l'extrémité sud
							p[x][y].SE=&p[x][y+1];
							p[x][y].NO=&p[x][y-1];
							p[x][y].SO=&p[x-1][y+1];;
							break;
						default :
							p[x][y].SE=NULL;//on ne lui affecte pas de voisin sud est
							p[x][y].NO=&p[x][y-1];
							p[x][y].SO=NULL;//on ne lui affecte pas de voisin sud ouest
							break;
					}
					break;
				default : //sinon
					p[x][y].E=&p[x+1][y];
					p[x][y].O=&p[x-1][y];
					switch(x)
					{
						case 0 : //si la case courante est à l'extrémité nord
							p[x][y].NO=NULL;//on ne lui affecte pas de voisin nord ouest
							p[x][y].NE=NULL;//on ne lui affecte pas de voisin nord est
							p[x][y].SO=&p[x-1][y+1];
							p[x][y].SE=&p[x][y+1];
							break;
						case LIGNE_MAX-1 : //si la case courante est à l'extrémité sud
							p[x][y].NO=&p[x][y-1];
							p[x][y].NE=&p[x+1][y-1];
							p[x][y].SO=NULL;//on ne lui affecte pas de voisin sud ouest
							p[x][y].SE=NULL;//on ne lui affecte pas de voisin sud est
							break;
						default :
							p[x][y].NO=&p[x][y-1];
							p[x][y].NE=&p[x+1][y-1];
							p[x][y].SO=&p[x-1][y+1];
							p[x][y].SE=&p[x][y+1];
							break;
					}
					break;
			}
		}
	}
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

bool dans_plateau(Coordonnees_tab c)
{
	bool abs_correcte=(0<=c.abscisse) && (c.abscisse<LIGNE_MAX);
	bool ord_correcte=(0<=c.ordonnee) && (c.ordonnee<LIGNE_MAX);
	return (abs_correcte && ord_correcte);
}



