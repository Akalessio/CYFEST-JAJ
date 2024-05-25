
#include "place.h"
#include "salle.h"
#include <stdio.h>

// Cette fonction crée une place en fonction de la catégorie spécifiée.
// Elle prend en paramètre un entier représentant la catégorie de la place.
// Si la catégorie spécifiée est valide (1 pour A, 2 pour B, 3 pour C), elle crée une place avec cette catégorie.
// Sinon, elle demande à l'utilisateur de saisir une catégorie valide.
Place creerPlace(int a) {
    Place c; // Déclaration d'une nouvelle place
    int res = -1; // Variable de contrôle pour la saisie
    c.classe = 0; // Initialisation de la classe à 0

    // Boucle tant que la classe de la place n'est pas valide (A, B ou C)
    while (c.classe != 'A' && c.classe != 'B' && c.classe != 'C') {
        // Si la catégorie spécifiée est 1, la classe de la place est A
        if (a == 1) {
            c.classe = 'A'; // Définition de la classe de la place
            c.code = 0; // Code correspondant à la classe A
        }
            // Si la catégorie spécifiée est 2, la classe de la place est B
        else if (a == 2) {
            c.classe = 'B'; // Définition de la classe de la place
            c.code = 1; // Code correspondant à la classe B
        }
            // Si la catégorie spécifiée est 3, la classe de la place est C
        else if (a == 3) {
            c.classe = 'C'; // Définition de la classe de la place
            c.code = 2; // Code correspondant à la classe C
        }
            // Si la catégorie spécifiée n'est pas valide
        else {
            // Boucle tant que l'utilisateur ne saisit pas une catégorie valide
            while(res != 1) {
                printf("entrez une categorie de siege disponible : 1, 2 ou 3\n");
                res = scanf("%d", &a); // Saisie de la catégorie
                // Si la saisie échoue, vide le tampon d'entrée
                if (res != 1) {
                    while (getchar() != '\n');
                }
            }
        }
    }
    c.res = 0; // Initialisation de la réservation à 0

    return c; // Retourne la place créée
}

// Cette fonction met à jour les informations d'une place en fonction de son code.
// Elle prend en paramètre un pointeur vers une place.
void devPlace(Place *a) {
    // Selon le code de la place, met à jour la classe et l'état de réservation
    if (a->code == 0) {
        a->classe = 'A'; // Classe de la place : A
        a->res = 0; // Non réservée
    } else if (a->code == 1) {
        a->classe = 'B'; // Classe de la place : B
        a->res = 0; // Non réservée
    } else if (a->code == 2) {
        a->classe = 'C'; // Classe de la place : C
        a->res = 0; // Non réservée
    } else if (a->code == 3) {
        a->classe = 'A'; // Classe de la place : A
        a->res = 1; // Réservée
    } else if (a->code == 4) {
        a->classe = 'B'; // Classe de la place : B
        a->res = 1; // Réservée
    } else if (a->code == 5) {
        a->classe = 'C'; // Classe de la place : C
        a->res = 1; // Réservée
    }
}
// Cette fonction vérifie le nombre de sièges réservés dans une salle et met à jour le compteur siegeres.
// Elle prend en paramètre une salle.
// Elle retourne la salle mise à jour.
Salle verifSiege(Salle a) {
    // Initialise le compteur de sièges réservés à 0
    a.siegeres = 0;

    // Parcourt tous les rangs et toutes les places dans la salle
    for (int i = 1; i < a.taille[0] + 1; ++i) {
        for (int j = 0; j < a.taille[i]; ++j) {
            // Si la place est réservée, incrémente le compteur de sièges réservés
            if (a.arr[i - 1][j].res == 1) {
                a.siegeres++;
            }
        }
    }

    // Retourne la salle mise à jour avec le nombre de sièges réservés
    return a;
}

// Cette fonction permet de réserver des places dans une salle.
// Elle prend en paramètre une salle.
// Elle retourne la salle mise à jour avec les places réservées.
Salle reservePlace(Salle a) {
    // Initialise les variables de contrôle
    int res = -1;
    int c = -1;

    // Affiche le plan de la salle et compte les places disponibles
    affichePlan(a);
    a = comptePlace(a);

    // Demande le nombre de places à réserver
    int p = -1;

    int r = 0, l = 0, v = 0;

    // Vérifie que le nombre de places à réserver est valide
    while (res != 1 || p <= 0 || p > a.siege - a.siegeres) {
        printf("combien de places voulez vous reservez\n");
        res = scanf("%d", &p);
        if (res != 1){
            while (getchar() != '\n');
        }
    }

    // Affiche le nombre de places disponibles par classe
    printf("il y a %d places libres de classe A\nil y a %d places libres de classe B\nil y a %d places libres de classe C\n", a.places[0], a.places[1], a.places[2]);

    // Variable pour contrôler la réservation de places en fosse
    int b = 0;

    // Boucle pour réserver les places demandées
    for (int i = 0; i < p; ++i) {
        res = -1;
        v = -1;

        // Vérifie si la salle a des places en fosse disponibles
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
                while (res != 1 || (v != 0 && v != 1)) {
                    printf("etes vous sur de vouloir reserver cette place\n1) oui\n0) non\n");
                    res = scanf("%d", &v);
                    if(res != 1){
                        while (getchar() != '\n');
                    }

                    // Réserve la place si l'utilisateur confirme
                    if (v == 1) {
                        for (int j = 1; j < a.taille[0]+1; ++j) {
                            for (int k = 0; k < a.taille[j]; ++k) {
                                if(a.arr[j-1][k].res != 1){
                                    a.arr[j-1][k].res = 1;
                                    b = 1;
                                    break;
                                }
                            }
                            if(b == 1){
                                break;
                            }
                        }
                        continue;
                    }
                    // Ignore la réservation si l'utilisateur annule
                    if (v == 0) {
                        i--;
                        b = 1;
                        continue;
                    }
                }

            }
        }
        if(b == 1){
            b = 0;
            continue;
        }
        v = -1;
        r = -1;
        l = -1;
        res = -1;

        // Demande le numéro de la rangée
        while (res != 1 || r > a.taille[0] || r <= 0) {
            printf("rentrez le numero de la rangee\n");
            res = scanf("%d", &r);

            if(res != 1){
                while (getchar() != '\n');
            }
        }
        res = -1;

        // Demande le numéro de la place dans la rangée
        while (res != 1 || l > a.taille[r] || l <= 0) {
            printf("rentrez le numero de la ligne\n");
            res = scanf("%d", &l);
            if(res != 1){
                while (getchar() != '\n');
            }
        }

        // Vérifie si la place est déjà réservée
        if (a.arr[r - 1][l - 1].res == 1) {
            printf("cette place est deja reserve choississez en une autre\n");
            i--;
            continue;
        }

        // Affiche le prix de la place selon sa classe
        if (a.arr[r - 1][l - 1].classe == 'A') {
            printf("le prix de la place est de %fe\n", a.classeA);
        } else if (a.arr[r - 1][l - 1].classe == 'B') {
            printf("le prix de la place est de %fe\n", a.classeB);
        } else if (a.arr[r - 1][l - 1].classe == 'C') {
            printf("le prix de la place est de %fe\n", a.classeC);
        }
        res = -1;

        // Demande confirmation pour réserver la place
        while (res != 1 || v != 0 && v != 1) {
            printf("etes vous sur de vouloir reserver cette place\n1 pour oui\n0 pour non\n");
            res = scanf("%d", &v);
            if (res != 1){
                while (getchar() != '\n');
            }
        }

        // Réserve la place si l'utilisateur confirme
        if (v == 1) {
            a.arr[r - 1][l - 1].res = 1;
        }
        // Ignore la réservation si l'utilisateur annule
        if (v == 0) {
            i--;
        }
    }
    // Actualise les données sur les sièges réservés dans la salle
    actualiseSiege(a);
    a = verifSiege(a);
    return a;
}


// Cette fonction met à jour le code des places dans la salle en fonction de leur classe et de leur statut de réservation.
// Elle prend en paramètre une salle.
// Elle retourne la salle mise à jour avec les codes des places actualisés.
Salle actualiseSiege(Salle a) {
    // Parcourt toutes les rangées de la salle
    for (int i = 1; i < a.taille[0] + 1; ++i) {
        // Parcourt toutes les places dans la rangée
        for (int j = 0; j < a.taille[i]; ++j) {
            // Si la place est de classe A et non réservée, son code est 0
            if (a.arr[i - 1][j].classe == 'A' && a.arr[i - 1][j].res == 0) {
                a.arr[i - 1][j].code = 0;
            }
                // Si la place est de classe B et non réservée, son code est 1
            else if (a.arr[i - 1][j].classe == 'B' && a.arr[i - 1][j].res == 0) {
                a.arr[i - 1][j].code = 1;
            }
                // Si la place est de classe C et non réservée, son code est 2
            else if (a.arr[i - 1][j].classe == 'C' && a.arr[i - 1][j].res == 0) {
                a.arr[i - 1][j].code = 2;
            }
                // Si la place est de classe A et réservée, son code est 3
            else if (a.arr[i - 1][j].classe == 'A' && a.arr[i - 1][j].res == 1) {
                a.arr[i - 1][j].code = 3;
            }
                // Si la place est de classe B et réservée, son code est 4
            else if (a.arr[i - 1][j].classe == 'B' && a.arr[i - 1][j].res == 1) {
                a.arr[i - 1][j].code = 4;
            }
                // Si la place est de classe C et réservée, son code est 5
            else if (a.arr[i - 1][j].classe == 'C' && a.arr[i - 1][j].res == 1) {
                a.arr[i - 1][j].code = 5;
            }
        }
    }
    return a;
}


// Cette fonction compte le nombre de places disponibles dans chaque classe de la salle.
// Elle prend en paramètre une salle.
// Elle retourne la salle avec le nombre de places disponibles dans chaque classe mis à jour.
Salle comptePlace(Salle a){
    // Initialise le compteur de places disponibles dans chaque classe à 0
    a.places[0] = 0;
    a.places[1] = 0;
    a.places[2] = 0;
    a.places[3] = 0;
    a.places[4] = 0;
    a.places[5] = 0;

    // Parcourt toutes les rangées de la salle
    for (int i = 1; i < a.taille[0]+1; ++i) {
        // Parcourt toutes les places dans la rangée
        for (int j = 0; j < a.taille[i]; ++j) {
            // Incrémente le compteur de la classe correspondante selon le code de la place
            if(a.arr[i-1][j].code == 0){
                a.places[0]++;
            }
            if(a.arr[i-1][j].code == 1){
                a.places[1]++;
            }
            if(a.arr[i-1][j].code == 2){
                a.places[2]++;
            }
            if(a.arr[i-1][j].code == 3){
                a.places[3]++;
            }
            if(a.arr[i-1][j].code == 4){
                a.places[4]++;
            }
            if(a.arr[i-1][j].code == 5){
                a.places[5]++;
            }
        }
    }

    return a;
}
