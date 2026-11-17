#ifndef OS_INT
#define OS_INT

#include "../../lib/STD_TYPES.h"


u8 OS_u8CreateTask(PTF ptr,u16 Copy_u16Periodicity,u8 Copy_u8Priority,u8 Copy_u8FirstDelay);
void OS_Scheduler(void);
void OS_Start(u32 Copy_TickTimeus);


#endif /* OS_INT */
