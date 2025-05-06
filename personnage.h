
#ifndef PERSONNAGE_H
#define PERSONNAGE_H

// Définition de la structure Ninja
typedef struct {
    char nom[50];
    char type[20];
    int PV_max;
    int PV;
    int attaque;
    int defense;
    int vitesse;
    int agilite;
    int nb_techniques;
    int nb_effets;
    // Effet temporaire (ex. : bouclier ou soin actif pour ce tour)
    int bouclier_actif;   // 1 si actif, 0 sinon
    int soin_ameliore;    // 1 si effet boisson magique actif
} Ninja;
} Ninja;

// Déclarations des fonctions
Ninja creerPersonnage(const char *nom, const char *type);
void afficherPersonnage(Ninja p);
int est_vivant(Ninja p);
Ninja saisirPersonnage();  // Fonction pour saisir un personnage

#endif
