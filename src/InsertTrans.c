#include <stdio.h>
#include <stdlib.h>
#include "../include/fintrackHeader.h"

void InsertTrans(TransNode **head, int target_pos, char *type, char *desc, double amount) {
    // MINIMAL FIX: Changed < 1 to < 0 to allow 0 as a shortcut for appending to the end
    if (target_pos < 0) {
        printf("Invalid position! insert Position 0 or more.\n");
        return;
    }

    // Create new node
    TransNode *newNode = (TransNode*)malloc(sizeof(TransNode));

    // init the stats 
    newNode->is_new = 1;      
    newNode->is_inserted = 0; 
    newNode->is_deleted = 0;
    newNode->next = NULL;

    // use sprintf to put char array into memory then 
    sprintf(newNode->type, "%s", type);
    sprintf(newNode->description, "%s", desc);
    newNode->amount = amount;
    
    // MINIMAL FIX: If list is empty, force it to become the head regardless of position input
    if (*head == NULL) {
        *head = newNode;
        printf("%s added.\n\n", type);
        return;
    }

    // at Position 1
    if (target_pos == 1) {
        //now being inserted

    
        newNode->is_inserted = 1;
        newNode->next = *head; // new node is hooked to head now
        *head = newNode;       // now newnode is the new head!!!
        printf("%s added at position 1.\n\n", type);
        return;
    }
    //at middle OR end oh yeah two in one 
    else {
        //in between or the bottm
        TransNode *current = *head;
        int current_pos = 1;

        // appending to end with 0
        if (target_pos == 0) {
            newNode->is_new = 1; // Natural addition gets (new) status tag
            newNode->is_inserted = 0;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
            printf("%s added.\n\n", type);
            return;
        }

        // Walk until we reach the node right BEFORE the target position
        // OR until we hit the end of the current chain
        while (current != NULL && current_pos < target_pos - 1) {
            current = current->next;
            current_pos++;
        }

        // adding past the bottom of the list + 1
        if (current == NULL) {
            printf("Invalid position! Out of bounds!!.\n");
            free(newNode); // be freeeee
            return;
        }

        // if in between then put is inserted
        if (current->next != NULL) {
            newNode->is_inserted = 1; 
            newNode->is_new = 0; // so that it shows inserted instead of new
        }

        newNode->next = current->next; 
        current->next = newNode;       
        printf("%s added at position %d.\n\n", type, target_pos);
    }
}