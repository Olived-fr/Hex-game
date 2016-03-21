/*
Interface graphique du jeu HEX
Olivier Dufour - 2016
*/

#ifndef interface_h
#define interface_h

//Met en pause la fenêtre en attendnt une action 
void pause_interface ();

//Charge l'image et l'optimise pour la fenêtre
SDL_Surface *loadMedia (SDL_Surface *imageSurface, SDL_Surface *screenSurface, char Nom[]);

#endif
