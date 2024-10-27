/********************************************************************************
* Definitions
********************************************************************************/
#include "SJN_linkedlist.h"

/********************************************************************************
* Variables
********************************************************************************/

/********************************************************************************
* Prototypes
********************************************************************************/

/********************************************************************************
* Code
********************************************************************************/
// Create a new Process linked list.
Plist* init_new_Plist(uint32_t id, uint32_t arrival_time, uint32_t burst_time);
// Delete the process list.
int8_t delete_Plist(Plist* first_proc);