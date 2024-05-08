#ifndef CYFEST_SALLE_H
#define CYFEST_SALLE_H

typedef struct{
    char *nom;
    int siege;
    int **arr;
    int *taille;
}Salle;

Salle creerSalle(void);

#endif

