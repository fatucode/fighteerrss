#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nom[50];
    int type;
    int duree;
    int tours_recharge;
} TechniqueSpeciale;

typedef struct {
    char nom[50];
    char type[20];
    int PV_max;
    int PV;
    int attaque;
    int defense;
    int agilite;
    int vitesse;
    int bouclier_actif;
    TechniqueSpeciale competence;
    int nb_techniques;
    int nb_effets;
} Personnage;

Personnage creerPersonnage(const char *nom, const char *type) {
    Personnage p;
    strcpy(p.nom, nom);
    strcpy(p.type, type);
    p.PV_max = 100;

    if (strcmp(type, "attaquant") == 0) {
        p.attaque = 30;
        p.defense = 10;
        p.vitesse = 20;
        p.agilite = 15;
    } else if (strcmp(type, "defenseur") == 0) {
        p.attaque = 15;
        p.defense = 30;
        p.vitesse = 10;
        p.agilite = 10;
    } else if (strcmp(type, "guerisseur") == 0) {
        p.attaque = 10;
        p.defense = 15;
        p.vitesse = 15;
        p.agilite = 20;
    } else {
        printf("Type inconnu, creation d'un personnage par defaut.\n");
        p.attaque = 10;
        p.defense = 10;
        p.vitesse = 10;
        p.agilite = 10;
    }

    if (strcmp(p.type, "attaquant") == 0) {
        strcpy(p.competence.nom, "Double Attaque");
        p.competence.type = 1;
        p.competence.duree = 0;
        p.competence.tours_recharge = 0;
    } else if (strcmp(p.type, "defenseur") == 0) {
        strcpy(p.competence.nom, "Bouclier d'equipe");
        p.competence.type = 2;
        p.competence.duree = 1;
        p.competence.tours_recharge = 0;
    } else if (strcmp(p.type, "guerisseur") == 0) {
        strcpy(p.competence.nom, "Boisson magique");
        p.competence.type = 3;
        p.competence.duree = 0;
        p.competence.tours_recharge = 0;
    }

    p.PV = p.PV_max;
    p.nb_techniques = 0;
    p.nb_effets = 0;
    p.bouclier_actif = 0;

    return p;
}

Personnage saisirPersonnage() {
    char nom[50];
    char type[20];

    printf("Entrez le nom du personnage : ");
    scanf("%49s", nom);

    printf("Entrez le type (attaquant/defenseur/guerisseur) : ");
    scanf("%19s", type);

    return creerPersonnage(nom, type);
}

void afficherPersonnage(Personnage p) {
    printf("\nNom : %s\n", p.nom);
    printf("Type : %s\n", p.type);
    printf("PV : %d/%d\n", p.PV, p.PV_max);
    printf("Attaque : %d | Defense : %d\n", p.attaque, p.defense);
    printf("Agilite : %d | Vitesse : %d\n", p.agilite, p.vitesse);
    if (p.bouclier_actif)
        printf("[Bouclier actif]\n");
}

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

void afficher_equipes(Personnage equipe1[], int taille1, Personnage equipe2[], int taille2) {
    printf("\n=== EQUIPE 1 ===\n");
    for (int i = 0; i < taille1; i++) {
        if (equipe1[i].PV > 0) {
            afficherPersonnage(equipe1[i]);
        }
    }

    printf("\n=== EQUIPE 2 ===\n");
    for (int i = 0; i < taille2; i++) {
        if (equipe2[i].PV > 0) {
            afficherPersonnage(equipe2[i]);
        }
    }
}

void jouer_tour(Personnage equipe1[], int taille1, Personnage equipe2[], int taille2) {
    // Tour equipe 1
    for (int i = 0; i < taille1; i++) {
        if (equipe1[i].PV <= 0) continue;

        printf("\n--- Tour de %s ---\n", equipe1[i].nom);
        afficher_equipes(equipe1, taille1, equipe2, taille2);

        int choix;
        printf("\n1. Attaquer\n2. Competence\n3. Soigner\nChoix : ");
        scanf("%d", &choix);

        if (choix == 1) {
            printf("Choisissez une cible : ");
            int cible;
            scanf("%d", &cible);
            attaquer(&equipe1[i], &equipe2[cible-1]);
        } 
        else if (choix == 2) {
            printf("Choisissez une cible : ");
            int cible;
            scanf("%d", &cible);
            utiliser_competence(&equipe1[i], equipe1, taille1, &equipe2[cible-1]);
        } 
        else if (choix == 3 && strcmp(equipe1[i].type, "guerisseur") == 0) {
            printf("Choisissez un allie : ");
            int allie;
            scanf("%d", &allie);
            soigner(&equipe1[i], &equipe1[allie-1]);
        }
    }
}

Personnage* jouer_partie(Personnage equipe1[], int taille1, Personnage equipe2[], int taille2) {
    int tour = 1;
    
    while (1) {
        printf("\n=== TOUR %d ===\n", tour);
        
        jouer_tour(equipe1, taille1, equipe2, taille2);
        
        // Vérifier si equipe2 est morte
        int equipe2_vivante = 0;
        for (int i = 0; i < taille2; i++) {
            if (equipe2[i].PV > 0) equipe2_vivante = 1;
        }
        if (!equipe2_vivante) return equipe1;
        
        jouer_tour(equipe2, taille2, equipe1, taille1);
        
        // Vérifier si equipe1 est morte
        int equipe1_vivante = 0;
        for (int i = 0; i < taille1; i++) {
            if (equipe1[i].PV > 0) equipe1_vivante = 1;
        }
        if (!equipe1_vivante) return equipe2;
        
        tour++;
    }
}

int main() {
    printf("=== NINJA COMBAT ===\n\n");
    
    // Création des équipes
    Personnage equipe1[3];
    Personnage equipe2[3];
    
    printf("-- Creation equipe 1 --\n");
    for (int i = 0; i < 3; i++) {
        printf("\nPersonnage %d :\n", i+1);
        equipe1[i] = saisirPersonnage();
    }
    
    printf("\n-- Creation equipe 2 --\n");
    for (int i = 0; i < 3; i++) {
        printf("\nPersonnage %d :\n", i+1);
        equipe2[i] = saisirPersonnage();
    }
    
    // Début du jeu
    Personnage* vainqueurs = jouer_partie(equipe1, 3, equipe2, 3);
    
    // Résultat
    printf("\n=== L'equipe de %s a gagne ! ===\n", vainqueurs[0].nom);
    
    return 0;
}
