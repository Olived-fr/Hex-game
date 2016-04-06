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
