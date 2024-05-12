#include <stdio.h>
#include "salle.h"
#include <string.h>
#include <stdlib.h>
#include "savefile.h"


int main() {

    Salle a = creerSalle();
    afficheSalle(a);
    saveSalle(a);
    freeSalle(a);

    return 0;
}
