#include "combat.h"
#include "jeu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

/**
 * @brief Effectue une attaque entre deux personnages avec gestion des critiques et esquives
 * @param attaquant Pointeur vers le personnage attaquant
 * @param cible Pointeur vers le personnage cible
 * 
 * @details Cette fonction gère :
 * - La vérification des personnages valides
 * - Le calcul de chance d'esquive basé sur l'agilité
 * - Les coups critiques aléatoires (10% de chance)
 * - La réduction des dégâts par les boucliers
 * - L'application des dégâts avec limites
 */
void attaquer(Personnage *attaquant, Personnage *cible) {
    // Vérification des paramètres d'entrée
    if (attaquant == NULL || cible == NULL || attaquant->PV <= 0 || cible->PV <= 0) {
        return;
    }

    // 1. Gestion de l'esquive
    if (cible->agilite > attaquant->agilite && (rand() % 100) < (cible->agilite - attaquant->agilite)) {
        printf("✨ %s esquive l'attaque de %s !\n", cible->nom, attaquant->nom);
        return;
    }

    // 2. Calcul des dégâts de base
    int degats = attaquant->attaque - (cible->defense / 3);
    
    // 3. Gestion des coups critiques (10% de chance)
    if ((rand() % 10) == 0) {
        degats *= 2;
        printf("💥 COUP CRITIQUE ! ");
    }

    // 4. Réduction des dégâts par bouclier (-30%)
    if (cible->bouclier_actif > 0) {
        degats = (degats * 70) / 100;
        printf("🛡️ Bouclier actif (-30%%) | ");
    }

    // 5. Limitation des dégâts entre 1 et PV max
    degats = (degats < 1) ? 1 : (degats > cible->PV_max) ? cible->PV_max : degats;

    // Application des dégâts
    cible->PV -= degats;
    printf("%s attaque %s : -%d PV | PV restants: %d/%d\n", 
           attaquant->nom, cible->nom, degats, cible->PV, cible->PV_max);

    // Gestion du KO
    if (cible->PV <= 0) {
        printf("💀 %s est mis K.O. !\n", cible->nom);
    }
}

/**
 * @brief Effectue un soin sur un personnage cible
 * @param guerisseur Pointeur vers le personnage soignant
 * @param cible Pointeur vers le personnage à soigner
 * 
 * @details Contrôles effectués :
 * - Validité des pointeurs
 * - Vérification que le soigneur est bien un guérisseur
 * - Vérification que la cible n'est pas morte
 * - Empêche l'auto-soin
 */
void soigner(Personnage *guerisseur, Personnage *cible) {
    // Vérifications préalables
    if (!guerisseur || !cible) {
        printf("Erreur : personnage(s) invalide(s).\n");
        return;
    }
    
    if (strcmp(guerisseur->type, "guerisseur") != 0) {
        printf("%s n'a pas la compétence de soin !\n", guerisseur->nom);
        return;
    }
    
    if (cible->PV <= 0) {
        printf("%s est mort et ne peut être soigné.\n", cible->nom);
        return;
    }
    
    if (guerisseur == cible) {
        printf("%s ne peut pas se soigner lui-même.\n", guerisseur->nom);
        return;
    }

    // Calcul et application du soin
    int soin = guerisseur->agilite * 2;
    cible->PV = (cible->PV + soin > cible->PV_max) ? cible->PV_max : cible->PV + soin;
    
    printf("%s soigne %s : +%d PV | PV: %d/%d\n", 
           guerisseur->nom, cible->nom, soin, cible->PV, cible->PV_max);
}

/**
 * @brief Effectue une double attaque (compétence spéciale)
 * @param attaquant Pointeur vers le personnage attaquant
 * @param cible Pointeur vers la cible
 */
void double_attaque(Personnage *attaquant, Personnage *cible) {
    printf("%s utilise DOUBLE ATTAQUE !\n", attaquant->nom);
    
    for (int i = 1; i <= 2; i++) {
        int degats = attaquant->attaque - (cible->defense / 2);
        degats = (degats < 1) ? 1 : degats;  // Dégâts minimum de 1
        
        cible->PV -= degats;
        printf("Attaque %d : %s → %s (-%d PV)\n", 
               i, attaquant->nom, cible->nom, degats);
    }
    
    // Correction PV négatifs
    if (cible->PV < 0) cible->PV = 0;
}

/**
 * @brief Active un bouclier pour toute l'équipe (compétence spéciale)
 * @param defenseur Pointeur vers le personnage défenseur
 * @param equipe Tableau des personnages de l'équipe
 * @param taille Nombre de personnages dans l'équipe
 */
void bouclier_equipe(Personnage *defenseur, Personnage equipe[], int taille) {
    printf("\n✨ %s active BOUCLIER D'EQUIPE (2 tours) !\n", defenseur->nom);
    
    for (int i = 0; i < taille; i++) {
        if (&equipe[i] != defenseur) {  // Ne s'applique pas au lanceur
            equipe[i].bouclier_actif = 2;
            printf("-> %s bénéficie du bouclier\n", equipe[i].nom);
        }
    }
}

/**
 * @brief Ressuscite un membre de l'équipe (compétence spéciale)
 * @param guerisseur Pointeur vers le personnage guérisseur
 * @param equipe Tableau des personnages de l'équipe
 * @param taille Nombre de personnages dans l'équipe
 * @return bool true si résurrection réussie, false sinon
 */
bool ressusciter(Personnage *guerisseur, Personnage equipe[], int taille) {
    int morts[taille];
    int nb_morts = 0;

    for (int i = 0; i < taille; i++) {
        if (equipe[i].PV <= 0) {
            morts[nb_morts++] = i;
        }
    }

    if (nb_morts == 0) {
        printf("\nℹ️ Aucun allié à ressusciter.\n");
        return false;
    }

    printf("\n🧟 Alliés K.O. :\n");
    for (int i = 0; i < nb_morts; i++) {
        printf("%d. %s\n", i + 1, equipe[morts[i]].nom);
    }

    int choix;
    do {
        printf("\nChoix du personnage à ressusciter (1-%d) : ", nb_morts);
        if (scanf("%d", &choix) != 1) {
            printf("❌ Entrée invalide.\n");
            while(getchar() != '\n');
        }
    } while (choix < 1 || choix > nb_morts);

    int index = morts[choix - 1];
    equipe[index].PV = equipe[index].PV_max / 2;
    printf("\n💖 %s ressuscite %s !\n", guerisseur->nom, equipe[index].nom);
    
    return true;
}

/**
 * @brief Utilise la compétence spéciale d'un personnage
 * @param perso Pointeur vers le personnage
 * @param equipe Tableau de l'équipe alliée
 * @param taille Taille de l'équipe
 * @param cible Pointeur vers la cible (si applicable)
 */
void utiliser_competence(Personnage *perso, Personnage equipe[], int taille, Personnage *cible) {
    if (perso->competence.tours_recharge > 0) {
        printf("%s doit attendre %d tour(s) avant de réutiliser sa compétence.\n",
               perso->nom, perso->competence.tours_recharge);
        return;
    }

    switch(perso->competence.type) {
        case 1:  // Attaquant
            double_attaque(perso, cible);
            break;
            
        case 2:  // Défenseur
            bouclier_equipe(perso, equipe, taille);
            break;
            
        case 3:  // Guérisseur - Résurrection
            if (perso->competence.nb_resurrections <= 0) {
                printf("\n⚠️ %s a épuisé ses résurrections !\n", perso->nom);
                return;
            }

            // Gérer la résurrection
            ressusciter(perso, equipe, taille);
            perso->competence.nb_resurrections--;  // Réduire le nombre de résurrections
            break;
    }

    perso->competence.tours_recharge = 2;  // Définir le temps de recharge
}
