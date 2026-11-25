//this file is for functions relating to monster
//it will be linked to the main and player files
#include "player.h"
#include "monster.h"
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



//this is a push function that will add a monster to the top of the stack
void pushMonster(Player **player, Monster monster) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Could not add monster: out of memory\n");
        return;
    }
    newNode->card = monster;
    newNode->next = (*player)->deck->top;
    (*player)->deck->top = newNode;
}

//this is a pop function that will remove a monster from the top of the stack
Monster popMonster(Player *player) {
    if (player->deck->top == NULL) {
        printf("Stack is empty, cannot pop\n");
        Monster emptyMonster = {"", 0, 0, ""};
        return emptyMonster; // return an empty monster if the stack is empty
    }
    Node *tempNode = player->deck->top;
    Monster poppedMonster = tempNode->card;
    player->deck->top = tempNode->next;
    free(tempNode);
    return poppedMonster;
}

//this function will read in a csv file of monsters and store them in a linked list stack
void readMonstersFromFile(Player **player, const char *filename) {
    FILE *file = fopen(filename, "r");
    //check if file is opened successfully
    if (file==NULL) {
        printf("Could not open file %s\n", filename);
        return;
    }
    printf("Reading monsters from file %s\n", filename);
    Monster monster;
    
    //now we will read in the file line by line and store the monsters in the stack
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        // Process each line to extract monster data
        if (sscanf(line, "%49[^,],%14[^,],%d,%d", monster.name, monster.type, &monster.attack, &monster.health) == 4) {
            pushMonster(player, monster);
        } else {
            printf("Invalid line format: %s", line);
        }
    }
    fclose(file);
}

//this function will enqueue a monster to the back of the queue
//the queue parameters will be player.attack or player.defense based off of when they are called in the main function
void enqueue(Queue **queue, Monster monster) {
    Node *newNode = malloc(sizeof(Node));
    newNode->card = monster;
    newNode->next = NULL;
    if ((*queue)->back == NULL) {
        (*queue)->front = newNode;
        (*queue)->back = newNode;
    } else {
        (*queue)->back->next = newNode;
        (*queue)->back = newNode;
    }
}

//this function will dequeue a monster from the front of the queue
Monster dequeue(Queue **queue) {
    if ((*queue)->front == NULL) {
        printf("Queue is empty, cannot dequeue\n");
        Monster emptyMonster = {"", 0, 0, ""};
        return emptyMonster; // return an empty monster if the queue is empty
    }
    Node *tempNode = (*queue)->front;
    Monster dequeuedMonster = tempNode->card;
    (*queue)->front = tempNode->next;
    if ((*queue)->front == NULL) {
        (*queue)->back = NULL;
    }
    free(tempNode);
    return dequeuedMonster;
}