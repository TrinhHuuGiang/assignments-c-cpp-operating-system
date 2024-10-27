#ifndef DELAY_H
#define DELAY_H
/********************************************************************************
* Definitions
********************************************************************************/
#ifdef _WIN32
    #include <windows.h>
    #define DELAY_MILLIS(x) Sleep(x)  // Windows using Sleep(millis_sec)

#elif defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
    #include <unistd.h>
    #define DELAY_MILLIS(x) usleep((x) * 1000)  // POSIX using usleep(micro_sec*1000)

#else
    #error "Hệ điều hành không được hỗ trợ! Chỉ hỗ trợ Windows và các hệ POSIX (Linux, macOS, ...)."

#endif

#endif // DELAY_H
