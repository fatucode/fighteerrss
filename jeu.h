#ifndef JEU_H
#define JEU_H

#include "personnage.h"

void afficher_equipes(Personnage equipe1[], int taille1, Personnage equipe2[], int taille2);
void jouer_tour(Personnage equipe1[], int taille1, Personnage equipe2[], int taille2);
void fin_tour(Personnage equipe[], int taille);
Personnage* jouer_partie(Personnage equipe1[], int taille1, Personnage equipe2[], int taille2);

#endif
