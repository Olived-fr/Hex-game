/*
Interface graphique du jeu HEX
*/

#ifndef interface_h
#define interface_h

void render (SDL_Texture *texture, SDL_Renderer *renderer, SDL_Surface *surface, SDL_Rect position);

typedef struct s_Coord Coord;
struct s_Coord
{
	int CoordX;
	int CoordY;
};

#endif
