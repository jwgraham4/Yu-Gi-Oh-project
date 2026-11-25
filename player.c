//this is the palyer file where functions that relate to the player class are going to be written

#include "player.h"
#include "monster.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//this function will create a new player and add it to the linked list of players
void createPlayer(Player **players){
    Player *newPlayer = calloc(1, sizeof(Player));
    if (newPlayer == NULL) {
        fprintf(stderr, "Could not create player: out of memory\n");
        return;
    }
    
    printf("Enter player name: ");
    fgets(newPlayer->name, sizeof(newPlayer->name), stdin);

    newPlayer->name[strcspn(newPlayer->name, "\r\n")] = '\0';
    newPlayer->health = 8000;
    newPlayer->deck = calloc(1, sizeof(Stack));
    newPlayer->attack = calloc(1, sizeof(Queue));
    newPlayer->defense = calloc(1, sizeof(Queue));
    if (newPlayer->deck == NULL || newPlayer->attack == NULL || newPlayer->defense == NULL) {
        fprintf(stderr, "Could not create player components: out of memory\n");
        free(newPlayer->deck);
        free(newPlayer->attack);
        free(newPlayer->defense);
        free(newPlayer);
        return;
    }

    //adding cards to the players deck
    printf("which deck would you like to use? (1 or 2): ");
    int deckChoice;
    scanf("%d", &deckChoice);
    const char *filename;
    while (deckChoice != 1 && deckChoice != 2) {
        printf("Invalid choice. Please enter 1 or 2: ");
        scanf("%d", &deckChoice);
    }
    if (deckChoice == 1) {
        filename = "YuGiOH-Deck1.csv";
    } else {
        filename = "YuGiOH-Deck2.csv";
    }
    
    printf("Reading monsters from file %s\n", filename);
    readMonstersFromFile(&newPlayer, filename);
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
    getchar(); // Clear the newline character left in the input buffer
}

void destroyPlayer(Player *player) {
    if (player == NULL) {
        return;
    }

    // Free the deck stack
    while (player->deck != NULL && player->deck->top != NULL) {
        Node *tempNode = player->deck->top;
        player->deck->top = tempNode->next;
        free(tempNode);
    }
    free(player->deck);

    // Free the attack queue
    while (player->attack != NULL && player->attack->front != NULL) {
        Node *tempNode = player->attack->front;
        player->attack->front = tempNode->next;
        free(tempNode);
    }
    free(player->attack);

    // Free the defense queue
    while (player->defense != NULL && player->defense->front != NULL) {
        Node *tempNode = player->defense->front;
        player->defense->front = tempNode->next;
        free(tempNode);
    }
    free(player->defense);

    // Finally, free the player itself
    free(player);
}
