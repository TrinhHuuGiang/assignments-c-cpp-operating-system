#ifndef _PROC_HANDLE_
#define _PROC_HANDLE_
/********************************************************************************
* Definitions
********************************************************************************/
#ifdef _WIN32
    #include <windows.h> 
    typedef PROCESS_INFORMATION CHILD_PID; // PID on Windows


#elif defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
    #include <sys/types.h>   //pid_t
    typedef pid_t CHILD_PID; // PID on POSIX

#else
    #error "Only support 'initialize process' for Window and POSIX"

#endif

/********************************************************************************
* API
********************************************************************************/
int init_proc(CHILD_PID* pid_ptr,const char* argv0, const char* shm_name);

void wait_proc(CHILD_PID pid);

#endif // _PROC_HANDLE_
