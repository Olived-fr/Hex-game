/********************************************** Jeu HEX ***********************************/
#include "Interface/interface.h"
#include "Structure/plateau.h"
#include "Regles/regles.h"


int main (int argc, char * argv[])
{
	
	Coord_SDL clic;
	s_Menu menu;
	s_Interface interface;
	s_Board board;
	
	interface = Init();
	board = loadBoard(interface);
	menu = loadMenu(interface);
	
	menu.mainMenu[0] = "Menu";
	menu.mainMenu[1] = "Jouer";
	menu.mainMenu[2] = "Charger";
	menu.mainMenu[3] = "Quitter";
	
	menu.playMenu[0] = " Humain vs Humain";
	menu.playMenu[1] = "    Humain vs IA1";
	menu.playMenu[2] = "    Humain vs IA2";
	menu.playMenu[3] = "          Retour";
	
	menu.inGameMenu[0] = "Sauver";
	menu.inGameMenu[1] = "Charger";
	menu.inGameMenu[2] = "Historique";
	menu.inGameMenu[3] = "Quitter";
	
	Plateau board_tab;
	Coordonnees_tab coord_tab;
	bool quit = false;
	int choix;
	menu.actualMenu = menu.mainMenu;
	SDL_Event event;
	Couleur joueur_courant = bleu;

	
	while (!quit)
	{
		SDL_WaitEvent(&event);
		
		switch (event.type)
		{
			case SDL_QUIT:
				quit = true;
				break;
				
			case SDL_MOUSEBUTTONDOWN: //On clique sur la souris
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					clic.CoordX = event.motion.x;
					clic.CoordY = event.motion.y;
					
					choix = choixMenu(clic, menu);
					
					if (menu.actualMenu == menu.mainMenu)
					{
						if (choix == 1)
							
						{
							menu.actualMenu = menu.playMenu;
							MaJ_Menu(menu, interface, nbPlayMenuChoice);
						}
						if (choix == 2)
						{
							;
						}
						if (choix == 3)
						{
							quit = true;
						}
					}
					
					else if (menu.actualMenu == menu.playMenu)
					{
						if (choix == 0)
						{
							menu.actualMenu = menu.inGameMenu;
							MaJ_Menu(menu, interface, nbinGameMenuChoice);
						}
						if (choix == 1)
						{
							;
						}
						if (choix == 2)
						{
							;
						}
						if (choix == 3)
						{
							menu.actualMenu = menu.mainMenu;
							MaJ_Menu(menu, interface, nbMenuChoice);
						}
					}
					else if (menu.actualMenu == menu.inGameMenu)
					{
						if (choix == 0)
						{
							nouvelle_partie(board_tab);
						}
						if (choix == 1)
						{
							;
						}
						if (choix == 2)
						{
							;
						}
						if (choix == 3)
						{
							quit = true;
						}
						coord_tab = pos_pion_tab(clic, board);
						if (dans_plateau(coord_tab))
						{
							
							if (choix_coup(board_tab, coord_tab, joueur_courant) == 0)
							{
								clic = pos_pion_SDL(coord_tab, board);
								if (joueur_courant == bleu)
								{
									board.posPionBleu.x = clic.CoordX;
									board.posPionBleu.y = clic.CoordY;
									SDL_BlitSurface(board.pionBleu,NULL,interface.screenSurface,&board.posPionBleu);
								}
								else
								{
									board.posPionRouge.x = clic.CoordX;
									board.posPionRouge.y = clic.CoordY;
									SDL_BlitSurface(board.pionRouge,NULL,interface.screenSurface,&board.posPionRouge);
								}
							
								joueur_courant = changer_joueur(joueur_courant);
							}
							
						}
					}
					
				}
				break;
				
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
			{
				case SDLK_ESCAPE: //On appuie sur la touche ECHAP
					quit = true;
					break;
			}
				break;
		}
		
			//Met à jour l'écran
		SDL_UpdateWindowSurface(interface.window);
	}
	
	return 0
}
