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
    int siege;
    Place **arr;
    int *taille;
}Salle;


Place creerPlace(int);
Salle creerSalle(void);
void afficheSalle(Salle);
void freeSalle(Salle);
void devPlace(Place *);

#endif

