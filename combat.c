#include "personnage.h"


void attaquer(Personnage *attaquant, Personnage *cible) {
    int degats = attaquant->attaque - cible->defense;
    if (cible->bouclier_actif) {
        printf("%s est protege par un bouclier ! Degats reduits.\n", cible->nom);
        degats /= 2;
        cible->bouclier_actif = 0;
    }

    if (degats < 1) degats = 1;

    cible->PV -= degats;
    if (cible->PV < 0) cible->PV = 0;

    printf("%s attaque %s et inflige %d degats !\n", attaquant->nom, cible->nom, degats);
}

void soigner(Personnage *guerisseur, Personnage *cible) {
    if (strcmp(guerisseur->type, "guerisseur") != 0) {
        printf("%s n'est pas un guerisseur !\n", guerisseur->nom);
        return;
    }

    int soin = guerisseur->agilite * 2;
    cible->PV += soin;
    if (cible->PV > cible->PV_max) cible->PV = cible->PV_max;

    printf("%s soigne %s pour %d PV !\n", guerisseur->nom, cible->nom, soin);
}

void double_attaque(Personnage *attaquant, Personnage *cible) {
    int degats1 = attaquant->attaque - (cible->defense / 2);
    if (degats1 < 1) degats1 = 1;
    cible->PV -= degats1;
    printf("%s attaque %s pour %d degats (1ere attaque)\n", attaquant->nom, cible->nom, degats1);

    int degats2 = attaquant->attaque - (cible->defense / 2);
    if (degats2 < 1) degats2 = 1;
    cible->PV -= degats2;
    printf("%s attaque %s pour %d degats (2eme attaque)\n", attaquant->nom, cible->nom, degats2);

    if (cible->PV < 0) cible->PV = 0;
}

void bouclier_equipe(Personnage *defenseur, Personnage equipe[], int taille) {
    printf("%s active un bouclier d'equipe !\n", defenseur->nom);
    for (int i = 0; i < taille; i++) {
        if (&equipe[i] != defenseur) {
            equipe[i].bouclier_actif = 1;
            printf("%s est maintenant protege !\n", equipe[i].nom);
        }
    }
}

void utiliser_competence(Personnage *perso, Personnage equipe[], int taille, Personnage *cible) {
    if (perso->competence.tours_recharge > 0) {
        printf("Competence en recharge (%d tours restants)\n", perso->competence.tours_recharge);
        return;
    }

    if (strcmp(perso->type, "attaquant") == 0) {
        double_attaque(perso, cible);
    } 
    else if (strcmp(perso->type, "defenseur") == 0) {
        bouclier_equipe(perso, equipe, taille);
    } 
    else if (strcmp(perso->type, "guerisseur") == 0) {
        soigner(perso, cible);
    }

    perso->competence.tours_recharge = 2;
}
