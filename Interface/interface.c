#include "interface.h"


const int SCREEN_WIDTH = 1120;
const int SCREEN_HEIGHT = 720;
const SDL_Color Black = {0,0,0};


/*********************************************** Initialisations ***********************************************/

s_Interface Init ()
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



/****************************************** Chargement du menu principal ***************************************/

s_Menu loadMenu (s_Interface interface)
{

	s_Menu menu;

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

	menu.fontMenu = TTF_OpenFont("Interface/Font/System San Francisco Display Regular.ttf",20);
	if (menu.fontMenu == NULL)
	{
		fprintf(stderr, "Impossible de charger la police de caractère");
		exit(EXIT_FAILURE);
	}

		//Surface du menu principal
	menu.menuSurface = IMG_Load("Interface/Images/Menu.png");
	menu.posMenu.x = 5;
	menu.posMenu.y = 200;
	SDL_BlitSurface(menu.menuSurface,NULL,interface.screenSurface,&menu.posMenu);


		//Menu principal
	menu.posText.x = menu.posMenu.x + 10;
	menu.posText.y = menu.posMenu.y + 30;
	for(int i = 0; i < nbMenuChoice; i++)
	{
		menu.menuText = TTF_RenderText_Blended(menu.fontMenu,menu.mainMenu[i],Black);
		SDL_BlitSurface(menu.menuText,NULL,interface.screenSurface,&menu.posText);
		menu.posText.y += MenuOptionHeight;
	}

		//Copyright
	menu.copyrightSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, 550, 40, 32, 0, 0, 0, 0);
	SDL_FillRect(menu.copyrightSurface, NULL, SDL_MapRGB(interface.screenSurface->format, 27, 142, 202));
	menu.posCopyright.x = 270,
	menu.posCopyright.y = 2;
	SDL_BlitSurface(menu.copyrightSurface,NULL,interface.screenSurface,&menu.posCopyright);
	menu.copyrightText = TTF_RenderText_Blended(menu.fontMenu, " Arnaud SOLER, Olivier DUFOUR, Rialy ANDRIAMISEZA - 2016" , Black);
	SDL_BlitSurface(menu.copyrightText,NULL,interface.screenSurface,&menu.posCopyright);
	
		//Infos
	menu.InfosSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, 700, 100, 32, 0, 0, 0, 0);
	SDL_FillRect(menu.InfosSurface, NULL, SDL_MapRGB(interface.screenSurface->format, 27, 142, 202));
	menu.posInfos.x = 220,
	menu.posInfos.y = 620;
	SDL_BlitSurface(menu.InfosSurface,NULL,interface.screenSurface,&menu.posInfos);
	

	return menu;
}


/***********************************************Mise à jour du menu ****************************************/

void MaJ_Menu (s_Menu menu, s_Interface interface, int nbChoice)
{
	
	SDL_BlitSurface(menu.menuSurface,NULL,interface.screenSurface,&menu.posMenu);
	menu.posText.x = menu.posMenu.x + 10;
	menu.posText.y = menu.posMenu.y + 30;
	for (int i = 0; i < nbChoice; i++)
	{
		menu.menuText = TTF_RenderText_Blended(menu.fontMenu,menu.actualMenu[i],Black);
		SDL_BlitSurface(menu.menuText,NULL,interface.screenSurface,&menu.posText);
		menu.posText.y += MenuOptionHeight;
	}
}


void MaJ_Infos (s_Menu menu, s_Interface interface, Couleur joueur_courant, Coordonnees_tab coord_tab)
{
	char *infos[3];
	char infosA[4];
	char infosO[4];
	char infosJ[10];
	int *abscisse, *ordonnee;
	
	dernier_coup(abscisse, ordonnee);
	sprintf(infosA, "(%d,", *abscisse);
	sprintf(infosO, "%d)", *ordonnee);
	
	if (joueur_courant == bleu)
		strcpy(infosJ,"Bleu");
	else
		strcpy(infosJ,"Rouge");
	
	infos[0] = infosJ;
	infos[1] = infosA;
	infos[2] = infosO;
	

	SDL_BlitSurface(menu.InfosSurface,NULL,interface.screenSurface,&menu.posInfos);
	menu.InfosText = TTF_RenderText_Blended(menu.fontMenu, "Dernier coup: " , Black);
	SDL_BlitSurface(menu.InfosText,NULL,interface.screenSurface,&menu.posInfos);
	menu.posInfos.x += 120;
	for (int i = 0; i < 2; i++)
	{
	menu.InfosText = TTF_RenderText_Blended(menu.fontMenu, infos[i] , Black);
	SDL_BlitSurface(menu.InfosText,NULL,interface.screenSurface,&menu.posInfos);
	menu.posInfos.x += 15;
	}

}


/******************************************** Chargement du plateau ******************************************/

s_Board loadBoard (s_Interface interface)
{
	s_Board board;

		//Chargement et position de l'image du plateau
	board.boardSurface = IMG_Load("Interface/Images/hexBoard.png");
	board.posBoard.x = 300;
	board.posBoard.y = 120;

		//Chargement des pions
	board.pionBleu = IMG_Load("Interface/Images/HexBlue.png");
	board.pionRouge = IMG_Load("Interface/Images/HexRed.png");

	if (board.boardSurface == NULL || board.pionBleu == NULL || board.pionRouge == NULL)
	{
		fprintf(stderr, "Impossible de charger l'image");
		exit(EXIT_FAILURE);
	}
	SDL_BlitSurface(board.boardSurface, NULL, interface.screenSurface, &board.posBoard);
	
	return board;
}



/********************************************** Fermeture de la SDL *****************************************/

void Quit (s_Board board, s_Interface interface, s_Menu menu)
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



/***************************************** Choix de l'option du menu *************************************/

int choixMenu (Coord_SDL clic, s_Menu menu)
{

	if (clic.CoordX > 5 && clic.CoordX < 205 && clic.CoordY > 200 && clic.CoordY < 280)
	{
		return 0;
	}
	if (clic.CoordX > 5 && clic.CoordX < 205 && clic.CoordY > 280 && clic.CoordY < 360)
	{
		return 1;
	}
	if (clic.CoordX > 5 && clic.CoordX < 205 && clic.CoordY > 360 && clic.CoordY < 420)
	{
		return 2;
	}
	if (clic.CoordX > 5 && clic.CoordX < 205 && clic.CoordY > 420 && clic.CoordY < 500)
	{
		return 3;
	}

	return -1;
}



/************************* Position d'un pion dans l'image et dans la structure de données *********************/

Coord_SDL pos_pion_SDL (Coordonnees_tab coord_tab, s_Board board)
{
	Coord_SDL coord;

	coord.CoordX = coord_tab.abscisse * 44 + coord_tab.abscisse + coord_tab.ordonnee * 23 + board.posBoard.x + 6;
	coord.CoordY = coord_tab.ordonnee * 50 + coord_tab.ordonnee - coord_tab.ordonnee * 12 + board.posBoard.y + 10;
	return coord;
}


Coordonnees_tab pos_pion_tab (Coord_SDL coord, s_Board board)
{
	Coordonnees_tab coord_tab;
	int sectX = coord.CoordX - board.posBoard.x - 6;
	int sectY = coord.CoordY - board.posBoard.y - 10;
	if (sectY < 0 || sectX < 0)
	{
		coord_tab.abscisse = -1;
		coord_tab.ordonnee = -1;
		return coord_tab;
	}
	
	int y = 1;
	int x = 1;
	coord_tab.abscisse = 0;
	coord_tab.ordonnee = 0;
	
	while ((y + 50 < sectY || x + 44 < sectX) && coord_tab.ordonnee != 11 )
	{
		coord_tab.abscisse += 1;
		x += 45;
		if (coord_tab.abscisse == 11)
		{
			coord_tab.abscisse = 0;
			coord_tab.ordonnee += 1;
			y += 40;
			x = coord_tab.ordonnee * 23;
		}
	}
	if (coord_tab.ordonnee != 11)
	{
		int i,j;
		i = sectX - x;
		j = sectY - y;
		if (i < 0 || j < 0)
		{
			coord_tab.abscisse = -1;
			coord_tab.ordonnee = -1;
			return coord_tab;
		}
		if (j > 37)
		{
			if (i < 23)
			{
				if (j > (((i+1)/2) + 37))
				{
					coord_tab.abscisse -= 1;
					coord_tab.ordonnee += 1;
				}
			}
			else if (i > 23)
			{
				if (j > ((-(i+1)/2) + 39))
					coord_tab.ordonnee += 1;
			}
		}
	}

	return coord_tab;
}



bool clic_on_board (Coord_SDL coord, s_Board board)
{
	Coordonnees_tab coord_tab = pos_pion_tab(coord, board);
	
	return (coord_tab.abscisse >= 0 && coord_tab.abscisse < 11 && coord_tab.ordonnee >= 0 && coord_tab.ordonnee < 11);
}



s_Board placer_pion (s_Board board, Coordonnees_tab coord_tab, Couleur joueur_courant, s_Interface interface, Plateau board_tab)
{
	Coord_SDL clic;
	
	choix_coup(board_tab, coord_tab, joueur_courant);
	
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
	
	return board;
}


/*************************************************************************************************************/
