/**
 * Viết chương trình C với yêu cầu sau:
 * - Process mẹ tạo vùng nhớ dùng chung cho một struct{int x, y, z}
 * Su dung mutex de dong bo hoa hai tien trinh nhu sau:
 * - Process me tao 1 khoa mutex sau do khoa lai
 * - Tao thread con va thread do se bi block
 * - Process me do gia tri x,y tu ban phim sau cho mo khoa va pthread_join thread con
 * - Thread sau do duoc  chay thuc hien z=x+y
 * - sau do no ket thuc
 * - sau do process me in ra z,  xoa khoa mutex va thoat chuong trinh
 */

/********************************************************************************
* Definitions
********************************************************************************/
#include <iostream>
#include <pthread.h>   //(pthread_mutex_)   init,lock,unlock,destroy

using namespace std;

typedef struct t_Share_Memory
{
    int x,y,z;
} smem;

/********************************************************************************
* Variables
********************************************************************************/
pthread_mutex_t mutexkey;    // initialize a mutex key
static smem s_cal_sum;           // struct to save shared value x,y,z,ready

/********************************************************************************
* Prototypes
********************************************************************************/
//thread 1 do: z = x+y ; ready = 0;
static void* thread(void* param);

/********************************************************************************
* Code
********************************************************************************/
int main()
{
    //initialize thread
    pthread_t tid; //setup a thread id

    //[create mutex]
    pthread_mutex_init(&mutexkey, NULL);

    //lock before start thread because we need input x,y first
    pthread_mutex_lock(&mutexkey);

    // create thread
    if(pthread_create(&tid,NULL,thread,&s_cal_sum))
    {
        cerr<<"[Error] Failed create thread\n";
        return 1;
    }

    // [main do]
    cout<<"Input x and y:";
    cin>>s_cal_sum.x>>s_cal_sum.y;

    //test locked
    cout<<"\n";
    for(int i=0;i<30;i++)
    {cout<<"| ";}

    //unlock mutex for thread 1 do z= x+y
    pthread_mutex_unlock(&mutexkey);

    // Sure that thread 1 was ended
    pthread_join(tid, NULL);

    // print z
    cout<<"\n\n-> z = "<< s_cal_sum.z <<"\n";

    // [deinit]
    // destroy mutex
    pthread_mutex_destroy(&mutexkey);

    //end
    return 0;
}

//z=x+y
static void* thread(void* param)
{
    //init
    smem* ref = (smem*)param;

    // [start critical session]
    // thread lock mutex
    pthread_mutex_lock(&mutexkey);

    //thread do z=x+y
    ref->z=ref->x+ref->y;

    //test lock
    cout<<"\n";
    for(int i=0;i<30;i++)
    {cout<<"_ ";}

    // unlock mutex
    pthread_mutex_unlock(&mutexkey);

    //end thread return nothing
    pthread_exit(0);//0 may be NULL :))
}