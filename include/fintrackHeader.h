#ifndef TRACKER_H
#define TRACKER_H

// Transaction Struct
typedef struct TransNode {
    char type[4];                //INC or EXP + null term
    char description[50];        //50 characters 
    double amount;              //MONey, has to double because the decimals
    
    //State Tracking
    int is_new;         //0 = (saved), 1 = (new)
    int is_deleted;     //0 = Not Delete, 1 = Marked deletion (---)
    int is_inserted;     //0 = inserted at the bottom, 1 = inserted between (+++)
    
    struct TransNode *next; //Point to next node
} TransNode;


// logs reading and writing
// main.c can pass the head pointer and file path
void LoadTrans(TransNode **head, char *filename);       
void SaveTrans(TransNode *head);  //Saves active nodes back to disk on exit


// Linked List 
void PrintTrans(TransNode *head);       //Shows history with +++  ---, Need to make priority for ---
void CalculateBal(TransNode *head);     //Calculates totals 

// Added these two so main.c knows they exist
void InsertTrans(TransNode **head, int pos, char *type, char *desc, double amount);
void DeleteTrans(TransNode *head, int marked_pos);

#endif