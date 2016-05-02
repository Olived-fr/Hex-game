#ifndef IA_h
#define IA_h

#include "../Structure/plateau.h"

int distance_bord_ouest(Plateau p,Type_Case c,bool verif[LIGNE_MAX][COLONNE_MAX],Couleur cou);
int distance_bord_est(Plateau p,Type_Case c,bool verif[LIGNE_MAX][COLONNE_MAX],Couleur cou);
int distance_bord_nord(Plateau p,Type_Case c,bool verif[LIGNE_MAX][COLONNE_MAX],Couleur cou);
int distance_bord_sud(Plateau p,Type_Case c,bool verif[LIGNE_MAX][COLONNE_MAX],Couleur cou);

Type_Case* voisin_NO(Type_Case c);
Type_Case* voisin_NE(Type_Case c);
Type_Case* voisin_O(Type_Case c);
Type_Case* voisin_E(Type_Case c);
Type_Case* voisin_SO(Type_Case c);
Type_Case* voisin_SE(Type_Case c);

bool impasse(Type_Case c,Couleur cou,bool verif[LIGNE_MAX][COLONNE_MAX]);
void initialiser_verif(bool verif[LIGNE_MAX][COLONNE_MAX]);

#endif 
