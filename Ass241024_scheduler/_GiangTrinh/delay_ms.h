#ifndef _DELAY_MILLIS_
#define _DELAY_MILLIS_
/********************************************************************************
* Definitions
********************************************************************************/
#include <stdint.h>

/********************************************************************************
* API
********************************************************************************/
void delay_millis(int x_milis);
void get_current_millis(uint32_t* millis_ptr);

#endif // _DELAY_MILLIS_
