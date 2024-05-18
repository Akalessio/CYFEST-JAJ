#include <stdio.h>
#include "salle.h"
#include <string.h>
#include <stdlib.h>
#include "savefile.h"
#include "place.h"
#include "fonx.h"


int main() {
    int c = -1;
    int c1 = -1;
    int c2 = -1;
    int res = -1;
    int res1 = -1;
    int res2 = -1;
    char nom[50];
    Salle a;

    while (res != 1 || c != 3){
        printf("1) mode manager\n2) mode festivalier\n3) quitter le programme\n");
        res = scanf("%d", &c);

        if(res != 1){
            while (getchar() != '\n');
        }

        if(c == 1){
            while (res1 != 1 || c1 != 4) {
                manage();
                printf("1) creer une salle\n2) modifier salle\n3) afficher une salle\n4) quitter le mode manager\n");
                res1 = scanf("%d", &c1);

                if(res1 != 1){
                    while (getchar() != '\n');
                }

                if(c1 == 1){
                    while (c2 < 1 || c2 > 2) {
                        manage();
                        printf("1) creer une salle\n2) lire une sauvegarde de salle\n");
                        res2 = scanf("%d", &c2);

                        if (res2 != 1) {
                            while (getchar() != '\n');
                        }
                        if(c2 == 1){
                            a = creerSalle();
                        } else if(c2 == 2){
                            fgetchar();
                            fgets(nom, 49, stdin);
                            a = lectureSave(nom);
                        }
                    }
                }
            }
        }
    }

    return 0;
}
