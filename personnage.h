#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nom[50];
    char type[20];  // "attaquant", "defenseur", "guerisseur"
    int PV_max;
    int PV;
    int attaque;
    int defense;
    int agilite;
    int vitesse;
    int bouclier_actif;
    int nb_techniques;
    int nb_effets;
    
typedef struct {
        char nom[50];
        int type;       // 1=Attaque, 2=Bouclier, 3=Soin
        int duree;
        int tours_recharge;
    } competence;
} Personnage;

// Chargement depuis fichier
Personnage chargerCombattant(const char* filename, int id);

// Affichage
void afficherPersonnage(Personnage p);
void afficherPV(Personnage p);

// Sélection interactive
Personnage choisirPersoParType(const char* filename, const char* type);
void genererEquipeEnnemie(Personnage equipe[], const char* filename);

#endif
