#include "jeu.h"
#include "combat.h"
#include <stdio.h>
#include "personnage.h"
#include <stdbool.h>
// Définition des codes couleur ANSI pour l'affichage
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define BLUE    "\033[1;34m"
#define GREY    "\033[0;37m"
#define RESET   "\033[0m"
#define YELLOW  "\033[1;33m"

/**
 * @brief Affiche l'état des deux équipes avec mise en forme colorée
 * @param equipe1 Tableau de la première équipe
 * @param taille1 Nombre de membres dans l'équipe 1
 * @param equipe2 Tableau de la seconde équipe
 * @param taille2 Nombre de membres dans l'équipe 2
 * 
 * @details Affiche pour chaque personnage :
 * - Un emoji selon son type
 * - Son nom coloré
 * - Une barre de vie visuelle
 * - Les effets actifs (bouclier, recharge)
 */
void afficher_equipes(Personnage equipe1[], int taille1, Personnage equipe2[], int taille2) {
    // Affichage équipe 1
    printf("\n┌───────────────────────────────────┐");
    printf("\n│           ÉQUIPE 1               │");
    printf("\n└───────────────────────────────────┘");

    for (int i = 0; i < taille1; i++) {
        // Configuration emoji et couleur selon le type
        char *emoji_type = "❓";
        char *couleur = GREY;

        if (strcmp(equipe1[i].type, "attaquant") == 0) {
            emoji_type = "🗡️";
            couleur = RED;
        } else if (strcmp(equipe1[i].type, "defenseur") == 0) {
            emoji_type = "🛡️";
            couleur = BLUE;
        } else if (strcmp(equipe1[i].type, "guerisseur") == 0) {
            emoji_type = "✨";
            couleur = GREEN;
        }

        printf("\n");
        if (equipe1[i].PV <= 0) {
            printf("☠️  %s [K.O.] %s%-15s%s", emoji_type, couleur, equipe1[i].nom, RESET);
        } else {
            // Barre de vie proportionnelle
            int bar_length = 20;
            int current_hp = (equipe1[i].PV * bar_length) / equipe1[i].PV_max;

            printf("%s %s%-15s%s [", emoji_type, couleur, equipe1[i].nom, RESET);
            for (int j = 0; j < current_hp; j++) printf("█");
            for (int j = current_hp; j < bar_length; j++) printf(" ");
            printf("] %3d/%-3d", equipe1[i].PV, equipe1[i].PV_max);

            // Affichage des effets
            if (equipe1[i].bouclier_actif > 0)
                printf(" 🛡️×%d", equipe1[i].bouclier_actif);
            if (equipe1[i].competence.tours_recharge > 0)
                printf(" ⏳%d", equipe1[i].competence.tours_recharge);
        }
    }

    // Affichage équipe 2 (identique mais pour l'équipe adverse)
    printf("\n\n┌───────────────────────────────────┐");
    printf("\n│           ÉQUIPE 2               │");
    printf("\n└───────────────────────────────────┘");

      for (int i = 0; i < taille2; i++) {
        char *emoji_type = "❓";
        char *couleur = GREY;

        if (strcmp(equipe2[i].type, "attaquant") == 0) {
            emoji_type = "🗡️";
            couleur = RED;
        } else if (strcmp(equipe2[i].type, "defenseur") == 0) {
            emoji_type = "🛡️";
            couleur = BLUE;
        } else if (strcmp(equipe2[i].type, "guerisseur") == 0) {
            emoji_type = "✨";
            couleur = GREEN;
        }

        printf("\n");
        if (equipe2[i].PV <= 0) {
            printf("☠️  %s [K.O.] %s%-15s%s", emoji_type, couleur, equipe2[i].nom, RESET);
        } else {
            int bar_length = 20;
            int current_hp = (equipe2[i].PV * bar_length) / equipe2[i].PV_max;

            printf("%s %s%-15s%s [", emoji_type, couleur, equipe2[i].nom, RESET);
            for (int j = 0; j < current_hp; j++) printf("█");
            for (int j = current_hp; j < bar_length; j++) printf(" ");
            printf("] %3d/%-3d", equipe2[i].PV, equipe2[i].PV_max);

            if (equipe2[i].bouclier_actif > 0)
                printf(" 🛡️×%d", equipe2[i].bouclier_actif);
        }
    }
    printf("\n");
}

/**
 * @brief Gère le tour d'une équipe complète
 * @param equipe1 Tableau de l'équipe active
 * @param taille1 Taille de l'équipe active
 * @param equipe2 Tableau de l'équipe adverse
 * @param taille2 Taille de l'équipe adverse
 */
void jouer_tour(Personnage equipe1[], int taille1, Personnage equipe2[], int taille2) {
    // Affichage initial
    printf("\n╔════════════════════════════╗");
    printf("\n║        ÉTAT DES ÉQUIPES     ║");
    printf("\n╚════════════════════════════╝");
    afficher_equipes(equipe1, taille1, equipe2, taille2);

    // Parcours de chaque membre de l'équipe
    for (int i = 0; i < taille1; i++) {
        if (equipe1[i].PV <= 0) {
            printf("\n\033[1;30m☠️ %s est hors combat!\033[0m\n", equipe1[i].nom);
            continue;
        }

        // Affichage du tour du personnage
        printf("\n\n╔════════════════════════════╗");
        printf("\n║ TOUR DE %-15s ║", equipe1[i].nom);
        printf("\n╚════════════════════════════╝");
        
        // Affichage des stats
        printf("\n\033[1;36mType: %s\033[0m | ", equipe1[i].type);
        afficherPV(equipe1[i]);
        
        // Sélection des cibles valides
        printf("\n\033[1;35mCibles disponibles :\033[0m\n");
        int cibles_valides[taille2];
        int nb_cibles = 0;

        for (int j = 0; j < taille2; j++) {
            if (equipe2[j].PV > 0) {
                printf("%d. %s : ", nb_cibles+1, equipe2[j].nom);
                afficherPV(equipe2[j]);
                cibles_valides[nb_cibles] = j;
                nb_cibles++;
            }
        }

        // Choix de la cible
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
        
        // Options spécifiques aux guérisseurs
        if (strcmp(equipe1[i].type, "guerisseur") == 0) {
            printf("\033[1;32m3. 💚 Soigner un allié\033[0m\n");
            printf("\033[1;36m4. 🧬 Ressusciter un allié K.O.\033[0m (%d restantes)\n", 
                equipe1[i].competence.tours_recharge);
        }

        // Choix de l'action
        int choix_action;
        int max_choice = (strcmp(equipe1[i].type, "guerisseur") == 0) ? 4 : 2;
        
        do {
            printf("\n\033[1;34mVotre choix (1-%d) : \033[0m", max_choice);
            if (scanf("%d", &choix_action) != 1) {
                while(getchar() != '\n');
                printf("\033[1;31m❌ Choix invalide.\033[0m\n");
            }
        } while(choix_action < 1 || choix_action > max_choice);

        int allies_valides[taille1];
        int nb_allies = 0;

    switch(choix_action) {
        case 1:
            printf(RED);
            attaquer(&equipe1[i], cible);
            printf(RESET);
            break;
            
        case 2:
            printf(YELLOW);
            utiliser_competence(&equipe1[i], equipe1, taille1, cible);
            printf(RESET);
            break;
            
        case 3:
            printf("\n" GREEN "Alliés à soigner :" RESET "\n");
            nb_allies = 0;
            
            for (int j = 0; j < taille1; j++) {
                if (equipe1[j].PV > 0 && j != i) {
                    printf("%d. %s : ", nb_allies + 1, equipe1[j].nom);
                    afficherPV(equipe1[j]);
                    allies_valides[nb_allies] = j;
                    nb_allies++;
                }
            }
            
            if (nb_allies == 0) {
                printf("Aucun allié à soigner!\n");
                continue;
            }
            
            int choix_allie;
            do {
                printf("\n" BLUE "Choisissez un allié à soigner (1-%d) : " RESET, nb_allies);
                if (scanf("%d", &choix_allie) != 1 || choix_allie < 1 || choix_allie > nb_allies) {
                    printf(RED "❌ Choix invalide.\n" RESET);
                    while(getchar() != '\n');
                }
            } while(choix_allie < 1 || choix_allie > nb_allies);

            printf(GREEN);
            soigner(&equipe1[i], &equipe1[allies_valides[choix_allie - 1]]);
            printf(RESET);
            break;
            
       
    }
    
    // Vérification KO
    if (cible->PV <= 0 && choix_action != 3) {
        printf(RED "\n💀 %s EST K.O. ! 💀\n" RESET, cible->nom);
    }
}  
}

/**
 * @brief Gère les effets de fin de tour (boucliers, recharges)
 * @param equipe Tableau des personnages à mettre à jour
 * @param taille Nombre de personnages dans l'équipe
 */
void fin_tour(Personnage equipe[], int taille) {
    for (int i = 0; i < taille; i++) {
        if (equipe[i].PV <= 0) continue;

        // Décrémentation du bouclier
        if (equipe[i].bouclier_actif > 0) {
            equipe[i].bouclier_actif--;
            if (equipe[i].bouclier_actif == 0) {
                printf("\n🔮 Le bouclier de %s disparaît.\n", equipe[i].nom);
            }
        }

        // Décrémentation du temps de recharge
        if (equipe[i].competence.tours_recharge > 0) {
            equipe[i].competence.tours_recharge--;
        }
    }
}

/**
 * @brief Gère une partie complète entre deux équipes
 * @param equipe1 Première équipe
 * @param taille1 Taille de la première équipe
 * @param equipe2 Seconde équipe
 * @param taille2 Taille de la seconde équipe
 * @return Personnage* Équipe gagnante (NULL si match nul)
 */
Personnage* jouer_partie(Personnage equipe1[], int taille1, Personnage equipe2[], int taille2) {
    // Vérification des paramètres
    if (equipe1 == NULL || equipe2 == NULL || taille1 <= 0 || taille2 <= 0) {
        fprintf(stderr, "Erreur : équipes invalides.\n");
        return NULL;
    }

    // Réinitialisation des états
    for (int i = 0; i < taille1; i++) {
        equipe1[i].bouclier_actif = 0;
        equipe1[i].competence.tours_recharge = 0;
    }
    for (int i = 0; i < taille2; i++) {
        equipe2[i].bouclier_actif = 0;
        equipe2[i].competence.tours_recharge = 0;
    }

    int tour = 1;
    const int TOURS_MAX = 20;  // Limite anti-boucle infinie

    // Boucle principale de jeu
    while (tour <= TOURS_MAX) {
        printf("\n\n═══════════════════════════════════");
        printf("\n            TOUR %d", tour);
        printf("\n═══════════════════════════════════\n");

        // Tour équipe 1
        printf("\n▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄");
        printf("\n█ JOUEUR - C'EST À VOUS ! █");
        printf("\n▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n");
        jouer_tour(equipe1, taille1, equipe2, taille2);

  

        // Vérifie si l'équipe 2 est éliminée
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

        // Tour de l'équipe 2
        printf("\n▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄");
        printf("\n█  ADVERSAIRE - SON TOUR  █");
        printf("\n▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n");
        jouer_tour(equipe2, taille2, equipe1, taille1);

        // Vérifie si l'équipe 1 est éliminée
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

        // Mise à jour des effets temporaires à la fin du tour
        fin_tour(equipe1, taille1);
        fin_tour(equipe2, taille2);

        tour++;
    }

    printf("\n🕛🕛🕛 LIMITE DE TOURS ATTEINTE - MATCH NUL ! 🕛🕛🕛\n");
 return NULL;

    
}

   
