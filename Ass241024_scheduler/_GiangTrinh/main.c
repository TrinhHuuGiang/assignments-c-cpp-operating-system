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
// common libraries
#include <stdio.h>
#include <stdint.h>
// linkedlist scheduler
#include "SJN_linkedlist.h"
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
int main(int argc,const char* argv)
{
    /* [CHECK WINDOW / POSIX] */
    // default parent process
    // if window_child = 0 is child of a process on window
    int window_child = 1;
    #ifdef _WIN32
    // WINDOW: check if this is a child process by argc and argv
    if (argc > 1)
    {
        printf("%s process...\n",argv[1]);
        window_child = 0;//disable code for parent process
    }
    #endif /* _WIN32 */


    /* [PARENT SCHEDULER USING SJN] */
    if(window_child)//parent do
    {
        //list
        Plist* blocked_first = NULL; //Events that have not yet arrival
        Plist* ready_first = NULL;   //Events appear but have to wait 'running process'
        //running child process
        Plist* running_proc = NULL;

        //[start init] 
        printf("Parent process...\n");
        //first arrange not yet arrival events in arrival time from small to large to simulate realtime
        //init blocked list
        for(int i = 0; i<MAX_EVENT;i++)
        {
            if(add_new_to_Plist(blocked_first,event_id[i],event_arrival_time[i],event_burst_time[i]))
            {
                fprintf(stderr,"[err_%s] init blocked list failed",__FUNCTION__);
                return 1;
            }
        }

        //arrange blocked list by time arrival
        if(arrange_Plist_by_time_arrival(blocked_first))
        {
            fprintf(stderr,"[err_%s] arrange blocked list failed",__FUNCTION__);
            return 2;
        }

        //[start handle events]
        printf("Start time: 00:00:00.000\n__________\n\n");
        start_scheduler = GET_CURRENT_MILLIS;//get current time millisec

    }

}