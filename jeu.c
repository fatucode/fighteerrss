#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "personnage.h"


void afficher_equipes(Personnage equipe1[], int taille1, Personnage equipe2[], int taille2) {
    printf("\n=== EQUIPE 1 ===\n");
    for (int i = 0; i < taille1; i++) {
        if (equipe1[i].PV > 0) {
            afficherPersonnage(equipe1[i]);
        }
    }

    printf("\n=== EQUIPE 2 ===\n");
    for (int i = 0; i < taille2; i++) {
        if (equipe2[i].PV > 0) {
            afficherPersonnage(equipe2[i]);
        }
    }
}

void jouer_tour(Personnage equipe1[], int taille1, Personnage equipe2[], int taille2) {
    // Tour equipe 1
    for (int i = 0; i < taille1; i++) {
        if (equipe1[i].PV <= 0) continue;

        printf("\n--- Tour de %s ---\n", equipe1[i].nom);
        afficher_equipes(equipe1, taille1, equipe2, taille2);

        int choix;
        printf("\n1. Attaquer\n2. Competence\n3. Soigner\nChoix : ");
        scanf("%d", &choix);

        if (choix == 1) {
            printf("Choisissez une cible : ");
            int cible;
            scanf("%d", &cible);
            attaquer(&equipe1[i], &equipe2[cible-1]);
        } 
        else if (choix == 2) {
            printf("Choisissez une cible : ");
            int cible;
            scanf("%d", &cible);
            utiliser_competence(&equipe1[i], equipe1, taille1, &equipe2[cible-1]);
        } 
        else if (choix == 3 && strcmp(equipe1[i].type, "guerisseur") == 0) {
            printf("Choisissez un allie : ");
            int allie;
            scanf("%d", &allie);
            soigner(&equipe1[i], &equipe1[allie-1]);
        }
    }
}

Personnage* jouer_partie(Personnage equipe1[], int taille1, Personnage equipe2[], int taille2) {
    int tour = 1;
    
    while (1) {
        printf("\n=== TOUR %d ===\n", tour);
        
        jouer_tour(equipe1, taille1, equipe2, taille2);
        
        // Vérifier si equipe2 est morte
        int equipe2_vivante = 0;
        for (int i = 0; i < taille2; i++) {
            if (equipe2[i].PV > 0) equipe2_vivante = 1;
        }
        if (!equipe2_vivante) return equipe1;
        
        jouer_tour(equipe2, taille2, equipe1, taille1);
        
        // Vérifier si equipe1 est morte
        int equipe1_vivante = 0;
        for (int i = 0; i < taille1; i++) {
            if (equipe1[i].PV > 0) equipe1_vivante = 1;
        }
        if (!equipe1_vivante) return equipe2;
        
        tour++;
    }
}
