#include "combat.h"
#include "jeu.h"
#include <stdio.h>
void attaquer(Personnage *attaquant, Personnage *cible) {
    int degats = (attaquant->attaque * (10 + attaquant->agilite)) / (10 + cible->defense);

    if (cible->bouclier_actif) {
        degats /= 2;
        printf("Bouclier activ� ! ");
    }

    degats = (degats < 1) ? 1 : degats;
    cible->PV -= degats;

    printf("%s inflige %d d�g�ts � %s !\n", attaquant->nom, degats, cible->nom);
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
void boisson_magique(Personnage* soigneur, Personnage* cible) {
    if (strcmp(soigneur->type, "guerisseur") != 0) {
        printf("%s n'est pas un guerisseur !\n", soigneur->nom);
        return;
    }

    int soin = 30; // ou soigneur->agilite * 2 selon ton choix
    cible->PV += soin;
    
    if (cible->PV > cible->PV_max) {
        cible->PV = cible->PV_max;
    }

    printf("%s prepare une boisson magique pour %s (+%d PV) !\n", 
           soigneur->nom, cible->nom, soin);
}
void utiliser_competence(Personnage *perso, Personnage equipe[], int taille, Personnage *cible) {
    if (perso->competence.tours_recharge > 0) {
        printf("%s doit encore attendre %d tours!\n",
              perso->nom, perso->competence.tours_recharge);
        return;
    }

    switch(perso->competence.type) {
        case 1: // Double attaque
            double_attaque(perso, cible);
            break;

        case 2: // Bouclier
            bouclier_equipe(perso, equipe, taille);
            // On active le bouclier pour la dur�e sp�cifi�e
            for (int i = 0; i < taille; i++) {
                if (&equipe[i] != perso) {
                    equipe[i].bouclier_actif = perso->competence.duree;
                }
            }
            break;

        case 3: // Soin
            boisson_magique(perso, cible);
            break;
    }

    perso->competence.tours_recharge = 2; // Recharge fix�e � 2 tours
}

