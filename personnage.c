#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "personnage.h"

/**
 * @brief Crée un nouveau personnage avec les caractéristiques de base
 * @param nom Le nom du personnage
 * @param type Le type de personnage ("attaquant", "defenseur" ou "guerisseur")
 * @return Personnage Le personnage initialisé
 * 
 * @details Initialise les statistiques de base et les compétences spéciales
 * selon le type du personnage. Gère également l'allocation des PV max.
 */
Personnage creerPersonnage(const char *nom, const char *type) {
    Personnage p;
    
    // Copie sécurisée du nom et du type
    strncpy(p.nom, nom, sizeof(p.nom) - 1);
    p.nom[sizeof(p.nom) - 1] = '\0';
    
    strncpy(p.type, type, sizeof(p.type) - 1);
    p.type[sizeof(p.type) - 1] = '\0';

    // Initialisation des statistiques de base selon le type
    if (strcmp(type, "attaquant") == 0) {
        p.attaque = 30;   // Forte attaque
        p.defense = 10;   // Faible défense
        p.vitesse = 20;   // Vitesse moyenne
        p.agilite = 15;   // Agilité moyenne
    }
    else if (strcmp(type, "defenseur") == 0) {
        p.attaque = 15;   // Attaque moyenne
        p.defense = 30;   // Forte défense
        p.vitesse = 10;   // Faible vitesse
        p.agilite = 10;   // Faible agilité
    }
    else if (strcmp(type, "guerisseur") == 0) {
        p.attaque = 10;   // Faible attaque
        p.defense = 15;   // Défense moyenne
        p.vitesse = 15;   // Vitesse moyenne
        p.agilite = 20;   // Haute agilité
    }

    // Initialisation des compétences spéciales
    if (strcmp(type, "attaquant") == 0) {
        strncpy(p.competence.nom, "Double Attaque", sizeof(p.competence.nom) - 1);
        p.competence.type = 1;               // Type attaque
        p.competence.duree = 0;              // Effet immédiat
        p.competence.tours_recharge = 0;     // Pas de recharge
        p.competence.nb_resurrections = 0;   // Non applicable
    }
    else if (strcmp(type, "defenseur") == 0) {
        strncpy(p.competence.nom, "Bouclier d'équipe", sizeof(p.competence.nom) - 1);
        p.competence.type = 2;               // Type défense
        p.competence.duree = 1;              // Durée d'un tour
        p.competence.tours_recharge = 0;     // Pas de recharge
        p.competence.nb_resurrections = 0;   // Non applicable
    }
    else if (strcmp(type, "guerisseur") == 0) {
        strncpy(p.competence.nom, "Résurrection", sizeof(p.competence.nom) - 1);
        p.competence.type = 3;               // Type soin
        p.competence.duree = 0;              // Effet immédiat
        p.competence.tours_recharge = 0;     // Pas de recharge
        p.competence.nb_resurrections = 3;   // 3 utilisations max
    }

    // Initialisation des points de vie
    p.PV_max = 100;
    p.PV = p.PV_max;
    
    // Initialisation des autres attributs
    p.nb_techniques = 0;
    p.nb_effets = 0;
    p.bouclier_actif = 0;

    return p;
}

/**
 * @brief Permet à l'utilisateur de saisir les informations d'un nouveau personnage
 * @return Personnage Le personnage créé
 * 
 * @details Demande à l'utilisateur de saisir le nom et le type du personnage,
 * avec validation du type saisi. Gère les erreurs de saisie.
 */
Personnage saisirPersonnage() {
    char nom[50];
    char type[20];
    int type_valide = 0;

    // Saisie du nom
    printf("Entrez le nom du personnage : ");
    scanf("%49s", nom);

    // Saisie et validation du type
    while (!type_valide) {
        printf("Entrez le type (attaquant/defenseur/guerisseur) : ");
        scanf("%19s", type);

        // Vérification du type saisi
        if (strcmp(type, "attaquant") == 0 ||
            strcmp(type, "defenseur") == 0 ||
            strcmp(type, "guerisseur") == 0) {
            type_valide = 1;
        } else {
            printf("Type invalide ! Les types valides sont :\n");
            printf("- attaquant\n- defenseur\n- guerisseur\n");
        }
    }

    return creerPersonnage(nom, type);
}

/**
 * @brief Affiche les caractéristiques détaillées d'un personnage
 * @param p Le personnage à afficher
 * 
 * @details Affiche le nom, type, PV, statistiques et état du bouclier
 */
void afficherPersonnage(Personnage p) {
    printf("\n=== FICHE PERSONNAGE ===\n");
    printf("Nom : %s\n", p.nom);
    printf("Type : %s\n", p.type);
    printf("PV : %d/%d\n", p.PV, p.PV_max);
    printf("Attaque : %d | Defense : %d\n", p.attaque, p.defense);
    printf("Agilite : %d | Vitesse : %d\n", p.agilite, p.vitesse);
    printf("Competence speciale : %s\n", p.competence.nom);
    
    if (p.competence.type == 3) { // Guérisseur
        printf("Resurrections restantes : %d\n", p.competence.nb_resurrections);
    }
    
    if (p.bouclier_actif) {
        printf("[Bouclier actif]\n");
    }
    printf("=======================\n");
}

/**
 * @brief Affiche une barre de vie visuelle pour le personnage
 * @param p Le personnage dont on veut afficher les PV
 * 
 * @details Affiche une barre de 20 caractères représentant
 * le pourcentage de PV restants
 */
void afficherPV(Personnage p) {
    const int bar_length = 20;
    int filled = (p.PV * bar_length) / p.PV_max;
    
    printf("PV : [");
    // Partie remplie de la barre
    for (int i = 0; i < filled; i++) printf("█");
    // Partie vide de la barre
    for (int i = filled; i < bar_length; i++) printf(" ");
    printf("] %d/%d\n", p.PV, p.PV_max);
}
