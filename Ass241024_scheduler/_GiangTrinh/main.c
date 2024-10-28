/* [ Shortest Job First | Shortest Job Next ]
- Input: Thông tin số process, arrival time, burst time (ở đây dùng ms) được
nhập sẵn trong chương trình, các tham số cần thiết của thuật toán sử dụng (giá trị tuỳ chọn)
- Output: In ra lần lượt với mỗi dòng gồm: process nào được chạy, 
thời điểm bắt đầu, thời gian chạy của từng process
- Nộp bài kèm cả output được copy vào một file .txt
*/

/********************************************************************************
* Definitions
********************************************************************************/
#include <stdio.h>

// linkedlist scheduler
#include "SJN_linkedlist.h"
// process
#include "process_handler.h"
// timer
#include "delay_ms.h"

/********************************************************************************
* Variables
********************************************************************************/

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
        printf("Parent process...\n");



    }

}