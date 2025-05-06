#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "personnage.h"


void initialiser_jeu() {
    // Créer équipe 1
    Ninja equipe1[3];
    printf("Création de l'équipe 1 :\n");
    for (int i = 0; i < 3; i++) {
        printf("Création du personnage %d :\n", i + 1);
        equipe1[i] = saisir_personnage();  // Appel à la fonction de saisie
    }

    // Créer équipe 2
    Ninja equipe2[3];
    printf("Création de l'équipe 2 :\n");
    for (int i = 0; i < 3; i++) {
        printf("Création du personnage %d :\n", i + 1);
        equipe2[i] = saisir_personnage();  // Appel à la fonction de saisie
    }

    // Affichage des équipes créées
    printf("Équipe 1 :\n");
    for (int i = 0; i < 3; i++) {
        afficherPersonnage(equipe1[i]);
    }

    printf("Équipe 2 :\n");
    for (int i = 0; i < 3; i++) {
        afficherPersonnage(equipe2[i]);
    }
}


int equipe_a_guerisseur(Ninja equipe[], int taille_equipe) {
    for (int i = 0; i < taille_equipe; i++) {
        if (strcmp(equipe[i].type, "guérisseur") == 0) {
            return 1; // Il y a un guérisseur
        }
    }
    return 0; // Pas de guérisseur
}
void jouer_partie() {
    while (1) {
        printf("\n========== Nouveau Tour ==========\n");

        int choix, index_attaquant, perso_a_attaquer, perso_a_soigner;

        // ==== TOUR DE L'ÉQUIPE 1 ====
        printf("\n--- Tour de l'Équipe 1 ---\n");

        if (equipe_a_guerisseur(equipe1, 3)) {
            printf("Choisissez une action :\n");
            printf("1. Attaquer\n");
            printf("2. Soigner\n");
            printf("3. Utiliser une compétence spéciale\n");
            printf("Votre choix : ");
            while (scanf("%d", &choix) != 1 || (choix < 1 || choix > 3)) {
                while (getchar() != '\n');
                printf("Choix invalide. Veuillez choisir 1, 2 ou 3 : ");
            }
        } else {
            printf("Choisissez une action :\n");
            printf("1. Attaquer\n");
            printf("Votre choix : ");
            while (scanf("%d", &choix) != 1 || choix != 1) {
                while (getchar() != '\n');
                printf("Choix invalide. Veuillez choisir 1 : ");
            }
            printf("Vous n'avez pas de guérisseur, option 'Soigner' désactivée.\n");
        }

        printf("Quel ninja de votre équipe voulez-vous utiliser ? (1-3) : ");
        scanf("%d", &index_attaquant);
        Ninja *joueur_attaquant = &equipe1[index_attaquant - 1];

        // Traitement de l'action choisie
        if (choix == 1) {
            // Attaque
            printf("Qui voulez-vous attaquer ? (1-3) :\n");
            for (int i = 0; i < 3; i++) {
                printf("%d. ", i + 1);
                afficherPersonnage(equipe2[i]);
            }
            scanf("%d", &perso_a_attaquer);
            Ninja *cible = &equipe2[perso_a_attaquer - 1];
            attaquer(joueur_attaquant, cible);
        } else if (choix == 2) {
            // Soigner
            printf("Qui voulez-vous soigner ? (1-3) :\n");
            for (int i = 0; i < 3; i++) {
                printf("%d. ", i + 1);
                afficherPersonnage(equipe1[i]);
            }
            scanf("%d", &perso_a_soigner);
            Ninja *cible_soin = &equipe1[perso_a_soigner - 1];
            soigner(joueur_attaquant, cible_soin);
        } else if (choix == 3) {
            // Utilisation de la technique spéciale
            if (strcmp(joueur_attaquant->type, "attaquant") == 0) {
                printf("%s utilise la technique spéciale 'Double Attaque'!\n", joueur_attaquant->nom);
                double_attaque(joueur_attaquant);
            } else if (strcmp(joueur_attaquant->type, "defenseur") == 0) {
                printf("%s utilise la technique spéciale 'Bouclier'!\n", joueur_attaquant->nom);
                bouclier(joueur_attaquant);
            } else if (strcmp(joueur_attaquant->type, "guerisseur") == 0) {
                printf("%s utilise la technique spéciale 'Boisson Magique'!\n", joueur_attaquant->nom);
                boisson_magique(joueur_attaquant, joueur_attaquant);  // Guérisseur peut se soigner lui-même ou un autre
            } else {
                printf("Aucune compétence spéciale disponible pour ce personnage.\n");
            }
        }

        // ==== TOUR DE L'ÉQUIPE 2 ====
        printf("\n--- Tour de l'Équipe 2 ---\n");

        if (equipe_a_guerisseur(equipe2, 3)) {
            printf("Choisissez une action :\n");
            printf("1. Attaquer\n");
            printf("2. Soigner\n");
            printf("3. Utiliser une compétence spéciale\n");
            printf("Votre choix : ");
            while (scanf("%d", &choix) != 1 || (choix < 1 || choix > 3)) {
                while (getchar() != '\n');
                printf("Choix invalide. Veuillez choisir 1, 2 ou 3 : ");
            }
        } else {
            printf("Choisissez une action :\n");
            printf("1. Attaquer\n");
            printf("Votre choix : ");
            while (scanf("%d", &choix) != 1 || choix != 1) {
                while (getchar() != '\n');
                printf("Choix invalide. Veuillez choisir 1 : ");
            }
            printf("Vous n'avez pas de guérisseur, option 'Soigner' désactivée.\n");
        }

        printf("Quel ninja de votre équipe voulez-vous utiliser ? (1-3) : ");
        scanf("%d", &index_attaquant);
        joueur_attaquant = &equipe2[index_attaquant - 1];

        // Traitement de l'action choisie pour l'équipe 2
        if (choix == 1) {
            // Attaque
            printf("Qui voulez-vous attaquer ? (1-3) :\n");
            for (int i = 0; i < 3; i++) {
                printf("%d. ", i + 1);
                afficherPersonnage(equipe1[i]);
            }
            scanf("%d", &perso_a_attaquer);
            Ninja *cible = &equipe1[perso_a_attaquer - 1];
            attaquer(joueur_attaquant, cible);
        } else if (choix == 2) {
            // Soigner
            printf("Qui voulez-vous soigner ? (1-3) :\n");
            for (int i = 0; i < 3; i++) {
                printf("%d. ", i + 1);
                afficherPersonnage(equipe2[i]);
            }
            scanf("%d", &perso_a_soigner);
            Ninja *cible_soin = &equipe2[perso_a_soigner - 1];
            soigner(joueur_attaquant, cible_soin);
        } else if (choix == 3) {
            // Utilisation de la technique spéciale
            if (strcmp(joueur_attaquant->type, "attaquant") == 0) {
                printf("%s utilise la technique spéciale 'Double Attaque'!\n", joueur_attaquant->nom);
                double_attaque(joueur_attaquant);
            } else if (strcmp(joueur_attaquant->type, "defenseur") == 0) {
                printf("%s utilise la technique spéciale 'Bouclier'!\n", joueur_attaquant->nom);
                bouclier(joueur_attaquant);
            } else if (strcmp(joueur_attaquant->type, "guerisseur") == 0) {
                printf("%s utilise la technique spéciale 'Boisson Magique'!\n", joueur_attaquant->nom);
                boisson_magique(joueur_attaquant, joueur_attaquant);  // Guérisseur peut se soigner lui-même ou un autre
            } else {
                printf("Aucune compétence spéciale disponible pour ce personnage.\n");
            }
        }

        // Vérification de la victoire après chaque tour
        if (verifier_victoire() == 1) {
            printf("L'équipe 1 a gagné!\n");
            break;
        }
        if (verifier_victoire() == 2) {
            printf("L'équipe 2 a gagné!\n");
            break;
        }
    }
}


