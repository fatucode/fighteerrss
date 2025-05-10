#ifndef COMBAT_H
#define COMBAT_H
// Attaquant : effectue deux attaques successives sur la même cible
void attaquer(Personnage *attaquant, Personnage *cible);
vois soigner(Personnage ,Personnage
void double_attaque(Personnage *attaquant, Personnage *cible);

// Défenseur : applique un effet de bouclier à tous les membres de l'équipe (réduction des dégâts pendant 1 tour)
void bouclier_equipe(Personnage equipe[], int taille);

// Guérisseur : soigne un allié ou lui-même avec un soin renforcé
void boisson_magique(Personnage *soigneur, Personnage *cible);
