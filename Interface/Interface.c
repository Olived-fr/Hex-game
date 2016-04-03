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
		//La fenêtre et les surfaces
    SDL_Window *window = NULL;
	SDL_Surface *screenSurface = NULL, *imageSurface = NULL, *menuSurface = NULL, *menuText = NULL, *pionBleu = NULL, *pionRouge = NULL;
	SDL_Color White = { 255, 255, 255 }, Black = {0,0,0};
	SDL_Rect posPionBleu, posPionRouge, posBoard, posMenu, posText;
	
	const int MenuOptionHeight = 82;
	const int nbMenuChoice = 3;
	int posMenuChoice = 0;
	char *titleMenu[nbMenuChoice];
	titleMenu[0] = "Jouer";
	titleMenu[1] = "Charger";
	titleMenu[2] = "Quitter";
	
	
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
	
	
		//Surface de la fenêtre
    screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB( screenSurface->format, 255, 255, 255 ));
	

		//Chargement et position de l'image du plateau
    imageSurface = IMG_Load("Images/jeu_hex_640.png");
    if (imageSurface == NULL)
        fprintf(stderr, "Impossible de charger l'image");
	posBoard.x = 350;
	posBoard.y = 100;
	SDL_BlitSurface(imageSurface, NULL, screenSurface, &posBoard);

		//Charge les pions
    pionBleu = IMG_Load("Images/button-blue22.png");
    posPionBleu.x = 845;
    posPionBleu.y = 150;
    pionRouge = IMG_Load("Images/button-red22.png");
    posPionRouge.x = 545;
    posPionRouge.y = 290;
	
		//Surface du menu
	menuSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, 240, 325, 32, 0, 0, 0, 0);
	SDL_FillRect(menuSurface, NULL, SDL_MapRGB(screenSurface->format, 75, 110, 225));
	SDL_BlitSurface(menuSurface,NULL,screenSurface,&posMenu);
	posMenu.x = 5;
	posMenu.y = 5;
	
		//Texte du menu
	posText.x = posMenu.x;
	posText.y = posMenu.y + 10;
	TTF_Font *fontMenu = TTF_OpenFont("Font/System San Francisco Display Regular.ttf",30);
	TTF_SetFontStyle(fontMenu, TTF_STYLE_BOLD);
	menuText = TTF_RenderText_Blended(fontMenu,"Menu",Black);
	SDL_BlitSurface(menuText,NULL,screenSurface,&posText);
	posText.y += MenuOptionHeight;
	TTF_SetFontStyle(fontMenu, TTF_STYLE_NORMAL);
	for(int i = 0; i < nbMenuChoice; i++)
	{
		menuText = TTF_RenderText_Blended(fontMenu,titleMenu[i],Black);
		SDL_BlitSurface(menuText,NULL,screenSurface,&posText);
		posText.y += MenuOptionHeight;
	}
	posMenuChoice = 0;
	posText.y = posMenu.y + MenuOptionHeight +10;
	menuText = TTF_RenderText_Blended(fontMenu,titleMenu[posMenuChoice],White);
	SDL_BlitSurface(menuText,NULL,screenSurface,&posText);


    int quit = false;
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
					int clicX = event.motion.x;
					int clicY = event.motion.y;
				}
				break;
				
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE: //On appuie sur la touche ECHAP
						quit = true;
						break;
				
					case SDLK_UP:  //On appuie sur la touche "HAUT"
					{
						if( posMenuChoice > 0)
						{
							menuText = TTF_RenderText_Solid(fontMenu, titleMenu[posMenuChoice],Black);
							SDL_BlitSurface(menuText,NULL,screenSurface,&posText);
							posMenuChoice--;
							posText.y = posText.y - MenuOptionHeight;
							menuText = TTF_RenderText_Solid(fontMenu, titleMenu[posMenuChoice],White);
							SDL_BlitSurface(menuText,NULL,screenSurface,&posText);
						}
					}
					break;
				
					case SDLK_DOWN:	//On appuie sur la touche BAS
					{
						if(posMenuChoice < nbMenuChoice -1)
						{
							menuText = TTF_RenderText_Solid(fontMenu, titleMenu[posMenuChoice],Black);
							SDL_BlitSurface(menuText,NULL,screenSurface,&posText);
							posMenuChoice++;
							posText.y = posText.y + MenuOptionHeight;
							menuText = TTF_RenderText_Solid(fontMenu, titleMenu[posMenuChoice],White);
							SDL_BlitSurface(menuText,NULL,screenSurface,&posText);
						}
					}
					break;
				}
		}
			//Applique les surfaces et met à jour l'écran
		SDL_BlitSurface(imageSurface, NULL, screenSurface, &posBoard);
		SDL_BlitSurface(pionBleu,NULL,screenSurface,&posPionBleu);
		SDL_BlitSurface(pionRouge,NULL,screenSurface,&posPionRouge);
		SDL_UpdateWindowSurface(window);
	}


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




