//this is the palyer file where functions that relate to the player class are going to be written

#include <player.h>
#include <stdio.h>

void createPlayer(Player **players){
    Player *newPlayer = malloc(sizeof(Player));
    printf("What is the players name: ");
    fgets(newPlayer->name, sizeof(newPlayer->name), stdin);
    newPlayer->health = 8000;

    if (*players == NULL){
        *players = newPlayer;
        (*players)->next = NULL;
        (*players)->prev = NULL;
    }
    else{
        Player* tempPlayer = *players;
        while (tempPlayer->next != NULL){
            tempPlayer = tempPlayer->next;
        }
        tempPlayer->next = newPlayer;
    }
}
