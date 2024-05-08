#include "salle.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


Salle creerSalle(void){
    Salle a;
    char chaine[50];

    printf("entrez le nom de la salle\n");
    scanf("%s", chaine);

    int b = (int)strlen(chaine)+1;

    a.nom = NULL;
    a.nom = malloc(b);

    if(a.nom == NULL){
        printf("erreur lors de l'allocation\n");
        exit(1);
    }

    for (int i = 0; i < b; ++i) {
        *(a.nom+i) = chaine[i];
    }

    a.siege = -1;

    while (a.siege<=0) {
        printf("combien de sieges dans votre salle\n");
        scanf("%d", &a.siege);
    }

    int r = -1;

    while (r<=0) {
        printf("combien de rangees de sieges dans votre salle\n");
        scanf("%d", &r);
    }

    a.arr = NULL;
    a.arr = malloc(sizeof(int *)*r);

    if(a.arr == NULL){
        printf("erreur lors de l'allocation\n");
        exit(1);
    }
    int l = -1;
    for (int i = 1; i < r+1; ++i) {
        while (l < 0) {
            printf("combien de sieges a la range num %d", i);
            scanf("%d", &l);
        }
        *(a.arr+i-1) =
    }




    return a;
};
