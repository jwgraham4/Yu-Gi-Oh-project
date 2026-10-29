#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

typedef struct Monster{
    char name[25];
    int attack;
    int health;
    char type[25];
}Monster;

typedef struct Player{
   char name[25];
   int health;
   Monster deck;
   Monster hand[5];
   Monster attackQueue;
   Monster defenseQueue;
}Player;

int main(){
    printf("Weclome to Yu-Gi-Oh\n\n");
    printf("Main menu\n");
    char choice;
    do{
        printf("Press 1 to create a player\n");
        printf("Press 2 to add cards to you deck\n");
        printf("Press 3 to battle other players\n");
        printf("Press 4 to exit\n");
        printf("What would you like to do? ");
        scanf("%c", &choice);

        switch (choice){
            case '1':
                printf("creating player");
                scanf("%c"); //clear input buffer
                break;

            case '2':
                printf("Adding Cards");
                scanf("%c"); //clear input buffer
                break;

            case '3':
                printf("Get ready for battle");
                scanf("%c"); //clear input buffer
                break;
            
            case '4':
                printf("Quiting the game\nThank you for playing!");
            default:
                printf("%c is not a valid character, enter again", choice);
                scanf("%c", &choice);
                scanf("%c"); //clear input buffer
        }
    }while(choice != '4');
    return 0;
}