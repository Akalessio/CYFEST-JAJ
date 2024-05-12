#include "savefile.h"
#include "salle.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fonx.h"

void saveSalle(Salle a){
    FILE *save = NULL;
    save = fopen(a.nomFichier, "w");

    if(save == NULL){
        printf("erreur lors de l'ouverture du fichier");
        exit(1);
    }

    fputs(a.nom, save);
    fputs("\n", save);

    fprintf(save, "%d\n", a.siege);
    fprintf(save, "%d\n", a.taille[0]);

    for (int i = 1; i < a.taille[0]+1; ++i) {
        fprintf(save, "%d\n",a.taille[i]);
    }

    fputs( "tableau de disposition :\n", save);

    for (int i = 1; i < a.taille[0]+1; ++i) {
        for (int j = 0; j < a.taille[i]; ++j) {
            fprintf(save, "%d ", a.arr[i-1][j].code);
        }
        fputs("\n", save);
    }

    fclose(save);
}