/********************************************************************************
* Definitions
********************************************************************************/
#include "mapping.h"

#ifdef _WIN32
    #include <windows.h>

    // Macro để mở bộ nhớ chia sẻ
    #define OPEN_SHM(shmid_ptr ,name, size) \
        {\
            shmid_ptr = (HANDLE*)shmid_ptr;\
            *shmid_ptr = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, size, name);\
            if(*shmid_ptr == NULL)\
            {return -1;}\
            else return 0;\
        }

    // Macro để ánh xạ vùng nhớ chia sẻ
    #define LINK_TO_SHM(shmid, size) \
        MapViewOfFile(shmid, FILE_MAP_ALL_ACCESS, 0, 0, size)

    // Macro để giải phóng vùng nhớ chia sẻ
    #define CLOSE_SHM(shmid, name) \
    { \
        /*check NULL and free*/\
        if (shmid) CloseHandle(shmid); \
    }

#elif defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
    #include <fcntl.h>       //For O_* constants,  shm_open(add Realtime extensionlib)
    #include <unistd.h>      //For ftruncate()
    #include <sys/mman.h>    //For mmap, shm_unlink(add Realtime extensionlib)

    // Macro để mở bộ nhớ chia sẻ
    #define OPEN_SHM(shmid_ptr, name, size) \
    {\
        int code;\
        shmid_ptr = (int*)shmid_ptr;\
        /*0666 == 0(octal) 110(owner r/w) 110(group) 110(others)*/\
        *shmid_ptr = shm_open(name, O_CREAT | O_RDWR, 0666);\
        if(*shmid_ptr == -1) {return -1;}\
        code = ftruncate(*shmid_ptr, size);\
        if(code == -1) {return -1;}\
        return 0;/*ok*/\
    }\

    // Macro để ánh xạ vùng nhớ chia sẻ
    #define LINK_TO_SHM(shmid, size) \
        mmap(NULL,size,PROT_WRITE,MAP_SHARED,shmid,0);

    // Macro để giải phóng vùng nhớ chia sẻ
    #define CLOSE_SHM(shmid, name) \
    { \
        shm_unlink(name);\
    }

#else
    #error "Only support 'shared memory' for Window and POSIX"

#endif


/********************************************************************************
* Code
********************************************************************************/
int open_shm(SHARED_ID* shmid_ptr ,char* name, int size)
{
    OPEN_SHM(shmid_ptr,name,size);
}

void* get_link_shm(SHARED_ID shmid,int size)
{
    return LINK_TO_SHM(shmid,size);
}

void delete_shm(SHARED_ID shmid, char* shm_name)
{
    CLOSE_SHM(shmid, shm_name);
}
