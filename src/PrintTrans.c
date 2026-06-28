#include <stdio.h>
#include "../include/fintrackHeader.h"

void PrintTrans(TransNode *head) {
    // if NULL then nothing to print :O 
    if (head == NULL) {
        printf("No transactions found!\n\n");
        return;
    }

    printf("[ Transactions ]\n");

    //current is head so we dont mocve the head
    TransNode *current = head;
    int order = 1; 

    while (current != NULL) {
        // see if it starts with I then its INC so we add +
        char sign; 
        if (current->type[0] == 'I') {
            sign = '+';
        } else {
            sign = '-';
        }

        char *status_tag; 
        if (current->is_deleted == 1) {
            status_tag = "--- d";
        } else if (current->is_inserted == 1) {
            status_tag = "+++ i";
        } else if (current->is_new == 1) {
            status_tag = "(new)";
        } else {
            status_tag = "(saved)";
        }
        
        double display_amount = current->amount;
        if (display_amount < 0) {
            display_amount = -display_amount; // Turn negative value positive for printing
        }
        
        //using padding to set min and max width for desc to 20 characters. that and the other paddings are arbritrary
        //prints the index with a dot, has padding to 20, then the desc, then sign, then status tag, 
        //the 10.2 also truncates to 2 decimal points, meaning a bunch of other decimal points added in are valid :O 
        //dont need to add the current-> to sign and status bc that was already established in the variables they are contained in
        //soz another bg comment block because i needed to write it out in plain english to understand before making it
        printf("%d. %-20.20s %c%-10.2f %s\n", 
            order, current->description, sign, display_amount, status_tag);
            
        // Move on...
        order += 1;
        current = current->next;
    }
    printf("\n");
}