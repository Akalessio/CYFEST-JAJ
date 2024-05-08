#include "salle.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


Salle creerSalle(void){                                                                                                 //creation d'une salle
    Salle a;
    char chaine[50];                                                                                                    //tableau contenant le nom de la salle

    printf("entrez le nom de la salle\n");
    scanf("%s", chaine);

    int b = (int)strlen(chaine)+1;                                                                                  //récuperation de la taille du nom de la salle

    a.nom = NULL;
    a.nom = malloc(b);                                                                                             //allocation d'un tableau de la bonne taille

    if(a.nom == NULL){
        printf("erreur lors de l'allocation\n");
        exit(1);
    }

    for (int i = 0; i < b; ++i) {                                                                                       //la salle est nommé avec le nom de la chaine
        *(a.nom+i) = chaine[i];
    }

    a.siege = -1;                                                                                                       //selection du nombre de siège

    while (a.siege<=0) {
        printf("combien de sieges dans votre salle\n");
        scanf("%d", &a.siege);
    }

    int r = -1;                                                                                                         //selection du nombmre de rangée

    while (r<=0) {
        printf("combien de rangees de sieges dans votre salle\n");
        scanf("%d", &r);
    }

    a.taille = NULL;                                                                                                    //creation du tableau contenant les caracteristique de taille de la salle
    a.taille = calloc(r+1, sizeof(int));

    if(a.taille == NULL){
        printf("erreur lors de l'allocation\n");
        exit(1);
    }

    a.taille[0] = r;

    a.arr = NULL;                                                                                                       //creation du tableau de l'arrangement de la salle
    a.arr = malloc(sizeof(int *)*r);

    if(a.arr == NULL){
        printf("erreur lors de l'allocation\n");
        exit(1);
    }
    int l = -1;
    for (int i = 1; i < r+1; ++i) {

        while (l < 0) {
            printf("combien de sieges a la range num %d\n", i);
            scanf("%d", &l);
        }

        *(a.arr+i-1) = calloc(l, sizeof(int));                                              //remplissage des differentes ligne
                                                                                                                        //sauvegarde des tailles des lignes
        a.taille[i] = l;

        l = -1;
    }
return a;
};

void afficheSalle(Salle a){
    printf("nom de salle : %s\nnombre de siege de la salle : %d\nplan de la salle : \n", a.nom, a.siege, a.taille[0]);

    for (int i = 0; i < a.taille[0]; ++i) {
        for (int j = 0; j < a.taille[i+1]; ++j) {
            printf("%d", a.arr[i][j]);
        }
        printf("\n");
    }
}

void freeSalle(Salle a){
    free(a.nom);
    for (int i = 0; i < a.taille[0]; ++i) {
        free(*(a.arr+i));
    }
    free(a.arr);
    free(a.taille);
}
