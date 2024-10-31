/********************************************************************************
* Definitions
********************************************************************************/
#include "delay_ms.h"

#ifdef _WIN32
    #include <windows.h>

    #define DELAY_MILLIS(x) Sleep(x)  // Windows using Sleep(millis_sec)
    #define GET_CURRENT_MILLIS(millis_ptr) \
    {\
        *millis_ptr = GetTickCount();\
    }

#elif defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
    #include <unistd.h>
    #include <time.h>

    #define DELAY_MILLIS(x) usleep((x) * 1000)  // POSIX using usleep(micro_sec*1000)
    #define GET_CURRENT_MILLIS(millis_ptr) \
    { \
        struct timespec ts; \
         /* go to definition in time.h*/\
        clock_gettime(CLOCK_MONOTONIC, &ts); \
        *millis_ptr = (ts.tv_sec * 1000.0) + (ts.tv_nsec / 1e6); \
    }

#else
    #error "Only support 'sleep/delay millisecond' for Window and POSIX"

#endif

/********************************************************************************
* Code
********************************************************************************/
void delay_millis(int x_milis)
{
    DELAY_MILLIS(x_milis);
}

void get_current_millis(uint32_t* millis_ptr)
{
    GET_CURRENT_MILLIS(millis_ptr);
}