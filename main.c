#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "jeu.h"
#include "combat.h"
#include "personnage.h"



int main() {
    printf("=== NINJA COMBAT ===\n\n");
    
    // Création des équipes
    Personnage equipe1[3];
    Personnage equipe2[3];
    
    printf("-- Creation equipe 1 --\n");
    for (int i = 0; i < 3; i++) {
        printf("\nPersonnage %d :\n", i+1);
        equipe1[i] = saisirPersonnage();
    }
    
    printf("\n-- Creation equipe 2 --\n");
    for (int i = 0; i < 3; i++) {
        printf("\nPersonnage %d :\n", i+1);
        equipe2[i] = saisirPersonnage();
    }
    
    // Début du jeu
    Personnage* vainqueurs = jouer_partie(equipe1, 3, equipe2, 3);
    
    // Résultat
    printf("\n=== L'equipe de %s a gagne ! ===\n", vainqueurs[0].nom);
    
    return 0;
    
}
    
