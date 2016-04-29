#ifndef IA_h
#define IA_h

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

int distance_bord_ouest(Plateau p,Type_Case c,Couleur cou);
int distance_bord_est(Plateau p,Type_Case c,Couleur cou);
int distance_bord_nord(Plateau p,Type_Case c,Couleur cou);
int distance_bord_sud(Plateau p,Type_Case c,Couleur cou);

Type_Case* voisin_NO(Type_Case c);
Type_Case* voisin_NE(Type_Case c);
Type_Case* voisin_O(Type_Case c);
Type_Case* voisin_E(Type_Case c);
Type_Case* voisin_SO(Type_Case c);
Type_Case* voisin_SE(Type_Case c);

#endif 
