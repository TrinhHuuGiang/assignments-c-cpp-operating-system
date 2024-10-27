#ifndef _SJN_LL_
#define _SJN_LL_
/********************************************************************************
* Definitions
********************************************************************************/
#include <stdint.h>

typedef struct t_Proc_Linkedlist
{
    /* data */
    uint32_t id;
    uint32_t arrival_time;
    uint32_t burst_time;
    Plist* Next;
} Plist;


/********************************************************************************
* API
********************************************************************************/
/**
 * @brief Create a new Process linked list.
 * 
 * This function initializes a new process linked list
 * with the specified parameters to add a new member.
 * Memory for the new member is dynamically allocated.
 * 
 * @param id  Identifier for the process.
 * @param arrival_time  The time at which the process arrives.
 * @param burst_time  The time required to complete the process.
 * 
 * @return Plist* : Pointer to unique member of the Process list.
 */
Plist* init_new_Plist(uint32_t id, uint32_t arrival_time, uint32_t burst_time);

/**
 * @brief Delete the process list.
 * This function deallocates the memory used for Process list
 * 
 * @param first_proc Pointer to the first element of the process list.
 * @return int 0 if no error, -1 if an error occurred.
 */
uint8_t delete_Plist(Plist* first_proc);


#endif/* _SJN_LL_ */
