#include "fonx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int plusGrand(int *tab, int a){
    int b = -1;
    for (int i = 1; i < a; ++i) {
        if(tab[i]>b){
            b = tab[i];
        }
    }
    return b;
}

int decal(int a, int b){
    if(a%2==0 && b%2==0){
        return ((a/2)-(b/2));
    }
    else if(a%2==0 && b%2!=0){
        b=b/2;
        b++;
        return ((a/2)-b);
    }
    else if(a%2!=0 && b%2==0){
        return (((a-1)/2)-((b)/2));
    }
    else{
        return (((a-1)/2)-((b-1)/2));
    }
}

void decalPrint(int a){
    for (int i = 0; i < a; ++i) {
        printf("  ");
    }
}

void verifAlloc(void *a){
    if(a == NULL){
        printf("erreur lors de l'allocation\n");
        exit(1);
    }
}

