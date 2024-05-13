#ifndef CYFEST_SALLE_H
#define CYFEST_SALLE_H

typedef struct {
    int res;
    char classe;
    int code;
}Place;

typedef struct{
    char *nom;
    char *nomFichier;
    int siegeres;
    int siege;
    Place **arr;
    int *taille;
    float classeA;
    float classeB;
    float classeC;
}Salle;


Place creerPlace(int);
Salle creerSalle(void);
void afficheSalle(Salle);
void freeSalle(Salle);
void devPlace(Place *);
void affichePlan(Salle);
Salle verifSiege(Salle);
Salle actualiseSiege(Salle);
Salle reservePlace(Salle);

#endif

