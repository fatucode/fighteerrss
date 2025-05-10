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
        int result;
        do {
            printf("\nChoisissez une cible (1-%d) : ", nb_cibles);
            result = scanf("%d", &choix_cible);
            while(getchar() != '\n'); // Vider le buffer

            if (result != 1 || choix_cible < 1 || choix_cible > nb_cibles) {
            printf("❌ Entrée invalide. Veuillez entrer un numéro entre 1 et %d.\n", nb_cibles);
        }
    } while(result != 1 || choix_cible < 1 || choix_cible > nb_cibles);

        Personnage *cible = &equipe2[cibles_valides[choix_cible - 1]];

        // 3. Choix de l'action
        printf("\nActions possibles pour %s:\n", equipe1[i].nom);
        printf("1. Attaque normale\n");
        printf("2. Competence speciale (%s)\n", equipe1[i].competence.nom);
        if (strcmp(equipe1[i].type, "guerisseur") == 0) {
            printf("3. Soigner un allie\n");
        }

        int choix_action;
        int max_action;
        if (strcmp(equipe1[i].type, "guerisseur") == 0) {
            max_action = 3;
        } else {
        max_action = 2;
        }

        do {
            printf("Votre choix : ");
            if (scanf("%d", &choix_action) != 1) {
            printf("Entrée invalide. Veuillez entrer un nombre.\n");
            while (getchar() != '\n'); // vide le buffer
            choix_action = 0; // pour que ça boucle
            } else if (choix_action < 1 || choix_action > max_action) {
            printf("Choix invalide. Veuillez entrer un nombre entre 1 et %d.\n", max_action);
        }
    } while (choix_action < 1 || choix_action > max_action);

                switch(choix_action) {
            case 1:
                attaquer(&equipe1[i], cible);
                if (cible->PV <= 0) {
                    printf("\n💀💀💀 %s A ÉTÉ ÉLIMINÉ ! 💀💀💀\n", cible->nom);
                }
                break;

            case 2:
                utiliser_competence(&equipe1[i], equipe1, taille1, cible);
                if (cible->PV <= 0) {
                    printf("\n💀💀💀 %s A ÉTÉ ÉLIMINÉ ! 💀💀💀\n", cible->nom);
                }
                break;

            case 3:
                printf("\nAlliés à soigner:\n");
                for (int j = 0; j < taille1; j++) {
                    if (equipe1[j].PV > 0 && j != i) {
                        printf("%d. %s (PV: %d/%d)\n", j+1, equipe1[j].nom, equipe1[j].PV, equipe1[j].PV_max);
                    }
                }
                int choix_allie;
                scanf("%d", &choix_allie);
                soigner(&equipe1[i], &equipe1[choix_allie - 1]);
                break;
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
    const int TOURS_MAX = 20;

    while (tour <= TOURS_MAX) {
        printf("\n\n═══════════════════════════════════");
        printf("\n            TOUR %d", tour);
        printf("\n═══════════════════════════════════\n");

        // Tour équipe 1
        printf("\n▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄");
        printf("\n█ JOUEUR - C'EST À VOUS ! █");
        printf("\n▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n");
        jouer_tour(equipe1, taille1, equipe2, taille2);

        // Vérifier si équipe 2 a perdu
        int equipe2_vivante = 0;
        for (int i = 0; i < taille2; i++) {
            if (equipe2[i].PV > 0) {
                equipe2_vivante = 1;
                break;
            }
        }
        if (!equipe2_vivante) {
            printf("\n⚔️⚔️⚔️ L'ÉQUIPE 1 REMPORTE LA VICTOIRE ! ⚔️⚔️⚔️\n");
            return equipe1;
        }

        // Tour équipe 2
        printf("\n▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄");
        printf("\n█  ADVERSAIRE - SON TOUR  █");
        printf("\n▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n");
        jouer_tour(equipe2, taille2, equipe1, taille1);

        // Vérifier si équipe 1 a perdu
        int equipe1_vivante = 0;
        for (int i = 0; i < taille1; i++) {
            if (equipe1[i].PV > 0) {
                equipe1_vivante = 1;
                break;
            }
        }
        if (!equipe1_vivante) {
            printf("\n☠️☠️☠️ L'ÉQUIPE 2 REMPORTE LA VICTOIRE ! ☠️☠️☠️\n");
            return equipe2;
        }

        // Fin de tour : mise à jour des effets temporaires
        fin_tour(equipe1, taille1);
        fin_tour(equipe2, taille2);

        tour++;
    }

    printf("\n🕛🕛🕛 LIMITE DE TOURS ATTEINTE - MATCH NUL ! 🕛🕛🕛\n");
    return NULL;
   
}
