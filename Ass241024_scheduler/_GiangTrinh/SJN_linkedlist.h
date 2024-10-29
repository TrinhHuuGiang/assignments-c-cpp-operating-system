#ifndef _SJN_LL_
#define _SJN_LL_
/********************************************************************************
* Definitions
********************************************************************************/
#include <stdint.h>
#include <time.h>

typedef struct t_Proc_Linkedlist
{
    /* data */
    uint32_t id;
    uint32_t arrival_time;
    uint32_t burst_time;
    time_t   start_time;
    time_t   end_time;
    Plist*   Next;
} Plist;


/********************************************************************************
* API
********************************************************************************/
/**
 * @brief Add a new Process to linked list.
 * 
 * add a new member to linkedlist.
 * Memory for the new member is dynamically allocated.
 * 
 * @param id  Identifier for the process.
 * @param arrival_time  The time at which the process arrives.
 * @param burst_time  The time required to complete the process.
 * 
 * @return int 0 if no error, -1 if an error occurred.
 */
int8_t add_new_to_Plist(Plist* first_proc, uint32_t id, uint32_t arrival_time, uint32_t burst_time);

/**
 * @brief Arrange Plist by time arrival.
 * 
 * using "selection soft"_O(n^2)
 * 
 * create a temp list to move member of Plist from lowest to highest time arrival.
 */
int8_t arrange_Plist_by_time_arrival(Plist* first_proc);

/**
 * @brief Move a member from this Plist to first of another Plist
 */
int8_t move_to_first_another_Plist(Plist* first_list1, Plist* memlist1, Plist* first_list2);

/**
 * @brief Delete the process list.
 * This function deallocates the memory used for Process list
 * 
 * @param first_proc Pointer to the first element of the process list.
 * @return int 0 if no error, -1 if an error occurred.
 */
int8_t delete_Plist(Plist* first_proc);


#endif/* _SJN_LL_ */
