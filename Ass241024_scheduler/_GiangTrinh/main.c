/* [ Shortest Job First | Shortest Job Next ]
- Yêu cầu: Viết chương trình mô phỏng thuật toán lập lịch SJN
- Input: Thông tin số process, arrival time, burst time (ở đây dùng ms) được
nhập sẵn trong chương trình, các tham số cần thiết của thuật toán sử dụng (giá trị tuỳ chọn)
- Output: In ra lần lượt với mỗi dòng gồm: process nào được chạy, 
thời điểm bắt đầu, thời gian chạy của từng process
- Nộp bài kèm cả output được copy vào một file .txt
*/

/********************************************************************************
* Definitions
********************************************************************************/
#define DEBUG 1

// common libraries
#include <stdio.h>
#include <stdint.h>
// linkedlist scheduler
#include "SJN_linkedlist.h"
// shared memory
#include "mapping.h"
// process
#include "process_handler.h"
// timer
#include "delay_ms.h"

// Scheduling parameters
#define MAX_EVENT 10
#define SHM_RUNNING_CHILD "child_shm"

/********************************************************************************
* Variables
********************************************************************************/
static uint32_t event_id[MAX_EVENT] =           {  1,  2,  3,  4,  5,  6,  7,  8,  9, 10};
static uint32_t event_arrival_time[MAX_EVENT] = {800,500,500,300,100,600,200,700,100,900};
static uint32_t event_burst_time[MAX_EVENT] =   {900,100,700,200,600,100,300,500,500,800};
static uint32_t start_scheduler = 0;
/********************************************************************************
* Prototypes
********************************************************************************/

/********************************************************************************
* Code
********************************************************************************/
int main(int argc,const char* argv[])
{
    /* [CHECK WINDOW / POSIX] */
    // default parent process
    // if window_child = 0 is child of a process on window
    int window_child = 1;
    #ifdef _WIN32
    // WINDOW: check if this is a child process by argc and argv
    if (argc > 1)
    {
        fprintf(stderr,"\nChild process...\n");
        window_child = 0;//disable code for parent process
    }
    #endif /* _WIN32 */


    /* [PARENT SCHEDULER USING SJN] */
    if(window_child)//parent do
    {
        //list
        Plist* blocked_first = NULL; //Events that have not yet arrival
        Plist* ready_first = NULL;   //Events appear but have to wait 'running process'
        //shared memory
        SHARED_ID shmid;
        //running child process == pointer to shared memory
        //save start time, stop time. send burst time to child process will run
        Plist* running_proc = NULL;

        //[start init] 
        fprintf(stderr,"Parent process...\n");
        //first arrange not yet arrival events in arrival time from small to large to simulate realtime
        //init blocked list
        for(int i = 0; i<MAX_EVENT;i++)
        {
            if(add_new_to_Plist(&blocked_first,event_id[i],event_arrival_time[i],event_burst_time[i]))
            {
                fprintf(stderr,"[err_%s] init blocked list failed",__FUNCTION__);
                return 1;
            }
        }

        //arrange blocked list by time arrival
        if(arrange_Plist_by_time_arrival(&blocked_first))
        {
            fprintf(stderr,"[err_%s] arrange blocked list failed",__FUNCTION__);
            return 2;
        }

#if DEBUG
        Plist* ttt = blocked_first;
        printf("Sort by arrival: ");
        while(ttt != NULL) {printf("%d ",ttt->id);ttt=ttt->Next;}
        printf("\n_____\n");
#endif
        
        //[start handle events]
        printf("Start time: 00:00:00.000\n__________\n\n");
        start_scheduler = get_current_millis();//get current time millisec
        //init shared memory
        if(open_shm(&shmid,SHM_RUNNING_CHILD,sizeof(Plist)))
        {
            fprintf(stderr,"[err_%s] shared memory failed",__FUNCTION__);
            return 3;
        }
        running_proc = (Plist*)get_link_shm(shmid, sizeof(Plist));

        //[Start scheduling]
        //check until 2 list empty
        while((blocked_first != NULL) || (ready_first!=NULL))
        {
            //[check arrival time]
            Plist* temp = blocked_first;
            uint32_t delta_time = get_current_millis() - start_scheduler;

            while((temp != NULL) && (temp->arrival_time < delta_time))
            {
                //if not empty list or reach the end of list
                //and arrival time < delta time (time from parent process start scheduler)
                //else stop check list
                move_to_first_another_Plist(&blocked_first,temp,&ready_first);
                temp = temp->Next;
            }

            //[check ready list]
            if(ready_first == NULL)//next loop because ready list empty
            {continue;}
            //check shortest job (burst time) first
            {
                //this is a small scope to get running process
                Plist* shortest_burst = ready_first;
                temp = ready_first;
                while(temp!=NULL)
                {
                    if(shortest_burst->burst_time<temp->burst_time)
                    {
                        shortest_burst=temp;
                    }
                    temp = temp->Next;
                }

                // [prepare run process]
                // cut 'process run' out of ready list
                if(shortest_burst==ready_first)
                {
                    ready_first = ready_first->Next;
                    shortest_burst->Next = NULL;
                }
                else
                {
                    temp = ready_first;
                    while(temp->Next!=shortest_burst)
                    {
                        temp = temp->Next;
                    }
                    temp->Next = shortest_burst->Next;
                    shortest_burst->Next = NULL;
                }
                // send burst time to child will be running
                *running_proc = *shortest_burst;
                running_proc->start_time = get_current_millis()-start_scheduler;

                //[Run child process]   
                {
                    CHILD_PID pid;
                    // run
                    if(init_proc(&pid, argv[0], SHM_RUNNING_CHILD))
                    {
                        fprintf(stderr,"[err_%s] child process run failed",__FUNCTION__);
                        return 4;
                    }

                    #if defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
                    //[POSIX CHILD Running process]
                    if(pid == 0)
                    {
                        //only delay burst ms
                        delay_millis(running_proc->burst_time);
                        
                    }
                    #endif

                    // wait end child proc
                    wait_proc(pid);
                }

                // save end time
                running_proc->end_time = get_current_millis() - start_scheduler;

                // free ran process
                free(shortest_burst);

                // print to file
                fprintf(stdout,"ID: %-10d|Arrival:%-10d|Start  :%-10d|End    :%-10d|RunTime:%-10d|Burst  :%-10d\n__________\n",
                running_proc->id, running_proc->arrival_time, 
                running_proc->start_time,running_proc->end_time,
                running_proc->end_time - running_proc->start_time,
                running_proc->burst_time
                );
            }

        }

        //end parent scheduler
        //delete shared memory
        delete_shm(shmid);

        //exit ok
        fprintf(stderr,"\n[END PROGRAM] - NO ERROR");
        return 0;
    }

#ifdef _WIN32
    //[WINDOW CHILD Running process]   
    {
        //open file share memory
        SHARED_ID shmid = OpenFileMapping(
        FILE_MAP_ALL_ACCESS,       // Read/write access
        FALSE,                     // Không kế thừa tên
        SHM_RUNNING_CHILD          // Tên của đối tượng mapping
        );
        Plist* running_proc = (Plist*)get_link_shm(shmid, sizeof(Plist));

        //only delay burst ms
        delay_millis(running_proc->burst_time);

        //exit ok
        return 0;
    }
#endif
}