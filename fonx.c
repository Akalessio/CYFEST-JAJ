#include "fonx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "salle.h"
#include "sauvefichier.h"


int plusGrand(int *tab, int a){
    int b = -1; // Initialisation de la variable pour stocker le plus grand élément
    for (int i = 1; i < a; ++i) { // Parcours du tableau à partir du deuxième élément
        if(tab[i]>b){ // Si l'élément actuel est plus grand que b
            b = tab[i]; // Mise à jour de b
        }
    }
    return b; // Retourne le plus grand élément trouvé
}

// Fonction qui calcule le décalage entre deux valeurs a et b
int decal(int a, int b){
    if(a%2==0 && b%2==0){ // Si a et b sont pairs
        return ((a/2)-(b/2));
    }
    else if(a%2==0 && b%2!=0){ // Si a est pair et b est impair
        b=b/2;
        b++;
        return ((a/2)-b);
    }
    else if(a%2!=0 && b%2==0){ // Si a est impair et b est pair
        return (((a-1)/2)-((b)/2));
    }
    else{ // Si a et b sont impairs
        return (((a-1)/2)-((b-1)/2));
    }
}

// Fonction qui imprime des espaces pour décaler le texte
void decalPrint(int a){
    for (int i = 0; i < a; ++i) { // Boucle pour imprimer des espaces
        printf("  ");
    }
}

// Fonction qui vérifie l'allocation de la mémoire
void verifAlloc(void *a){
    if(a == NULL){ // Si l'allocation a échoué
        printf("erreur lors de l'allocation\n");
        exit(1); // Quitte le programme avec un code d'erreur
    }
}

// Fonction qui affiche un message indiquant le mode manager
void manage(void){
    printf("Mode manager\n");
}

// Fonction qui affiche un message indiquant le mode festivalier
void festival(void){
    printf("Mode Festivalier\n");
}

// Fonction qui remplace les espaces dans une chaîne de caractères par des underscores
void verifNom(char *a){
    int str = strlen(a); // Obtient la longueur de la chaîne
    for (int i = 0; i < str; ++i) { // Parcours de la chaîne
        if(a[i] == ' '){ // Si le caractère actuel est un espace
            a[i] = '_'; // Remplace par un underscore
        }
    }
}

// Fonction qui affiche les sauvegardes disponibles en fonction de la date et d'une clé
void afficheSauvegarde(Date date, int cle) {
    FILE *fichier;
    fichier = fopen("sauvegarde.txt", "r"); // Ouvre le fichier de sauvegarde en lecture

    if (fichier == NULL) { // Si l'ouverture du fichier échoue
        printf("erreur lors de l'ouverture du fichier");
        exit(2); // Quitte le programme avec un code d'erreur
    }

    if (cle == 1) { // Si la clé est 1
        int m = 0;
        char save[50];
        Salle s;
        printf("les sauvegardes disponibles sont\n\n");
        while (fgets(save, 49, fichier)) { // Parcours du fichier de sauvegarde
            m++;
            save[strcspn(save, "\n")] = '\0'; // Supprime le caractère de nouvelle ligne
            s = lectureSauve(save); // Lecture de la sauvegarde

            // Vérifie si la date de la sauvegarde est postérieure ou égale à la date donnée
            if ((date.annee < s.date.annee) || (date.annee == s.date.annee && date.mois < s.date.mois) ||
                (date.annee == s.date.annee && date.mois == s.date.mois && date.jour <= s.date.jour)) {
                printf("%s\n", save); // Affiche le nom de la sauvegarde
            }
        }
        fclose(fichier); // Ferme le fichier
    } else { // Si la clé n'est pas 1

        char save[50];
        printf("les sauvegardes disponibles sont\n\n");

        while (fgets(save, 49, fichier)) { // Parcours du fichier de sauvegarde
            printf("%s\n", save); // Affiche le nom de la sauvegarde
        }

    }
}

// Fonction qui vide le terminal
void videTerminal() {
#if defined(_WIN32) || defined(_WIN64) // Si le système est Windows
    system("cls"); // Utilise la commande cls
#else // Si le système est Unix/Linux
    system("clear"); // Utilise la commande clear
#endif
}

// Fonction qui met en pause le terminal en attendant une entrée de l'utilisateur
void pauseTerminal() {
    printf("Appuyez sur entree pour revenir au menu...");
    while (getchar() != '\n'); // Attend l'entrée de l'utilisateur
    getchar(); // Lit l'entrée
}