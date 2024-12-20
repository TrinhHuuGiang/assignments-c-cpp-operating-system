/********************************************************************************
* Definitions
********************************************************************************/
#include "SJN_linkedlist.h"
#include <stdio.h>
#include <stdlib.h>//allocate memory
/********************************************************************************
* Variables
********************************************************************************/

/********************************************************************************
* Prototypes
********************************************************************************/

/********************************************************************************
* Code
********************************************************************************/
// Add a new Process to head of linked list.
int8_t add_new_to_Plist(Plist** first_proc, uint32_t id, uint32_t arrival_time, uint32_t burst_time)
{
    Plist* new_proc = (Plist*)calloc(1, sizeof(Plist));
    if(new_proc==NULL)
    {return -1;/*malloc failed*/}

    new_proc->id=id;
    new_proc->arrival_time=arrival_time;
    new_proc->burst_time=burst_time;

    if((*first_proc) != NULL)
    {
        new_proc->Next = *first_proc;
        *first_proc = new_proc;
    }
    else
    {
        *first_proc = new_proc;
    }

    /* anything ok */
    return 0;
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
int8_t move_to_first_another_Plist(Plist** first_list1, Plist* memlist1, Plist** first_list2)
{
    //cut memlist1
    if(memlist1 == *first_list1)
    {
        *first_list1 = (*first_list1)->Next;
    }
    else
    {
        Plist* pre_memlist1 = *first_list1;
        while(pre_memlist1->Next != memlist1)
        {
            pre_memlist1=pre_memlist1->Next;
        }
        pre_memlist1->Next = memlist1->Next;
    }
    //then add it to first of list 2
    memlist1->Next=*first_list2;
    *first_list2=memlist1;

    //anything ok
    return 0;
}

// Delete the process list.
int8_t delete_Plist(Plist** first_proc)
{
    while(*first_proc!=NULL)
    {
        Plist* temp = *first_proc; 
        *first_proc = (*first_proc)->Next;
        free(temp);
    }
    return 0;
}