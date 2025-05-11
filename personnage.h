#ifndef PERSONNAGE_H
#define PERSONNAGE_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nom[50];
    char type[20]; // "attaquant", "defenseur", "guerisseur"
    int PV;
    int PV_max;
    int attaque;
    int vitesse;
    int agilite;
    int nb_techniques;
    int nb_effets;
    int defense;
    int bouclier_actif;
    int nb_resurrections; 


    struct {
        char nom[50];
        int nb_resurrections; 
        int type;       // 1=Attaque, 2=Bouclier, 3=Soin
        int duree;
        int tours_recharge;
    } competence;

    

} Personnage;


Personnage creerPersonnage(const char *nom, const char *type) ;
Personnage saisirPersonnage() ;
void afficherPersonnage(Personnage p);
void afficherPV(Personnage p);
#endif
