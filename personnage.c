#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "personnage.h"

// Crée un personnage selon son type : attaquant, défenseur ou guérisseur
Ninja creerPersonnage(const char *nom, const char *type) {
    Ninja p;
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

    p.PV = p.PV_max;

    // Initialisation vide des techniques et effets spéciaux
    p.nb_techniques = 0;
    p.nb_effets = 0;

    return p;
}
// Permet à l’utilisateur de saisir un personnage
Ninja saisirPersonnage() {
    char nom[50];
    char type[20];

    printf("Entrez le nom du personnage : ");
    scanf("%49s", nom);

    printf("Entrez le type de personnage (attaquant / défenseur / guérisseur) : ");
    scanf("%19s", type);

    return creerPersonnage(nom, type);
}


// Affiche les informations d’un personnage
void afficherPersonnage(Ninja p) {
    printf("Nom : %s\n", p.nom);
    printf("Type : %s\n", p.type);
    printf("PV : %d / %d\n", p.PV, p.PV_max);
    printf("Attaque : %d\n", p.attaque);
    printf("Défense : %d\n", p.defense);
    printf("Vitesse : %d\n", p.vitesse);
    printf("Agilité : %d\n", p.agilite);
}

// Vérifie si le personnage est encore en vie
int est_vivant(Ninja p) {
    return p.PV > 0;
}


