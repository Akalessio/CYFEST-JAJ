#include <stdio.h>
#include "salle.h"
#include <string.h>
#include <stdlib.h>
#include "savefile.h"
#include "place.h"
#include "fonx.h"

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

int main() {
    int c = -1;
    int c1 = -1;
    int c2 = -1;
    int res = -1;
    int res1 = -1;
    int res2 = -1;
    char nom[50];
    int str;
    Salle a;
    a.nom = NULL;

    while (res != 1 || c != 3) {
        printf("1) mode manager\n2) mode festivalier\n3) quitter le programme\n");
        res = scanf("%d", &c);

        if (res != 1) {
            while (getchar() != '\n');
        }

        if (c == 1) {
            while (res1 != 1 || c1 != 4) {
                videTerminal();
                manage();
                printf("1) creer une salle\n2) modifier salle\n3) afficher une salle\n4) quitter le mode manager\n");
                res1 = scanf("%d", &c1);

                if (res1 != 1) {
                    while (getchar() != '\n');
                }

                if (c1 == 1) {
                    while (c2 < 1 || c2 > 2) {
                        videTerminal();
                        manage();
                        printf("1) creer une salle\n2) lire une sauvegarde de salle\n");
                        res2 = scanf("%d", &c2);

                        if (res2 != 1) {
                            while (getchar() != '\n');
                        }
                        if (c2 == 1) {
                            a = creerSalle();
                            saveSalle(a);
                        } else if (c2 == 2) {
                            a.nom = NULL;
                            while (fopen(nom, "r") == NULL) {
                                videTerminal();
                                manage();
                                printf("entrez le nom du fichier de sauvegarde(avec l'extension .SALLESAUVE)\n");
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
                    }
                } else if (c1 == 2) {
                    if (a.nom == NULL) {
                        while (fopen(nom, "r") == NULL) {
                            videTerminal();
                            manage();
                            printf("entrez le nom du fichier de sauvegarde(avec l'extension .SALLESAUVE)\n");
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
                    a = modifSalle(a, nom);
                    saveSalle(a);
                } else if (c1 == 3) {
                    if (a.nom == NULL) {
                        while (fopen(nom, "r") == NULL) {
                            videTerminal();
                            manage();
                            printf("entrez le nom du fichier de sauvegarde(avec l'extension .SALLESAUVE)\n");
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
                    afficheSalle(a);
                    pauseTerminal();
                    freeSalle(a);
                }
            }
        } else if (c == 2) {
            while (res1 != 1 || c1 != 4) {
                videTerminal();
                festival();
                printf("1) afficher les différentes salles\n2) reserver des places\n3) afficher une salle\n4) quitter le mode festivalier\n");
                res1 = scanf("%d", &c1);

                if (res1 != 1) {
                    while (getchar() != '\n');
                }

                if(c1 == 1){
                
                }
            }
        }
    }
}
