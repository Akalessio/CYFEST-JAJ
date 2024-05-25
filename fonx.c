#include "fonx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "salle.h"
#include "sauvefichier.h"


int plusGrand(int *tab, int a){
    int b = -1;
    for (int i = 1; i < a; ++i) {
        if(tab[i]>b){
            b = tab[i];
        }
    }
    return b;
}

int decal(int a, int b){
    if(a%2==0 && b%2==0){
        return ((a/2)-(b/2));
    }
    else if(a%2==0 && b%2!=0){
        b=b/2;
        b++;
        return ((a/2)-b);
    }
    else if(a%2!=0 && b%2==0){
        return (((a-1)/2)-((b)/2));
    }
    else{
        return (((a-1)/2)-((b-1)/2));
    }
}

void decalPrint(int a){
    for (int i = 0; i < a; ++i) {
        printf("  ");
    }
}

void verifAlloc(void *a){
    if(a == NULL){
        printf("erreur lors de l'allocation\n");
        exit(1);
    }
}

void manage(void){
    printf("Mode manager\n");
}

void festival(void){
    printf("Mode Festivalier\n");
}

void verifNom(char *a){
    int str = strlen(a);
    for (int i = 0; i < str; ++i) {
        if(a[i] == ' '){
            a[i] = '_';
        }
    }
}

void afficheSauvegarde(Date date, int cle) {
    FILE *fichier;
    fichier = fopen("sauvegarde.txt", "r");

    if (fichier == NULL) {
        printf("erreur lors de l'ouverture du fichier");
        exit(2);
    }

    if (cle == 1) {
        int m = 0;
        char save[50];
        Salle s;
        printf("les sauvegardes disponibles sont\n\n");
        while (fgets(save, 49, fichier)) {
            m++;
            save[strcspn(save, "\n")] = '\0';
            s = lectureSave(save);

            if ((date.annee < s.date.annee) || (date.annee == s.date.annee && date.mois < s.date.mois) ||
                (date.annee == s.date.annee && date.mois == s.date.mois && date.jour <= s.date.jour)) {
                printf("%s\n", save);
            }
        }
        fclose(fichier);
    } else {

        char save[50];
        printf("les sauvegardes disponibles sont\n\n");

        while (fgets(save, 49, fichier)) {
            printf("%s\n", save);
        }

    }
}
void videTerminal() {
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif
}

void pauseTerminal() {
    printf("Appuyez sur entree pour revenir au menu...");
    while (getchar() != '\n');
    getchar();
}
