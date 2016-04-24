#ifndef plateau_h
#define plateau_h

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define LIGNE_MAX 11
#define COLONNE_MAX 11

// Liste des types : Coordonnes, Coup, Type_Case, Plateau, Joueur,Couleur

typedef enum Couleur {rouge,bleu,neutre} Couleur; //Une case peut prendre les valeurs "rouge", "bleu" ou "neutre"

typedef struct Coordonnees Coordonnees_tab;

struct Coordonnees
{
	int abscisse;
	int ordonnee;
};

typedef struct Type_Case Type_Case;

struct Type_Case
{
	Couleur coul;
	Coordonnees_tab co;
	Type_Case* NE;
	Type_Case* NO;
	Type_Case* E;
	Type_Case* O;
	Type_Case* SE;
	Type_Case* SO;
};

typedef Type_Case Plateau[LIGNE_MAX][COLONNE_MAX]; //Le plateau est un tableau à deux dimensions de cases

/*NOTE : les coordonnées du plateau sont [0-10][0-10], pour toute
 * interaction avec l'utilisateur ne pas oublier que ce dernier écrit et lit de sintervalles [1-11][1-11]*/

/* REPRESENTATION INTERNE DU TABLEAU */

void initialiser_plateau(Plateau);//Renvoie un plateau dont toutes les cases sont de valeurs "neutre"
bool est_vide(Plateau p); //Renvoie true si le plateau passé en paramètre est vide

/*----------------------------------*/

/* GESTION DES COORDONNEES */

bool dans_plateau(Coordonnees_tab); //renvoie true si la case de coordonnées (x,y) est dans le plateau
bool sont_voisines(Type_Case,Type_Case); // renvoie true si c1 et c2 sont des cases voisines

#endif