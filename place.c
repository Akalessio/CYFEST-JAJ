
#include "place.h"
#include "salle.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fonx.h"


Place creerPlace(int a) {
    Place c;
    c.classe = 0;

    while (c.classe != 'A' && c.classe != 'B' && c.classe != 'C') {
        if (a == 1) {
            c.classe = 'A';
            c.code = 0;
        } else if (a == 2) {
            c.classe = 'B';
            c.code = 1;
        } else if (a == 3) {
            c.classe = 'C';
            c.code = 2;
        } else {
            printf("entrez une categorie de siege disponible : 1, 2 ou 3\n");
            scanf("%d", &a);
        }
    }
    c.res = 0;


    /*if(c.classe == 'A' && c.res == 0){
        c.code == 0;
    }
    else if (c.classe == 'B' && c.res == 0){
        c.code == 1;
    }
    else if (c.classe == 'C' && c.res == 0){
        c.code == 2;
    }
    else if (c.classe == 'A' && c.res == 1){
        c.code == 3;
    }
    else if (c.classe == 'B' && c.res == 1){
        c.code == 4;
    }
    else if (c.classe == 'C' && c.res == 1){
        c.code == 5;
    }*/

    return c;
}

void devPlace(Place *a) {

    if (a->code == 0) {
        a->classe = 'A';
        a->res = 0;
    } else if (a->code == 1) {
        a->classe = 'B';
        a->res = 0;
    } else if (a->code == 2) {
        a->classe = 'C';
        a->res = 0;
    } else if (a->code == 3) {
        a->classe = 'A';
        a->res = 1;
    } else if (a->code == 4) {
        a->classe = 'B';
        a->res = 1;
    } else if (a->code == 5) {
        a->classe = 'C';
        a->res = 1;
    }
}

Salle verifSiege(Salle a) {
    a.siegeres = 0;
    for (int i = 1; i < a.taille[0] + 1; ++i) {
        for (int j = 0; j < a.taille[i]; ++j) {
            if (a.arr[i - 1][j].res == 1) {
                a.siegeres++;
            }
        }
    }
    return a;
}

Salle reservePlace(Salle a) {
    int res = -1;
    int c = -1;
    affichePlan(a);
    a = comptePlace(a);

    int p = -1;

    int r = 0, l = 0, v = 0;

    while (p <= 0 || p > a.siege - a.siegeres) {
        printf("combien de places voulez vous reservez\n");
        scanf("%d", &p);
    }

    for (int i = 0; i < p; ++i) {
        res = -1;
        v = -1;
        printf("il y a %d places libres de classe A\nil y a %d places libres de classe B\nil y a %d places libres de classe C\n", a.places[0], a.places[1], a.places[2]);

        if(a.fosse == 1 && a.places[0] != 0) {
            while (res != 1 || c < 1 || c > 2) {

                printf("voulez vous une place en fosse\n1) oui\n2) non\n");
                res = scanf("%d", &c);

                if(res != 1){
                    while (getchar() != '\n');
                }
            }
            res = -1;
            if(c == 1){
                printf("le prix d'une place en fosse est de %fe", a.classeA);

                while (res != 1 || v != 0 && v != 1) {
                    printf("etes vous sur de vouloir reserver cette place\n1) oui\n0) non\n");
                    res = scanf("%d", &v);

                    if(res != 1){
                        while (getchar() != '\n');
                    }

                    if (v == 1) {
                        for (int j = 1; j < a.taille[0]+1; ++j) {
                            for (int k = 0; k < a.taille[j]; ++k) {
                                if(a.arr[i-1][j].res != 1){
                                    a.arr[i-1][j].res = 1;
                                    j=a.taille[0]+3;
                                }
                            }
                        }
                        continue;
                    }
                    if (v == 0) {
                        i--;
                        continue;
                    }
                }

            }
        }
        v = -1;
        r = -1;
        l = -1;

        while (r > a.taille[0] - 1 || r <= 0) {
            printf("rentrez le numero de la rangee\n");
            scanf("%d", &r);
        }
        while (l > a.taille[r + 1] - 1 || l <= 0) {
            printf("rentrez le numero de la ligne\n");
            scanf("%d", &l);
        }

        if (a.arr[r - 1][l - 1].res == 1) {
            printf("cette place est deja reserve choississez en une autre\n");
            i--;
            continue;
        }

        if (a.arr[r - 1][l - 1].classe == 'A') {
            printf("le prix de la place est de %fe\n", a.classeA);
        } else if (a.arr[r - 1][l - 1].classe == 'B') {
            printf("le prix de la place est de %fe\n", a.classeB);
        } else if (a.arr[r - 1][l - 1].classe == 'C') {
            printf("le prix de la place est de %fe\n", a.classeC);
        }
        res = -1;
        while (res != 1 || v != 0 && v != 1) {
            printf("etes vous sur de vouloir reserver cette place\n1 pour oui\n0 pour non\n");
            res = scanf("%d", &v);

            if (v == 1) {
                a.arr[r - 1][l - 1].res = 1;
            }
            if (v == 0) {
                i--;
                continue;
            }
        }

    }
    actualiseSiege(a);
    a = verifSiege(a);
    return a;
}

Salle actualiseSiege(Salle a) {

    for (int i = 1; i < a.taille[0] + 1; ++i) {
        for (int j = 0; j < a.taille[i]; ++j) {
            if (a.arr[i - 1][j].classe == 'A' && a.arr[i - 1][j].res == 0) {
                a.arr[i - 1][j].code = 0;
            } else if (a.arr[i - 1][j].classe == 'B' && a.arr[i - 1][j].res == 0) {
                a.arr[i - 1][j].code = 1;
            } else if (a.arr[i - 1][j].classe == 'C' && a.arr[i - 1][j].res == 0) {
                a.arr[i - 1][j].code = 2;
            } else if (a.arr[i - 1][j].classe == 'A' && a.arr[i - 1][j].res == 1) {
                a.arr[i - 1][j].code = 3;
            } else if (a.arr[i - 1][j].classe == 'B' && a.arr[i - 1][j].res == 1) {
                a.arr[i - 1][j].code = 4;
            } else if (a.arr[i - 1][j].classe == 'C' && a.arr[i - 1][j].res == 1) {
                a.arr[i - 1][j].code = 5;
            }
        }
    }
    return a;
}

Salle comptePlace(Salle a){
    a.places[0] = 0;
    a.places[1] = 0;
    a.places[2] = 0;
    a.places[3] = 0;
    a.places[4] = 0;
    a.places[5] = 0;

    for (int i = 1; i < a.taille[0]+1; ++i) {
        for (int j = 0; j < a.taille[i]; ++j) {
            if(a.arr[i-1][j].code == 0){
                a.places[0]++;
            }if(a.arr[i-1][j].code == 1){
                a.places[1]++;
            }if(a.arr[i-1][j].code == 2){
                a.places[2]++;
            }if(a.arr[i-1][j].code == 3){
                a.places[3]++;
            }if(a.arr[i-1][j].code == 4){
                a.places[4]++;
            }if(a.arr[i-1][j].code == 5){
                a.places[5]++;
            }
        }
    }

    return a;
}
