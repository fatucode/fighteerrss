#ifndef COMBAT_H
#define COMBAT_H

#include "personnage.h"

void attaquer(Ninja* attaquant, Ninja* cible);
void soigner(Ninja* guerisseur, Ninja* cible);
void tourDeCombat(Ninja* equipe1, int taille1, Ninja* equipe2, int taille2);

#endif
