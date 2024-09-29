// About: In ra menu voi tham so la lua con nguoi dung nhap
// Tra ve menu nguoi dung da nhap
// Nguoi dung nhap day stt cac order
// Tra ve san pham nguoi dung order
/********************************************************************************
* Definitions
********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_ORDER (101) //size string order limited by 100
#define ZERO_OFFSET (48)
/********************************************************************************
* Code
********************************************************************************/
int main(int argc, const char** argv)
{
    char* order_str = NULL; // save order by user
    char* token = NULL; //get each order
    int check = argc>1?0:1;
    /*
    * [1. check menu]
    * - if nothing input -> check = 1
    * - else -> check = 0
    */
    if(check)
    {
        printf("[ERR] The user input nothing\n");
        return -1;
    }
    //else if user input something, print ignore $0
    for(int i = 1; i < argc; i++)
    {
        printf("%3d. %s\n",i,argv[i]);
    }

    /*[2. User input order]*/
    /*allocate order*/
    order_str = (char*)calloc(MAX_ORDER,sizeof(char));
    if(order_str == NULL)
    {
        printf("[ERR] Allocate Failed.\n");
        return -2;
    }
    /*User input orders*/
    printf("Input your order, separated by ' ' and limited by 100 character.\n");
    printf("Let's input your order:\n->");
    fgets(order_str,MAX_ORDER,stdin);

    /*check syntax: !number, out of range*/
    for(int i = 0;i<MAX_ORDER;i++)
    {
        /*[check end]*/
        // \n is valid end
        if(order_str[i] == '\n')
        {
            break;//break;
        }
        // \0 is out of range
        else if(order_str[i] == '\0')
        {
            printf("[WARN] Input size out of range 100\n");
            break;//break;
        }
        // ignore ' '
        else if(order_str[i] == ' ')
        {
            //do nothing
            continue;
        }
        // check !number
        else if(order_str[i] < '0' || order_str[i] > '9')
        {
            printf("[ERR] User input a char - at position [%d]\n", i);
            return -3;
        }
        //else do nothing
    }
    
    /*config order_str to get order*/
    token = strtok(order_str," ");
    while(token!=NULL)
    {
        token = strtok(NULL," ");
        //continue check
    }

    /*get order*/
    printf("Your order:\n");
    for(int i = 0; i<MAX_ORDER; i++)
    {
        int mul = 0;
        int sum = 0;
        int reversed_sum = 0;
        //check until before MAX_ORDER = \0 or get \n
        //write order reverse
        while(order_str[i] != '\n' && order_str[i] != '\0')
        {
            sum += (order_str[i] - ZERO_OFFSET) * pow(10,mul);
            mul++;
            i++;
        }
        //check mul then reverse
        if(mul > 0)
        {
            while (sum > 0) 
            {
                int last_digit = sum % 10;   // Lấy chữ số cuối cùng
                reversed_sum = reversed_sum * 10 + last_digit;  // Ghép số mới
                sum /= 10;  // Loại bỏ chữ số cuối cùng
            }
            //print what user want
            if(reversed_sum > 0 && reversed_sum < argc)
            {
                printf("%3d. %s\n",reversed_sum,argv[reversed_sum]);
            }
            else //>=argc
            {
                printf("%3d. [Not available]\n",reversed_sum);
            }
        }
        // end if == \n
        if(order_str[i] == '\n')
        {
            i=MAX_ORDER; // then i++ to end
        }
    }
    //[end]
    free(order_str);
    return 0; // anything ok
}