/********************************************************************************
* Definitions
********************************************************************************/
#include "SJN_linkedlist.h"
#include <stdio.h>
/********************************************************************************
* Variables
********************************************************************************/

/********************************************************************************
* Prototypes
********************************************************************************/

/********************************************************************************
* Code
********************************************************************************/
// Add a new Process to linked list.
Plist* add_new_to_Plist(Plist* first_proc, uint32_t id, uint32_t arrival_time, uint32_t burst_time)
{

}

//Arrange Plist by time arrival.
int8_t arrange_Plist_by_time_arrival(Plist** first_proc)
{
    Plist* shortest_list = NULL; //arranged list
    //check empty list
    if(*first_proc == NULL)
    {
        fprintf(stderr,"[warn_%s] list empty",__FUNCTION__);
        return 0;
    }
    //selection soft
    while((*first_proc)!=NULL)
    {
        //get biggest arrival time
        uint32_t biggest_time = (*first_proc)->arrival_time;
        Plist* temp_biggest = *first_proc;
        Plist* temp_first = *first_proc;
        
        while(temp_first!= NULL)
        {
            if(biggest_time < temp_first->arrival_time)
            {
                biggest_time = temp_first->arrival_time;
                temp_biggest = temp_first;
            }
            temp_first = temp_first->Next;
        }
        //before cut it
        //if the cut is first of list->update *first_proc
        //then cut it
        if(temp_biggest==*first_proc)
        {
            *first_proc = (*first_proc)->Next;
        }
        else
        {
            Plist* pre_biggest = *first_proc;
            while(pre_biggest->Next!=temp_biggest)
            {
                pre_biggest = pre_biggest->Next;
            }
            pre_biggest->Next = temp_biggest->Next;
        }

        //add it to first of shortest_list
        temp_biggest->Next = shortest_list;
        shortest_list = temp_biggest;
    }
    //update list
    *first_proc = shortest_list;

    //any ok
    return 0;
}

//Move a member from this Plist to first of another Plist
int8_t move_to_first_another_Plist(Plist* first_list1, Plist* memlist1, Plist* first_list2);

// Delete the process list.
int8_t delete_Plist(Plist* first_proc);