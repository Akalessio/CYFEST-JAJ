#include <stdio.h>
#include "salle.h"
#include <string.h>
#include <stdlib.h>
#include "savefile.h"
#include "place.h"


int main() {
    int b = -1;

    printf("chiffre\n");
    scanf("%d", &b);

    if (b == 1) {
    Salle a = creerSalle();
    afficheSalle(a);
    saveSalle(a);
    freeSalle(a);
    }
    else if(b == 2){
        char nom[50];
        printf("entrez le nom de la salle sauvegarde\n");
        scanf("%s", nom);
        Salle a = lectureSave(nom);


        a = reservePlace(a);
        affichePlan(a);
        saveSalle(a);
        freeSalle(a);

    } else if(b == 3){
        char nom[50];
        printf("entrez le nom de la salle sauvegarde\n");
        scanf("%s", nom);
        Salle a = lectureSave(nom);

        a = modifSalle(a, nom);
        afficheSalle(a);
        saveSalle(a);
        freeSalle(a);
    }
    else{
        char nom[50];
        printf("entrez le nom de la salle sauvegarde\n");
        scanf("%s", nom);

        Salle a = lectureSave(nom);
        afficheSalle(a);
        freeSalle(a);
    }

    return 0;
}
