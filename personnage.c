#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "personnage.h"

/**
 * Charge un personnage présent à une certaine ligne d'un fichier.
 *
 * @param fichier Nom du fichier texte contenant les combattants.
 * @param id Index du personnage à charger (0 = premier).
 * @return Une structure Personnage initialisée.
 */
Personnage chargerCombattant(const char* fichier, int id) {
    FILE* f = fopen(fichier, "r");
    if (!f) {
        printf("Erreur : fichier %s introuvable !\n", fichier);
        exit(1);
    }

    Personnage p;
    char ligne[256];
    for (int i = 0; i <= id; i++) {
        if (!fgets(ligne, sizeof(ligne), f)) {
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

/**
 * Affiche une liste de personnages disponibles d'un certain type (interface menu).
 *
 * @param persos Tableau de personnages.
 * @param count Nombre de personnages dans le tableau.
 * @param type Type de personnage (ex: "attaquant").
 */
void afficherMenuCombattants(Personnage persos[], int count, const char* type) {
    printf("\n=== Choix %s ===\n", type);
    for (int i = 0; i < count; i++) {
        printf("%d. %s (Att:%d Def:%d Vit:%d Agi:%d)\n", 
              i+1, persos[i].nom, persos[i].attaque, persos[i].defense,
              persos[i].vitesse, persos[i].agilite);
    }
}

/**
 * Permet au joueur de choisir un personnage d'un certain type.
 *
 * @param filename Nom du fichier contenant les personnages.
 * @param type Type de personnage à filtrer.
 * @return Le personnage choisi.
 */
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

/**
 * Génère une équipe aléatoire de 3 personnages pour l'IA.
 *
 * @param equipe Tableau de Personnages à remplir.
 * @param filename Nom du fichier source de personnages.
 */
void genererEquipeEnnemie(Personnage equipe[], const char* filename) {
    FILE* file = fopen(filename, "r");
    char line[256];
    int totalPersos = 0;
    while (fgets(line, sizeof(line), file)) totalPersos++;
    fclose(file);

    srand(time(NULL));
    for (int i = 0; i < 3; i++) {
        int id = rand() % totalPersos;
        equipe[i] = chargerCombattant(filename, id);
    }
}

/**
 * Affiche les statistiques d'un personnage (avec barre de PV).
 *
 * @param p Personnage à afficher.
 */
void afficherPersonnage(Personnage p) {
    printf("\nNom : %s\n", p.nom);
    printf("Type : %s\n", p.type);
    afficherPV(p);
    printf("Attaque : %d | Defense : %d\n", p.attaque, p.defense);
    printf("Agilite : %d | Vitesse : %d\n", p.agilite, p.vitesse);
    if (p.bouclier_actif) printf("[Bouclier actif]\n");
}

/**
 * Affiche une barre de PV pour le personnage donné.
 *
 * @param p Personnage cible.
 */
void afficherPV(Personnage p) {
    int bar_length = 20;
    int filled = (p.PV * bar_length) / p.PV_max;
    printf("PV : [");
    for (int i = 0; i < filled; i++) printf("█");
    for (int i = filled; i < bar_length; i++) printf(" ");
    printf("] %d/%d\n", p.PV, p.PV_max);
}
