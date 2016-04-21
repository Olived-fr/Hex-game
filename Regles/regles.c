#include "rules.h"

bool premier_joueur(Joueur choix_premier)
{
	return choix_premier==joueur1;
}

void nouvelle_partie(Plateau p, int choix)
{
	switch (choix)
	{
		case 1:
			p=initialiser_plateau();
			creation_config();
		break;

		case 2:
			p=initialiser_plateau();
			creation_config();
		break;

		case 3:
			p=initialiser_plateau();
			creation_config();
		break;

		default:
			exit(1);
		break;
	}
	
}


Joueur changer_joueur(Joueur joueur_courant) 
{
	if (joueur_courant==joueur1)
		return joueur2;
	else
		return joueur1;
}


Couleur couleur_joueur(Joueur j)
{
	if(j==joueur1)
		return rouge;
	else
		return bleu;
}



Plateau choix_coup(Plateau p,Coup c)
{
	if(coup_valide(p,c.coord))
		p[c.coord.abscisse][c.coord.ordonnee].coul=c.couleur;
	return p;
}

bool coup_valide(Plateau p,Coordonnees_tab c)
{
	return dans_plateau(c) && p[c.abscisse][c.ordonnee].coul==neutre;
}
