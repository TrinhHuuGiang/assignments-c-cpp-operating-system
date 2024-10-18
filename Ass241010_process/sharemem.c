/*
Viết chương trình C với yêu cầu sau:
- Process mẹ tạo vùng nhớ dùng chung cho một struct{int x, y, z; int ready;}, khởi tạo ready = 0, rồi tạo process con.
- Process mẹ đọc giá trị x, y từ bàn phím xong và gán ready = 1, sau đó chờ đến khi ready == 0 thì in giá trị z và kết thúc.
- Process con chờ đến khi ready == 1 thì tính z = x + y, rồi gán ready = 0 và kết thúc.
*/
/********************************************************************************
* Definitions
********************************************************************************/
#include <stdio.h>

#include <fcntl.h>              //For O_* constants,  shm_open(add Realtime extensionlib)
#include <unistd.h>           // For ftruncate(),  fork
#include <sys/mman.h>    // For mmap, shm_unlink(add Realtime extensionlib)

#include <sys/types.h>     //pid_t

#include <sys/wait.h>       //wait

#define SHM_NAME "my-shm"   //share memory name
#define SHM_SIZE   (1)              //1*sizeof(smem)

typedef struct t_Share_Memory
{
    int x,y,z;          //x,y get from keyboard|z=x+y
    int ready;        //init == 0
} smem;

/********************************************************************************
* Prototype
********************************************************************************/
/* init memmory to save a struct t_Share_Memory */
int init_ShareMemory(char* name, int size, int*  sid);

/*  init 'ready = 0' */
int init_smemToShm(int sid);

/* user modify x,y */
void input_xy(smem* p);
/********************************************************************************
* Code
********************************************************************************/
int main()
{
    //variable
    int shmid;                  //save id of share memory
    pid_t childPID = -1;   //check parent or child or failed init proc

    //init sharing mem
    if(init_ShareMemory(SHM_NAME,SHM_SIZE, &shmid))
    {
        return 1;
    }

    //init ready = 0
    if(init_smemToShm(shmid))
    {
        return 2;
    }

    //init child
    childPID = fork();
    if(childPID == -1)//init failed, parent do
    {
        fprintf(stderr,"[ERR] Failed init child process");
        return 3;
    }
    else if(childPID == 0)//child do
    {
        smem* p = (smem*)mmap(NULL,sizeof(smem),PROT_WRITE,MAP_SHARED,shmid,0);
        while(p->ready == 0)
        {
            continue;//polling untill ready == 1
        }
        //while ready == 1 -> z = x + y -> ready = 0
        p->z = p->x +p->y;
        //ready = 0
        p->ready = 0;
    }
    else//parent do
    {
        smem* p = (smem*)mmap(NULL,sizeof(smem),PROT_WRITE,MAP_SHARED,shmid,0);
        //get x,y
        input_xy(p);
        //then set ready = 1
        p->ready=1;
        //polling to wait child calculating
        while(p->ready == 1)
        {
            continue;
        }
        //print z
        fprintf(stdout,"\n[z =  %d]",p->z);
        //wait child end
        wait(NULL);
        //then end share mem
        shm_unlink(SHM_NAME);
    }

    // exit ok
    return 0;
}

/* init memory, size */
int init_ShareMemory(char* name, int size, int*  sid)
{
    int code;
    *sid = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    //check init mem
    if(*sid == -1)//error
    {
        fprintf(stderr,"[ERR] Failed open share memmory");
        return 1;
    }
    //allocate mem size
    code = ftruncate(*sid, size*sizeof(smem));
    if(code == -1)
    {
        fprintf(stderr,"[ERR] Failed modify memmory");
        return 2;
    }
    //anything ok
    return 0;
}

/* add a struct smem to Share memory*/
int init_smemToShm(int sid)
{
    smem* p = (smem*)mmap(NULL,sizeof(smem),PROT_WRITE,MAP_SHARED,sid,0);
    if((void*)p == MAP_FAILED)
    {
        return 1;
    }
    //init ready =0
    p->ready=0;
    return 0;
}

/* user modify x,y */
void input_xy(smem* p)
{
    fprintf(stdout,"\nIn put x, y: ");
    fscanf(stdin,"%d%d", &(p->x), &(p->y)); //input x,y
    fscanf(stdin,"%*[^\n]%*c"); //get \n out of buffer
}