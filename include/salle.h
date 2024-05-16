#ifndef CYFEST_SALLE_H
#define CYFEST_SALLE_H

typedef struct {
    int res;
    char classe;
    int code;
}Place;

typedef struct{
    char *nom;                      //nom de la salle
    char *nomFichier;               //nom du fichier de sauvegarde de la salle
    int siegeres;                   //nombre de siege reservé
    int siege;                      //nombre de siege total
    Place **arr;                    //tableau de disposition des sièges
    int *taille;                    //tableau contenant le nombre de rangées et la tailles des rangées de sièges
    float classeA;                  //prix des sièges de classe A
    float classeB;                  //prix des sièges de classe B
    float classeC;                  //prix des sièges de classe C
    char *artiste;                  //nom de l'artiste jouant dans la salle
    int fosse;                      //présence d'un fosse pour ce concert
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
Salle modifSalle(Salle, char *);

#endif

