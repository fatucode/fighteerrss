#include <stdio.h>
#include <string.h>
#include "personnage.h"

// Fonction d’attaque
void attaquer(Ninja* attaquant, Ninja* cible) {
    if (!est_vivant(*attaquant) || !est_vivant(*cible)) {
        printf("Attaque invalide (personnage mort).\n");
        return;
    }

    int degats = attaquant->attaque - (cible->defense / 2);
    if (degats < 0) degats = 0;

    cible->PV -= degats;
    if (cible->PV < 0) cible->PV = 0;

    printf("%s attaque %s et inflige %d points de dégâts !\n", attaquant->nom, cible->nom, degats);
}

// Fonction de soin
void soigner(Ninja* guerisseur, Ninja* cible) {
    if (!est_vivant(*guerisseur) || !est_vivant(*cible)) {
        printf("Soin invalide (personnage mort).\n");
        return;
    }

    int soin = guerisseur->agilite * 2;
    cible->PV += soin;
    if (cible->PV > cible->PV_max) {
        cible->PV = cible->PV_max;
    }

    printf("%s soigne %s et lui rend %d PV !\n", guerisseur->nom, cible->nom, soin);
}

// Tour de combat simplifié (1 tour pour chaque ninja vivant)
void tourDeCombat(Ninja* equipe1, int taille1, Ninja* equipe2, int taille2) {
    for (int i = 0; i < taille1; i++) {
        if (!est_vivant(equipe1[i])) continue;

        // Trouver une cible vivante dans l'équipe ennemie
        for (int j = 0; j < taille2; j++) {
            if (est_vivant(equipe2[j])) {
                if (strcmp(equipe1[i].type, "guérisseur") == 0) {
                    // Cherche un allié blessé
                    for (int k = 0; k < taille1; k++) {
                        if (est_vivant(equipe1[k]) && equipe1[k].PV < equipe1[k].PV_max) {
                            soigner(&equipe1[i], &equipe1[k]);
                            break;
                        }
                    }
                } else {
                    attaquer(&equipe1[i], &equipe2[j]);
                }
                break;
            }
        }
    }
}
