#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "personnage.h"

typedef struct {
    char nom[50];               // Nom de la technique spéciale
    int type;                   // 0 = aucune, 1 = double attaque, 2 = bouclier, 3 = boisson magique
    int duree;                  // Nombre de tours pendant lesquels l’effet est actif
    int tours_recharge;         // 0 = non, 1 = oui
} TechniqueSpeciale;

typedef struct {
    char nom[50];
    char type[20];              // type doit être un tableau de char, pas un int
    int PV_max;
    int PV;
    int attaque;
    int defense;
    int agilite;
    int vitesse;
    int bouclier_actif;
    TechniqueSpeciale competence;
    int nb_techniques;
    int nb_effets;
} Personnage;

Personnage creerPersonnage(const char *nom, const char *type) {
    Personnage p;
    strcpy(p.nom, nom);
    strcpy(p.type, type);
    p.PV_max = 100;

    if (strcmp(type, "attaquant") == 0) {
        p.attaque = 30;
        p.defense = 10;
        p.vitesse = 20;
        p.agilite = 15;
    } else if (strcmp(type, "défenseur") == 0) {
        p.attaque = 15;
        p.defense = 30;
        p.vitesse = 10;
        p.agilite = 10;
    } else if (strcmp(type, "guérisseur") == 0) {
        p.attaque = 10;
        p.defense = 15;
        p.vitesse = 15;
        p.agilite = 20;
    } else {
        printf("Type inconnu, création d’un personnage par défaut.\n");
        p.attaque = 10;
        p.defense = 10;
        p.vitesse = 10;
        p.agilite = 10;
    }

    if (strcmp(p.type, "attaquant") == 0) {
        strcpy(p.competence.nom, "Double Attaque");
        p.competence.type = 1;
        p.competence.duree = 0;
        p.competence.tours_recharge = 0;
    } else if (strcmp(p.type, "défenseur") == 0) {
        strcpy(p.competence.nom, "Bouclier d'équipe");
        p.competence.type = 2;
        p.competence.duree = 1;
        p.competence.tours_recharge = 0;
    } else if (strcmp(p.type, "guérisseur") == 0) {
        strcpy(p.competence.nom, "Boisson magique");
        p.competence.type = 3;
        p.competence.duree = 0;
        p.competence.tours_recharge = 0;
    }

    p.PV = p.PV_max;
    p.nb_techniques = 0;
    p.nb_effets = 0;

    return p;
}

Personnage saisirPersonnage() {
    char nom[50];
    char type[20];

    printf("Entrez le nom du personnage : ");
    scanf("%49s", nom);

    printf("Entrez le type de personnage (attaquant / défenseur / guérisseur) : ");
    scanf("%19s", type);

    return creerPersonnage(nom, type);
}

void afficherPersonnage(Personnage p) {
    printf("Nom : %s\n", p.nom);
    printf("Type : %s\n", p.type);
    printf("PV : %d / %d\n", p.PV, p.PV_max);
    printf("Attaque : %d\n", p.attaque);
    printf("Défense : %d\n", p.defense);
    printf("Vitesse : %d\n", p.vitesse);
    printf("Agilité : %d\n", p.agilite);
}

