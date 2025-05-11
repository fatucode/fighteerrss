#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "jeu.h"
#include "combat.h"
#include "personnage.h"



int main() {
    printf("=== NINJA COMBAT ===\n\n");

    Personnage equipe1[3], equipe2[3];

    // Équipe joueur
    printf("\n=== Composition équipe joueur ===\n");
    equipe1[0] = choisirPersoParType("combattants.txt", "attaquant");
    equipe1[1] = choisirPersoParType("combattants.txt", "defenseur");
    equipe1[2] = choisirPersoParType("combattants.txt", "guerisseur");

    // Équipe ennemie aléatoire
    genererEquipeEnnemie(equipe2, "combattants.txt");

    // Combat
    Personnage* vainqueurs = jouer_partie(equipe1, 3, equipe2, 3);
    printf("\n=== L'équipe de %s a gagné ! ===\n", vainqueurs[0].nom);

    return 0;
}
