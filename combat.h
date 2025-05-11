#ifndef COMBAT_H
#define COMBAT_H
#include "jeu.h"
#include "personnage.h"
#include <stdbool.h>

void utiliser_competence(Personnage* utilisateur, Personnage equipe[], int taille, Personnage* cible);
void attaquer(Personnage* attaquant, Personnage* cible);
void soigner(Personnage* soigneur, Personnage* cible);
void double_attaque(Personnage *attaquant, Personnage *cible);
void bouclier_equipe(Personnage *defenseur, Personnage equipe[], int taille);
bool ressusciter(Personnage *guerisseur, Personnage equipe[], int taille);

#endif
