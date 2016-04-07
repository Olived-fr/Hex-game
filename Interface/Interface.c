#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "interface.h"

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 640;

int main(int argc, char * argv[])
{
	
/********************************************** Variables de la SDL *******************************************/
	
		//La fenêtre et les surfaces
    SDL_Window *window = NULL;
	SDL_Surface *screenSurface = NULL, *imageSurface = NULL, *menuSurface = NULL, *menuText = NULL, *copyrightSurface = NULL, *copyrightText = NULL, *pionBleu = NULL, *pionRouge = NULL;
	SDL_Color Black = {0,0,0};
	SDL_Rect posPionBleu, posPionRouge, posBoard, posMenu, posText, posCopyright;
	
	Coord clic;
	const int MenuOptionHeight = 80;
	const int nbMenuChoice = 3;
	const int nbPlayMenuChoice = 4;
	char **actualMenu;
	char *mainMenu[nbMenuChoice];
	mainMenu[0] = "Jouer";
	mainMenu[1] = "Charger";
	mainMenu[2] = "Quitter";
	char *playMenu[nbPlayMenuChoice];
	playMenu[0] = " Humain vs Humain";
	playMenu[1] = "    Humain vs IA1";
	playMenu[2] = "    Humain vs IA2";
	playMenu[3] = "          Retour";
	
	
/*********************************************** Initialisations ***********************************************/
	
		//Initialise la SDL
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL ! Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    
		//Créer la fenêtre
    window = SDL_CreateWindow( "Hex", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if (window == NULL)
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
	
/******************************************** Chargement des surfaces ***************************************/
	
		//Surface de la fenêtre
    screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB( screenSurface->format, 255, 255, 255 ));
	

		//Chargement et position de l'image du plateau
    imageSurface = IMG_Load("Images/jeu_hex_640.png");
    if (imageSurface == NULL)
        fprintf(stderr, "Impossible de charger l'image");
	posBoard.x = 370;
	posBoard.y = 100;
	SDL_BlitSurface(imageSurface, NULL, screenSurface, &posBoard);

		//Charge les pions
    pionBleu = IMG_Load("Images/button-blue22.png");
    posPionBleu.x = 845;
    posPionBleu.y = 150;
    pionRouge = IMG_Load("Images/button-red22.png");
    posPionRouge.x = 545;
    posPionRouge.y = 290;
	
		//Surface du menu principal
	menuSurface = IMG_Load("Images/Menu1.png");
	posMenu.x = 5;
	posMenu.y = 120;
	SDL_BlitSurface(menuSurface,NULL,screenSurface,&posMenu);
	
	TTF_Font *fontMenu = TTF_OpenFont("Font/System San Francisco Display Regular.ttf",20);
	
		//Copyright
	copyrightSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, 550, 50, 32, 0, 0, 0, 0);
	SDL_FillRect(copyrightSurface, NULL, SDL_MapRGB(screenSurface->format, 27, 142, 202));
	posCopyright.x = 225,
	posCopyright.y = 2;
	SDL_BlitSurface(copyrightSurface,NULL,screenSurface,&posCopyright);
	copyrightText = TTF_RenderText_Blended(fontMenu, " Arnaud SOLER, Olivier DUFOUR, Rialy ANDRIAMISEZA - 2016" , Black);
	SDL_BlitSurface(copyrightText,NULL,screenSurface,&posCopyright);
	
	
	
/*************************************** Chargement du menu principal *****************************************/
	
	
		//Titre du menu
	TTF_SetFontStyle(fontMenu, TTF_STYLE_BOLD);
	menuText = TTF_RenderText_Blended(fontMenu,"Menu",Black);
	posText.x = posMenu.x + 10;
	posText.y = posMenu.y + 30;
	SDL_BlitSurface(menuText,NULL,screenSurface,&posText);
	
		//Menu principal
	posText.y += MenuOptionHeight;
	TTF_SetFontStyle(fontMenu, TTF_STYLE_NORMAL);
	for(int i = 0; i < nbMenuChoice; i++)
	{
		menuText = TTF_RenderText_Blended(fontMenu,mainMenu[i],Black);
		SDL_BlitSurface(menuText,NULL,screenSurface,&posText);
		posText.y += MenuOptionHeight;
	}


/******************************************* Boucle des évènements ****************************************/
	
    int quit = false;
	actualMenu = mainMenu;
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
				
					if (actualMenu == mainMenu)
					{
						clic.CoordX = event.motion.x;
						clic.CoordY = event.motion.y;
						
						if (clic.CoordX > 5 && clic.CoordX < 205 && clic.CoordY > 200 && clic.CoordY < 279) //Premier bouton du menu
						{
							SDL_BlitSurface(menuSurface,NULL,screenSurface,&posMenu);
							actualMenu = playMenu;
							posText.x = posMenu.x + 10;
							posText.y = posMenu.y + 30;
							for(int i = 0; i < nbPlayMenuChoice; i++)
							{
								menuText = TTF_RenderText_Blended(fontMenu,actualMenu[i],Black);
								SDL_BlitSurface(menuText,NULL,screenSurface,&posText);
								posText.y += MenuOptionHeight;
							}
	
						}
						if (clic.CoordX > 5 && clic.CoordX < 205 && clic.CoordY > 280 && clic.CoordY < 359) //Deuxième bouton du menu
						{
							;
						}
						if (clic.CoordX > 5 && clic.CoordX < 205 && clic.CoordY > 360 && clic.CoordY < 439) //Troisième bouton du menu
						{
							SDL_Quit();
						}
					}
					
					else if (actualMenu == playMenu)
					{
						clic.CoordX = event.motion.x;
						clic.CoordY = event.motion.y;
						
						if (clic.CoordX > 5 && clic.CoordX < 205 && clic.CoordY > 360 && clic.CoordY < 439)
						{
							SDL_BlitSurface(menuSurface,NULL,screenSurface,&posMenu);
							actualMenu = mainMenu;
							TTF_SetFontStyle(fontMenu, TTF_STYLE_BOLD);
							menuText = TTF_RenderText_Blended(fontMenu,"Menu",Black);
							posText.x = posMenu.x + 10;
							posText.y = posMenu.y + 30;
							SDL_BlitSurface(menuText,NULL,screenSurface,&posText);
							posText.y += MenuOptionHeight;
							TTF_SetFontStyle(fontMenu, TTF_STYLE_NORMAL);
							for(int i = 0; i < nbMenuChoice; i++)
							{
								menuText = TTF_RenderText_Blended(fontMenu,actualMenu[i],Black);
								SDL_BlitSurface(menuText,NULL,screenSurface,&posText);
								posText.y += MenuOptionHeight;
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
		SDL_BlitSurface(imageSurface, NULL, screenSurface, &posBoard);
		SDL_BlitSurface(pionBleu,NULL,screenSurface,&posPionBleu);
		SDL_BlitSurface(pionRouge,NULL,screenSurface,&posPionRouge);
		SDL_UpdateWindowSurface(window);
	}

/*********************************** Supression des textures et fermeture de la SDL ************************/

		//Supprime les surfaces (texte, image ...)
	SDL_FreeSurface(imageSurface);
	SDL_FreeSurface(screenSurface);
	SDL_FreeSurface(menuText);
	SDL_FreeSurface(pionBleu);
	SDL_FreeSurface(pionRouge);
	
		//Supprime la fenêtre
	SDL_DestroyWindow(window);
	
		//Quitte SDL et les extensions
	IMG_Quit();
	TTF_CloseFont(fontMenu);
	TTF_Quit();
	SDL_Quit();
	
	return 0;
}




