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

void afficherMenuCombattants(Personnage persos[], int count, const char* type) {
    printf("\n=== Choix %s ===\n", type);
    for (int i = 0; i < count; i++) {
        printf("%d. %s (Att:%d Def:%d Vit:%d Agi:%d)\n", 
              i+1, persos[i].nom, persos[i].attaque, persos[i].defense,
              persos[i].vitesse, persos[i].agilite);
    }
}

Personnage choisirPersoParType(const char* filename, const char* type) {
    FILE* file = fopen(filename, "r");
    Personnage persos[3]; // Max 3 persos par type
    int count = 0;
    char line[256];

    while (fgets(line, sizeof(line), file) && count < 3) {
        Personnage p;
        sscanf(line, "%[^;];%[^;];%d;%d;%d;%d;%[^;];%d;%d",
               p.nom, p.type, &p.attaque, &p.defense,
               &p.vitesse, &p.agilite, p.competence.nom,
               &p.competence.type, &p.competence.duree);

        if (strcmp(p.type, type) == 0) {
            persos[count++] = p;
        }
    }
    fclose(file);

    afficherMenuCombattants(persos, count, type);

    int choix;
    do {
        printf("Choisissez votre %s (1-%d): ", type, count);
        scanf("%d", &choix);
    } while (choix < 1 || choix > count);

    return persos[choix-1];
}

void genererEquipeEnnemie(Personnage equipe[], const char* filename) {
    // Compter le nombre total de persos
    FILE* file = fopen(filename, "r");
    int totalPersos = 0;
    while (fgets(line, sizeof(line), file) totalPersos++;
    fclose(file);

    // Choisir 3 persos aléatoires
    srand(time(NULL));
    for (int i = 0; i < 3; i++) {
        int id = rand() % totalPersos;
        equipe[i] = chargerCombattant(filename, id);
    }
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
