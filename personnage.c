Personnage creerPersonnage(const char *nom, const char *type) {
    Personnage p;
    strcpy(p.nom, nom);
    strcpy(p.type, type);


    if (strcmp(type, "attaquant") == 0) {
        p.attaque = 30;
        p.defense = 10;
        p.vitesse = 20;
        p.agilite = 15;
    }
    else if (strcmp(type, "defenseur") == 0) {
        p.attaque = 15;
        p.defense = 30;
        p.vitesse = 10;
        p.agilite = 10;
    }
    else if (strcmp(type, "guerisseur") == 0) {
        p.attaque = 10;
        p.defense = 15;
        p.vitesse = 15;
        p.agilite = 20;
    }

    // Comp�tences sp�ciales
    if (strcmp(type, "attaquant") == 0) {
        strcpy(p.competence.nom, "Double Attaque");
        p.competence.type = 1;
        p.competence.duree = 0;
        p.competence.tours_recharge = 0;
    }
    else if (strcmp(type, "defenseur") == 0) {
        strcpy(p.competence.nom, "Bouclier d'equipe");
        p.competence.type = 2;
        p.competence.duree = 1;
        p.competence.tours_recharge = 0;
    }
    else if (strcmp(type, "guerisseur") == 0) {
        strcpy(p.competence.nom, "Boisson magique");
        p.competence.type = 3;
        p.competence.duree = 0;
        p.competence.tours_recharge = 0;
    }
    p.PV_max = 100;
    p.PV = p.PV_max;
    p.nb_techniques = 0;
    p.nb_effets = 0;
    p.bouclier_actif = 0;

    return p;
}
Personnage saisirPersonnage() {
    char nom[50];
    char type[20];
    int type_valide = 0;

    printf("Entrez le nom du personnage : ");
    scanf("%49s", nom);

    // Boucle jusqu'� avoir un type valide
    while (!type_valide) {
        printf("Entrez le type (attaquant/defenseur/guerisseur) : ");
        scanf("%19s", type);

        // V�rifie le type
        if (strcmp(type, "attaquant") == 0 ||
            strcmp(type, "defenseur") == 0 ||
            strcmp(type, "guerisseur") == 0) {
            type_valide = 1;
        } else {
            printf("Type invalide ! Les types valides sont :\n");
            printf("- attaquant\n- defenseur\n- guerisseur\n");
        }
    }

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

