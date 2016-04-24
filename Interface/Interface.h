/**********************************/
/* Interface graphique du jeu HEX */
/**********************************/

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
#include "./Structure/plateau.h"
#include "./Regles/regles.h"

/*************************************** Constantes de la SDL **************************/
#define nbMenuChoice 4
#define nbPlayMenuChoice 4
#define nbinGameMenuChoice 4
#define MenuOptionHeight 80



/******************************************Structures *************************************/
typedef struct s_Interface s_Interface;
struct s_Interface
{
	SDL_Window *window;
	SDL_Surface *screenSurface;
};

typedef struct s_Coord Coord_SDL;
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
	char *inGameMenu[nbinGameMenuChoice];
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


/******************************************Prototypes ***************************************/
s_Interface Init();
s_Menu loadMenu(s_Interface interface);
s_Board loadBoard(s_Interface interface);
void Quit(s_Board, s_Interface, s_Menu);
int choixMenu ( Coord_SDL clic, s_Menu menu);
Coord_SDL pos_pion_SDL (Coordonnees_tab coord_tab, s_Board board);
Coordonnees_tab pos_pion_tab (Coord_SDL coord, s_Board board);
bool clic_on_board (Coord_SDL coord, s_Board board);
void MaJ_Menu (s_Menu menu, s_Interface interface, int nbChoice);

#endif
