#ifndef regles_h
#define regles_h

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../Structure/plateau.h"
#include "plateau.h"
#include "../Structure/plateau.h"
#include "../Persistance/persistance.h"

bool premier_joueur();
PLateau nouvelle_partie();
bool bord(Type_Case c);
bool bord_oppose(Type_Case deb, Type_Case comp);
bool verify_win(Type_Case cur, Type_Case prev, Type_Case deb);
void nouvelle_partie(Plateau p);
Joueur changer_joueur(Joueur joueur_courant); //renvoie "joueur1" si joueur_courant==joueur2 et renvoie "joueur2" si joueur_courant==joueur1
Couleur couleur_joueur(Joueur j);//renvoie "bleu" si j est égal à "joueur1" et "rouge si j est égal à "joueur2"
Plateau choix_coup(Plateau p,Coup c);/* Mets à jour un tableau en fonction d'un coup c après avoir vérifie la validité de ce dernier*/
bool coup_valide(Plateau p,Coordonnees_tab c); // renvoie true si la case de coordonnees c est libre et est dans le plateau

#endif
