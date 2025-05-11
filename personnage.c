#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "personnage.h"

Personnage chargerCombattant(const char* fichier, int id) {
    FILE* f = fopen(fichier, "r");
    if (!f) {
        printf("Erreur : fichier %s introuvable !\n", fichier);
        exit(1);
    }

    Personnage p;
    char ligne[256];
    for (int i = 0; i <= id; i++) {
        if (!fgets(ligne, sizeof(ligne), f) {
            printf("Erreur : combattant %d inexistant !\n", id);
            exit(1);
        }
    }

    sscanf(ligne, "%[^;];%[^;];%d;%d;%d;%d;%[^;];%d;%d",
           p.nom, p.type, &p.attaque, &p.defense, 
           &p.vitesse, &p.agilite, p.competence.nom,
           &p.competence.type, &p.competence.duree);

    p.PV_max = 100;
    p.PV = p.PV_max;
    p.bouclier_actif = 0;
    fclose(f);
    return p;
}

void afficherPersonnage(Personnage p) {
    printf("\nNom : %s\n", p.nom);
    printf("Type : %s\n", p.type);
    afficherPV(p);
    printf("Attaque : %d | Defense : %d\n", p.attaque, p.defense);
    printf("Agilite : %d | Vitesse : %d\n", p.agilite, p.vitesse);
    if (p.bouclier_actif) printf("[Bouclier actif]\n");
}

void afficherPV(Personnage p) {
    int bar_length = 20;
    int filled = (p.PV * bar_length) / p.PV_max;
    printf("PV : [");
    for (int i = 0; i < filled; i++) printf("█");
    for (int i = filled; i < bar_length; i++) printf(" ");
    printf("] %d/%d\n", p.PV, p.PV_max);
}
