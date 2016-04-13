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
