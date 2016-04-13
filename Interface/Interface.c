#include "Interface.h"


	
/*********************************************** Initialisations ***********************************************/
	
s_Interface Init()
{
	s_Interface interface;
	interface.window = NULL;
	interface.screenSurface = NULL;
		
		//Initialise la SDL
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL ! Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    
		//Création de la fenêtre
    interface.window = SDL_CreateWindow( "Hex", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if (interface.window == NULL)
    {
        fprintf(stderr, "La fenêtre n'a pas pu être créée ! Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    
		//Initialise la librairie image
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        fprintf(stderr, "Erreur d'initilisation de SDL_image ! Error: %s\n", IMG_GetError());
        exit(EXIT_FAILURE);
    }
	
		//Initialise la librairie de texte
    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init ! Error : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
	
		//Surface de la fenêtre
	interface.screenSurface = SDL_GetWindowSurface(interface.window);
	SDL_FillRect(interface.screenSurface, NULL, SDL_MapRGB( interface.screenSurface->format, 255, 255, 255 ));
	
	
	return interface;
}



/*************************************** Chargement du menu principal *****************************************/

s_Menu loadMenu (s_Interface interface)
{
		
	s_Menu menu;
	
	menu.mainMenu[0] = "Jouer";
	menu.mainMenu[1] = "Charger";
	menu.mainMenu[2] = "Quitter";
	
	menu.playMenu[0] = " Humain vs Humain";
	menu.playMenu[1] = "    Humain vs IA1";
	menu.playMenu[2] = "    Humain vs IA2";
	menu.playMenu[3] = "          Retour";
		
	menu.fontMenu = TTF_OpenFont("Font/System San Francisco Display Regular.ttf",20);
	
	
		//Surface du menu principal
	menu.menuSurface = IMG_Load("Images/Menu1.png");
	menu.posMenu.x = 5;
	menu.posMenu.y = 120;
	SDL_BlitSurface(menu.menuSurface,NULL,interface.screenSurface,&menu.posMenu);

	
		//Titre du menu
	TTF_SetFontStyle(menu.fontMenu, TTF_STYLE_BOLD);
	menu.menuText = TTF_RenderText_Blended(menu.fontMenu,"Menu",Black);
	menu.posText.x = menu.posMenu.x + 10;
	menu.posText.y = menu.posMenu.y + 30;
	SDL_BlitSurface(menu.menuText,NULL,interface.screenSurface,&menu.posText);
	
	
		//Menu principal
	menu.posText.y += MenuOptionHeight;
	TTF_SetFontStyle(menu.fontMenu, TTF_STYLE_NORMAL);
	for(int i = 0; i < nbMenuChoice; i++)
	{
		menu.menuText = TTF_RenderText_Blended(menu.fontMenu,menu.mainMenu[i],Black);
		SDL_BlitSurface(menu.menuText,NULL,interface.screenSurface,&menu.posText);
		menu.posText.y += MenuOptionHeight;
	}
	
		//Copyright
	menu.copyrightSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, 550, 50, 32, 0, 0, 0, 0);
	SDL_FillRect(menu.copyrightSurface, NULL, SDL_MapRGB(interface.screenSurface->format, 27, 142, 202));
	menu.posCopyright.x = 225,
	menu.posCopyright.y = 2;
	SDL_BlitSurface(menu.copyrightSurface,NULL,interface.screenSurface,&menu.posCopyright);
	menu.copyrightText = TTF_RenderText_Blended(menu.fontMenu, " Arnaud SOLER, Olivier DUFOUR, Rialy ANDRIAMISEZA - 2016" , Black);
	SDL_BlitSurface(menu.copyrightText,NULL,interface.screenSurface,&menu.posCopyright);
	
	
	return menu;
}



/******************************************** Chargement du plateau *************************************/

s_Board loadBoard(s_Interface interface)
{
	s_Board board;
	
		//Chargement et position de l'image du plateau
	board.boardSurface = IMG_Load("Images/jeu_hex_640.png");
	if (board.boardSurface == NULL)
		fprintf(stderr, "Impossible de charger l'image");
	board.posBoard.x = 300;
	board.posBoard.y = 100;
	SDL_BlitSurface(board.boardSurface, NULL, interface.screenSurface, &board.posBoard);
	
		//Chargement des pions
	board.pionBleu = IMG_Load("Images/button-blue22.png");
	board.pionRouge = IMG_Load("Images/button-red22.png");
	
	
	return board;
}



/********************************************** Fermeture de la SDL **********************************/

void Quit(s_Board board, s_Interface interface, s_Menu menu)
{
		//Supprime les surfaces (texte, image ...)
	SDL_FreeSurface(board.boardSurface);
	SDL_FreeSurface(interface.screenSurface);
	SDL_FreeSurface(menu.menuText);
	SDL_FreeSurface(board.pionBleu);
	SDL_FreeSurface(board.pionRouge);
	
		//Supprime la fenêtre
	SDL_DestroyWindow(interface.window);
	TTF_CloseFont(menu.fontMenu);
	
		//Quitte SDL et les extensions
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
	
}



/************************************ Choix de l'option du menu *************************************/

int choixMenu (s_Coord clic, s_Menu menu)
{
	
	if (clic.CoordX > 5 && clic.CoordX < 205 && clic.CoordY > 120 && clic.CoordY < 199)
	{
		return 0;
	}
	if (clic.CoordX > 5 && clic.CoordX < 205 && clic.CoordY > 200 && clic.CoordY < 279)
	{
		return 1;
	}
	if (clic.CoordX > 5 && clic.CoordX < 205 && clic.CoordY > 280 && clic.CoordY < 359)
	{
		return 2;
	}
	if (clic.CoordX > 5 && clic.CoordX < 205 && clic.CoordY > 360 && clic.CoordY < 439)
	{
		return 3;
	}
	
	return -1;
}


/********************************* Programme principal et boucle des évènements *******************************/

int main(int argc, char * argv[])
{
	
	s_Coord clic;
	s_Menu menu;
	s_Interface interface;
	s_Board board;
	
	interface = Init();
	board = loadBoard(interface);
	menu = loadMenu(interface);
	
	menu.mainMenu[0] = "Jouer";
	menu.mainMenu[1] = "Charger";
	menu.mainMenu[2] = "Quitter";
	
	menu.playMenu[0] = " Humain vs Humain";
	menu.playMenu[1] = "    Humain vs IA1";
	menu.playMenu[2] = "    Humain vs IA2";
	menu.playMenu[3] = "          Retour";
	

	
    bool quit = false;
	int choix;
	menu.actualMenu = menu.mainMenu;
    SDL_Event event;
	
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
					
					if (clic.CoordX > 300 && clic.CoordY > 100 && clic.CoordY < 500)
					{
						board.posPionBleu.x = clic.CoordX;
						board.posPionBleu.y = clic.CoordY;
					}
					
					else
					{
					choix = choixMenu(clic, menu);
				
					if (menu.actualMenu == menu.mainMenu)
					{
						if (choix == 1)
		
						{
							SDL_BlitSurface(menu.menuSurface,NULL,interface.screenSurface,&menu.posMenu);
							menu.actualMenu = menu.playMenu;
							menu.posText.x = menu.posMenu.x + 10;
							menu.posText.y = menu.posMenu.y + 30;
							for (int i = 0; i < nbPlayMenuChoice; i++)
							{
								menu.menuText = TTF_RenderText_Blended(menu.fontMenu,menu.actualMenu[i],Black);
								SDL_BlitSurface(menu.menuText,NULL,interface.screenSurface,&menu.posText);
								menu.posText.y += MenuOptionHeight;
							}
	
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
							;
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
							SDL_BlitSurface(menu.menuSurface,NULL,interface.screenSurface,&menu.posMenu);
							menu.actualMenu = menu.mainMenu;
							TTF_SetFontStyle(menu.fontMenu, TTF_STYLE_BOLD);
							menu.menuText = TTF_RenderText_Blended(menu.fontMenu,"Menu",Black);
							menu.posText.x = menu.posMenu.x + 10;
							menu.posText.y = menu.posMenu.y + 30;
							SDL_BlitSurface(menu.menuText,NULL,interface.screenSurface,&menu.posText);
							menu.posText.y += MenuOptionHeight;
							TTF_SetFontStyle(menu.fontMenu, TTF_STYLE_NORMAL);
							for (int i = 0; i < nbMenuChoice; i++)
							{
								menu.menuText = TTF_RenderText_Blended(menu.fontMenu,menu.actualMenu[i],Black);
								SDL_BlitSurface(menu.menuText,NULL,interface.screenSurface,&menu.posText);
								menu.posText.y += MenuOptionHeight;
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
		
			//Applique les surfaces et met à jour l'écran
		SDL_BlitSurface(board.boardSurface, NULL, interface.screenSurface, &board.posBoard);
		SDL_BlitSurface(board.pionBleu,NULL,interface.screenSurface,&board.posPionBleu);
		SDL_BlitSurface(board.pionRouge,NULL,interface.screenSurface,&board.posPionRouge);
		SDL_UpdateWindowSurface(interface.window);
	}
	return 0;
}



