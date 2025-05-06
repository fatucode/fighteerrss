#ifndef COMBAT_H
#define COMBAT_H
// Attaquant : effectue deux attaques successives sur la même cible
void double_attaque(Ninja *attaquant, Ninja *cible);

// Défenseur : applique un effet de bouclier à tous les membres de l'équipe (réduction des dégâts pendant 1 tour)
void bouclier_equipe(Ninja equipe[], int taille);

// Guérisseur : soigne un allié ou lui-même avec un soin renforcé
void boisson_magique(Ninja *soigneur, Ninja *cible);
