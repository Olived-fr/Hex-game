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
	menu.inGameMenu[2] = "Annuler";
	menu.inGameMenu[3] = "Quitter";
	
	menu.firstPlayerMenu[0] = "Premier joueur: ";
	menu.firstPlayerMenu[1] = "Bleu";
	menu.firstPlayerMenu[2] = "Rouge";
	
	SDL_Event event;
	Plateau board_tab;
	Coordonnees_tab coord_tab;
	Coordonnees_tab dernier_coup_bleu;
	Coordonnees_tab dernier_coup_rouge;
	Couleur joueur_courant = bleu;
	menu.actualMenu = menu.mainMenu;
	bool quit = false;
	int choix;
	
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
							menu.actualMenu = menu.firstPlayerMenu;
							MaJ_Menu(menu, interface, nbfirstPlayerMenu);
						}
						if (choix == 1)
						{
							nouvelle_partie(board_tab);
						}
						if (choix == 2)
						{
							nouvelle_partie(board_tab);
						}
						if (choix == 3)
						{
							menu.actualMenu = menu.mainMenu;
							MaJ_Menu(menu, interface, nbMenuChoice);
						}
					}
					
					else if (menu.actualMenu == menu.firstPlayerMenu)
					{
						if (choix == 1)
						{
							joueur_courant = bleu;
							menu.actualMenu = menu.inGameMenu;
							MaJ_Menu(menu, interface, nbinGameMenuChoice);
							nouvelle_partie(board_tab);
						}
						if (choix == 2)
						{
							joueur_courant = rouge;
							menu.actualMenu = menu.inGameMenu;
							MaJ_Menu(menu, interface, nbinGameMenuChoice);
							nouvelle_partie(board_tab);
						}
					}
					else if (menu.actualMenu == menu.inGameMenu)
					{
						if (choix == 0)
						{
							board_save(board_tab);
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
						
						if (clic_on_board(clic, board))
						{
							
							coord_tab = pos_pion_tab(clic, board);
							if (coup_valide(board_tab, coord_tab))
							{
								placer_pion(board, coord_tab, joueur_courant, interface, board_tab);
								
								if (joueur_courant == bleu)
								{
									dernier_coup_bleu = coord_tab;
									MaJ_Infos(menu, interface, joueur_courant, dernier_coup_bleu);
								}
								else
								{
									dernier_coup_rouge = coord_tab;
									MaJ_Infos(menu, interface, joueur_courant, dernier_coup_rouge);
								}
							
								joueur_courant = changer_joueur(joueur_courant);
								
								if (bord(board_tab[coord_tab.abscisse][coord_tab.ordonnee]))
								{
									if (verify_win(board_tab[coord_tab.abscisse][coord_tab.ordonnee], board_tab[coord_tab.abscisse][coord_tab.ordonnee], board_tab[coord_tab.abscisse][coord_tab.ordonnee]))
										printf("win");
								}
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
	
	return 0;
}
