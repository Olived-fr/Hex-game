/********************************************** Jeu HEX ***********************************/
#include "Interface/interface.h"
#include "Structure/plateau.h"
#include "Regles/regles.h"
#include "Persistance/persistance.h"
#include "IA/IA.h"


int main (int argc, char * argv[])
{
	
	Coord_SDL clic;
	s_Menu menu;
	s_Interface interface;
	s_Board board;
	
	interface = Init();
	board = load_Board(interface);
	menu = load_Menu(interface);
	
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
	Couleur joueur_courant = bleu, dernier_joueur = bleu;
	menu.actualMenu = menu.mainMenu;
	bool quit = false, premier_coup = true, IA = false;
	int choix;
	
	while (!quit)
	{
		SDL_WaitEvent(&event);
		
		if (IA)
			if (joueur_courant == rouge)
			{
				event.button.button = SDL_BUTTON_LEFT;
				event.type = SDL_MOUSEBUTTONDOWN;
			}
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
					
					choix = choix_Menu(clic, menu);
					
					if (menu.actualMenu == menu.mainMenu)
					{
						if (choix == 1)
							
						{
							menu.actualMenu = menu.playMenu;
							MaJ_Menu(menu, interface, nbPlayMenuChoice);
						}
						if (choix == 2)
						{
							initialiser_plateau(board_tab);
							chargement(board_tab);
							MaJ_Board(board, interface, board_tab);
							menu.actualMenu = menu.inGameMenu;
							MaJ_Menu(menu, interface, nbinGameMenuChoice);
							premier_coup = false;
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
							nouvelle_partie(board_tab);
							MaJ_Board(board, interface, board_tab);
							premier_coup = true;

						}
						if (choix == 1)
						{
							menu.actualMenu = menu.inGameMenu;
							MaJ_Menu(menu, interface, nbinGameMenuChoice);
							nouvelle_partie(board_tab);
							MaJ_Board(board, interface, board_tab);
							premier_coup = true;
							IA = true;
						}
						if (choix == 2)
						{
							menu.actualMenu = menu.inGameMenu;
							MaJ_Menu(menu, interface, nbinGameMenuChoice);
							nouvelle_partie(board_tab);
							MaJ_Board(board, interface, board_tab);
							
							IA = true;
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
							board_save(board_tab);
						}
						if (choix == 1)
						{
							chargement(board_tab);
							MaJ_Board(board, interface, board_tab);
						}
						if (choix == 2)
						{
							if (joueur_courant != dernier_joueur)
							{
								annuler(board_tab);
								MaJ_Board(board, interface, board_tab);
								MaJ_Infos(menu, interface, joueur_courant);
								joueur_courant = changer_joueur(joueur_courant);
							}
						}
						if (choix == 3)
						{
							quit = true;
						}
						
						if (!IA)
						{
							if (clic_on_board(clic, board))
							{
								coord_tab = pos_pion_tab(clic, board);
								if (coup_valide(board_tab, coord_tab))
								{
									placer_pion(board, coord_tab, joueur_courant, interface, board_tab);
								
									if (joueur_courant == bleu)
										dernier_joueur = bleu;
									else
										dernier_joueur = rouge;

									historique(premier_coup, coord_tab, joueur_courant);
									MaJ_Infos(menu, interface, joueur_courant);
								
									if (verify_win(board_tab[coord_tab.abscisse][coord_tab.ordonnee], board_tab))
									{
										affiche_vainqueur(menu, interface, joueur_courant);
										menu.actualMenu = menu.mainMenu;
										MaJ_Menu(menu, interface, nbMenuChoice);
									}
								
									premier_coup = false;
									joueur_courant = changer_joueur(joueur_courant);
								}
							}
						}
						
						else if (IA)
						{
							if (joueur_courant == bleu)
							{
								if (clic_on_board(clic, board))
								{
									coord_tab = pos_pion_tab(clic, board);
									if (coup_valide(board_tab, coord_tab))
									{
										placer_pion(board, coord_tab, joueur_courant, interface, board_tab);
									}
								}
							}
							else
							{
								coord_tab = coup_IA1 (board_tab, joueur_courant);
								placer_pion(board, coord_tab, joueur_courant, interface, board_tab);
							}
							
							historique(premier_coup, coord_tab, joueur_courant);
							MaJ_Infos(menu, interface, joueur_courant);
							
							if (verify_win(board_tab[coord_tab.abscisse][coord_tab.ordonnee], board_tab))
							{
								affiche_vainqueur(menu, interface, joueur_courant);
								menu.actualMenu = menu.mainMenu;
								MaJ_Menu(menu, interface, nbMenuChoice);
							}
							
							premier_coup = false;
							joueur_courant = changer_joueur(joueur_courant);
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
