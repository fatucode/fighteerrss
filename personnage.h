#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#define MAX_NOM 50
#define MAX_TYPE 20

typedef struct {
    char nom[MAX_NOM];
    char type[MAX_TYPE];
    int PV;
    int PV_max;
    int attaque;
    int defense;
    int vitesse;
    int agilite;
    int nb_techniques;
    int nb_effets;
    // Tu peux ajouter des tableaux de techniques/effets plus tard
} Ninja;

Ninja creerPersonnage(const char *nom, const char *type);
void afficherPersonnage(Ninja p);
int est_vivant(Ninja p);

#endif
