/* [ Shortest Job First | Shortest Job Next ]
- Input: Thông tin số process, arrival time, burst time được
nhập sẵn trong chương trình, các tham số cần thiết của thuật toán sử dụng (giá trị tuỳ chọn)
- Output: In ra lần lượt với mỗi dòng gồm: process nào được chạy, 
thời điểm bắt đầu, thời gian chạy của từng process
- Nộp bài kèm cả output được copy vào một file .txt
*/

/********************************************************************************
* Definitions
********************************************************************************/
#include <stdio.h>

// process - POSIX
#include <unistd.h>          //fork
#include <sys/types.h>     //pid_t
#include <sys/wait.h>       //wait
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
