#include "salle.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fonx.h"
#include "place.h"


// Cette fonction crée une nouvelle salle en demandant à l'utilisateur de fournir les informations nécessaires.
Salle creerSalle(void) {
    Salle a;
    char chaine[50];
    char *res = NULL;
    int ress;
    int str;
    int sec = -1;

    // Demande le nom de la salle à l'utilisateur
    while (res == NULL) {
        printf("Entrez le nom de la salle :\n");
        while (getchar() != '\n');
        res = fgets(chaine, 49, stdin);
        str = strlen(chaine);
        chaine[str - 1] = '\0'; // Supprime le retour à la ligne

        // Alloue dynamiquement de la mémoire pour stocker le nom de la salle
        a.nom = NULL;
        a.nom = malloc(str);
        a.nomFichier = NULL;
        a.nomFichier = malloc(str + 11);

        if (a.nom == NULL || a.nomFichier == NULL) {
            printf("Erreur lors de l'allocation de mémoire\n");
            exit(1);
        }

        // Vérifie et copie le nom de la salle dans la structure
        verifNom(chaine);
        for (int i = 0; i < str; ++i) {
            a.nom[i] = chaine[i];
            a.nomFichier[i] = chaine[i];
        }
        a.nom[str - 1] = '\0';

        // Ajoute l'extension ".SALLESAUVE" au nom du fichier de sauvegarde
        a.nomFichier[str - 1] = '.';
        a.nomFichier[str] = 'S';
        a.nomFichier[str + 1] = 'A';
        a.nomFichier[str + 2] = 'L';
        a.nomFichier[str + 3] = 'L';
        a.nomFichier[str + 4] = 'E';
        a.nomFichier[str + 5] = 'S';
        a.nomFichier[str + 6] = 'A';
        a.nomFichier[str + 7] = 'U';
        a.nomFichier[str + 8] = 'V';
        a.nomFichier[str + 9] = 'E';
        a.nomFichier[str + 10] = chaine[str - 1];
    }

    // Demande le nombre de sièges dans la salle
    a.siege = -1;
    ress = -1;
    while (a.siege <= 0 || ress != 1) {
        printf("Combien de sièges dans votre salle ?\n");
        ress = scanf("%d", &a.siege);
        if (ress != 1) {
            while (getchar() != '\n');
        }
    }

    // Demande le nombre de rangées de sièges dans la salle
    int r = -1;
    ress = -1;
    while (r <= 0 || ress != 1) {
        printf("Combien de rangées de sièges dans votre salle ?\n");
        ress = scanf("%d", &r);
        if (ress != 1) {
            while (getchar() != '\n');
        }
    }

    // Alloue dynamiquement de la mémoire pour stocker les tailles des rangées
    a.taille = NULL;
    a.taille = calloc(r + 1, sizeof(int));

    if (a.taille == NULL) {
        printf("Erreur lors de l'allocation de mémoire\n");
        exit(1);
    }

    // Initialise le nombre de rangées
    a.taille[0] = r;

    // Alloue dynamiquement de la mémoire pour stocker les sièges
    a.arr = NULL;
    a.arr = malloc(sizeof(Place *) * r);

    if (a.arr == NULL) {
        printf("Erreur lors de l'allocation de mémoire\n");
        exit(1);
    }

    // Demande s'il y a une fosse dans la salle
    a.fosse = -1;
    ress = -1;
    while (ress != 1 || a.fosse < 1 || a.fosse > 2) {
        printf("Y a-t-il une fosse durant ce concert ?\n1) Oui\n2) Non (les rangées en classe A auront le double de sièges)\n");
        ress = scanf("%d", &a.fosse);
        if (ress != 1) {
            while (getchar() != '\n');
        }
    }

    // Demande le nombre de rangées de classe A
    ress = -1;
    int x = -1;
    while (ress != 1 || x > a.taille[0]) {
        printf("Combien de rangées de classe A ?\n");
        ress = scanf("%d", &x);
        if (ress != 1) {
            while (getchar() != '\n');
        }
        if (x > a.taille[0]) {
            printf("Il y a %d rangées, vous dépassez le maximum possible.\n", a.taille[0]);
        }
    }

    // Demande le nombre de rangées de classe B
    ress = -1;
    int x1 = -1;
    if (x != a.taille[0]) {
        while (ress != 1 || x1 > a.taille[0] - x) {
            printf("Combien de rangées de classe B ?\n");
            ress = scanf("%d", &x1);
            if (ress != 1) {
                while (getchar() != '\n');
            }
            if (x1 > a.taille[0]) {
                printf("Il reste %d rangées, vous dépassez le maximum possible.\n", a.taille[0] - x);
            }
        }
    }

    // Demande le nombre de sièges dans chaque rangée
    for (int i = 1; i < r + 1; ++i) {
        ress = -1;
        int l = -1;
        while (l < 0 || ress != 1) {
            printf("Combien de sièges à la rangée numéro %d ?\n", i);
            ress = scanf("%d", &l);
            if (ress != 1) {
                while (getchar() != '\n');
            }
        }

        // Crée une place selon la classe de la rangée
        Place y;
        if (i <= x) {
            y = creerPlace(1);
        } else if (i > x && i <= (x + x1)) {
            y = creerPlace(2);
        } else {
            y = creerPlace(3);
        }


        if (i > x || a.fosse == 2) {
            a.arr[i - 1] = NULL;
            a.arr[i - 1] = malloc(sizeof(Place) * l);

            if (a.arr[i - 1] == NULL) {
                printf("Erreur lors de l'allocation de mémoire\n");
                exit(1);
            }

            // Initialise chaque siège dans la rangée
            for (int j = 0; j < l; ++j) {
                a.arr[i - 1][j] = y;
            }

            // Enregistre la taille de la rangée
            a.taille[i] = l;
        } else if (i <= x && a.fosse == 1) {
            a.arr[i - 1] = NULL;
            a.arr[i - 1] = malloc(sizeof(Place) * l * 2);

            if (a.arr[i - 1] == NULL) {
                printf("Erreur lors de l'allocation de mémoire\n");
                exit(1);
            }

            // Initialise chaque siège dans la rangée
            for (int j = 0; j < l * 2; ++j) {
                a.arr[i - 1][j] = y;
            }

            // Enregistre la taille de la rangée
            a.taille[i] = 2 * l;
        }
    }

// Vérifie si le nombre total de sièges correspond au nombre de sièges entrés
int z = 0;
for (int i = 1; i < r + 1; ++i) {
     z += a.taille[i];
  }
 if (z != a.siege) {
     printf("Le nombre de sièges annoncé ne correspond pas au nombre de rangées et de sièges\n");
     freeSalle(a);
    a = creerSalle();
}


// Demande les prix des différentes classes de sièges
    while (sec != 1) {
        printf("Quel est le prix d'une place de classe 1 ?\n");
        sec = scanf("%f", &a.classeA);
        if (sec != 1) {
            while (getchar() != '\n');
        }
    }
    sec = -1;
    while (sec != 1) {
        printf("Quel est le prix d'une place de classe 2 ?\n");
        sec = scanf("%f", &a.classeB);
        if (sec != 1) {
            while (getchar() != '\n');
        }
    }
    sec = -1;
    while (sec != 1) {
        printf("Quel est le prix d'une place de classe 3 ?\n");
        sec = scanf("%f", &a.classeC);
        if (sec != 1) {
            while (getchar() != '\n');
        }
    }

// Demande la date du concert
    ress = -1;
    a.date.jour = 0;
    a.date.mois = 0;
    a.date.annee = 0;
    int ressj = -1, ressm = -1, ressa = -1;
    while (ress != 3) {
        while (ressa != 1 || a.date.annee < 2024) {
            printf("Entrez l'année du concert :\n");
            ressa = scanf("%d", &a.date.annee);
            if (ressa != 1) {
                while (getchar() != '\n');
            }
        }

        ress++;
        if ((a.date.annee % 4 == 0 && a.date.annee % 100 != 0) || (a.date.annee % 400 == 0)) {
            while (ressm != 1 || a.date.mois < 1 || a.date.mois > 12) {
                printf("Entrez le mois du concert :\n");
                ressm = scanf("%d", &a.date.mois);
                if (ressm != 1) {
                    while (getchar() != '\n');
                }
            }
            ress++;
            if (a.date.mois == 1 || a.date.mois == 3 || a.date.mois == 5 || a.date.mois == 7 || a.date.mois == 8 ||
                a.date.mois == 10 || a.date.mois == 12) {
                while (ressj != 1 || a.date.jour < 1 || a.date.jour > 31) {
                    printf("Entrez le jour du concert :\n");
                    ressj = scanf("%d", &a.date.jour);
                    if (ressj != 1) {
                        while (getchar() != '\n');
                    }
                }
                ress++;
            } else if (a.date.mois == 4 || a.date.mois == 6 || a.date.mois == 9 || a.date.mois == 11) {
                while (ressj != 1 || a.date.jour < 1 || a.date.jour > 30) {
                    printf("Entrez le jour du concert :\n");
                    ressj = scanf("%d", &a.date.jour);
                    if (ressj != 1) {
                        while (getchar() != '\n');
                    }
                }
                ress++;
            } else {
                while (ressj != 1 || a.date.jour < 1 || a.date.jour > 29) {
                    printf("Entrez le jour du concert :\n");
                    ressj = scanf("%d", &a.date.jour);
                    if (ressj != 1) {
                        while (getchar() != '\n');
                    }
                }
                ress++;
            }
        } else {
            while (ressm != 1 || a.date.mois < 1 || a.date.mois > 12) {
                printf("Entrez le mois du concert :\n");
                ressm = scanf("%d", &a.date.mois);
                if (ressm != 1) {
                    while (getchar() != '\n');
                }
            }
            ress++;
            if (a.date.mois == 1 || a.date.mois == 3 || a.date.mois == 5 || a.date.mois == 7 || a.date.mois == 8 ||
                a.date.mois == 10 || a.date.mois == 12) {
                while (ressj != 1 || a.date.jour < 1 || a.date.jour > 31) {
                    printf("Entrez le jour du concert :\n");
                    ressj = scanf("%d", &a.date.jour);
                    if (ressj != 1) {
                        while (getchar() != '\n');
                    }
                }
                ress++;
            } else if (a.date.mois == 4 || a.date.mois == 6 || a.date.mois == 9 || a.date.mois == 11) {
                while (ressj != 1 || a.date.jour < 1 || a.date.jour > 30) {
                    printf("Entrez le jour du concert :\n");
                    ressj = scanf("%d", &a.date.jour);
                    if (ressj != 1) {
                        while (getchar() != '\n');
                    }
                }
                ress++;
            } else {
                while (ressj != 1 || a.date.jour < 1 || a.date.jour > 28) {
                    printf("entrez le jour du concert\n");
                    ressj = scanf("%d", &a.date.jour);
                    if (ressj != 1) {
                        while (getchar() != '\n');
                    }
                }
                ress++;
            }
        }
    }
    // Demande le nom de l'artiste
    ress = -1;
    char test[50];
    int l1;
    char *testc = NULL;

    while (testc == NULL) {
        printf("Quel est le nom de l'artiste ?\n");
        while (getchar() != '\n');
        testc = fgets(test, 49, stdin);
        l1 = strlen(test);

        // Alloue dynamiquement de la mémoire pour stocker le nom de l'artiste
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
}

void afficheSalle(Salle a, int cle) {

    // Recherche du suffixe ".SALLESAUVE" dans le nom de fichier pour l'affichage
    char *suffixe = ".SALLESAUVE";
    char aff[50] = "";
    strncpy(aff, a.nomFichier, 49);
    char *fin = strstr(aff, suffixe);

    // Si le suffixe est trouvé, il est supprimé pour l'affichage
    if (fin != NULL) {
        *fin = '\0';
    }

    // Affichage des informations générales sur la salle et le concert
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");
    a = comptePlace(a);
    printf("Nom de salle : %s\nNombre de sièges libres de la salle : %d\nDate du concert : %d/%d/%d\nIl s'agit d'un concert de %s\n",
           aff, (int) (a.siege - a.siegeres), a.date.jour, a.date.mois, a.date.annee, a.artiste);

    // Affichage du nombre de places libres et réservées selon la classe
    if (cle == 0) {
        printf("Il y a %d places libres de classe A\nIl y a %d places libres de classe B\nIl y a %d places libres de classe C\nIl y a %d places réservées de classe A\nIl y a %d places réservées de classe B\nIl y a %d places réservées de classe C\n",
               a.places[0], a.places[1], a.places[2], a.places[3], a.places[4], a.places[5]);
    } else {
        printf("Il y a %d places libres de classe A\nIl y a %d places libres de classe B\nIl y a %d places libres de classe C\n",
               a.places[0], a.places[1], a.places[2]);
    }

    // Affichage de la présence d'une fosse lors du concert
    if (a.fosse == 1) {
        printf("Il y a une fosse lors de ce concert\n");
    }

    // Affichage du plan de la salle
    printf("\nPlan de la salle :\n");
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
            // Affichage des codes correspondant à chaque type de place
            if ((a.arr[i][j]).code == 0) {
                printf("O "); // Classe A libre
            } else if ((a.arr[i][j]).code == 1) {
                printf("0 "); // Classe B libre
            } else if ((a.arr[i][j]).code == 2) {
                printf("8 "); // Classe C libre
            } else if ((a.arr[i][j]).code == 3) {
                printf("X "); // Classe A réservée
            } else if ((a.arr[i][j]).code == 4) {
                printf("X "); // Classe B réservée
            } else if ((a.arr[i][j]).code == 5) {
                printf("X "); // Classe C réservée
            }
        }
        printf("\n");
    }

    // Affichage de la légende pour interpréter les codes des places
    printf("\nLégende :\nClasse A (libre) : O\nClasse B (libre) : 0\nClasse C (libre) : 8\nClasse A (prise) : X\nClasse B (prise) : X\nClasse C (prise) : X\n");
    printf("\n");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

void freeSalle(Salle a) {
    // Libération de la mémoire allouée pour le nom de la salle et le nom du fichier
    free(a.nom);
    free(a.nomFichier);

    // Libération de la mémoire allouée pour chaque ligne de sièges dans la salle
    for (int i = 0; i < a.taille[0]; ++i) {
        free(*(a.arr + i));
    }
}

void affichePlan(Salle a) {
    // Recherche du suffixe ".SALLESAUVE" dans le nom de fichier pour l'affichage
    char *suffix = ".SALLESAUVE";
    char aff[50] = "";
    strncpy(aff, a.nomFichier, 49);
    char *pos = strstr(aff, suffix);

    // Si le suffixe est trouvé, il est supprimé pour l'affichage
    if (pos != NULL) {
        *pos = '\0';
    }

    // Affichage des informations générales sur la salle et le concert
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");
    a = comptePlace(a);
    printf("Nom de salle : %s\nNombre de sièges libres de la salle : %d\nDate du concert : %d/%d/%d\nIl s'agit d'un concert de %s\n",
           aff, (int) (a.siege - a.siegeres), a.date.jour, a.date.mois, a.date.annee, a.artiste);
    printf("Il y a %d places libres de classe A\nIl y a %d places libres de classe B\nIl y a %d places libres de classe C\n",
           a.places[0], a.places[1], a.places[2]);

    // Affichage de la présence d'une fosse lors du concert
    if (a.fosse == 1) {
        printf("Il y a une fosse lors de ce concert\n");
    }

    // Affichage du plan de la salle
    printf("\nPlan de la salle :\n");
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
            // Affichage des codes correspondant à chaque type de place
            if ((a.arr[i][j]).code == 0) {
                printf("O "); // Classe A libre
            } else if ((a.arr[i][j]).code == 1) {
                printf("0 "); // Classe B libre
            } else if ((a.arr[i][j]).code == 2) {
                printf("8 "); // Classe C libre
            } else if ((a.arr[i][j]).code == 3) {
                printf("X "); // Classe A réservée
            } else if ((a.arr[i][j]).code == 4) {
                printf("X "); // Classe B réservée
            } else if ((a.arr[i][j]).code == 5) {
                printf("X "); // Classe C réservée
            }
        }
        printf("\n");
    }

    // Affichage de la légende pour interpréter les codes des places
    printf("\nLégende :\nClasse A (libre) : O\nClasse B (libre) : 0\nClasse C (libre) : 8\nClasse A (prise) : X\nClasse B (prise) : X\nClasse C (prise) : X\n");
    printf("\n");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

Salle modifSalle(Salle a, Date date) {
    // Vérification si le concert a déjà eu lieu
    if ((date.annee < a.date.annee) || (date.annee == a.date.annee && date.mois < a.date.mois) ||
        (date.annee == a.date.annee && date.mois == a.date.mois && date.jour <= a.date.jour)) {
        printf("le concert n'a pas encore eu lieu et ne peut pas etre modifie\n");
        return a;
    } else {
        // Réinitialisation des sièges réservés pour la modification
        for (int i = 1; i < a.taille[0] + 1; ++i) {
            for (int j = 0; j < a.taille[i]; ++j) {
                if (a.arr[i - 1][j].code > 2) {
                    a.arr[i - 1][j].code -= 3;
                }
            }
        }
    }

    // Initialisation des variables
    int res = -1;
    int c = -1;
    char tabs[50];
    int sec = -1;
    char *sectab = NULL;

    // Boucle pour le menu de modification
    while (c != 6) {
        // Menu principal
        while (sec != 1 || c < 1 || c > 6) {
            printf("que voulez vous modifier, entrez le chiffre correspondant\n");
            printf("1) nom/nom fichier\n2) nombre de siege/disposition de la salle\n3) prix des places\n4) le nom de l'artiste jouant\n5) la date du concert\n6) quitter le mode de modification\n");
            sec = scanf("%d", &c);
            if (sec != 1) {
                videTerminal();
                while (getchar() != '\n');
            }
        }
        sec = -1;
        if (c == 1) {
            // Modification du nom de la salle
            while (sectab == NULL) {
                printf("entrez le nouveau nom de la salle\n");
                while (getchar() != '\n');
                sectab = fgets(tabs, 49, stdin);
            }
            // Traitement du nouveau nom
            char *suffixe = "\n";
            char *fin = strstr(tabs, suffixe);
            if (fin != NULL) {
                *fin = '\0';
            }
            sectab = NULL;
            int l = strlen(tabs);
            // Libération des anciens noms
            free(a.nom);
            free(a.nomFichier);
            // Allocation des nouveaux noms
            a.nom = malloc(l);
            a.nomFichier = malloc(l + 11);
            verifAlloc(a.nom);
            verifAlloc(a.nomFichier);
            // Copie des nouveaux noms
            for (int i = 0; i <= l; ++i) {
                a.nom[i] = tabs[i];
                a.nomFichier[i] = tabs[i];
            }
            // Ajout du suffixe au nom de fichier
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
            // Affichage des nouveaux noms
            printf("le nouveau nom de la salle est : %s\nle nouveau nom du fichier est : %s\n", a.nom, a.nomFichier);
        } else if (c == 2) {
            // Modification du nombre de sièges ou de la disposition de la salle
            int c1 = -1, c2 = -1;
            int r = -1, l = -1, k = -1;
            res = -1;
            // Menu de sous-modification
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
                // Sous-menu pour ajouter ou modifier une rangée
                while (res != 1 || c2 < 0 || c2 > 2) {
                    printf("voulez vous\n1)ajouter une rangee\n2) modifier ou supprimer une rangee\n");
                    res = scanf("%d", &c2);
                    if (res != 1) {
                        while (getchar() != '\n');
                    }
                }
                // Vérification si la salle contient des rangées avant de les modifier
                if (a.taille[0] == 0 && c2 == 2) {
                    printf("\n\nvous ne pouvez pas modifier de rangee car il n'y en a plus\n\n");
                    c2 = -1;
                }
                res = -1;
                if (c2 == 1) {
                    res = -1;
                    // Boucle pour obtenir la rangée à ajouter
                    while (res != 1 || r <= 0 || r > a.taille[0] + 1) {
                        printf("quelle rangee souhaiter vous rajouter\nvous pouvez selectionner une rangee de 1 a %d\n",
                               a.taille[0] + 1);
                        res = scanf("%d", &r);

                        if (res != 1) {
                            while (getchar() != '\n');
                        }
                    }
                    // Augmentation du nombre total de rangées
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
                    // Obtenir la taille de la nouvelle rangée
                    while (res != 1) {
                        printf("quel est la taille de la rangee\n");
                        res = scanf("%d", &l);
                        if (res != 1) {
                            while (getchar() != '\n');
                        }
                    }

                    taille[r] = l;
                    res = -1;
                    // Obtenir la catégorie de place de la nouvelle rangée
                    while (res != 1) {
                        printf("qu'elle est la categorie de place de cette rangee\n1) classe A\n2) classe B\n3) classe C\n");
                        res = scanf("%d", &k);
                        if (res != 1) {
                            while (getchar() != '\n');
                        }
                    }
                    // Allouer la mémoire pour la nouvelle rangée
                    if (a.fosse == 1 && k == 1) {
                        tab[r - 1] = malloc(2 * l * sizeof(Place));
                        for (int i = 0; i < 2 * l; ++i) {
                            tab[r - 1][i] = creerPlace(k);
                        }
                        for (int i = r; i < a.taille[0]; ++i) {
                            tab[i] = a.arr[i - 1];
                            taille[i + 1] = a.taille[i];
                        }
                    } else {
                        tab[r - 1] = malloc(l * sizeof(Place));
                        for (int i = 0; i < l; ++i) {
                            tab[r - 1][i] = creerPlace(k);
                        }
                        for (int i = r; i < a.taille[0]; ++i) {
                            tab[i] = a.arr[i - 1];
                            taille[i + 1] = a.taille[i];
                        }
                    }

                    // Libérer l'ancien tableau de tailles et le remplacer par le nouveau
                    free(a.taille);
                    a.taille = taille;

                    // Libérer l'ancien tableau de rangées et le remplacer par le nouveau
                    free(a.arr);
                    a.arr = tab;

                    // Mettre à jour le nombre total de sièges dans la salle
                    a.siege += l;
                    res = -1;
                } else if (c2 == 2) {
                    // Sous-menu pour modifier ou supprimer une rangée existante
                    res = -1;
                    // Demander à l'utilisateur de choisir la rangée à modifier
                    while (res != 1 || r <= 0 || r > a.taille[0]) {
                        printf("quelle rangee voulez vous modifer de 1 a %d\n", a.taille[0]);
                        res = scanf("%d", &r);
                        if (res != 1) {
                            while (getchar() != '\n');
                        }
                    }
                    // Demander à l'utilisateur de spécifier la nouvelle taille de la rangée (0 pour la supprimer)
                    res = -1;
                    while (res != 1 || l < 0) {
                        printf("quel est la nouvelle taille de la rangee (0 pour supprimer la rangee)\n");
                        res = scanf("%d", &l);
                        if (res != 1) {
                            while (getchar() != '\n');
                        }
                    }
                    if (l == 0) {
                        // Supprimer la rangée sélectionnée
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
                        if (r < a.taille[0]) {
                            taille1[r] = a.taille[r + 1];

                            for (int i = r + 1; i < a.taille[0]; ++i) {
                                taille1[i] = a.taille[i + 1];
                            }
                        }
                        for (int i = 0; i < r - 1; ++i) {
                            tab1[i] = a.arr[i];
                        }
                        if (r < a.taille[0]) {
                            tab1[r - 1] = a.arr[r];

                            for (int i = r; i < a.taille[0] - 1; ++i) {
                                tab1[i] = a.arr[i + 1];
                            }
                        }
                        // Mettre à jour les données de la salle
                        free(a.taille);
                        a.taille = taille1;
                        free(a.arr);
                        a.arr = tab1;

                        // Gérer le cas où il n'y a plus de rangées
                        if (a.taille[0] == 0) {
                            a.arr = malloc(sizeof(Place *));
                            free(a.taille);
                            a.taille = malloc(2 * sizeof(int));
                            a.taille[0] = 0;
                            a.taille[1] = 1;
                        }


                    } else {
                        // Modifier la taille de la rangée sélectionnée
                        k = (a.arr[r - 1][0].code);
                        free(a.arr[r - 1]);
                        if (a.fosse == 1 && k == 0) {
                            a.arr[r - 1] = malloc(2 * l * sizeof(Place));

                            for (int i = 0; i < 2 * l; ++i) {
                                a.arr[r - 1][i] = creerPlace(k + 1);
                            }
                            if (2 * l < a.taille[r]) {
                                a.siege -= 2 * l;
                            } else if (2 * l > a.taille[r]) {
                                a.siege += l * 2;
                            }

                            a.taille[r] = l * 2;
                        } else {
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
            // Modifier les prix des places pour une catégorie donnée
            int k;
            float p;
            res = -1;
            // Demander à l'utilisateur de choisir la catégorie à modifier
            while (res != 1 || k < 1 || k > 3) {
                printf("quelle categorie voulez vous modifer\n1) A\n2) B\n3) C\n");
                res = scanf("%d", &k);
                if (res != 1) {
                    while (getchar() != '\n');
                }
            }
            res = -1;
            switch (k) {
                // Modifier le prix pour la catégorie A
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
                    // Modifier le prix pour la catégorie B
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
                    // Modifier le prix pour la catégorie C
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
            // Modifier le nom de l'artiste
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
        } else if (c == 5) {
            // Modifier la date du concert
            int ress = 0;
            a.date.jour = 0;
            a.date.mois = 0;
            a.date.annee = 0;
            int ressj = -1, ressm = -1, ressa = -1;
            // Boucle pour demander à l'utilisateur d'entrer une date valide
            while (ress != 3) {
                while (ressa != 1 || a.date.annee < 2024) {
                    printf("entrez l'annee du concert\n");
                    ressa = scanf("%d", &a.date.annee);
                    if (ressa != 1) {
                        while (getchar() != '\n');
                    }
                }

                ress++;
                // Vérifier si l'année est bissextile
                if ((a.date.annee % 4 == 0 && a.date.annee % 100 != 0) || (a.date.annee % 400 == 0)) {
                    while (ressm != 1 || a.date.mois < 1 || a.date.mois > 12) {
                        printf("entrez le mois du concert\n");
                        ressm = scanf("%d", &a.date.mois);
                        if (ressm != 1) {
                            while (getchar() != '\n');
                        }
                    }
                    ress++;
                    // Vérifier le nombre de jours selon le mois
                    if (a.date.mois == 1 || a.date.mois == 3 || a.date.mois == 5 || a.date.mois == 7 ||
                        a.date.mois == 8 || a.date.mois == 10 || a.date.mois == 12) {
                        while (ressj != 1 || a.date.jour < 1 || a.date.jour > 31) {
                            printf("entrez le jour du concert\n");
                            ressj = scanf("%d", &a.date.jour);
                            if (ressj != 1) {
                                while (getchar() != '\n');
                            }
                        }
                        ress++;
                    } else if (a.date.mois == 4 || a.date.mois == 6 || a.date.mois == 9 || a.date.mois == 11) {
                        while (ressj != 1 || a.date.jour < 1 || a.date.jour > 30) {
                            printf("entrez le jour du concert\n");
                            ressj = scanf("%d", &a.date.jour);
                            if (ressj != 1) {
                                while (getchar() != '\n');
                            }
                        }
                        ress++;
                    } else {
                        while (ressj != 1 || a.date.jour < 1 || a.date.jour > 29) {
                            printf("entrez le jour du concert\n");
                            ressj = scanf("%d", &a.date.jour);
                            if (ressj != 1) {

                            }
                        }
                        ress++;
                    }
                } else {
                    while (ressm != 1 || a.date.mois < 1 || a.date.mois > 12) {
                        printf("entrez le mois du concert\n");
                        ressm = scanf("%d", &a.date.mois);
                        if (ressm != 1) {
                            while (getchar() != '\n');
                        }
                    }
                    ress++;
                    // Vérifier le nombre de jours selon le mois
                    if (a.date.mois == 1 || a.date.mois == 3 || a.date.mois == 5 || a.date.mois == 7 ||
                        a.date.mois == 8 || a.date.mois == 10 || a.date.mois == 12) {
                        while (ressj != 1 || a.date.jour < 1 || a.date.jour > 31) {
                            printf("entrez le jour du concert\n");
                            ressj = scanf("%d", &a.date.jour);
                            if (ressj != 1) {
                                while (getchar() != '\n');
                            }
                        }
                        ress++;
                    } else if (a.date.mois == 4 || a.date.mois == 6 || a.date.mois == 9 || a.date.mois == 11) {
                        while (ressj != 1 || a.date.jour < 1 || a.date.jour > 30) {
                            printf("entrez le jour du concert\n");
                            ressj = scanf("%d", &a.date.jour);
                            if (ressj != 1) {
                                while (getchar() != '\n');
                            }
                        }
                        ress++;
                    } else {
                        while (ressj != 1 || a.date.jour < 1 || a.date.jour > 28) {
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

