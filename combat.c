#include "combat.h"
#include "jeu.h"
#include <stdio.h>
void attaquer(Personnage *attaquant, Personnage *cible) {
    void attaquer(Personnage *attaquant, Personnage *cible) {
    // Coup critique (5% de chance)
    if (rand() % 100 < 5) {
        int degats = attaquant->attaque * 2 - (cible->defense / 2);
        printf("\033[1;33m"); // Jaune
        printf("💥 CRITIQUE ! %s écrase %s pour %d dégâts !\n", attaquant->nom, cible->nom, degats);
        printf("\033[0m");
    } 
    // Esquive (agilité)
    else if (rand() % 100 < cible->agilite) {
        printf("\033[1;36m"); // Cyan
        printf("🍃 %s esquive avec grâce !\n", cible->nom);
        printf("\033[0m");
    } 
    // Attaque normale
    else if {
    int degats = attaquant->attaque - (cible->defense / 2);  // Exemple de calcul
    
    if (cible->bouclier_actif > 0) {
        degats = degats / 2;  // Réduction de 50%
        printf("🛡️ Bouclier actif ! Dégâts réduits à %d\n", degats);
    }

    cible->PV -= degats;

    printf("%s inflige %d d�g�ts � %s !\n", attaquant->nom, degats, cible->nom);
}

void soigner(Personnage *guerisseur, Personnage *cible) {
    if (guerisseur == NULL || cible == NULL) {
        printf("Erreur : guérisseur ou cible invalide.\n");
        return;
    }

    if (strcmp(guerisseur->type, "guerisseur") != 0) {
        printf("%s n'est pas un guérisseur !\n", guerisseur->nom);
        return;
    }

    if (cible->PV <= 0) {
        printf("%s est mort et ne peut pas être soigné.\n", cible->nom);
        return;
    }

    if (guerisseur == cible) {
        printf("%s ne peut pas se soigner lui-même.\n", guerisseur->nom);
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
    printf("\n✨ %s invoque un BOUCLIER DIVIN (2 tours) !\n", defenseur->nom);
    for (int i = 0; i < taille; i++) {
        if (&equipe[i] != defenseur) {  // Ne s'applique pas au défenseur lui-même
            equipe[i].bouclier_actif = 2;  // Durée = 2 tours
            printf("-> %s est protégé (%d/2 tours)\n", equipe[i].nom, equipe[i].bouclier_actif);
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
        printf("%s doit encore attendre %d tours!\n", perso->nom, perso->competence.tours_recharge);
        return;
    }

    // Exécution de la compétence spéciale en fonction du type
    switch(perso->competence.type) {
        case 1: // Double attaque
            double_attaque(perso, cible);
            break;
        case 2: // Bouclier
            bouclier_equipe(perso, equipe, taille);
            // On active le bouclier pour la durée spécifiée
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

    // Mise en place de la recharge de la compétence
    perso->competence.tours_recharge = 2; // Recharge fixée à 2 tours
}
