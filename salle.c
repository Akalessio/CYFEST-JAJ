#include "salle.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fonx.h"
#include "place.h"






Salle creerSalle(void) {
    Salle a;
    char chaine[50];
    char *res = NULL;
    int ress;
    int str;
    int sec = -1;

    while (res == NULL) {
        printf("entrez le nom de la salle\n");

        while (getchar() != '\n');

        res = fgets(chaine, 49, stdin);

        str = strlen(chaine);

        chaine[str-1] = '\0';
    }

    int b = str;
    a.nom = NULL;
    a.nom = malloc(b);

    a.nomFichier = NULL;
    a.nomFichier = malloc(b + 11);

    if (a.nom == NULL || a.nomFichier == NULL) {
        printf("erreur lors de l'allocation\n");
        exit(1);
    }

    verifNom(chaine);

    for (int i = 0; i < b; ++i) {
        *(a.nom + i) = chaine[i];
        *(a.nomFichier + i) = chaine[i];
    }

    a.nomFichier[b - 1] = '.';
    a.nomFichier[b ] = 'S';
    a.nomFichier[b + 1] = 'A';
    a.nomFichier[b + 2] = 'L';
    a.nomFichier[b + 3] = 'L';
    a.nomFichier[b + 4] = 'E';
    a.nomFichier[b + 5] = 'S';
    a.nomFichier[b + 6] = 'A';
    a.nomFichier[b + 7] = 'U';
    a.nomFichier[b + 8] = 'V';
    a.nomFichier[b + 9] = 'E';
    a.nomFichier[b + 10] = chaine[b - 1];

    a.nom[b-1] = '\0';

    a.siege = -1;
    ress = -1;

    while (a.siege <= 0 || ress != 1) {
        printf("combien de sieges dans votre salle\n");
        ress = scanf("%d", &a.siege);

        if (ress != 1) {
            while (getchar() != '\n');
        }
    }

    int r = -1;
    ress = -1;
    while (r <= 0 || ress !=1){
        printf("combien de rangees de sieges dans votre salle\n");
        ress = scanf("%d", &r);

        if (ress != 1) {
            while (getchar() != '\n');
        }
    }

    a.taille = NULL;
    a.taille = calloc(r + 1, sizeof(int));

    if (a.taille == NULL) {
        printf("erreur lors de l'allocation\n");
        exit(1);
    }

    a.taille[0] = r;

    a.arr = NULL;
    a.arr = malloc(sizeof(Place *) * r);

    if (a.arr == NULL) {
        printf("erreur lors de l'allocation\n");
        exit(1);
    }
    int l = -1;
    int x = -1;
    Place y;
    int z = 0;
    a.fosse = -1;
    ress = -1;

    while (ress != 1 || a.fosse < 1 || a.fosse > 2){
        printf("y a t'il une fosse durant ce concert\n1) oui\n2) non\n(les rangees en classe A auront le double de siège)\n");
        ress = scanf("%d", &a.fosse);

        if (ress != 1) {
            while (getchar() != '\n');
        }
    }
    ress = -1;
    x = -1;
    int x1 = -1;

    while (ress != 1 || x > a.taille[0]) {
        printf("combien de rangees de classe A\n");
        ress = scanf("%d", &x);

        if (ress != 1) {
            while (getchar() != '\n');
        }
        if(x > a.taille[0]){
            printf("il y a %d rangees, vous depassez le maximum possible\n", a.taille[0]);
        }
    }

    ress = -1;
    if(x != a.taille[0]){
        while (ress != 1 || x1 > a.taille[0] - x) {
            printf("combien de rangees de classe B\n");
            ress = scanf("%d", &x1);

            if (ress != 1) {
                while (getchar() != '\n');
            }
            if(x1 > a.taille[0]){
                printf("il y a %d rangees restantes, vous depassez le maximum possible\n", a.taille[0]-x);
            }
        }
    }


    for (int i = 1; i < r + 1; ++i) {
    ress = -1;
        while (l < 0 || ress != 1) {
            printf("combien de sieges a la range num %d\n", i);
            ress = scanf("%d", &l);

            if (ress != 1) {
                while (getchar() != '\n');
            }
        }

        if(i<=x) {
            y = creerPlace(1);
        } else if(i > x && i <= (x + x1)){
            y = creerPlace(2);
        } else{
            y = creerPlace(3);
        }

        if(i > x || a.fosse == 2) {
            *(a.arr + i - 1) = NULL;
            *(a.arr + i - 1) = malloc(sizeof(Place) * l);

            if (*(a.arr + i - 1) == NULL) {
                printf("erreur lors de l'allocation\n");
                exit(1);
            }

            for (int j = 0; j < l; ++j) {
                a.arr[i - 1][j] = y;
            }

            a.taille[i] = l;
            z = z + l;
            l = -1;
        } else if(i <= x && a.fosse == 1){
            *(a.arr + i - 1) = NULL;
            *(a.arr + i - 1) = malloc(sizeof(Place) * l * 2);

            if (*(a.arr + i - 1) == NULL) {
                printf("erreur lors de l'allocation\n");
                exit(1);
            }

            for (int j = 0; j < l * 2; ++j) {
                a.arr[i - 1][j] = y;
            }

            a.taille[i] = 2*l;
            z = z + 2*l;
            l = -1;
        }

    }
    while(sec != 1) {
        printf("quel est le prix d'une place de classe 1\n");
        sec = scanf("%f", &a.classeA);
        if (sec != 1) {
            while (getchar() != '\n');
        }
    }
    sec = -1;
    while(sec != 1) {
        printf("quel est le prix d'une place de classe 2\n");
        sec = scanf("%f", &a.classeB);
        if (sec != 1) {
            while (getchar() != '\n');
        }
    }
    sec = -1;
    while(sec != 1) {
        printf("quel est le prix d'une place de classe 3\n");
        sec = scanf("%f", &a.classeC);
        if (sec != 1) {
            while (getchar() != '\n');
        }
    }
    if (z != a.siege) {
        printf("le nombre de siege annonce ne correspond pas au nombre de rangees et lignes\n");
        freeSalle(a);
        a = creerSalle();
    }
    ress = 0;
    a.date.jour = 0;
    a.date.mois = 0;
    a.date.annee = 0;
    int ressj = -1, ressm = -1, ressa = -1;
    while(ress != 3){
        while (ressa != 1 || a.date.annee < 2024){
            printf("entrez l'annee du concert\n");
            ressa = scanf("%d", &a.date.annee);
            if (ressa != 1) {
                while (getchar() != '\n');
            }
        }

        ress++;
        if((a.date.annee % 4 == 0 && a.date.annee % 100 != 0) || (a.date.annee % 400 == 0)){
            while (ressm != 1 || a.date.mois < 1 || a.date.mois > 12){
                printf("entrez le mois du concert\n");
                ressm = scanf("%d", &a.date.mois);
                if (ressm != 1) {
                    while (getchar() != '\n');
                }
            }
            ress++;
            if(a.date.mois == 1 || a.date.mois == 3 || a.date.mois == 5 || a.date.mois == 7 || a.date.mois == 8 || a.date.mois == 10 || a.date.mois == 12){
                while(ressj != 1 || a.date.jour <1 || a.date.jour > 31){
                    printf("entrez le jour du concert\n");
                    ressj = scanf("%d", &a.date.jour);
                    if (ressj != 1) {
                        while (getchar() != '\n');
                    }
                }
                ress++;
            } else if(a.date.mois == 4 || a.date.mois == 6 || a.date.mois == 9 || a.date.mois == 11){
                while(ressj != 1 || a.date.jour <1 || a.date.jour > 30){
                    printf("entrez le jour du concert\n");
                    ressj = scanf("%d", &a.date.jour);
                    if (ressj != 1) {
                        while (getchar() != '\n');
                    }
                }
                ress++;
            }else{
                while(ressj != 1 || a.date.jour <1 || a.date.jour > 29){
                    printf("entrez le jour du concert\n");
                    ressj = scanf("%d", &a.date.jour);
                    if (ressj != 1) {
                        while (getchar() != '\n');
                    }
                }
                ress++;
            }
        }else{
            while (ressm != 1 || a.date.mois < 1 || a.date.mois > 12){
                printf("entrez le mois du concert\n");
                ressm = scanf("%d", &a.date.mois);
                if (ressm != 1) {
                    while (getchar() != '\n');
                }
            }
            ress++;
            if(a.date.mois == 1 || a.date.mois == 3 || a.date.mois == 5 || a.date.mois == 7 || a.date.mois == 8 || a.date.mois == 10 || a.date.mois == 12){
                while(ressj != 1 || a.date.jour <1 || a.date.jour > 31){
                    printf("entrez le jour du concert\n");
                    ressj = scanf("%d", &a.date.jour);
                    if (ressj != 1) {
                        while (getchar() != '\n');
                    }
                }
                ress++;
            } else if(a.date.mois == 4 || a.date.mois == 6 || a.date.mois == 9 || a.date.mois == 11){
                while(ressj != 1 || a.date.jour <1 || a.date.jour > 30){
                    printf("entrez le jour du concert\n");
                    ressj = scanf("%d", &a.date.jour);
                    if (ressj != 1) {
                        while (getchar() != '\n');
                    }
                }
                ress++;
            }else{
                while(ressj != 1 || a.date.jour <1 || a.date.jour > 28){
                    printf("entrez le jour du concert\n");
                    ressj = scanf("%d", &a.date.jour);
                    if (ressj != 1) {

                    }
                }
                ress++;
            }
        }
    }
    ress = -1;
    char test[50];
    int l1;
    char* testc = NULL;

    while (testc == NULL) {
        printf("quel est le nom de l'artiste\n");
        while (getchar() != '\n');

        testc = fgets(test, 49, stdin);
        l1 = strlen(test);

        a.artiste = malloc(l1);
        verifAlloc(a.artiste);

        for (int i = 0; i < l1; ++i) {
            a.artiste[i] = test[i];
        }
        a.artiste[l1 - 1] = '\0';

        if (ress != 1) {
            while (getchar() != '\n');
        }
    }
    return a;
};

void afficheSalle(Salle a, int cle) {

    char *suffixe = ".SALLESAUVE";
    char aff[50] = "";
    strncpy(aff, a.nomFichier, 49);
    char *fin = strstr(aff, suffixe);

    if (fin != NULL) {
        *fin = '\0';
    }

    printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");
    a=comptePlace(a);
    printf("Nom de salle : %s\nNombre de siege libre de la salle : %d\nDate du concert : %d/%d/%d\nil s'agit d'un concert de %s\n", aff, (int)(a.siege - a.siegeres), a.date.jour, a.date.mois, a.date.annee, a.artiste);
    if(cle == 0){
        printf("il y a %d places libres de classe A\nil y a %d places libres de classe B\nil y a %d places libres de classe C\nil y a %d places reservees de classe A\nil y a %d places reservees de classe B\nil y a %d places reservees de classe C\n", a.places[0], a.places[1], a.places[2], a.places[3], a.places[4], a.places[5]);
    } else{
        printf("il y a %d places libres de classe A\nil y a %d places libres de classe B\nil y a %d places libres de classe C\n", a.places[0], a.places[1], a.places[2]);
    }

    if(a.fosse == 1){
        printf("il y a une fosse lors de ce concert\n");
    }
    printf("\nplan de la salle : \n");
    int l = plusGrand(a.taille, a.taille[0]);
    int d = 0;

    for (int i = 0; i < a.taille[0]; ++i) {
        if (i < 9) {
            printf("R%d |  ", i + 1);
        } else {
            printf("R%d|  ", i + 1);
        }
        d = decal(l, a.taille[i + 1]);
        decalPrint(d);

        for (int j = 0; j < a.taille[i + 1]; ++j) {

            if ((a.arr[i][j]).code == 0) {
                printf("O ");
            } else if ((a.arr[i][j]).code == 1) {
                printf("0 ");
            } else if ((a.arr[i][j]).code == 2) {
                printf("8 ");
            } else if ((a.arr[i][j]).code == 3) {
                printf("X ");
            } else if ((a.arr[i][j]).code == 4) {
                printf("X ");
            } else if ((a.arr[i][j]).code == 5) {
                printf("X ");
            }
        }
        printf("\n");
    }
    printf("\nLegende :\nClasse A (libre) : O\nClasse B (libre) : 0\nClasse C (libre) : 8\nClasse A (prise) : X\nClasse B (prise) : X\nClasse C (prise) : X\n");
    printf("\n");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");
}


void affichePlan(Salle a) {

    char *suffix = ".SALLESAUVE";
    char aff[50] = "";
    strncpy(aff, a.nomFichier, 49);
    char *pos = strstr(aff, suffix);

    if (pos != NULL) {
        *pos = '\0';
    }

    printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");
    a=comptePlace(a);
    printf("Nom de salle : %s\nNombre de siege libre de la salle : %d\nDate du concert : %d/%d/%d\nil s'agit d'un concert de %s\n", aff, (int)(a.siege - a.siegeres), a.date.jour, a.date.mois, a.date.annee, a.artiste);

    printf("il y a %d places libres de classe A\nil y a %d places libres de classe B\nil y a %d places libres de classe C\n", a.places[0], a.places[1], a.places[2]);


    if(a.fosse == 1){
        printf("il y a une fosse lors de ce concert\n");
    }
    printf("\nplan de la salle : \n");
    int l = plusGrand(a.taille, a.taille[0]);
    int d = 0;

    for (int i = 0; i < a.taille[0]; ++i) {
        if (i < 9) {
            printf("R%d |  ", i + 1);
        } else {
            printf("R%d|  ", i + 1);
        }
        d = decal(l, a.taille[i + 1]);
        decalPrint(d);

        for (int j = 0; j < a.taille[i + 1]; ++j) {

            if ((a.arr[i][j]).code == 0) {
                printf("O ");
            } else if ((a.arr[i][j]).code == 1) {
                printf("0 ");
            } else if ((a.arr[i][j]).code == 2) {
                printf("8 ");
            } else if ((a.arr[i][j]).code == 3) {
                printf("X ");
            } else if ((a.arr[i][j]).code == 4) {
                printf("X ");
            } else if ((a.arr[i][j]).code == 5) {
                printf("X ");
            }
        }
        printf("\n");
    }
    printf("\nLegende :\nClasse A (libre) : O\nClasse B (libre) : 0\nClasse C (libre) : 8\nClasse A (prise) : X\nClasse B (prise) : X\nClasse C (prise) : X\n");
    printf("\n");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

void freeSalle(Salle a) {
    free(a.nom);
    free(a.nomFichier);
    for (int i = 0; i < a.taille[0]; ++i) {
        free(*(a.arr + i));
    }
    free(a.arr);
    free(a.taille);
}

Salle modifSalle(Salle a, Date date) {
    if((date.annee < a.date.annee) || (date.annee == a.date.annee && date.mois <  a.date.mois) || (date.annee == a.date.annee && date.mois == a.date.mois && date.jour <= a.date.jour)){
        printf("le concert n'a pas encore eu lieu et ne peut pas etre modifie\n");
        return a;
    } else{
        for (int i = 1; i < a.taille[0] + 1; ++i) {
            for (int j = 0; j < a.taille[i]; ++j) {
                if( a.arr[i-1][j].code > 2) {
                    a.arr[i - 1][j].code -= 3;
                }
            }
        }
    }

    int res = -1;
    int c = -1;
    char tabs[50];
    int sec =-1;
    char *sectab = NULL;
    while (c != 6) {
        while (sec != 1 || c < 1 || c > 6) {
            printf("que voulez vous modifier, entrez le chiffre correspondant\n");
            printf("1) nom/nom fichier\n2) nombre de siege/disposition de la salle\n3) prix des places\n4) le nom de l'artiste jouant\n5) la date du concert\n6) quitter le mode de modification\n");
            sec = scanf("%d", &c);
            if(sec != 1){
                videTerminal();
                while (getchar() != '\n');
            }
        }
        sec = -1;
        if (c == 1) {

            while (sectab == NULL) {
                printf("entrez le nouveau nom de la salle\n");
                while (getchar() != '\n');
                sectab = fgets(tabs, 49, stdin);
            }
            char *suffixe = "\n";
            char *fin = strstr(tabs, suffixe);
            if (fin != NULL) {
                *fin = '\0';
            }
            sectab = NULL;
            int l = strlen(tabs);
            free(a.nom);
            free(a.nomFichier);

            a.nom = malloc(l);
            a.nomFichier = malloc(l + 11);
            verifAlloc(a.nom);
            verifAlloc(a.nomFichier);

            for (int i = 0; i <= l; ++i) {
                a.nom[i] = tabs[i];
                a.nomFichier[i] = tabs[i];
            }
            a.nomFichier[l] = '.';
            a.nomFichier[l + 1] = 'S';
            a.nomFichier[l + 2] = 'A';
            a.nomFichier[l + 3] = 'L';
            a.nomFichier[l + 4] = 'L';
            a.nomFichier[l + 5] = 'E';
            a.nomFichier[l + 6] = 'S';
            a.nomFichier[l + 7] = 'A';
            a.nomFichier[l + 8] = 'U';
            a.nomFichier[l + 9] = 'V';
            a.nomFichier[l + 10] = 'E';
            a.nomFichier[l + 11] = tabs[l];

            printf("le nouveau nom de la salle est : %s\nle nouveau nom du fichier est : %s\n", a.nom, a.nomFichier);
        } else if (c == 2) {
            int c1 = -1, c2 = -1;
            int r = -1, l = -1, k = -1;
            res = -1;
            while (res != 1 || c1 <= 0 || c1 > 2) {
                printf("voulez vous changer\n1)une rangee\n2)retour\n");
                res = scanf("%d", &c1);

                if (res != 1) {
                    while (getchar() != '\n');
                }
            }
            //==========================================================================================================
            res = -1;
            if (c1 == 1) {
                while (res != 1 || c2 < 0 || c2 > 2) {
                    printf("voulez vous\n1)ajouter une rangee\n2) modifier ou supprimer une rangee\n");
                    res = scanf("%d", &c2);
                    if (res != 1){
                        while (getchar() != '\n');
                    }
                }
                if(a.taille[0] == 0 && c2 == 2){
                    printf("\n\nvous ne pouvez pas modifier de rangee car il n'y en a plus\n\n");
                    c2 = -1;
                }
                res = -1;
                if (c2 == 1) {
                    res = -1;
                    while (res != 1 || r <= 0 || r > a.taille[0] + 1) {
                        printf("quelle rangee souhaiter vous rajouter\nvous pouvez selectionner une rangee de 1 a %d\n",
                               a.taille[0] + 1);
                        res = scanf("%d", &r);

                        if (res != 1){
                            while (getchar() != '\n');
                        }
                    }
                    a.taille[0]++;
                    Place **tab = NULL;
                    tab = malloc((a.taille[0]) * sizeof(Place *));

                    int *taille = NULL;
                    taille = malloc((a.taille[0] + 1) * sizeof(int));

                    verifAlloc(tab);

                    for (int i = 0; i < r - 1; ++i) {
                        tab[i] = a.arr[i];
                        taille[i] = a.taille[i];
                    }
                    taille[r - 1] = a.taille[r - 1];
                    res = -1;
                    while(res != 1) {
                        printf("quel est la taille de la rangee\n");
                        res = scanf("%d", &l);
                        if (res != 1) {
                            while (getchar() != '\n');
                        }
                    }

                    taille[r] = l;
                    res = -1;
                    while(res != 1) {
                        printf("qu'elle est la categorie de place de cette rangee\n1) classe A\n2) classe B\n3) classe C\n");
                        res = scanf("%d", &k);
                        if (res != 1) {
                            while (getchar() != '\n');
                        }
                    }
                    if(a.fosse == 1 && k == 1) {
                        tab[r - 1] = malloc(2 * l * sizeof(Place));
                        for (int i = 0; i < 2*l; ++i) {
                            tab[r - 1][i] = creerPlace(k);
                        }
                        for (int i = r; i < a.taille[0]; ++i) {
                            tab[i] = a.arr[i - 1];
                            taille[i + 1] = a.taille[i];
                        }
                    }
                    else{
                        tab[r - 1] = malloc(l * sizeof(Place));
                        for (int i = 0; i < l; ++i) {
                            tab[r - 1][i] = creerPlace(k);
                        }
                        for (int i = r; i < a.taille[0]; ++i) {
                            tab[i] = a.arr[i - 1];
                            taille[i + 1] = a.taille[i];
                        }
                    }



                    free(a.taille);
                    a.taille = taille;

                    free(a.arr);
                    a.arr = tab;
                    a.siege += l;
                    res = -1;
                } else if (c2 == 2) {
                    res = -1;
                    while (res != 1 || r <= 0 || r > a.taille[0]) {
                        printf("quelle rangee voulez vous modifer de 1 a %d\n", a.taille[0]);
                        res = scanf("%d", &r);
                        if (res != 1){
                            while (getchar() != '\n');
                        }
                    }
                    res = -1;
                    while (res != 1 || l < 0) {
                        printf("quel est la nouvelle taille de la rangee (0 pour supprimer la rangee)\n");
                        res = scanf("%d", &l);
                        if (res != 1){
                            while (getchar() != '\n');
                        }
                    }
                    if (l == 0) {
                        free(a.arr[r - 1]);
                        Place **tab1 = NULL;
                        tab1 = malloc((a.taille[0] - 1) * sizeof(Place *));
                        verifAlloc(tab1);

                        int *taille1 = NULL;
                        taille1 = malloc((a.taille[0]) * sizeof(int));
                        verifAlloc(taille1);

                        taille1[0] = a.taille[0] - 1;
                        a.siege -= a.taille[r];

                        for (int i = 1; i < r; ++i) {
                            taille1[i] = a.taille[i];
                        }
                        if(r < a.taille[0]) {
                            taille1[r] = a.taille[r + 1];

                            for (int i = r + 1; i < a.taille[0]; ++i) {
                                taille1[i] = a.taille[i + 1];
                            }
                        }
                        for (int i = 0; i < r - 1; ++i) {
                            tab1[i] = a.arr[i];
                        }
                        if(r < a.taille[0]) {
                            tab1[r - 1] = a.arr[r];

                            for (int i = r; i < a.taille[0] - 1; ++i) {
                                tab1[i] = a.arr[i + 1];
                            }
                        }
                        free(a.taille);
                        a.taille = taille1;
                        free(a.arr);
                        a.arr = tab1;

                        if(a.taille[0] == 0){
                            a.arr = malloc(sizeof(Place *));
                            free(a.taille);
                            a.taille = malloc(2*sizeof(int));
                            a.taille[0] = 0;
                            a.taille[1] = 1;
                        }


                    } else {
                        k = (a.arr[r - 1][0].code);
                        free(a.arr[r - 1]);
                        if(a.fosse == 1 && k == 0){
                            a.arr[r - 1] = malloc(2 * l * sizeof(Place));

                            for (int i = 0; i < 2 * l; ++i) {
                                a.arr[r - 1][i] = creerPlace(k + 1);
                            }
                            if (2 * l < a.taille[r]) {
                                a.siege -=  2 *l;
                            } else if (2 * l > a.taille[r]) {
                                a.siege += l * 2;
                            }

                            a.taille[r] = l * 2;
                        }else {
                            a.arr[r - 1] = malloc(l * sizeof(Place));

                            for (int i = 0; i < l; ++i) {
                                a.arr[r - 1][i] = creerPlace(k + 1);
                            }
                            if (l < a.taille[r]) {
                                a.siege -= l;
                            } else if (l > a.taille[r]) {
                                a.siege += l;
                            }

                            a.taille[r] = l;
                        }
                    }
                }

            }
            //==========================================================================================================
        } else if (c == 3) {
            int k;
            float p;
            res = -1;
            while (res != 1 || k < 1 || k > 3) {
                printf("quelle categorie voulez vous modifer\n1) A\n2) B\n3) C\n");
                res = scanf("%d", &k);
                if (res != 1){
                    while (getchar() != '\n');
                }
            }
            res = -1;
            switch (k) {
                case 1:
                    while (res != 1) {
                        printf("quel est le nouveau prix\n");
                        res = scanf("%f", &p);
                        if (res != 1) {
                            while (getchar() != '\n');
                        }
                    }
                    a.classeA = p;
                    break;
                case 2:
                    while (res != 1) {
                        printf("quel est le nouveau prix\n");
                        res = scanf("%f", &p);
                        if (res != 1) {
                            while (getchar() != '\n');
                        }
                    }
                    a.classeB = p;
                    break;
                case 3:
                    while (res != 1) {
                        printf("quel est le nouveau prix\n");
                        res = scanf("%f", &p);
                        if (res != 1) {
                            while (getchar() != '\n');
                        }
                    }
                    a.classeC = p;
                    break;
            }
        } else if (c == 4) {
            char test[50];
            int l1;
            char *testc = NULL;
            free(a.artiste);

            while (testc == NULL) {
                printf("quel est le nom de l'artiste\n");
                while (getchar() != '\n');

                testc = fgets(test, 49, stdin);
                l1 = strlen(test);

                a.artiste = malloc(l1);
                verifAlloc(a.artiste);

                for (int i = 0; i < l1; ++i) {
                    a.artiste[i] = test[i];
                }
                a.artiste[l1 - 1] = '\0';
            }
        } else if (c == 5){
            int ress = 0;
            a.date.jour = 0;
            a.date.mois = 0;
            a.date.annee = 0;
            int ressj = -1, ressm = -1, ressa = -1;
            while(ress != 3){
                while (ressa != 1 || a.date.annee < 2024){
                    printf("entrez l'annee du concert\n");
                    ressa = scanf("%d", &a.date.annee);
                    if (ressa != 1) {
                        while (getchar() != '\n');
                    }
                }

                ress++;
                if((a.date.annee % 4 == 0 && a.date.annee % 100 != 0) || (a.date.annee % 400 == 0)){
                    while (ressm != 1 || a.date.mois < 1 || a.date.mois > 12){
                        printf("entrez le mois du concert\n");
                        ressm = scanf("%d", &a.date.mois);
                        if (ressm != 1) {
                            while (getchar() != '\n');
                        }
                    }
                    ress++;
                    if(a.date.mois == 1 || a.date.mois == 3 || a.date.mois == 5 || a.date.mois == 7 || a.date.mois == 8 || a.date.mois == 10 || a.date.mois == 12){
                        while(ressj != 1 || a.date.jour <1 || a.date.jour > 31){
                            printf("entrez le jour du concert\n");
                            ressj = scanf("%d", &a.date.jour);
                            if (ressj != 1) {
                                while (getchar() != '\n');
                            }
                        }
                        ress++;
                    } else if(a.date.mois == 4 || a.date.mois == 6 || a.date.mois == 9 || a.date.mois == 11){
                        while(ressj != 1 || a.date.jour <1 || a.date.jour > 30){
                            printf("entrez le jour du concert\n");
                            ressj = scanf("%d", &a.date.jour);
                            if (ressj != 1) {
                                while (getchar() != '\n');
                            }
                        }
                        ress++;
                    }else{
                        while(ressj != 1 || a.date.jour <1 || a.date.jour > 29){
                            printf("entrez le jour du concert\n");
                            ressj = scanf("%d", &a.date.jour);
                            if (ressj != 1) {
                                while (getchar() != '\n');
                            }
                        }
                        ress++;
                    }
                }else{
                    while (ressm != 1 || a.date.mois < 1 || a.date.mois > 12){
                        printf("entrez le mois du concert\n");
                        ressm = scanf("%d", &a.date.mois);
                        if (ressm != 1) {
                            while (getchar() != '\n');
                        }
                    }
                    ress++;
                    if(a.date.mois == 1 || a.date.mois == 3 || a.date.mois == 5 || a.date.mois == 7 || a.date.mois == 8 || a.date.mois == 10 || a.date.mois == 12){
                        while(ressj != 1 || a.date.jour <1 || a.date.jour > 31){
                            printf("entrez le jour du concert\n");
                            ressj = scanf("%d", &a.date.jour);
                            if (ressj != 1) {
                                while (getchar() != '\n');
                            }
                        }
                        ress++;
                    } else if(a.date.mois == 4 || a.date.mois == 6 || a.date.mois == 9 || a.date.mois == 11){
                        while(ressj != 1 || a.date.jour <1 || a.date.jour > 30){
                            printf("entrez le jour du concert\n");
                            ressj = scanf("%d", &a.date.jour);
                            if (ressj != 1) {
                                while (getchar() != '\n');
                            }
                        }
                        ress++;
                    }else{
                        while(ressj != 1 || a.date.jour <1 || a.date.jour > 28){
                            printf("entrez le jour du concert\n");
                            ressj = scanf("%d", &a.date.jour);
                            if (ressj != 1) {

                            }
                        }
                        ress++;
                    }
                }
            }
        }
    }
    return a;
}


