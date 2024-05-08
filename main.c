#include <stdio.h>
#include "salle.h"
#include <string.h>
#include <stdlib.h>


int main() {

    Salle a = creerSalle();
    afficheSalle(a);
    freeSalle(a);

    return 0;
}
