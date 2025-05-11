#include "jeu.h"
#include "combat.h"
#include <stdio.h>
#include"personnage.h"

void afficher_equipes(Personnage equipe1[], int taille1, Personnage equipe2[], int taille2) {
    // En-tête stylisé
    printf("\n┌───────────────────────────────────┐");
    printf("\n│           ÉQUIPE JOUEUR           │");
    printf("\n└───────────────────────────────────┘");
    
    for (int i = 0; i < taille1; i++) {
        printf("\n");
        if (equipe1[i].PV <= 0) {
            printf("☠️  [K.O.] %-15s", equipe1[i].nom);
        } else {
            // Barre de vie visuelle
            int bar_length = 20;
            int current_hp = (equipe1[i].PV * bar_length) / equipe1[i].PV_max;
            
            printf("❤️  %-15s ", equipe1[i].nom);
            printf("[");
            for (int j = 0; j < current_hp; j++) printf("█");
            for (int j = current_hp; j < bar_length; j++) printf(" ");
            printf("] %3d/%-3d", equipe1[i].PV, equipe1[i].PV_max);
            
            // Affichage des effets
            if (equipe1[i].bouclier_actif > 0) {
                printf(" 🛡️×%d", equipe1[i].bouclier_actif);
            }
            if (equipe1[i].competence.tours_recharge > 0) {
                printf(" ⏳%d", equipe1[i].competence.tours_recharge);
            }
        }
    }

    // Séparation visuelle
    printf("\n\n┌───────────────────────────────────┐");
    printf("\n│          ÉQUIPE ENNEMIE           │");
    printf("\n└───────────────────────────────────┘");
    
    for (int i = 0; i < taille2; i++) {
        printf("\n");
        if (equipe2[i].PV <= 0) {
            printf("☠️  [K.O.] %-15s", equipe2[i].nom);
        } else {
            int bar_length = 20;
            int current_hp = (equipe2[i].PV * bar_length) / equipe2[i].PV_max;
            
            printf("💀  %-15s ", equipe2[i].nom);
            printf("[");
            for (int j = 0; j < current_hp; j++) printf("█");
            for (int j = current_hp; j < bar_length; j++) printf(" ");
            printf("] %3d/%-3d", equipe2[i].PV, equipe2[i].PV_max);
            
            if (equipe2[i].bouclier_actif > 0) {
                printf(" 🛡️×%d", equipe2[i].bouclier_actif);
            }
        }
    }
    printf("\n");
}

void jouer_tour(Personnage equipe1[], int taille1, Personnage equipe2[], int taille2) {
    // Affichage état des équipes
    printf("\n╔════════════════════════════╗");
    printf("\n║        ÉTAT DES ÉQUIPES     ║");
    printf("\n╚════════════════════════════╝");
    afficher_equipes(equipe1, taille1, equipe2, taille2);

    for (int i = 0; i < taille1; i++) {
        if (equipe1[i].PV <= 0) {
            printf("\n\033[1;30m☠️ %s est hors combat!\033[0m\n", equipe1[i].nom);
            continue;
        }

        // Header du tour
        printf("\n\n╔════════════════════════════╗");
        printf("\n║ TOUR DE %-15s ║", equipe1[i].nom);
        printf("\n╚════════════════════════════╝");
        
        // Stats du perso
        printf("\n\033[1;36mType: %s\033[0m | ", equipe1[i].type);
        afficherPV(equipe1[i]); // Barre de vie
        
        // Choix de la cible
        printf("\n\033[1;35mCibles disponibles :\033[0m\n");
        int cibles_valides[taille2];
        int nb_cibles = 0;

        for (int j = 0; j < taille2; j++) {
            if (equipe2[j].PV > 0) {
                printf("%d. %s : ", nb_cibles+1, equipe2[j].nom);
                afficherPV(equipe2[j]); // Barre de vie pour chaque cible
                cibles_valides[nb_cibles] = j;
                nb_cibles++;
            }
        }

        int choix_cible;
        do {
            printf("\n\033[1;34mChoisissez une cible (1-%d) : \033[0m", nb_cibles);
            if (scanf("%d", &choix_cible) != 1 || choix_cible < 1 || choix_cible > nb_cibles) {
                printf("\033[1;31m❌ Choix invalide.\033[0m\n");
                while(getchar() != '\n');
            }
        } while(choix_cible < 1 || choix_cible > nb_cibles);

        Personnage *cible = &equipe2[cibles_valides[choix_cible - 1]];

        // Menu des actions
        printf("\n\033[1;35mActions possibles :\033[0m\n");
        printf("\033[1;31m1. ⚔️ Attaque normale\033[0m\n");
        printf("\033[1;33m2. ✨ %s\033[0m\n", equipe1[i].competence.nom);
        
        if (strcmp(equipe1[i].type, "guerisseur") == 0) {
            printf("\033[1;32m3. 💚 Soigner un allié\033[0m\n");
        }

        int choix_action;
        do {
            printf("\n\033[1;34mVotre choix (1-%d) : \033[0m", 
                  (strcmp(equipe1[i].type, "guerisseur") == 0) ? 3 : 2);
            if (scanf("%d", &choix_action) != 1) {
                while(getchar() != '\n');
                printf("\033[1;31m❌ Choix invalide.\033[0m\n");
            }
        } while(choix_action < 1 || choix_action > ((strcmp(equipe1[i].type, "guerisseur") == 0) ? 3 : 2));

        // Exécution de l'action
        switch(choix_action) {
            case 1:
                printf("\033[1;31m");
                attaquer(&equipe1[i], cible);
                printf("\033[0m");
                break;
                
            case 2:
                printf("\033[1;33m");
                utiliser_competence(&equipe1[i], equipe1, taille1, cible);
                printf("\033[0m");
                break;
                
            case 3:
                printf("\n\033[1;32mAlliés à soigner :\033[0m\n");
                for (int j = 0; j < taille1; j++) {
                    if (equipe1[j].PV > 0 && j != i) {
                        printf("%d. %s : ", j+1, equipe1[j].nom);
                        afficherPV(equipe1[j]);
                    }
                }
                int choix_allie;
                scanf("%d", &choix_allie);
                printf("\033[1;32m");
                soigner(&equipe1[i], &equipe1[choix_allie-1]);
                printf("\033[0m");
                break;
        }

        if (cible->PV <= 0) {
            printf("\n\033[1;31m💀 %s EST K.O. ! 💀\033[0m\n", cible->nom);
        }
    }
}

void fin_tour(Personnage equipe[], int taille) {
    for (int i = 0; i < taille; i++) {
        // Gestion bouclier
        if (equipe[i].bouclier_actif > 0) {
            equipe[i].bouclier_actif--;  // Décrémente le compteur
            
            if (equipe[i].bouclier_actif == 0) {
                printf("\n🔮 Le bouclier de %s disparaît.\n", equipe[i].nom);
            }
        }

        // Gestion recharge compétences
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
