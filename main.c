#include "personnage.h"
#include "jeu.h"
#include "combat.h"

int main() {
    // Initialisation des équipes
    Ninja equipe1[3] = { ... };  // Remplir avec les données des ninjas
    Ninja equipe2[3] = { ... };  // Remplir avec les données des ninjas

    // Démarrer la partie
    jouer_partie(equipe1, equipe2);

    return 0;
}
