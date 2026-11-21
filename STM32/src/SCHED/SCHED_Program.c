#include "../../lib/STD_TYPES.h"

#include "../../include/MCAL/SYSTICK/STK_Int.h"

#include "../../include/SCHED/SCHED_int.h"

#include "../../include/SCHED/SECHED_private.h"

static trigger_t istrigger=nottriggered;

static u8 current_index =0;

static TASK*SCHED_Runnable[TOTAL_TASK]={0};

error_t  SCHED_Init(void)
{
    error_t status=OK;

    status=STK_Init();

    status=STK_SetCallback(SCHED_Handler);

    status=STK_NotifyONnMS(1);

    return status;
}

void SCHED_Stop(void)
{
    STK_Stop();
}

error_t SCHED_registerRunnable(TASK *task)
{
    error_t status=OK;

    if(task==NULL)
    {
        status=NULL_PTR;
    }
    else if(current_index>=TOTAL_TASK)
    {
        status=OUT_OF_RANGE;
    }
    else
    {
        SCHED_Runnable[current_index]=task;
        current_index++;
    }

    return status;
}


void SCHED_Start(void)
{
    STK_Start();

    while(1)
    {
        if(istrigger==triggered)
        {
            istrigger=nottriggered;

            for(int i=0;i<current_index;i++)
            {
                if(SCHED_Runnable[i]!=NULL)
                {
                    if(SCHED_Runnable[i]->TASK_FirstDalay==0)
                    {

                        SCHED_Runnable[i]->TASK_PTR();
                        SCHED_Runnable[i]->TASK_FirstDalay=SCHED_Runnable[i]->TASK_CyclicTime;
                    }
                    else
                    {
                        SCHED_Runnable[i]->TASK_FirstDalay--;
                        
                    }
                    
                }

            }


        }

    }
}


void SCHED_Handler(void)
{
    istrigger=triggered;
}

