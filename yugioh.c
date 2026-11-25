//this is the main source file


#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "player.h"
#include "monster.h"

static int hasCardsToDraw(Player *player) {
    return player->deck != NULL && player->deck->top != NULL;
}

void drawCards(Player *player, int numCards) {
    for (int i = 0; i < numCards; i++) {
        if (hasCardsToDraw(player)) {
            Monster drawnMonster = popMonster(player);
            player->hand[i] = drawnMonster;
            printf("%s drew %s\n", player->name, drawnMonster.name);
        } else {
            printf("%s has no more cards to draw!\n", player->name);
            break;
        }
    }
}

void displayHand(Player *player) {
    printf("%s's hand:\n", player->name);
    for (int i = 0; i < 5; i++) {
        printf("Slot %d: ", i + 1);
        if (strlen(player->hand[i].name) > 0) {
            printf("Card %d: %s (Type: %s, Attack: %d, Health: %d)\n", 
                   i + 1, player->hand[i].name, player->hand[i].type, 
                   player->hand[i].attack, player->hand[i].health);
        }
        else {
            printf("Empty\n");
        }
    }
}

void chooseCards(Queue **queue, Player *player) {
    displayHand(player);
    printf("%s, choose a card (1-5): ", player->name);
    int choice;
    scanf("%d", &choice);
    if (choice < 1 || choice > 5) {
        printf("Invalid choice. Please enter a number between 1 and 5.\n");
        while (getchar() != '\n'); // Clear input buffer
        return;
    }
    while (getchar() != '\n'); // Clear input buffer

    Monster chosenMonster = player->hand[choice - 1];
    if (strlen(chosenMonster.name) == 0) {
        printf("No card in that slot. Please choose again.\n");
        return;
    }

    enqueue(queue, chosenMonster);
    printf("%s has chosen %s.\n", player->name, chosenMonster.name);

    //after a card is chosen, we will remove it from the players hand then draw a new card from the deck if there are any left
    if (hasCardsToDraw(player)) {
        Monster drawnMonster = popMonster(player);
        player->hand[choice - 1] = drawnMonster;
        printf("%s drew %s to replace the chosen card.\n", player->name, drawnMonster.name);
    } else {
        printf("%s has no more cards to draw to replace the chosen card.\n", player->name);
        player->hand[choice - 1] = (Monster){"", 0, 0, ""}; // Reset the chosen slot to empty
    }
}

//this function will toss a coin and return heads or tails
int tossCoin() {
    return rand() % 2;
}

void battle(Player *player1, Player *player2) {
    printf("Battle between %s and %s!\n", player1->name, player2->name);
    printf("We will toss a coin to determine who goes first.\n");
    getchar(); // Wait for user input before tossing the coin
    int coinResult = tossCoin();

    Player *firstPlayer;
    Player *secondPlayer;
    if (coinResult == 0) {
        printf("It is heads!\n");
        printf("%s goes first!\n", player1->name);
        firstPlayer = player1;
        secondPlayer = player2;
    } 
    else {
        printf("It is tails!\n");
        printf("%s goes first!\n", player2->name);
        firstPlayer = player2;
        secondPlayer = player1;
    }
    //each player will draw 5 cards into their hand
    printf("Each player will now draw 5 cards into their hand.\n");
    getchar(); // Wait for user input before drawing cards
    drawCards(firstPlayer, 5);
    getchar(); // Wait for user input before drawing cards
    drawCards(secondPlayer, 5);
    printf("The battle begins!\n");
    printf("Each player begins with 8000 health points.\n");
    printf("Good luck!\n");
   

    //this is the main battle loop
    while(player1->deck->top != NULL && player2->deck->top != NULL) {
        //each player will take a turn to choose attack and defense cards
        printf("%s's turn to choose cards.\n", firstPlayer->name);
        printf("Choose an attack card\n");
        chooseCards(&firstPlayer->attack, firstPlayer);
        printf("Choose a defense card\n");
        chooseCards(&firstPlayer->defense, firstPlayer);
        printf("%s's turn to choose cards.\n", secondPlayer->name);
        printf("Choose an attack card\n");
        chooseCards(&secondPlayer->attack, secondPlayer);
        printf("Choose a defense card\n");
        chooseCards(&secondPlayer->defense, secondPlayer);
    }

    //this is where the battle logic will go, we will compare the attack and defense cards and determine the winner of the round
    int round = 1;
    while(firstPlayer->health > 0 && secondPlayer->health > 0) {
        printf("Round %d\n", round);
        Monster attackCard1 = dequeue(&firstPlayer->attack);
        Monster defenseCard1 = dequeue(&firstPlayer->defense);
        Monster attackCard2 = dequeue(&secondPlayer->attack);
        Monster defenseCard2 = dequeue(&secondPlayer->defense);

        // if the attack card's attack is greater than the defense card's health
        //the defending player will lose health equal to the difference
        if (attackCard1.attack > defenseCard2.health) {
            secondPlayer->health -= attackCard1.attack - defenseCard2.health;
        }
        if (attackCard2.attack > defenseCard1.health) {
            firstPlayer->health -= attackCard2.attack - defenseCard1.health;
        }
        // output to show the health of each player after each round
        printf("%s's health: %d\n", firstPlayer->name, firstPlayer->health);
        printf("%s's health: %d\n", secondPlayer->name, secondPlayer->health);
        round++;
    }
    //declare a winner based on the health of each player
    if (firstPlayer->health <= 0 && secondPlayer->health <= 0) {
        printf("It's a draw!\n");
    } 
    else if (firstPlayer->health <= 0) {
        printf("%s wins the battle!\n", secondPlayer->name);
    } 
    else if (secondPlayer->health <= 0) {
        printf("%s wins the battle!\n", firstPlayer->name);
    }
}

int main(){
    printf("Welcome to Yu-Gi-Oh\n\n");
    srand((unsigned int)time(NULL));  // Seed the random number generator for coin tosses
    char input[32];
    char choice = '\0';
    Player* playerList = NULL;  // this is the head of a linked list for all the players
    do{
        printf("Main menu\n");
        printf("Press 1 to create a player\n");
        printf("Press 2 to battle other players\n");
        printf("Press 3 to exit\n");
        printf("What would you like to do? ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        choice = input[0];

        switch (choice){
            case '1':
                printf("creating player\n");
                createPlayer(&playerList);  //the players are going to be connected by linked list
                break;

            case '2':
                printf("Get ready for battle");
                if (playerList == NULL || playerList->next == NULL) {
                    printf("Not enough players to battle. Create at least two players.\n");
                    break;
                }
                Player* player1 = playerList;
                Player* player2 = playerList->next;
                battle(player1, player2);
                break;
            
            case '3':
                
                printf("Quitting the game\nThank you for playing!");
                break;

            default:
                printf("%c is not a valid choice. Enter again.\n", choice);
        }
    }while(choice != '3');
    return 0;
}