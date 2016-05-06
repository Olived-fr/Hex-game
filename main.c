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
	
	SDL_Event event;
	Plateau board_tab;
	Coordonnees_tab coord_tab;
	Couleur joueur_courant = bleu, dernier_joueur = bleu;
	menu.actualMenu = menu.mainMenu;
	bool quit = false, premier_coup = true, IA = false;
	int choix;
	
	coord_tab.abscisse = 0;
	coord_tab.ordonnee = 0;
	
	
	while (!quit)  //Boucle des évènements
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
				
			case SDL_MOUSEBUTTONDOWN:	//On clique sur la souris
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					clic.CoordX = event.motion.x;
					clic.CoordY = event.motion.y;
					
					choix = choix_Menu(clic, menu);
					
					
					/********************* Menus ***********************/
					
					if (menu.actualMenu == menu.mainMenu)	//Menu principal
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
					
					
					else if (menu.actualMenu == menu.playMenu)	//Menu de sélection de partie
					{
						if (choix == 0)
						{
							menu.actualMenu = menu.inGameMenu;
							MaJ_Menu(menu, interface, nbinGameMenuChoice);
							nouvelle_partie(board_tab);
							MaJ_Board(board, interface, board_tab);
							joueur_courant = bleu;
							premier_coup = true;
							MaJ_Infos(menu, interface, joueur_courant, premier_coup);

						}
						if (choix == 1)
						{
							menu.actualMenu = menu.inGameMenu;
							MaJ_Menu(menu, interface, nbinGameMenuChoice);
							nouvelle_partie(board_tab);
							MaJ_Board(board, interface, board_tab);
							joueur_courant = bleu;
							premier_coup = true;
							IA = true;
							
						}
						if (choix == 2)
						{
							menu.actualMenu = menu.inGameMenu;
							MaJ_Menu(menu, interface, nbinGameMenuChoice);
							nouvelle_partie(board_tab);
							MaJ_Board(board, interface, board_tab);
							joueur_courant = bleu;
							premier_coup = true;
							IA = true;
							MaJ_Infos(menu, interface, joueur_courant, premier_coup);
						}
						if (choix == 3)
						{
							menu.actualMenu = menu.mainMenu;
							MaJ_Menu(menu, interface, nbMenuChoice);
						}
					}
					
					
					else if (menu.actualMenu == menu.inGameMenu)	//Menu en jeu
					{
						if (choix == 0)
						{
							menu.actualMenu = menu.playMenu;
							MaJ_Menu(menu, interface, nbPlayMenuChoice);
						}
						if (choix == 1)
						{
							board_save(board_tab);
						}
						if (choix == 2)
						{
							if (joueur_courant != dernier_joueur)
							{
								annuler(board_tab);
								MaJ_Board(board, interface, board_tab);
								MaJ_Infos(menu, interface, joueur_courant, premier_coup);
								joueur_courant = changer_joueur(joueur_courant);
							}
						}
						if (choix == 3)
						{
							quit = true;
						}
						
						
						/********************* Tour de jeu *********************/
						
						if (!IA)	//Partie humain vs humain
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
									premier_coup = false;
									MaJ_Infos(menu, interface, joueur_courant,premier_coup);

									if (verify_win(board_tab[coord_tab.abscisse][coord_tab.ordonnee], board_tab))
									{
										affiche_vainqueur(menu, interface, joueur_courant);
										menu.actualMenu = menu.mainMenu;
										MaJ_Menu(menu, interface, nbMenuChoice);
									}
									joueur_courant = changer_joueur(joueur_courant);
								}
							}
						}
						
						else if (IA)	//Partie humain vs IA
						{
							if (joueur_courant == bleu)
								coord_tab = pos_pion_tab(clic, board);
							else
								coord_tab = coup_IA1 (board_tab);
							
							if (coup_valide(board_tab, coord_tab))
							{
								placer_pion(board, coord_tab, joueur_courant, interface, board_tab);
								historique(premier_coup, coord_tab, joueur_courant);
								premier_coup = false;
								MaJ_Infos(menu, interface, joueur_courant,premier_coup);
								
								if (verify_win(board_tab[coord_tab.abscisse][coord_tab.ordonnee], board_tab))
								{
									affiche_vainqueur(menu, interface, joueur_courant);
									menu.actualMenu = menu.mainMenu;
									MaJ_Menu(menu, interface, nbMenuChoice);
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
	
	return 0;
}
