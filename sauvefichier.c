#include "sauvefichier.h"
#include "salle.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fonx.h"
#include "place.h"

// Cette fonction vérifie si un nom existe déjà dans le fichier de sauvegarde.
// Si le nom n'existe pas, il est ajouté à la fin du fichier.
void verifSauvegarde(char *nom) {
    // Ouvre le fichier de sauvegarde en mode lecture/écriture
    FILE *fichier;
    fichier = fopen("sauvegarde.txt", "r+");

    // Vérifie si le fichier a été correctement ouvert
    if (fichier == NULL) {
        printf("erreur lors de l'ouverture du fichier");
        exit(2);
    }

    char save[50];
    int c = 0;

    // Parcourt le fichier ligne par ligne
    while (fgets(save, 49, fichier)) {
        // Supprime le caractère de saut de ligne à la fin de chaque ligne
        save[strcspn(save, "\n")] = '\0';

        // Vérifie si le nom existe déjà dans le fichier
        if (strcmp(save, nom) == 0) {
            c++; // Incrémente le compteur si le nom est trouvé
            break;
        }
    }

    // Si le nom n'existe pas dans le fichier, l'ajoute à la fin du fichier
    if (c == 0) {
        fseek(fichier, 0, SEEK_END); // Place le curseur à la fin du fichier
        fputs(nom, fichier); // Écrit le nom dans le fichier
        fputc('\n', fichier); // Ajoute un saut de ligne après le nom
    }

    fclose(fichier); // Ferme le fichier
}

// Cette fonction sauvegarde les informations d'une salle dans un fichier.
void sauveSalle(Salle a) {
    a = comptePlace(a); // Met à jour le nombre de places disponibles dans la salle
    FILE *save = NULL;
    save = fopen(a.nomFichier, "w"); // Ouvre le fichier en mode écriture

    // Vérifie si le fichier a été correctement ouvert
    if (save == NULL) {
        printf("erreur lors de l'ouverture du fichier");
        exit(1);
    }

    // Supprime l'extension ".SALLESAUVE" du nom de fichier s'il est présent
    char *suffix = ".SALLESAUVE";
    char aff[50] = "";
    strncpy(aff, a.nomFichier, 49);
    char *pos = strstr(aff, suffix);

    if (pos != NULL) {
        *pos = '\0';
    }

    // Écrit le nom de fichier sans l'extension dans le fichier de sauvegarde
    fputs(aff, save);
    fputs("\n", save);

    // Écrit les informations de la salle dans le fichier
    fprintf(save, "%d\n", a.siege); // Nombre total de sièges
    fprintf(save, "%d\n", a.taille[0]); // Nombre de rangées

    // Écrit le nombre de sièges dans chaque rangée
    for (int i = 1; i < a.taille[0] + 1; ++i) {
        fprintf(save, "%d\n", a.taille[i]);
    }

    // Écrit les codes de chaque siège dans le fichier
    for (int i = 1; i < a.taille[0] + 1; ++i) {
        for (int j = 0; j < a.taille[i]; ++j) {
            fprintf(save, "%d ", a.arr[i - 1][j].code);
        }
        fputs("\n", save);
    }

    // Écrit les prix des différentes classes de sièges
    fprintf(save, "%f\n", a.classeA);
    fprintf(save, "%f\n", a.classeB);
    fprintf(save, "%f\n", a.classeC);

    // Écrit l'indicateur de présence de fosse
    fprintf(save, "%d\n", a.fosse);

    // Écrit la date de l'événement
    fprintf(save, "%d %d %d\n", a.date.jour, a.date.mois, a.date.annee);

    // Écrit le nom de l'artiste ou de l'événement
    fputs(a.artiste, save);
    fputc('\n', save);

    // Écrit le nombre de places disponibles pour chaque classe de sièges
    fprintf(save, "%d %d %d %d %d %d", a.places[0], a.places[1], a.places[2], a.places[3], a.places[4], a.places[5]);

    // Vérifie et met à jour le fichier de sauvegarde des noms de fichiers
    verifSauvegarde(a.nomFichier);

    fclose(save); // Ferme le fichier
}


// Cette fonction lit les informations d'une salle à partir d'un fichier de sauvegarde.
Salle lectureSauve(char *nom) {
    FILE *save = NULL;
    save = fopen(nom, "r+");

    if (save == NULL) {
        printf("erreur lors de l'ouverture du fichier");
        exit(2);
    }

    Salle a;
    char b[50];
    rewind(save);

    fgets(b, 49, save);
    int c = strlen(b);

    // Alloue dynamiquement de la mémoire pour le nom de la salle
    a.nom = NULL;
    a.nom = malloc(c + 1);

    // Alloue dynamiquement de la mémoire pour le nom du fichier de sauvegarde
    a.nomFichier = NULL;
    a.nomFichier = malloc(c + 12);

    // Vérifie si l'allocation de mémoire a réussi
    if (a.nom == NULL || a.nomFichier == NULL) {
        printf("erreur lors de l'allocation\n");
        exit(1);
    }

    // Copie le nom de fichier dans la structure de salle
    for (int i = 0; i < c; ++i) {
        a.nom[i] = b[i];
        a.nomFichier[i] = b[i];
    }
    b[c - 1] = '\0';

    // Ajoute l'extension ".SALLESAUVE" au nom du fichier de sauvegarde
    a.nomFichier[c - 1] = '.';
    a.nomFichier[c] = 'S';
    a.nomFichier[c + 1] = 'A';
    a.nomFichier[c + 2] = 'L';
    a.nomFichier[c + 3] = 'L';
    a.nomFichier[c + 4] = 'E';
    a.nomFichier[c + 5] = 'S';
    a.nomFichier[c + 6] = 'A';
    a.nomFichier[c + 7] = 'U';
    a.nomFichier[c + 8] = 'V';
    a.nomFichier[c + 9] = 'E';
    a.nomFichier[c + 10] = b[c - 1];

    // Lit les informations de la salle à partir du fichier
    fscanf(save, "%d", &a.siege);
    fgetc(save);
    int taille;
    fscanf(save, "%d", &taille);
    fgetc(save);

    // Alloue dynamiquement de la mémoire pour stocker les tailles des rangées
    a.taille = NULL;
    a.taille = malloc(sizeof(int) * (taille + 1));
    verifAlloc(a.taille);

    a.taille[0] = taille;

    // Lit le nombre de sièges dans chaque rangée
    for (int i = 1; i < a.taille[0] + 1; ++i) {
        fscanf(save, "%d", &a.taille[i]);
        fgetc(save);
    }

    // Alloue dynamiquement de la mémoire pour stocker les sièges
    a.arr = NULL;
    a.arr = malloc(sizeof(Place *) * a.taille[0]);
    verifAlloc(a.arr);

    for (int i = 0; i < a.taille[0]; ++i) {
        a.arr[i] = NULL;
        a.arr[i] = malloc(sizeof(Place) * a.taille[i + 1]);
        verifAlloc(a.arr[i]);
    }

    // Lit les codes de chaque siège et les initialise
    for (int i = 1; i < a.taille[0] + 1; ++i) {
        for (int j = 0; j < a.taille[i]; ++j) {
            fscanf(save, "%d ", &a.arr[i - 1][j].code);
            devPlace(&a.arr[i - 1][j]);
        }
    }

    // Lit les prix des différentes classes de sièges
    fscanf(save, "%f", &a.classeA);
    fscanf(save, "%f", &a.classeB);
    fscanf(save, "%f", &a.classeC);

    // Lit l'indicateur de présence de fosse
    fscanf(save, "%d", &a.fosse);

    // Lit la date de l'événement
    fscanf(save, "%d %d %d", &a.date.jour, &a.date.mois, &a.date.annee);
    fgetc(save);

    // Lit le nom de l'artiste ou de l'événement
    fgets(b, 49, save);
    c = strlen(b);

    // Alloue dynamiquement de la mémoire pour le nom de l'artiste
    a.artiste = malloc(c);
    verifAlloc(a.artiste);

    for (int i = 0; i < c; ++i) {
        a.artiste[i] = b[i];
    }
    a.artiste[c - 1] = '\0';

    // Lit le nombre de places disponibles pour chaque classe de sièges
    fscanf(save, "%d %d %d %d %d %d", &a.places[0], &a.places[1], &a.places[2], &a.places[3], &a.places[4],
           &a.places[5]);

    fclose(save); // Ferme le fichier
    a = verifSiege(a); // Vérifie et met à jour le nombre de sièges réservés

    return a; // Renvoie la salle lue
}
