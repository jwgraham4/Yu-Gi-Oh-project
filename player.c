//this is the palyer file where functions that relate to the player class are going to be written

#include "player.h"
#include "monster.h"
#include <stdio.h>
#include <stdlib.h>

void createPlayer(Player **players){
    Player *newPlayer = calloc(1, sizeof(Player));
    if (newPlayer == NULL) {
        fprintf(stderr, "Could not create player: out of memory\n");
        return;
    }

    newPlayer->deck = calloc(1, sizeof(Stack));
    if (newPlayer->deck == NULL) {
        fprintf(stderr, "Could not create player deck: out of memory\n");
        free(newPlayer);
        return;
    }

    printf("What is the players name: ");
    fgets(newPlayer->name, sizeof(newPlayer->name), stdin);
    newPlayer->health = 8000;

    if (*players == NULL){
        *players = newPlayer;
    }
    else{
        Player* tempPlayer = *players;
        while (tempPlayer->next != NULL){
            tempPlayer = tempPlayer->next;
        }
        tempPlayer->next = newPlayer;
        newPlayer->prev = tempPlayer;
    }
}
