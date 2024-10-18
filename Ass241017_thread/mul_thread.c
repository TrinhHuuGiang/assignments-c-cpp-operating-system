/*
Viết chương trình C với yêu cầu sau:
- Process tạo vùng nhớ global dùng chung struct{int x, y, z; int ready;}
- khởi tạo ready = 0, rồi tạo 1 thread.
- Process đọc giá trị x, y từ bàn phím xong và gán ready = 1, sau đó chờ đến khi ready == 0 thì in giá trị z và kết thúc.
- Thread chờ đến khi ready == 1 thì tính z = x + y, rồi gán ready = 0 và kết thúc.
*/

/********************************************************************************
* Definitions
********************************************************************************/
#include <stdio.h>
#include <pthread.h>

typedef struct t_Share_Memory
{
    int x,y,z;
    int ready;
} smem;

/********************************************************************************
* Variables
********************************************************************************/
static smem s_cal_sum;//struct to save shared value x,y,z,ready

/********************************************************************************
* Prototypes
********************************************************************************/
//thread 1 do: z = x+y ; ready = 0;
static void* thread_1(void* param);

/********************************************************************************
* Code
********************************************************************************/
int main()
{
    pthread_t tid; //setup a thread id
    pthread_attr_t attr; //setup thread attribute

    //init ready = 0
    s_cal_sum.ready = 0;

    //[create thead]
    // set defaut attribute 
    if(pthread_attr_init(&attr))
    {
        fprintf(stderr,"[Error] Failed init attribute\n");
        return 1;
    }
    // create thread
    if(pthread_create(&tid,&attr,thread_1,&s_cal_sum))
    {
        fprintf(stderr,"[Error] Failed create thread\n");
        return 2;
    }

    // [main do]
    fprintf(stdout,"Input x and y: ");
    fscanf(stdin,"%d %d",&(s_cal_sum.x),&(s_cal_sum.y));
    // ready = 1; thread do
    s_cal_sum.ready = 1;

    // start and wait thread 1 end; ready = 0;
    while(s_cal_sum.ready == 1){continue;}
    // print z
    fprintf(stdout,"\n-> z = %d\n",s_cal_sum.z);

    // Sure that thread 1 was ended
    pthread_join(tid, NULL);

    //end
    return 0;
}

static void* thread_1(void* param)
{
    //wait main done input
    while(s_cal_sum.ready == 0){continue;}
    
    //thread do z=x+y
    s_cal_sum.z=s_cal_sum.x+s_cal_sum.y;
    
    //thread done ready = 0
    s_cal_sum.ready=0;

    //end thread return nothing
    pthread_exit(0);//0 may be NULL :))
}