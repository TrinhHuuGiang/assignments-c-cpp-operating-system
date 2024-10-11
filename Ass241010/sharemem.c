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

typedef struct t_Share_Memory
{
    int x,y,z;          //x,y get from keyboard|z=x+y
    int ready;        //init == 0
} smem;

/********************************************************************************
* Prototype
********************************************************************************/
/* Parent proc init 'ready==0'*/
void init_Memory(smem *mem);
/* Parent proc get value for x,y*/
void input_xy(smem *mem);


/********************************************************************************
* Code
********************************************************************************/
int main()
{
    smem shared_mem;
    //init mem
    init_Memory(&shared_mem);

    //get x, y
    input_xy(&shared_mem);

    fprintf(stdout,"\nx=[%d],y=[%d]",shared_mem.x,shared_mem.y);

    // exit ok
    return 0;
}

void init_Memory(smem *mem)
{
    mem->z=0;
    //anything ok
    return;
}

void input_xy(smem *mem)
{
    fprintf(stdout,"\nInput x,y: ");
    fscanf(stdin,"%d%d",&mem->x,&mem->y);
    fscanf(stdin,"%*[^\n]%*c");
}