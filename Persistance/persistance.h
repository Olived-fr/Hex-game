#ifndef persistance_h
#define persistance_h

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool verif_file(char *name);
void creation_config();
void board_save(Plateau p);
void historique(bool b, Coordonnees_tab cor);

#endif