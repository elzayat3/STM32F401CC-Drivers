#ifndef SCHED_INT
#define SCHED_INT

#include "../../lib/STD_TYPES.h"

typedef struct
{
	PTF TASK_PTR;
	u16 TASK_CyclicTime;
    u8  TASK_FirstDalay;

}TASK;
typedef enum
{
    triggered,
    nottriggered
}trigger_t;


error_t  SCHED_Init(void);

void SCHED_Stop(void);

void SCHED_Start(void);

void SCHED_Handler(void);




#endif /* SCHED_INT */
