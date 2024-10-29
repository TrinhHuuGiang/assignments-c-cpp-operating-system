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
static uint32_t event_id[MAX_EVENT] =           {1,2,3,4,5,6,7,8,9,10};
static uint32_t event_arrival_time[MAX_EVENT] = {8,5,5,3,1,6,2,7,10,9};
static uint32_t event_burst_time[MAX_EVENT] =   {9,10,7,2,6,1,3,5,5,8};
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

        //start init 
        printf("Parent process...\n");
        //first arrange not yet arrival events in arrival time from small to large to simulate realtime
        //init blocked list



    }

}