#ifndef _MAPPING_
#define _MAPPING_
/********************************************************************************
* Definitions
********************************************************************************/

#ifdef _WIN32
    #include <windows.h>
    typedef HANDLE SHARED_ID;

#elif defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
    typedef int SHARED_ID;

#else
    #error "Only support 'shared memory' for Window and POSIX"

#endif

/********************************************************************************
* API
********************************************************************************/
int open_shm(SHARED_ID* shmid_ptr,char* name, int size);

void* get_link_shm(SHARED_ID shmid,int size);

void delete_shm(SHARED_ID shmid, char* shm_name);

#endif/* MAPPING */
