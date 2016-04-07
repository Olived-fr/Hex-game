#include "rules.h"

int choix_du_joueur()
{
	if(/* condition */)
	{
		return 1;
	}
	else if (/* condition */)
	{
		return 2;
	}
	else
	{
		return 3;
	}
	return ;
}

bool premier_joueur(Joueur choix_premier)
{
	return choix_premier==joueur1;
}

void nouvelle_partie(Plateau p)
{
	p=initialiser_plateau();
	creation_config();
}
