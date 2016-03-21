#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define NB_LIGNES 11
#define NB_COLONNES 11

// Liste des types : Coordonnes, Coup, Type_Case, Plateau, Joueur

struct Coordonnees
{
	int abscisses;
	int ordonnees;
}

struct Coup
{
	Coordonnees coord;
	Type_Case couleur;
};

typedef struct Coordonnees Coordonnees
typedef struct Coup Coup;
enum Type_Case {rouge,bleu,neutre}; //Une case peut prendre les valeurs "rouge", "bleu" ou "neutre"
typedef Type_Case Plateau[NB_LIGNES,NB_COLONNES]; //Le plateau est un tableau à deux dimensions de cases
enum Joueur {joueur1,joueur2}; //une variable de type joueur peut prendre les valeurs "joueur1" ou "joueur2"

/* REPRESENTATION INTERNE DU TABLEAU */

Plateau initialiser_plateau();//Renvoie un plateau dont toutes les cases sont de valeurs "neutre"
bool est_vide(Plateau p); //Renvoie true si le plateau passé en paramètre est vide
Plateau modifier_case(Plateau p,Coup c); // Affecte à la case du plateau p de coordonnées (x,y) la valeur de c

/*----------------------------------*/

/* GESTION DES COORDONNEES */

bool vainqueur(Plateau p,Coup dernier_coup);//renvoie true si le dernier coup joué a généré un vainqueur
bool dans_plateau(Coordonnees); //renvoie true si la case de coordonnées (x,y) est dans le plateau
bool sont_voisines(Type_Case c1,Type_Case c2); // renvoie true si c1 et c2 sont des cases voisines
bool au_bord(int x,int y);//renvoie true si la case de coordonnées (x,y) est au bord

int nb_voisin(Coordonnees coor,Type_Case c);//renvoie le nombre de voisin de la case de coordonnees coor qui ont la couleur c
/* Cette fonction sera utile lors de la determination du vainqueur */

Coordonnees voisin_NE(Coordonnees c); // renvoie les coordonnées du voisin au nord-est de la case de coordonnees c
Coordonnees voisin_SE(Coordonnees c); // renvoie les coordonnées du voisin au sud-est de la case de coordonnees c
Coordonnees voisin_E(Coordonnees c); // renvoie les coordonnées du voisin à l'est de la case de coordonnees c
Coordonnees voisin_O(Coordonnees c); // renvoie les coordonnées du voisin au l'ouest de la case de coordonnees c
Coordonnees voisin_SE(Coordonnees c); // renvoie les coordonnées du voisin au sud_est de la case de coordonnees c
Coordonnees voisin_SO(Coordonnees c); // renvoie les coordonnées du voisin au sud-ouest de la case de coordonnees c

Coordonnees case_suivante(Coordonnees c, Coordonnees suivant(Coordonnees));
/*renvoie les coordonnees voisines de c, le second parametre est un pointeur de fonction determinant le voisin (une des six fonctions ci-dessus)*/


/*----------------------------------*/

/* TOUR DE JEU */

Joueur changer_joueur(Joueur joueur_courant); //renvoie "joueur1" si joueur_courant==joueur2 et renvoie "joueur2" si joueur_courant==joueur1
Type_Case couleur_joueur(Joueur j);//renvoie "bleu" si j est égal à "joueur1" et "rouge si j est égal à "joueur2"

/*----------------------------------*/

/* VERIFICATION DE LA VALIDITE D'UN COUP */

bool coup_valide(Plateau p,Coordonnees c); // renvoie true si la case de coordonnees c est libre et est dans le plateau

/*----------------------------------*/

/* IA1 */

void partie_IA1(); //Lance une partie humain vs IA1

/*----------------------------------*/

/* IA2 */

void partie_IA2(); //Lance une partie humain vs IA1

/*----------------------------------*/
