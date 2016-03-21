#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "interface.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;

int main(int argc, char * argv[])
{
    //La fenêtre
    SDL_Window *window = NULL;
    SDL_Surface *screenSurface = NULL, *imageSurface = NULL, *texte1 = NULL, *pionBleu = NULL, *pionRouge = NULL;
    
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
    
   // Surface de la fenêtre
    screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB( screenSurface->format, 255, 255, 255 ));
    
    // Chargement et position de l'image du plateau
    imageSurface = loadMedia(imageSurface, screenSurface, "Images/jeu_hex_940.png");
    if (imageSurface == NULL)
        fprintf(stderr, "Impossible de charger l'image");
    SDL_Rect posBoard;
    posBoard.x = 300;
    posBoard.y = 100;
    
    //Charge la police d'écriture
    TTF_Font *fontMenu = TTF_OpenFont("Font/System San Francisco Display Regular.ttf",30);
    SDL_Color fontBlack = {0,0,0};
    texte1 = TTF_RenderText_Blended(fontMenu,"Menu",fontBlack);

    //Charge les pions
    pionBleu = loadMedia(pionBleu, screenSurface,"Images/button-blue22.png");
    SDL_Rect posPionBleu;
    posPionBleu.x = 377;
    posPionBleu.y = 149;
    pionRouge = loadMedia(pionRouge, screenSurface, "Images/button-red22.png");
    SDL_Rect posPionRouge;
    posPionRouge.x = 545;
    posPionRouge.y = 273;
    
    //Applique les surfaces et met à jour l'écran
    SDL_BlitSurface(imageSurface, NULL, screenSurface, &posBoard);
    SDL_BlitSurface(texte1,NULL,screenSurface,NULL);
    SDL_BlitSurface(pionBleu,NULL,screenSurface,&posPionBleu);
    SDL_BlitSurface(pionRouge,NULL,screenSurface,&posPionRouge);
    SDL_UpdateWindowSurface(window);
    //Met en pause l'affichage
    pause_interface();
    
    
    //Supprime les surfaces (texte, image ...)
    SDL_FreeSurface(imageSurface);
    SDL_FreeSurface(screenSurface);
    SDL_FreeSurface(texte1);
    SDL_FreeSurface(pionBleu);
    SDL_FreeSurface(pionRouge);
    //Supprime la fenêtre
    SDL_DestroyWindow(window);
    //Quitte SDL et les extensions
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}

SDL_Surface *loadMedia (SDL_Surface *imageSurface, SDL_Surface *screenSurface, char Nom[])
{
    SDL_Surface* optimizedSurface = NULL;
    imageSurface = IMG_Load(Nom);
    if(imageSurface == NULL)
    {
        fprintf(stderr,"Impossible de charger l'image !\n");
        exit(EXIT_FAILURE);
    }
    optimizedSurface = SDL_ConvertSurface(imageSurface, screenSurface->format, 0);
    if(optimizedSurface == NULL)
    {
        fprintf(stderr, "Impossible d'optimiser l'image ! Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    
    return optimizedSurface;
}



void pause_interface()
{
    int quit = false;
    SDL_Event event;
    while (!quit)
    {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
            quit = true;
    }
}