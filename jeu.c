#include "jeu.h"
#include "combat.h"
#include <stdio.h>
#include"personnage.h"

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
    // D'abord afficher l'état complet
    printf("\n╔════════════════════════════╗");
    printf("\n║        ÉTAT DES ÉQUIPES     ║");
    printf("\n╚════════════════════════════╝");
    afficher_equipes(equipe1, taille1, equipe2, taille2);

    // Ensuite gérer chaque personnage
    for (int i = 0; i < taille1; i++) {
        if (equipe1[i].PV <= 0) continue;

        // Afficher le tour seulement après l'état global
        printf("\n\n╔════════════════════════════╗");
        printf("\n║ TOUR DE %-15s ║", equipe1[i].nom);
        printf("\n╚════════════════════════════╝");
        printf("\nType: %s | PV: %d/%d", equipe1[i].type, equipe1[i].PV, equipe1[i].PV_max);
        
        // 1. Afficher les cibles disponibles
        printf("\nCibles disponibles (Equipe adverse):\n");
        int cibles_valides[taille2];
        int nb_cibles = 0;

        for (int j = 0; j < taille2; j++) {
            if (equipe2[j].PV > 0) {
                printf("%d. %s (PV: %d/%d)\n", nb_cibles+1, equipe2[j].nom, equipe2[j].PV, equipe2[j].PV_max);
                cibles_valides[nb_cibles] = j;
                nb_cibles++;
            }
        }

        // 2. Choix de la cible
        int choix_cible;
        do {
            printf("\nChoisissez une cible (1-%d) : ", nb_cibles);
            scanf("%d", &choix_cible);
        } while(choix_cible < 1 || choix_cible > nb_cibles);

        Personnage *cible = &equipe2[cibles_valides[choix_cible-1]];

        // 3. Choix de l'action
        printf("\nActions possibles pour %s:\n", equipe1[i].nom);
        printf("1. Attaque normale\n");
        printf("2. Competence speciale (%s)\n", equipe1[i].competence.nom);
        if (strcmp(equipe1[i].type, "guerisseur") == 0) {
            printf("3. Soigner un allie\n");
        }

        int choix_action;
        do {
            printf("Votre choix : ");
            scanf("%d", &choix_action);
        } while(choix_action < 1 || choix_action > 3);

        // 4. Ex�cution
        switch(choix_action) {
            case 1:
                attaquer(&equipe1[i], cible);
                break;
            case 2:
                utiliser_competence(&equipe1[i], equipe1, taille1, cible);
                break;
            case 3:
                // Soin (uniquement pour gu�risseur)
                printf("\nAlli�s � soigner:\n");
                for (int j = 0; j < taille1; j++) {
                    if (equipe1[j].PV > 0 && j != i) {
                        printf("%d. %s (PV: %d/%d)\n", j+1, equipe1[j].nom, equipe1[j].PV, equipe1[j].PV_max);
                    }
                }
                int choix_allie;
                scanf("%d", &choix_allie);
                soigner(&equipe1[i], &equipe1[choix_allie-1]);
                break;
        }
    }
}
void fin_tour(Personnage equipe[], int taille) {
    for (int i = 0; i < taille; i++) {
        // R�duit la dur�e des effets
        if (equipe[i].bouclier_actif > 0) {
            equipe[i].bouclier_actif--;
            if (equipe[i].bouclier_actif == 0) {
                printf("%s perd son bouclier!\n", equipe[i].nom);
            }
        }

        // R�duit le temps de recharge
        if (equipe[i].competence.tours_recharge > 0) {
            equipe[i].competence.tours_recharge--;
        }
    }
}
Personnage* jouer_partie(Personnage equipe1[], int taille1, Personnage equipe2[], int taille2) {
    int tour = 1;

    while (1) {
        printf("\n=== TOUR %d ===\n", tour);

        jouer_tour(equipe1, taille1, equipe2, taille2);
        fin_tour(equipe1, taille1);

        // V�rifier si equipe2 est morte
        int equipe2_vivante = 0;
        for (int i = 0; i < taille2; i++) {
            if (equipe2[i].PV > 0) equipe2_vivante = 1;
        }
        if (!equipe2_vivante) return equipe1;

        jouer_tour(equipe2, taille2, equipe1, taille1);
        fin_tour(equipe2, taille2);

        // V�rifier si equipe1 est morte
        int equipe1_vivante = 0;
        for (int i = 0; i < taille1; i++) {
            if (equipe1[i].PV > 0) equipe1_vivante = 1;
        }
        if (!equipe1_vivante) return equipe2;

        tour++;
    }
}
