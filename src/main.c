#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/fintrackHeader.h"

int main() {
    //initialize the head of the node
    TransNode *head = NULL;
    char choose;

    // startup
    printf("Welcome to your Personal Finance Tracker!\n\n");
    printf("Would you like to resume your previous session? (y/n): ");
    scanf("%c", &choose);

    //chose yea
    if (choose == 'y') {
        printf("\nResuming from last session...\n");
        LoadTrans(&head, "logs/transaction_log.txt");
        printf("Previous transactions loaded.\n\n");
        CalculateBal(head);
    } else {
        printf("\nStarting a fresh session.\n\n");
    }

    char action[20];
    char action2[20];
    //had to use two different actions to grab the stuff from scanf idk how else to do it
    int check_input;
    
    // Menu Loop
    while (1) { 
        printf("\nEnter command: ");
        check_input = scanf("%19s", action);
        
        if (check_input != 1) {
            break;
        }

        // Handle add income/expense
        if (strcmp(action, "add") == 0) {
            //13 string becase thats the max amount of characters + EOF
            scanf("%13s", action2);

            char desc[50];
            double amount;
            int pos_num;
            
            //had to learn what strcmp was to make this i was so conchfused
            if (strcmp(action2, "income") == 0) {
                printf("Enter income description: ");
                scanf(" %49[^\n]", desc);
                printf("Enter amount: ");
                scanf("%lf", &amount);
                
                // prompt pos
                printf("Insert at position (Enter 0 to append to end): ");
                scanf("%d", &pos_num);
                
                //goes allll into thte func 
                InsertTrans(&head, pos_num, "INC", desc, amount);
                CalculateBal(head);
            } 
        
            else if (strcmp(action2, "expense") == 0) {
                printf("Enter expense description: ");
                scanf(" %49[^\n]", desc);
                printf("Enter amount: ");
                scanf("%lf", &amount);
                
                // same here
                printf("Insert at position (Enter 0 to append to end): ");
                scanf("%d", &pos_num);

                InsertTrans(&head, pos_num, "EXP", desc, amount);
                CalculateBal(head);
            }
        } 
        // print and delelel
        else if (strcmp(action, "print") == 0) {
            PrintTrans(head);
        } 
        else if (strcmp(action, "delete") == 0) {
            //to catch pos from scan
            int pos;
            printf("position to delete: ");
            scanf("%d", &pos);
            
            DeleteTrans(head, pos);
            printf("\n");
            CalculateBal(head);
        } 
        else if (strcmp(action, "quit") == 0) {
            SaveTrans(head);
            break;
        }
    }

    // Free memory
    TransNode *current = head;
    while (current != NULL) {
        TransNode *next_node = current->next;
        free(current);
        current = next_node;
    }

    return 0;
    //WOOOO PLEASEEE WORKKKK :pray: :pray:
}
