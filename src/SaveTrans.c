#include <stdio.h>
#include <stdlib.h>
#include "../include/fintrackHeader.h"

void SaveTrans(TransNode *head) {
    FILE *logs = fopen("logs/transaction_log.txt", "w");

    if (logs == NULL) {
        perror("Error saving logs");
        return;
    }

    // formmatting needed
    fprintf(logs, "# Format: TYPE|DESCRIPTION|AMOUNT\n");
    fprintf(logs, "# TYPE: INC (Income) or EXP (Expense)\n");
    fprintf(logs, "# AMOUNT: Positive decimal number\n\n");

    TransNode *current = head;
    while (current != NULL) {
        if (current->is_deleted == 0) {
            double save_amount = current->amount;
            
            // Enforce rule: AMOUNT must be a positive decimal number
            if (save_amount < 0) {
                save_amount = -save_amount;
            }
            
            fprintf(logs, "%s|%s|%.2f\n", current->type, current->description, save_amount);
        }
        current = current->next;
    }

    fclose(logs);
    printf("Data saved successfully. Quitting program.\n");
}