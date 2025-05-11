#include "combat.h"
#include "jeu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * Effectue une attaque entre deux personnages avec possibilité de coup critique ou esquive.
 * @param attaquant Le personnage qui attaque.
 * @param cible Le personnage ciblé.
 */
void attaquer(Personnage *attaquant, Personnage *cible) {
    // Coup critique (5%)
    if (rand() % 100 < 5) {
        int degats = attaquant->attaque * 2 - (cible->defense / 2);
        printf("\033[1;33m");
        printf("💥 CRITIQUE ! %s écrase %s pour %d dégâts !\n", attaquant->nom, cible->nom, degats);
        printf("\033[0m");
        cible->PV -= degats;
        return;
    }

    // Esquive
    if (rand() % 100 < cible->agilite) {
        printf("\033[1;36m");
        printf("🍃 %s esquive avec grâce !\n", cible->nom);
        printf("\033[0m");
        return;
    }

    // Attaque normale
    int degats = attaquant->attaque - (cible->defense / 2);
    if (cible->bouclier_actif > 0) {
        degats /= 2;
        printf("🛡️ Bouclier actif ! Dégâts réduits à %d\n", degats);
    }
    cible->PV -= degats;
    printf("%s inflige %d dégâts à %s !\n", attaquant->nom, degats, cible->nom);
}

/**
 * Soigne un allié avec un personnage de type "guerisseur".
 * @param guerisseur Le personnage qui soigne.
 * @param cible La cible à soigner.
 */
void soigner(Personnage *guerisseur, Personnage *cible) {
    if (!guerisseur || !cible) {
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

/**
 * Effectue une double attaque sur une cible.
 * @param attaquant Le personnage attaquant.
 * @param cible La cible visée.
 */
void double_attaque(Personnage *attaquant, Personnage *cible) {
    for (int i = 1; i <= 2; i++) {
        int degats = attaquant->attaque - (cible->defense / 2);
        if (degats < 1) degats = 1;
        cible->PV -= degats;
        printf("%s attaque %s pour %d dégâts (%dème attaque)\n", attaquant->nom, cible->nom, degats, i);
    }
    if (cible->PV < 0) cible->PV = 0;
}

/**
 * Applique un bouclier temporaire à toute l'équipe sauf au lanceur.
 * @param defenseur Le personnage qui applique le bouclier.
 * @param equipe Tableau contenant l'équipe.
 * @param taille Taille de l'équipe.
 */
void bouclier_equipe(Personnage *defenseur, Personnage equipe[], int taille) {
    printf("\n✨ %s invoque un BOUCLIER DIVIN (2 tours) !\n", defenseur->nom);
    for (int i = 0; i < taille; i++) {
        if (strcmp(equipe[i].nom, defenseur->nom) != 0){
            equipe[i].bouclier_actif = 2;
            printf("-> %s est protégé (%d/2 tours)\n", equipe[i].nom, equipe[i].bouclier_actif);
        }
    }
}

/**
 * Soigne un allié via une boisson magique (compétence spéciale).
 * @param soigneur Le personnage soignant.
 * @param cible Le personnage à soigner.
 */
void boisson_magique(Personnage* soigneur, Personnage* cible) {
    if (strcmp(soigneur->type, "guerisseur") != 0) {
        printf("%s n'est pas un guerisseur !\n", soigneur->nom);
        return;
    }
    int soin = 30;
    cible->PV += soin;
    if (cible->PV > cible->PV_max) cible->PV = cible->PV_max;
    printf("%s prépare une boisson magique pour %s (+%d PV) !\n", soigneur->nom, cible->nom, soin);
}

/**
 * Utilise la compétence spéciale d'un personnage (attaque, soin, bouclier).
 * @param perso Personnage utilisant la compétence.
 * @param equipe Équipe alliée du personnage.
 * @param taille Taille de l'équipe.
 * @param cible La cible visée par la compétence.
 */
void utiliser_competence(Personnage *perso, Personnage equipe[], int taille, Personnage *cible) {
    if (!perso || !equipe || !cible) {
        printf("Erreur : pointeur nul détecté dans utiliser_competence.\n");
        return;
    }

    if (perso->competence.tours_recharge > 0) {
        printf("%s doit encore attendre %d tours!\n", perso->nom, perso->competence.tours_recharge);
        return;
    }

    printf("✨ %s utilise sa compétence spéciale !\n", perso->nom);

    switch(perso->competence.type) {
        case 1:
            double_attaque(perso, cible);
            break;
        case 2:
            bouclier_equipe(perso, equipe, taille);
            break;
        case 3:
            boisson_magique(perso, cible);
            break;
    }

    perso->competence.tours_recharge = 2;
}
