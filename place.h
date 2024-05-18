//
// Created by siode on 18/05/2024.
//

#ifndef CYFEST_PLACE_H
#define CYFEST_PLACE_H

#include "salle.h"

typedef struct {
    int res;
    char classe;
    int code;
}Place;


Place creerPlace(int);
void devPlace(Place *);
Salle verifSiege(Salle);
Salle actualiseSiege(Salle);
Salle reservePlace(Salle);

#endif //CYFEST_PLACE_H
