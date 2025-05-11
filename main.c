#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "jeu.h"
#include "combat.h"
#include "personnage.h"

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

int main() {
    printf("=== NINJA COMBAT ===\n\n");

    Personnage equipe1[3], equipe2[3];

    // Équipe joueur
    printf("\n=== Composition équipe joueur ===\n");
    equipe1[0] = choisirPersoParType("combattants.txt", "attaquant");
    equipe1[1] = choisirPersoParType("combattants.txt", "defenseur");
    equipe1[2] = choisirPersoParType("combattants.txt", "guerisseur");

    // Équipe ennemie aléatoire
    genererEquipeEnnemie(equipe2, "combattants.txt");

    // Combat
    Personnage* vainqueurs = jouer_partie(equipe1, 3, equipe2, 3);
    printf("\n=== L'équipe de %s a gagné ! ===\n", vainqueurs[0].nom);

    return 0;
}
