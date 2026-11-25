#ifndef MONSTER_H
#define MONSTER_H

typedef struct Monster {
    char name[50];
    int attack;
    int health;
    char type[15];
} Monster;

struct Player;
struct Queue;

void pushMonster(struct Player **player, Monster monster);
Monster popMonster(struct Player *player);
void readMonstersFromFile(struct Player **player, const char *filename);
void enqueue(struct Queue **queue, Monster monster);
Monster dequeue(struct Queue **queue);

#endif
