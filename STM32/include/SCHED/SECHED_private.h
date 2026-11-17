#ifndef OS_PRIVATE
#define OS_PRIVATE


#include "../../lib/STD_TYPES.h"


typedef struct
{
	PTF TASK_PTR;
	u16 TASK_CyclicTime;
    u8  TASK_FirstDalay;

}TASK;

#endif /* OS_PRIVATE */
