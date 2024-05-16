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

    for (int i = 1; i < a.taille[0]+1; ++i) {
        for (int j = 0; j < a.taille[i]; ++j) {
            fprintf(save, "%d ", a.arr[i-1][j].code);
        }
        fputs("\n", save);
    }

    fprintf(save, "%f\n", a.classeA);
    fprintf(save, "%f\n", a.classeB);
    fprintf(save, "%f\n", a.classeC);


    fclose(save);
}

Salle lectureSave(char *nom){
    FILE *save = NULL;
    save = fopen(nom, "r+");

    if(save == NULL){
        printf("erreur lors de l'ouverture du fichier");
        exit(2);
    }

    Salle a;
    char b[50];
    rewind(save);

    fgets(b, 49, save);
    int c = strlen(b);

    a.nom = NULL;
    a.nom = malloc(c+1);

    a.nomFichier = NULL;
    a.nomFichier = malloc(c+12);

    if(a.nom == NULL ||a.nomFichier == NULL){
        printf("erreur lors de l'allocation\n");
        exit(1);
    }

    for (int i = 0; i < c; ++i) {
        a.nom[i] = b[i];
        a.nomFichier [i] = b[i];
    }
    b[c-1] = '\0';

    a.nomFichier[c-1] = '.';
    a.nomFichier[c] = 'S';
    a.nomFichier[c+1] = 'A';
    a.nomFichier[c+2] = 'L';
    a.nomFichier[c+3] = 'L';
    a.nomFichier[c+4] = 'E';
    a.nomFichier[c+5] = 'S';
    a.nomFichier[c+6] = 'A';
    a.nomFichier[c+7] = 'U';
    a.nomFichier[c+8] = 'V';
    a.nomFichier[c+9] = 'E';
    a.nomFichier[c+10] = b[c-1];

    fscanf(save, "%d", &a.siege);
    fgetc(save);
    int taille;
    fscanf(save, "%d", &taille);
    fgetc(save);

    a.taille = NULL;
    a.taille = malloc(sizeof(int) * (taille+1));
    verifAlloc(a.taille);

    a.taille[0] = taille;


    for (int i = 1; i < a.taille[0]+1; ++i) {
        fscanf(save, "%d", &a.taille[i]);
        fgetc(save);
    }

    a.arr = NULL;
    a.arr = malloc(sizeof(Place *) * a.taille[0]);

    verifAlloc(a.arr);



    for (int i = 0; i < a.taille[0]; ++i) {
        a.arr[i] = NULL;
        a.arr[i] = malloc(sizeof(Place) * a.taille[i+1]);
        verifAlloc(a.arr[i]);
    }

    for (int i = 1; i < a.taille[0]+1; ++i) {

        for (int j = 0; j < a.taille[i]; ++j) {
            fscanf(save, "%d ", &a.arr[i-1][j].code);
            devPlace(&a.arr[i-1][j]);
        }
    }

    fscanf(save, "%f", &a.classeA);
    fscanf(save, "%f", &a.classeB);
    fscanf(save, "%f", &a.classeC);

    fclose(save);

    return a;
}