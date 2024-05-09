#include "salle.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fonx.h"


Place creerPlace(int a){
    Place c;
    c.classe = 0;

    while (c.classe!='A' && c.classe!='B' && c.classe!='C') {
        if (a == 1) {
            c.classe = 'A';
        } else if (a == 2) {
            c.classe = 'B';
        } else if (a == 3) {
            c.classe = 'C';
        } else {
            printf("entrez une categorie de siege disponible : 1, 2 ou 3\n");
            scanf("%d", &a);
        }
    }
    c.res=0;
    return c;
}

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
    a.arr = malloc(sizeof(Place *)*r);

    if(a.arr == NULL){
        printf("erreur lors de l'allocation\n");
        exit(1);
    }
    int l = -1;
    int x = -1;
    Place y;

    for (int i = 1; i < r+1; ++i) {

        while(l < 0){
            printf("combien de sieges a la range num %d\n", i);
            scanf("%d", &l);
        }

        *(a.arr+i-1) = NULL;
        *(a.arr+i-1) = malloc(sizeof(Place)*l);                                         //remplissage des differentes ligne
                                                                                                                     //sauvegarde des tailles des lignes
        if(*(a.arr+i-1) == NULL){
            printf("erreur lors de l'allocation\n");
            exit(1);
        }

        printf("qu'elle est la categorie de place de cette rangée\n");
        scanf("%d", &x);
        y = creerPlace(x);

        for (int j = 0; j < l; ++j) {
            a.arr[i-1][j] = y;
        }

        a.taille[i] = l;

        l = -1;
    }
return a;
};

void afficheSalle(Salle a){
    printf("nom de salle : %s\nnombre de siege de la salle : %d\nplan de la salle : \n", a.nom, a.siege, a.taille[0]);

    int l = plusGrand(a.taille, a.taille[0]);
    int d =0;

    for (int i = 0; i < a.taille[0]; ++i) {
        if(i<9) {
            printf("R%d |  ", i + 1);
        } else{
            printf("R%d|  ", i+1);
        }
        d = decal(l, a.taille[i+1]);
        decalPrint(d);
        for (int j = 0; j < a.taille[i+1]; ++j) {
            if((a.arr[i][j]).res == 0) {
                printf("0 ");
            }
            else{
                printf("X");
            }
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

