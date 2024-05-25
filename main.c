#include <stdio.h>
#include "salle.h"
#include <string.h>
#include <stdlib.h>
#include "savefile.h"
#include "place.h"
#include "fonx.h"

int main() {

    if(fopen("sauvegarde.txt", "r") == NULL){
        FILE *savetxt = fopen("sauvegarde.txt", "w");
        if(savetxt == NULL){
            printf("erreur lors de l'ouverture du fichier");
            exit(2);
        }
        fclose(savetxt);
    }

    int c = -1;
    int c1 = -1;
    int c2 = -1;
    int res = -1;
    int res1 = -1;
    int res2 = -1;
    char nom[50];
    int str;
    Salle a;
    Date date;
    a.nom = NULL;
    Salle k1 = {0};

    int ress = 0;
    date.jour = 0;
    date.mois = 0;
    date.annee = 0;
    int ressj = -1, ressm = -1, ressa = -1;

    while(ress != 3){
        while (ressa != 1 || date.annee < 2024){
            printf("entrez l'année actuelle\n");
            ressa = scanf("%d", &date.annee);
            if (ressa != 1) {
                while (getchar() != '\n');
            }
        }

        ress++;
        if((date.annee % 4 == 0 && date.annee % 100 != 0) || (date.annee % 400 == 0)){
            while (ressm != 1 || date.mois < 1 || date.mois > 12){
                printf("entrez le mois actuel\n");
                ressm = scanf("%d", &date.mois);
                if (ressm != 1) {
                    while (getchar() != '\n');
                }
            }
            ress++;
            if(date.mois == 1 || date.mois == 3 || date.mois == 5 || date.mois == 7 || date.mois == 8 || date.mois == 10 || date.mois == 12){
                while(ressj != 1 || date.jour <1 || date.jour > 31){
                    printf("entrez le jour actuel\n");
                    ressj = scanf("%d", &date.jour);
                    if (ressj != 1) {
                        while (getchar() != '\n');
                    }
                }
                ress++;
            } else if(date.mois == 4 || date.mois == 6 || date.mois == 9 || date.mois == 11){
                while(ressj != 1 || date.jour <1 || date.jour > 30){
                    printf("entrez le jour actuel\n");
                    ressj = scanf("%d", &date.jour);
                    if (ressj != 1) {
                        while (getchar() != '\n');
                    }
                }
                ress++;
            }else{
                while(ressj != 1 || date.jour <1 || date.jour > 29){
                    printf("entrez le jour actuel\n");
                    ressj = scanf("%d", &date.jour);
                    if (ressj != 1) {
                        while (getchar() != '\n');
                    }
                }
                ress++;
            }
        }else{
            while (ressm != 1 || date.mois < 1 || date.mois > 12){
                printf("entrez le mois actuel\n");
                ressm = scanf("%d", &date.mois);
                if (ressm != 1) {
                    while (getchar() != '\n');
                }
            }
            ress++;
            if(date.mois == 1 || date.mois == 3 || date.mois == 5 || date.mois == 7 || date.mois == 8 || date.mois == 10 || date.mois == 12){
                while(ressj != 1 || date.jour <1 || date.jour > 31){
                    printf("entrez le jour actuel\n");
                    ressj = scanf("%d", &date.jour);
                    if (ressj != 1) {
                        while (getchar() != '\n');
                    }
                }
                ress++;
            } else if(date.mois == 4 || date.mois == 6 || date.mois == 9 || date.mois == 11){
                while(ressj != 1 || date.jour <1 || date.jour > 30){
                    printf("entrez le jour actuel\n");
                    ressj = scanf("%d", &date.jour);
                    if (ressj != 1) {
                        while (getchar() != '\n');
                    }
                }
                ress++;
            }else{
                while(ressj != 1 || date.jour <1 || date.jour > 28){
                    printf("entrez le jour actuel\n");
                    ressj = scanf("%d", &date.jour);
                    if (ressj != 1) {
                        while (getchar() != '\n');
                    }
                }
                ress++;
            }
        }
    }



    while (res != 1 || c != 3) {
        a.nom = NULL;
        res = -1, c = -1, c1 = -1, res1 = -1, res2 = -1, c2 = -1;
        videTerminal();
        printf("1) mode manager\n2) mode festivalier\n3) quitter le programme\n");
        res = scanf("%d", &c);

        if (res != 1) {
            while (getchar() != '\n');
        }

        if (c == 1) {
            while (res1 != 1 || c1 != 4) {
                a.nom = NULL;
                c1 = -1;
                res1 = -1;
                videTerminal();
                manage();
                printf("1) creer une salle\n2) modifier salle\n3) afficher une salle\n4) quitter le mode manager\n");
                res1 = scanf("%d", &c1);

                if (res1 != 1) {
                    while (getchar() != '\n');
                }

                if (c1 == 1) {
                    videTerminal();
                    manage();
                    a = creerSalle();
                    saveSalle(a);
                }
                else if (c1 == 2) {

                    if (a.nom == NULL) {
                        while (fopen(nom, "r") == NULL) {
                            videTerminal();
                            manage();
                            printf("entrez le nom du fichier de sauvegarde(avec l'extension .SALLESAUVE)\n");
                            afficheSauvegarde(date, 0);
                            fgetchar();
                            fgets(nom, 49, stdin);
                            str = strlen(nom);
                            nom[str-1] = '\0';
                            if (fopen(nom, "r") == NULL) {
                                printf("le nom du fichier que vous avez entre n'existe pas\n");
                            }else{
                                a = lectureSave(nom);
                            }
                        }
                    }
                    videTerminal();
                    manage();
                    a = modifSalle(a, nom, date);
                    pauseTerminal();
                    nom[0] = '\0';
                    saveSalle(a);
                } else if (c1 == 3) {
                    while (fopen(nom, "r") == NULL) {
                        if(a.nom != NULL){
                            freeSalle(a);
                        }   videTerminal();
                            manage();
                            printf("entrez le nom du fichier de sauvegarde(avec l'extension .SALLESAUVE)\n");
                            afficheSauvegarde(date , 0);
                            fgetchar();
                            fgets(nom, 49, stdin);
                            str = strlen(nom);
                            nom[str-1] = '\0';

                            if (fopen(nom, "r") == NULL) {
                                printf("le nom du fichier que vous avez entre n'existe pas\n");
                            }else{
                                a = lectureSave(nom);
                            }
                    }

                    nom[0] = '\0';
                    videTerminal();
                    manage();
                    afficheSalle(a, 0);
                    pauseTerminal();
                    freeSalle(a);
                }
            }
        }
        //==================================================================================================================================================================================================
        else if (c == 2) {
            while (res1 != 1 || c1 != 4) {
                a.nom = NULL;
                c1 = -1;
                res1 = -1;
                videTerminal();
                festival();
                printf("1) afficher les différentes salles\n2) reserver des places\n3) afficher une salle\n4) quitter le mode festivalier\n");
                res1 = scanf("%d", &c1);

                if (res1 != 1) {
                    while (getchar() != '\n');
                }

                if(c1 == 1){
                    videTerminal();
                    festival();
                    int m = 0;
                    char save[50];
                    Salle s;
                    FILE *fichier;

                    fichier = fopen("sauvegarde.txt", "r+");
                    if(fichier == NULL){
                        printf("erreur lors de l'ouverture du ficher\n");
                        exit(2);
                    }

                    while(fgets(save, 49, fichier)){
                        m++;
                        save[strcspn(save, "\n")] = '\0';
                        s = lectureSave(save);
                        if((date.annee < s.date.annee) || (date.annee == s.date.annee && date.mois <  s.date.mois) || (date.annee == s.date.annee && date.mois == s.date.mois && date.jour <= s.date.jour)){
                            afficheSalle(s, 1);
                        }
                    }
                    pauseTerminal();
                    fclose(fichier);
                }
                else if(c1 == 2){
                    if (a.nom == NULL) {
                        while (fopen(nom, "r") == NULL) {
                            videTerminal();
                            festival();
                            printf("entrez le nom du fichier de sauvegarde(avec l'extension .SALLESAUVE)\n");
                            afficheSauvegarde(date, 1);
                            fgetchar();
                            fgets(nom, 49, stdin);
                            str = strlen(nom);
                            nom[str-1] = '\0';

                            if (fopen(nom, "r") == NULL) {
                                printf("le nom du fichier que vous avez entre n'existe pas\n");
                                pauseTerminal();
                            }else{
                                a = lectureSave(nom);
                            }
                        }
                    }
                    videTerminal();
                    festival();
                    a = reservePlace(a);
                    saveSalle(a);
                    videTerminal();
                    festival();
                    afficheSalle(a, 1);
                    pauseTerminal();
                    nom[0] = '\0';
                } else if(c1 == 3) {
                    a.nom = NULL;
                    if (a.nom == NULL) {
                        while (fopen(nom, "r") == NULL) {
                            videTerminal();
                            festival();
                            printf("entrez le nom du fichier de sauvegarde(avec l'extension .SALLESAUVE)\n");
                            afficheSauvegarde(date, 1);
                            fgetchar();
                            fgets(nom, 49, stdin);
                            str = strlen(nom);
                            nom[str - 1] = '\0';

                            if (fopen(nom, "r") == NULL) {
                                printf("le nom du fichier que vous avez entre n'existe pas\n");
                            } else {
                                a = lectureSave(nom);
                            }
                        }
                    }
                    nom[0] = '\0';
                    videTerminal();
                    festival();
                    afficheSalle(a, 1);
                    pauseTerminal();
                }
            }
        }
    }
    freeSalle(a);
}
