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
    //La surface contenue dans la fenêtre
    SDL_Surface *screenSurface = NULL;
    //L'image
    SDL_Surface *imageSurface = NULL;
    SDL_Surface *texte1 = NULL;
    
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
    
    // Chargement et position de l'image
    //loadMedia(imageSurface, screenSurface);
    imageSurface = SDL_LoadBMP("Images/hello_world.bmp");
    if (imageSurface == NULL)
        printf("error");
  /*  SDL_Rect posBoard;
    posBoard.x = 280;
    posBoard.y = 100;
    
    //Charge la police d'écriture
    TTF_Font *fontMenu = TTF_OpenFont("Font/System San Francisco Display Regular.ttf",30);
    SDL_Color fontBlack = {0,0,0};
    texte1 = TTF_RenderText_Blended(fontMenu,"Hello guys !",fontBlack); */

    //Applique les surfaces et met à jour l'écran
    SDL_BlitSurface(imageSurface, NULL, screenSurface,NULL);//, &posBoard);
    //SDL_BlitSurface(texte1,NULL,screenSurface,NULL);
    SDL_UpdateWindowSurface(window);
    //Met en pause l'affichage
    pause_interface();
    
    
    //Supprime les surfaces (texte, image ...)
    SDL_FreeSurface(imageSurface);
    SDL_FreeSurface(screenSurface);
    SDL_FreeSurface(texte1);
    //Supprime la fenêtre
    SDL_DestroyWindow(window);
    //Quitte SDL et les extensions
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}

SDL_Surface *loadMedia (SDL_Surface *imageSurface, SDL_Surface *screenSurface)
{
    SDL_Surface* optimizedSurface = NULL;
    imageSurface = IMG_Load("jeu_hex_940.png");
    if(imageSurface == NULL)
    {
        fprintf(stderr,"Impossible de charger l'image !\n");
        exit(EXIT_FAILURE);
    }
    optimizedSurface = SDL_ConvertSurface(imageSurface, screenSurface->format, 0);
    if(optimizedSurface == NULL)
    {
        fprintf(stderr, "Unable to optimize image ! SDL Error: %s\n", SDL_GetError());
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