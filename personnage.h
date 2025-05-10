
#ifndef PERSONNAGE_H
#define PERSONNAGE_H

// D�finition de la structure Ninja
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nom[50];
    int type;
    int duree;
    int tours_recharge;
} TechniqueSpeciale;

typedef struct {
    char nom[50];
    char type[20];
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


// D�clarations des fonctions
Personnage creerPersonnage(const char *nom, const char *type);
Personnage saisirPersonnage();
void afficherPersonnage(Personnage p);
// Fonction pour saisir un personnage

#endif
