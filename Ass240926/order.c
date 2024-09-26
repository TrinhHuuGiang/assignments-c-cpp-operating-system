// About: In ra menu voi tham so la lua con nguoi dung nhap
// Tra ve menu nguoi dung da nhap
/********************************************************************************
* Definitions
********************************************************************************/
#include <stdio.h>

/********************************************************************************
* Code
********************************************************************************/
int main(int argc, const char** argv)
{
    int check = argc>1?0:1;
    /*
    * [check]
    * - if nothing input -> check = 1
    * - else -> check = 0
    */
    if(check)
    {
        printf("The user input nothing\n");
        return -1;
    }
    //else if user input something, print ignore $0
    for(int i = 1; i < argc; i++)
    {
        printf("%2d. %s\n",i,argv[i]);
    }
    return 0; // anything ok
}