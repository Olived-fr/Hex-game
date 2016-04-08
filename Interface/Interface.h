/*
Interface graphique du jeu HEX
*/

#ifndef interface_h
#define interface_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 640;
const int MenuOptionHeight = 80;
const int nbMenuChoice = 3;
const int nbPlayMenuChoice = 4;
const SDL_Color Black = {0,0,0};

typedef struct s_Interface s_Interface;
struct s_Interface
{
	SDL_Window *window;
	SDL_Surface *screenSurface;
};

typedef struct s_Coord s_Coord;
struct s_Coord
{
	int CoordX;
	int CoordY;
};

typedef struct s_Menu s_Menu;
struct s_Menu
{
	char **actualMenu;
	char *mainMenu[nbMenuChoice];
	char *playMenu[nbPlayMenuChoice];
	SDL_Rect posMenu, posText, posCopyright;
	SDL_Surface *menuSurface, *menuText, *copyrightSurface, *copyrightText;
	TTF_Font *fontMenu;
};

typedef struct s_Board s_Board;
struct s_Board
{
	SDL_Surface *boardSurface, *pionBleu, *pionRouge;
	SDL_Rect posPionBleu, posPionRouge, posBoard;
};

int choixMenu( s_Coord clic, char **actualMenu);
s_Interface Init();
s_Menu loadMenu(s_Interface interface);
s_Board loadBoard(s_Interface interface);
void Quit(s_Board, s_Interface, s_Menu);


#endif
