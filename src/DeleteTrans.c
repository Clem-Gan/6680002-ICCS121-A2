#include <stdio.h>
#include "../include/fintrackHeader.h"

void DeleteTrans(TransNode *head, int marked_pos) {

    TransNode *current = head;
    int current_pos = 1;

    // keep stepping until the current is the marked pos
    // had to add the !=NULL here explained below
    while (current != NULL && current_pos < marked_pos) {
        //if this part ever bcomes NULL then the code stops BUT the null value is kept,
        // if statement handles this below!!
        current = current->next;
        
        current_pos++;
    }

    //also without the != NULL made me crash a bunch while testing :p 
    // I think its because it was reading memory chunks outside of the nodes? because if I only have liek 3 items
    // and I try to ptu pos 999 then it just reads farr out of the memory of the structure
    if (current == NULL) {
        printf("Position not found!\n");
        return;
    }

    // flip the flag to 1
    // CalculateBal will ignore this chunk
    // AND print will mark as ---d
    //automatically deleted because chunk ignored and its not saved with the others!! pretty cool i think
    current->is_deleted = 1;
    printf("Transaction at position %d marked for deletion\n", marked_pos);
}

