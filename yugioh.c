//this is the main source file


#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "player.h"
#include "monster.h"

int main(){
    printf("Weclome to Yu-Gi-Oh\n\n");
    printf("Main menu\n");
    char choice;
    Player* playerList = NULL;  // this is the head of a linked list for all the players
    do{
        printf("Press 1 to create a player\n");
        printf("Press 2 to add cards to you deck\n");
        printf("Press 3 to battle other players\n");
        printf("Press 4 to exit\n");
        printf("What would you like to do? ");
        scanf("%c", &choice);

        switch (choice){
            case '1':
                getchar(); //clear input buffer
                printf("creating player\n");
                //function to add players
                createPlayer(&playerList);  //the players are going to be connected by linked list
                getchar(); //clear input buffer
                break;

            case '2':
                printf("which deck would you like to add cards from? (1 or 2)\n");
                int deckChoice;
                scanf("%d", &deckChoice);
                getchar(); //clear input buffer
                if (deckChoice != 1 && deckChoice != 2) {
                    printf("Invalid deck choice. Please choose 1 or 2.\n");
                    break;
                }
                else if (deckChoice == 1) {
                    printf("Adding cards from deck 1\n");
                    // specify the filename for deck 1
                    readMonstersFromFile(&playerList, "YuGiOH-Deck1.csv");
                }
                else if (deckChoice == 2) {
                    printf("Adding cards from deck 2\n");
                    // specify the filename for deck 2
                    readMonstersFromFile(&playerList, "YuGiOH-Deck2.csv");
                }
                //debugging code to print the monsters in the stack
                Node* currentNode = playerList->deck->top;
                while (currentNode != NULL) {
                    printf("Monster: %s, Attack: %d, Health: %d, Type: %s\n", currentNode->card.name, currentNode->card.attack, currentNode->card.health, currentNode->card.type);
                    currentNode = currentNode->next;
                }
                getchar(); //clear input buffer
                break;

            case '3':
                printf("Get ready for battle");
                //functions to battle
                getchar(); //clear input buffer
                break;
            
            case '4':
                printf("Quiting the game\nThank you for playing!");
                break;

            default:
                printf("%c is not a valid character, enter again", choice);
                scanf("%c", &choice);
                getchar(); //clear input buffer
        }
    }while(choice != '4');
    return 0;
}