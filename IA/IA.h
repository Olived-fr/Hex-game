#ifndef IA_h
#define IA_h

#include "../Structure/plateau.h"
#include "../Regles/regles.h"
#include <time.h>

Coordonnees_tab coup_IA1(Plateau p);

void distance_bord_sud(Type_Case* c,Type_Case* voisin,int* d,int* min_interne);

Type_Case* voisin_suivant(Type_Case* depart,Type_Case* voisin);
Type_Case* contourner(Type_Case* case_choisie,Type_Case* voisin);


#endif 
