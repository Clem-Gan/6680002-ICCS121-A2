#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/fintrackHeader.h"

void LoadTrans(TransNode **head, char *filename) {
    FILE *logs = fopen(filename, "r");
    
    // Check log
    if (logs == NULL) {
        perror("Error opening logs");
        return; 
    }
    
    // temp loading dock 
    // fgets will dump a line into this array one at a time
    char sz[256];

    // Skip the 4 header lines
    for (int i = 0; i < 4; i++) {
        if (fgets(sz, sizeof(sz), logs) == NULL) {
            fclose(logs);
            return; 
        }
    }

    //init as null
    TransNode *local_head = NULL;
    TransNode *tail = NULL;

    //need raw txt data to be parsed
    //new vars for parsed
    while (fgets(sz, sizeof(sz), logs) != NULL){ // loop fgets until it hits NULL (EOF)
        char parsed_type[4];        //initialize the parsed files sizes 
        char parsed_desc[50];
        double parsed_amount;

        //extract using scanf, logs seperats with |. have to use mem address for amount to change the value of it
        if (sscanf(sz, "%3[^|]|%49[^|]|%lf", parsed_type, parsed_desc, &parsed_amount) == 3) { 
            
            /* Creates a "newNode" variable with the transnode structure
            it is a memory address which is pointing to
            a chunk of memory, now being treated as a transnode structure.
            The chunk is seperated and designated the byte amounts for type, desc, and amount
            it has the size of a transnode structure.
            Writing this mostly for my own understanding this is hard as to read :sob: 
            */
            TransNode *newNode = (TransNode*)malloc(sizeof(TransNode));
            
            //finally, getting to the actual part where I put the parsed data into the TransNode structure
            strcpy(newNode->type, parsed_type);             // Copy strings into the node's designated memory blocks
            strcpy(newNode->description, parsed_desc);
            
            // Assign the double amount value
            newNode->amount = parsed_amount;

            // Initializing states
            newNode->is_new = 0;
            newNode->is_inserted = 0;
            newNode->is_deleted = 0;
            
            // Set the next to NULL
            // using -> coz cleaner than (*newNode)->next
            //explanation, the next data type is a POINTER to another TransNode Structure
            newNode->next = NULL;
            
            if (local_head == NULL) {
                local_head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
        }
    } 
    //be freeeeee
    fclose(logs);
    *head = local_head;
}