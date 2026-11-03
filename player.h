#ifndef PLAYER_H
#define PLAYER_H

#include "monster.h"

typedef struct Node {
    Monster card;
    struct Node *next;
} Node;

typedef struct Queue {
    Node *front;
    Node *back;
} Queue;

typedef struct Stack {
    Node *top;
} Stack;

typedef struct Player Player;

struct Player {
    char name[25];
    int health;
    Stack deck;
    Monster hand[5];
    Queue attack;
    Queue defense;
    Player* next;
    Player* prev;
};

void createPlayer(Player **players);

#endif
