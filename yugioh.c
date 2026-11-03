//this is the main source file


#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "player.h"

typedef struct Player Player;

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
                printf("creating player");
                //function to add players
                createPlayer(&playerList);  //the players are going to be connected by linked list
                getchar(); //clear input buffer
                break;

            case '2':
                printf("Adding Cards");
                //function to add cards

                getchar(); //clear input buffer
                break;

            case '3':
                printf("Get ready for battle");
                //functions to battle
                getchar(); //clear input buffer
                break;
            
            case '4':
                printf("Quiting the game\nThank you for playing!");
            default:
                printf("%c is not a valid character, enter again", choice);
                scanf("%c", &choice);
                getchar(); //clear input buffer
        }
    }while(choice != '4');
    return 0;
}