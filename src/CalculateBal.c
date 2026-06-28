#include <stdio.h>
#include "../include/fintrackHeader.h"

void CalculateBal(TransNode *head) {
    double balance = 0.0;
    TransNode *current = head;

    //calculate balance
    while (current != NULL) {
        // Skip deleted transactions!
        if (current->is_deleted != 1) {
            if (current->type[0] == 'I') { // INC
                balance += current->amount;
            } else {                       // EXP
                balance -= current->amount;
            }
        }
        current = current->next;
    }

    // Match your assignment output styling exactly
    printf("Current Balance: ");
    if (balance < 0) {
        // Prints the negative sign right before the dollar sign: -$45.00
        printf("-$%.2f\n", -balance); 
    } else {
        printf("$%.2f\n", balance);
    }

    // Budget Status Logic
    if (balance < 0) {
        printf("Budget Status: Over Budget!\n");
    } else {
        printf("Budget Status: Within Budget\n");
    }
}