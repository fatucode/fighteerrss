#include "personnage.h"


void attaquer(Ninja *attaquant, Ninja *cible) {
    int degats = attaquant->attaque - cible->defense;
    if (degats < 0) degats = 0;

    cible->PV -= degats;

    if (cible->PV < 0) {
        cible->PV = 0;
    }

    printf("%s attaque %s et lui inflige %d dégâts !\n", attaquant->nom, cible->nom, degats);
    if (cible->bouclier_actif==1 ) {
    printf("%s est protégé par un bouclier ! Dégâts réduits.\n", cible->nom);
    degats /= 2;
    cible->bouclier_actif = 0; // L’effet ne dure qu’un tour
}

}



void soigner(Ninja *guerisseur, Ninja *cible) {
    if (strcmp(guerisseur->type, "guérisseur") != 0) {
        printf("%s n’est pas un guérisseur et ne peut pas soigner !\n", guerisseur->nom);
        return;
    }

    int soin = guerisseur->agilite * 2;
    cible->PV += soin;

    if (cible->PV > cible->PV_max) {
        cible->PV = cible->PV_max;
    }

    printf("%s soigne %s et lui rend %d PV !\n", guerisseur->nom, cible->nom, soin);
}


void double_attaque(Ninja *attaquant, Ninja *cible){

    // Calcul des dégâts de la première attaque
    int degats1 = attaquant->attaque - cible->defense;
    if (degats1 < 0) degats1 = 0;
    cible->PV -= degats1;  // Applique les dégâts à la cible
    printf("%s attaque %s pour %d dégâts (1ère attaque)\n", attaquant->nom, cible->nom, degats1);

    // Calcul des dégâts de la deuxième attaque
    int degats2 = attaquant->attaque - cible->defense;
    if (degats2 < 0) degats2 = 0;  // Empêcher les dégâts négatifs
    cible->PV -= degats2;  // Applique les dégâts à la cible
    printf("%s attaque %s pour %d dégâts (2ème attaque)\n", attaquant->nom, cible->nom, degats2);
}

void bouclier_equipe(Ninja *equipe[], int taille) {
    printf("Le défenseur utilise un bouclier magique sur toute l’équipe !\n");
    for (int i = 0; i < taille; i++) {
        equipe[i]->bouclier_actif = 1;
        printf("%s est maintenant protégé par un bouclier temporaire !\n", equipe[i]->nom);
    }
}

void boisson_magique(Ninja *soigneur, Ninja *cible) {
    printf("%s utilise sa potion magique !\n", soigneur->nom);

    if (strcmp(soigneur->type, "guérisseur") != 0) {
        printf("%s n’est pas un guérisseur et ne peut pas utiliser la potion magique !\n", soigneur->nom);
        return;
    }

    cible->PV += 30;


    if (cible->PV > cible->PV_max) {
        cible->PV = cible->PV_max;
    }

    printf("%s récupère des PV grâce à la potion magique ! PV actuels : %d/%d\n", cible->nom, cible->PV, cible->PV_max);
}










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
