#ifndef _DELAY_MILLIS_
#define _DELAY_MILLIS_
/********************************************************************************
* Definitions
********************************************************************************/
#ifdef _WIN32
    #include <windows.h>

    #define DELAY_MILLIS(x) Sleep(x)  // Windows using Sleep(millis_sec)
    #define GET_CURRENT_MILLIS GetTickCount()

#elif defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
    #include <unistd.h>
    #include <time.h>

    #define DELAY_MILLIS(x) usleep((x) * 1000)  // POSIX using usleep(micro_sec*1000)
    #define GET_CURRENT_MILLIS { \
        struct timespec ts; \
        clock_gettime(CLOCK_MONOTONIC, &ts); \
        return (ts.tv_sec * 1000.0) + (ts.tv_nsec / 1e6); \
    }

#else
    #error "Only support 'sleep/delay millisecond' for Window and POSIX"

#endif

#endif // _DELAY_MILLIS_
