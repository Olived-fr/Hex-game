#ifndef plateau_h
#define plateau_h

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define LIGNE_MAX 11
#define COLONNE_MAX 11

// Liste des types : Coordonnes, Coup, Type_Case, Plateau, Joueur,Couleur

typedef enum Couleur {rouge,bleu,neutre} Couleur; //Une case peut prendre les valeurs "rouge", "bleu" ou "neutre"
typedef enum Joueur {joueur1,joueur2} Joueur; //une variable de type joueur peut prendre les valeurs "joueur1" ou "joueur2"

typedef struct Coordonnees Coordonnees_tab;

struct Coordonnees
{
	int abscisse;
	int ordonnee;
};

typedef struct Coup Coup;

struct Coup
{
	Coordonnees_tab coord;
	Couleur couleur;
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

typedef Type_Case** Plateau/*[LIGNE_MAX][COLONNE_MAX]*/; //Le plateau est un tableau à deux dimensions de cases

/*NOTE : les coordonnées du plateau sont [0-10][0-10], pour toute
 * interaction avec l'utilisateur ne pas oublier que ce dernier écrit et lit des intervalles [1-11][1-11]*/
 
typedef struct Coup Coup;

/* REPRESENTATION INTERNE DU TABLEAU */

Plateau initialiser_plateau();//Renvoie un plateau dont toutes les cases sont de valeurs "neutre"
bool est_vide(Plateau p); //Renvoie true si le plateau passé en paramètre est vide

/*----------------------------------*/

/* GESTION DES COORDONNEES */

bool vainqueur(Plateau p,Coup dernier_coup);//renvoie true si le dernier coup joué a généré un vainqueur
bool dans_plateau(Coordonnees_tab); //renvoie true si la case de coordonnées (x,y) est dans le plateau
bool sont_voisines(Type_Case,Type_Case); // renvoie true si c1 et c2 sont des cases voisines

int nb_voisin(Coordonnees_tab coor,Type_Case c);//renvoie le nombre de voisin de la case de Coordonnees coor qui ont la couleur c
/* Cette fonction sera utile lors de la determination du vainqueur */




#endif