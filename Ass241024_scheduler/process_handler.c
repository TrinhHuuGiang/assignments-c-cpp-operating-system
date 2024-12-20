/********************************************************************************
* Definitions
********************************************************************************/
#include "process_handler.h"

#ifdef _WIN32
    #include <stdio.h>    //sprintf
    #include <windows.h>  // CreateProcess, WaitForSingleObject

    #define INIT_PROC(pid_ptr, argv0, shm_name)  /*parameter is a pointer* CHILD_PID */\
    {\
        STARTUPINFO si;\
        char path_param[512];\
        ZeroMemory(&si, sizeof(si));\
        /* si.cb set size of STARTUPINFO field */\
        si.cb = sizeof(si);\
        /* alert sizeof(pid_ptr) is wrong, only size of pointer */\
        ZeroMemory(pid_ptr, sizeof(PROCESS_INFORMATION));\
        \
        /* add path and parameter for child process */\
        /* default using reopen this program */\
        /* 'child' using to identify child process in main */\
        sprintf(path_param,"\"%s\" child",argv0);\
        \
        if (!CreateProcess(\
            NULL,                /* Name of execute program file */\
            path_param,          /* Path to program */\
            NULL,                /* Security attributes for process */\
            NULL,                /* Security attributes for thread */\
            FALSE,               /* Thừa kế handle không? */\
            0,                   /* Các cờ tạo tiến trình */\
            NULL,                /* Môi trường mới (NULL = thừa kế từ cha) */\
            NULL,                /* Thư mục làm việc ban đầu */\
            &si,                 /* Thông tin cấu hình cửa sổ */\
            pid_ptr              /* Nhận thông tin về tiến trình và luồng */\
        ))\
        {return -1;}  /* failed */\
        else return 0;/* create process success */\
    }
    
    #define WAIT_PROC(pid) \
    {\
        /* wait child process complete */\
        WaitForSingleObject(pid.hProcess, INFINITE);\
        \
        /* close hanle for process and thread */\
        CloseHandle(pid.hProcess);\
        CloseHandle(pid.hThread);\
    }

#elif defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
    #include <unistd.h>      //fork
    #include <sys/types.h>   //pid_t
    #include <sys/wait.h>    //wait

    #define INIT_PROC(pid_ptr, argv0, shm_name) /* return -1 if create process failed, 0 if success */\
    {\
        *pid_ptr = fork();\
        if(*pid_ptr == -1)\
        {return -1;}\
        else return 0;\
    }

    #define WAIT_PROC(pid) waitpid(pid,NULL,0)  //wait child process close

#else
    #error "Only support 'initialize process' for Window and POSIX"

#endif

/********************************************************************************
* Code
********************************************************************************/
int init_proc(CHILD_PID* pid_ptr,const char* argv0, const char* shm_name)
{
    INIT_PROC(pid_ptr, argv0, shm_name);
}

void wait_proc(CHILD_PID pid)
{
    WAIT_PROC(pid);
}