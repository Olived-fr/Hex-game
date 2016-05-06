#ifndef IA_h
#define IA_h

#include "../Structure/plateau.h"
#include "../Regles/regles.h"

Coordonnees_tab coup_IA1(Plateau p);

int distance_bord_nord(Plateau p,Type_Case c,bool verif[LIGNE_MAX][COLONNE_MAX],Couleur cou);
int distance_bord_sud(Plateau p,Type_Case c,bool verif[LIGNE_MAX][COLONNE_MAX],Couleur cou);

bool relie_bord_nord(Plateau p,Type_Case c,bool verif[LIGNE_MAX][COLONNE_MAX],Couleur cou);
bool relie_bord_sud(Plateau p,Type_Case c,bool verif[LIGNE_MAX][COLONNE_MAX],Couleur cou);

Type_Case* voisin_NO(Type_Case c);
Type_Case* voisin_NE(Type_Case c);
Type_Case* voisin_O(Type_Case c);
Type_Case* voisin_E(Type_Case c);
Type_Case* voisin_SO(Type_Case c);
Type_Case* voisin_SE(Type_Case c);

bool impasse_bord(Type_Case c,Couleur cou,bool verif[LIGNE_MAX][COLONNE_MAX]);
bool impasse(Type_Case c,Couleur cou,bool verif[LIGNE_MAX][COLONNE_MAX]);
void initialiser_verif(bool verif[LIGNE_MAX][COLONNE_MAX]);
Type_Case* voisin_suivant(Type_Case* depart,Type_Case* voisin);
Type_Case* contourner(Type_Case* case_choisie,Type_Case* voisin);


#endif 
