#ifndef regles_h
#define regles_h

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../Structure/plateau.h"
#include "../Persistance/persistance.h"


void nouvelle_partie(Plateau p);
void reinitialise_case_checked(Plateau p);
bool bord_bleu(Type_Case c);
bool bord_rouge(Type_Case c);
bool bord_oppose_bleu(Type_Case deb, Type_Case comp);
bool bord_oppose_rouge(Type_Case deb, Type_Case comp);
bool verify_bord(Type_Case *cur, Type_Case *ret);
bool verify_bord_oppose(Type_Case *cur, Type_Case deb);
bool verify_win(Type_Case cur, Plateau p);
Couleur changer_joueur(Couleur couleur_courante); //renvoie "joueur1" si joueur_courant==joueur2 et renvoie "joueur2" si joueur_courant==joueur1
void choix_coup(Plateau p,Coordonnees_tab c,Couleur couleur_courante); /* Mets à jour un tableau en fonction d'un coup c */
bool coup_valide(Plateau p,Coordonnees_tab c); // renvoie true si la case de coordonnees c est libre et est dans le plateau



#endif

