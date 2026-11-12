#ifndef MONSTER_H
#define MONSTER_H

#include "player.h"
#include <stdio.h>

typedef struct Monster {
    char name[50];
    int attack;
    int health;
    char type[15];
} Monster;

#endif
