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

    while (res == NULL) {
        printf("entrez le nom de la salle\n");
        while (getchar() != '\n');
        res = fgets(chaine, 49, stdin);
        str = strlen(chaine);
        chaine[str-1] = '\0';
    }

    int b = (int)strlen(chaine) + 1;
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
        printf("y a t'il une fosse durant ce concert\n1) oui\n2) non\n");
        ress = scanf("%d", &a.fosse);

        if (ress != 1) {
            while (getchar() != '\n');
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
        ress = -1;
        x = -1;
        while (ress != 1 || x < 1 || x > 3) {
            printf("qu'elle est la categorie de place de cette rangée\n1) Classe A\n2) Classe B\nClasse C\n");
            ress = scanf("%d", &x);

            if (ress != 1) {
                while (getchar() != '\n');
            }
        }

        y = creerPlace(x);

        if(x != 1 || a.fosse == 2) {
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
        } else if(x == 1 && a.fosse == 1){
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
    printf("quel est le prix d'une place de classe 1\n");
    scanf("%f", &a.classeA);
    printf("quel est le prix d'une place de classe 2\n");
    scanf("%f", &a.classeB);
    printf("quel est le prix d'une place de classe 3\n");
    scanf("%f", &a.classeC);

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
            printf("entrez l'année du concert\n");
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

        printf("quel est le nom de l'artiste\n");
        while (getchar() != '\n');

        fgets(test, 49, stdin);
        l1 = strlen(test);

        a.artiste = malloc(l1);
        verifAlloc(a.artiste);

        for (int i = 0; i < l1; ++i) {
            a.artiste[i] = test[i];
        }
        a.artiste[l1 -1] = '\0';

        if (ress != 1) {
            while (getchar() != '\n');
        }

        printf("%s\n", a.artiste);


    return a;
};

void afficheSalle(Salle a) {
    printf("Nom de salle : %s\nNombre de siege libre de la salle : %d\nDate du concert : %d/%d/%d\nil s'agit d'un concert de %s\nplan de la salle : \n", a.nom, a.siege - a.siegeres, a.date.jour, a.date.mois, a.date.annee, a.artiste);

    if(a.fosse == 1){
        printf("il y a une fosse lors de ce concert\n");
    }

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
}


void affichePlan(Salle a) {
    printf("plan de la salle : \n", a.nom, a.siege, a.taille[0]);

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

Salle modifSalle(Salle a, char *nom) {
    int c = -1;
    char tab[50];
    while (c != 4) {
        printf("que voulez vous modifier, entrez le chiffre correspondant\n");
        printf("1) nom/nom fichier\n2) nombre de siege/disposition de la salle\n3) prix des places\n4) quitter le mode de modification\n");
        scanf("%d", &c);
    

    if (c == 1) {
        printf("entrez le nouveau nom de la salle\n");
        scanf("%s", tab);
        int l = strlen(tab);

        free(a.nom);
        free(a.nomFichier);

        a.nom = malloc(l);
        a.nomFichier = malloc(l + 11);
        verifAlloc(a.nom);
        verifAlloc(a.nomFichier);

        for (int i = 0; i <= l; ++i) {
            a.nom[i] = tab[i];
            a.nomFichier[i] = tab[i];
        }
        a.nomFichier[l] = '.';
        a.nomFichier[l+1] = 'S';
        a.nomFichier[l + 2] = 'A';
        a.nomFichier[l + 3] = 'L';
        a.nomFichier[l + 4] = 'L';
        a.nomFichier[l + 5] = 'E';
        a.nomFichier[l + 6] = 'S';
        a.nomFichier[l + 7] = 'A';
        a.nomFichier[l + 8] = 'U';
        a.nomFichier[l + 9] = 'V';
        a.nomFichier[l + 10] = 'E';
        a.nomFichier[l + 11] = tab[l];

        printf("le nouveau nom de la salle est : %s\nle nouveau nom du fichier est : %s\n", a.nom, a.nomFichier);
        remove(nom);
    } else if (c == 2) {
        int c1 = -1, c2 = -1;
        int r = -1, l = -1, k = -1;

        while (c1 <= 0 || c1 > 3) {
            printf("voulez vous changer\n1)une rangee\n2)le nombre de rangee\n");
            scanf("%d", &c1);
        }
        //==========================================================================================================
        if (c1 == 1) {
            while (c2 <= 0 || c2 > 2) {
                printf("voulez vous \n1)ajouter une rangee\n2) modifier ou supprimer une rangee\n");
                scanf("%d", &c2);
            }
            if (c2 == 1) {
                while (r <= 0 || r > a.taille[0]+1) {
                    printf("quelle rangee souhaiter vous rajouter\nvous pouvez selectionner une rangee de 1 a %d\n",
                           a.taille[0] + 1);
                    scanf("%d", &r);
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

                printf("quel est la taille de la rangee\n");
                scanf("%d", &l);

                taille[r] = l;

                printf("qu'elle est la categorie de place de cette rangée\n");
                scanf("%d", &k);

                tab[r - 1] = malloc(l * sizeof(Place));

                for (int i = 0; i < l; ++i) {
                    tab[r - 1][i] = creerPlace(k);
                }

                for (int i = r; i < a.taille[0]; ++i) {
                    tab[i] = a.arr[i - 1];
                    taille[i + 1] = a.taille[i];
                }
                free(a.taille);
                a.taille = taille;

                free(a.arr);
                a.arr = tab;
                a.siege += l;

            } else if (c2 == 2) {
                while (r <= 0) {
                    printf("quelle rangee voulez vous modifer de 1 a %d\n", a.taille[0]);
                    scanf("%d", &r);
                }
                while (l < 0) {
                    printf("quel est la nouvelle taille de la rangee (0 pour supprimer la rangee)\n");
                    scanf("%d", &l);
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

                    for (int i = 1; i < r + 1; ++i) {
                        taille1[i] = a.taille[i];
                    }

                    taille1[r + 1] = a.taille[r + 2];

                    for (int i = r + 2; i < a.taille[0]; ++i) {
                        taille1[i] = a.taille[i + 1];
                    }

                    for (int i = 0; i < r - 1; ++i) {
                        tab1[i] = a.arr[i];
                    }

                    tab1[r - 1] = a.arr[r];

                    for (int i = r; i < a.taille[0] - 1; ++i) {
                        tab1[i] = a.arr[i + 1];
                    }

                    free(a.taille);
                    a.taille = taille1;
                    free(a.arr);
                    a.arr = tab1;


                } else {
                    free(a.arr[r - 1]);
                    k = (int) (a.arr[r - 1][0].classe - 16);
                    a.arr[r - 1] = malloc(l * sizeof(Place));

                    for (int i = 0; i < l; ++i) {
                        a.arr[r - 1][i] = creerPlace(k);
                    }
                    if(l<a.taille[r]){
                        a.siege-=l;
                    } else if(l>a.taille[r]){
                        a.siege+=l;
                    }

                    a.taille[r] = l;

                }
            }

        }
        //==========================================================================================================
    }
    else if(c==3){
        int k;
        float p;
        while (k<1 || k>3) {
            printf("quelle categorie voulez vous modifer\n1) A\n2) B\n3) C\n");
            scanf("%d", &k);
        }
        switch (k) {
            case 1:
                printf("quelle est le nouveau prix\n");
                scanf("%f", &p);
                a.classeA = p;
                break;
            case 2:
                printf("quelle est le nouveau prix\n");
                scanf("%f", &p);
                a.classeB = p;
                break;
            case 3:
                printf("quelle est le nouveau prix\n");
                scanf("%f", &p);
                a.classeC = p;
                break;
        }
    }
}
    return a;
}

