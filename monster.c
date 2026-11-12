//this file is for functions relating to monster
//it will be linked to the main and player files
#include "player.h"
#include "monster.h"
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

static char *trimWhitespace(char *text) {
    while (*text == ' ' || *text == '\t' || *text == '\r' || *text == '\n') {
        text++;
    }

    char *end = text + strlen(text);
    while (end > text && (end[-1] == ' ' || end[-1] == '\t' ||
                          end[-1] == '\r' || end[-1] == '\n')) {
        *--end = '\0';
    }
    return text;
}

static int parseInteger(char *text, int *value) {
    char *field = trimWhitespace(text);
    char *end;
    errno = 0;
    long parsed = strtol(field, &end, 10);
    if (field == end || *trimWhitespace(end) != '\0' ||
        errno == ERANGE || parsed < INT_MIN || parsed > INT_MAX) {
        return 0;
    }
    *value = (int)parsed;
    return 1;
}

//this is a push function that will add a monster to the top of the stack
void push(Player **player, Monster monster) {
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
Monster pop(Player **player) {
    if ((*player)->deck->top == NULL) {
        printf("Stack is empty, cannot pop\n");
        Monster emptyMonster = {"", 0, 0, ""};
        return emptyMonster; // return an empty monster if the stack is empty
    }
    Node *tempNode = (*player)->deck->top;
    Monster poppedMonster = tempNode->card;
    (*player)->deck->top = tempNode->next;
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
    char line[256];
    int loaded = 0;
    int lineNumber = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        lineNumber++;
        char *record = trimWhitespace(line);
        size_t length = strlen(record);
        if (length >= 2 && record[0] == '"' && record[length - 1] == '"') {
            record[length - 1] = '\0';
            record++;
        }

        char *healthField = strrchr(record, ',');
        if (healthField == NULL) {
            fprintf(stderr, "Skipping malformed card on line %d of %s\n", lineNumber, filename);
            continue;
        }
        *healthField++ = '\0';

        char *attackField = strrchr(record, ',');
        if (attackField == NULL) {
            fprintf(stderr, "Skipping malformed card on line %d of %s\n", lineNumber, filename);
            continue;
        }
        *attackField++ = '\0';

        char *typeField = strrchr(record, ',');
        if (typeField == NULL) {
            fprintf(stderr, "Skipping malformed card on line %d of %s\n", lineNumber, filename);
            continue;
        }
        *typeField++ = '\0';
        char *name = trimWhitespace(record);
        char *type = trimWhitespace(typeField);
        int valid = parseInteger(attackField, &monster.attack) &&
                    parseInteger(healthField, &monster.health);
        if (!valid || *name == '\0' || *type == '\0' ||
            strlen(name) >= sizeof(monster.name) ||
            strlen(type) >= sizeof(monster.type)) {
            fprintf(stderr, "Skipping malformed or oversized card on line %d of %s\n",
                    lineNumber, filename);
            continue;
        }

        strcpy(monster.name, name);
        strcpy(monster.type, type);
        push(player, monster);
        loaded++;
    }
    fclose(file);
    printf("Loaded %d monsters from %s\n", loaded, filename);

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