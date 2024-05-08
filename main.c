#include <stdio.h>
#include "salle.h"
#include <string.h>
#include <stdlib.h>


int main() {

    Salle a = creerSalle();
    printf("salle : %s\nnombre de siege : %d\nnombre : %d\n", a.nom, a.siege, a.taille[0]);

    for (int i = 0; i < a.taille[0]; ++i) {
        for (int j = 0; j < a.taille[i+1]; ++j) {
            printf("%d", a.arr[i][j]);
        }
        printf("\n");
    }
    free(a.taille);
    free(a.arr);



    return 0;
}
