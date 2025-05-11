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
    
struct {
        char nom[50];
        int type;       // 1=Attaque, 2=Bouclier, 3=Soin
        int duree;
        int tours_recharge;
    } competence;
} Personnage;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
Personnage creerPersonnage(const char *nom, const char *type) ;
Personnage saisirPersonnage() ;
void afficherPersonnage(Personnage p);
