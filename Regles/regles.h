#ifndef regles_h
#define regles_h

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../Structure/plateau.h"
#include "../Persistance/persistance.h"


bool premier_joueur();
void nouvelle_partie(Plateau p);
bool bord(Type_Case c);
bool bord_oppose(Type_Case deb, Type_Case comp);
bool verify_win(Type_Case cur, Type_Case prev, Type_Case deb);
Couleur changer_joueur(Couleur joueur_courant); //renvoie "joueur1" si joueur_courant==joueur2 et renvoie "joueur2" si joueur_courant==joueur1
int choix_coup(Plateau,Coordonnees_tab,Couleur);/* Mets à jour un tableau en fonction d'un coup c après avoir vérifie la validité de ce dernier*/
bool coup_valide(Plateau p,Coordonnees_tab c); // renvoie true si la case de coordonnees c est libre et est dans le plateau



#endif

