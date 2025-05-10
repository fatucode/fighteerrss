#ifndef COMBAT_H
#define COMBAT_H
void attaquer(Personnage *attaquant, Personnage *cible);
vois soigner(Personnage *guerisseur ,Personnage *cible);
void double_attaque(Personnage *attaquant, Personnage *cible);
void boisson_magique(Personnage *soigneur, Personnage *cible);
void bouclier_equipe(Personnage *defenseur, Personnage equipe[], int taille) ;
void utiliser_competence(Personnage *perso, Personnage equipe[], int taille, Personnage *cible) ;
