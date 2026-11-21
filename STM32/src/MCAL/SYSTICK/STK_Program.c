

#include "../../../lib/STD_TYPES.h"

#include "../../../include/MCAL/SYSTICK/STK_Int.h"

#include "../../../include/MCAL/SYSTICK/STK_Private.h"

#include "../../../include/MCAL/RCC/RCC_Int.h"


static PTF STK_Callback=NULL;

static volatile u32 STK_u32ElapsedMs=0;

static volatile u32 STK_u32NotifyPeriodMs=0;


error_t STK_Init(void)
{
    error_t status=OK;

    u32 AHB_Freq=RCC_GetAHBClk_Freq();

    u32 ticks=AHB_Freq/1000UL;

    if(ticks==0 || ticks>(MAX_TICKS+1UL))
    {
        status = OUT_OF_RANGE;
    }
    else
    {
        /* Disable SysTick */
        CLR_BIT(STK->CTRL, STK_ENABLE_BIT);

        /* Configure 1ms reload */
        STK->LOAD=ticks-1UL;

        /* Clear current counter */
        STK->VAL=0;

        /* Select AHB clock */
        SET_BIT(STK->CTRL,STK_PRE_BIT);

        /* Enable interrupt */
        SET_BIT(STK->CTRL,STK_TICKINT_BIT);
    }

    return status;
}


void STK_Start(void)
{
    /* Reset Counter */
    STK->VAL = 0;

    /* Start Counting */
    SET_BIT(STK->CTRL, STK_ENABLE_BIT);
}


void STK_Stop(void)
{
    CLR_BIT(STK->CTRL, STK_ENABLE_BIT);
}

error_t STK_SetCallback(PTF Copy_pfnCallback)
{
    error_t status = OK;

    if(Copy_pfnCallback==NULL)
    {
        status=NULL_PTR;
    }
    else
    {
        STK_Callback=Copy_pfnCallback;
    }

    return status;
}

error_t STK_NotifyONnMS(u32 Copy_u32TimeMs)
{
    error_t status=OK;

    if(Copy_u32TimeMs==0UL)
    {
        status = OUT_OF_RANGE;
    }
    else
    {
        STK_u32NotifyPeriodMs=Copy_u32TimeMs;
        STK_u32ElapsedMs=0;
    }

    return status;
}

void SysTick_Handler(void)
{
    if(STK_u32NotifyPeriodMs != 0UL)
    {
        STK_u32ElapsedMs++;

        if(STK_u32ElapsedMs>=STK_u32NotifyPeriodMs)
        {
            STK_u32ElapsedMs=0;

            if (STK_Callback!=NULL)
            {
                STK_Callback();
            }
        }
    }
}

