
#include "../../../lib/STD_TYPES.h"

#include "../../../include/MCAL/NVIC/NVIC_Int.h"

#include "../../../include/MCAL/NVIC/NVIC_Private.h"




error_t NVIC_EnableIRQ(NVIC_IRQ_t IRQn)
{
    error_t status=OK;

    u32 reg=IRQn/NVIC_DIV;

    u32 bit=IRQn%NVIC_DIV;

    if(IRQn < IRQ_TOTAL && IRQn >= IRQ_0)
    {
        status=OUT_OF_RANGE;
    }
    else
    {
        SET_BIT(NVIC->ISER[reg], bit);
    }

    return status;
}

error_t  NVIC_DisableIRQ(NVIC_IRQ_t IRQn)
{
    error_t status=OK;

    u32 reg=IRQn/NVIC_DIV;

    u32 bit=IRQn%NVIC_DIV;

    if(IRQn < IRQ_TOTAL && IRQn >= IRQ_0)
    {
        status=OUT_OF_RANGE;
    }
    else
    {
        SET_BIT(NVIC->ICER[reg], bit);
    }

    return status;
}

error_t NVIC_SetPendingIRQ(NVIC_IRQ_t IRQn)
{
    error_t status=OK;

    u32 reg=IRQn/NVIC_DIV;

    u32 bit=IRQn%NVIC_DIV;

    if(IRQn < IRQ_TOTAL && IRQn >= IRQ_0)
    {
        status=OUT_OF_RANGE;
    }
    else
    {
        SET_BIT(NVIC->ISPR[reg], bit);
    }

    return status;
}

error_t NVIC_ClearPendingIRQ(NVIC_IRQ_t IRQn)
{
    error_t status=OK;

    u32 reg=IRQn/NVIC_DIV;

    u32 bit=IRQn%NVIC_DIV;

    if(IRQn < IRQ_TOTAL && IRQn >= IRQ_0)
    {
        status=OUT_OF_RANGE;
    }
    else
    {
        SET_BIT(NVIC->ICPR[reg], bit);
    }

    return status;
}

error_t NVIC_GetPendingIRQ(NVIC_IRQ_t IRQerror_t,u8*value)
{
    error_t status=OK;

    u32 reg=IRQerror_t / NVIC_DIV;

    u32 bit=IRQerror_t % NVIC_DIV;

    if(IRQerror_t < IRQ_TOTAL && IRQerror_t >= IRQ_0)
    {
        status=OUT_OF_RANGE;
    }
    else
    {
        *(value)=GET_BIT(NVIC->ICPR[reg], bit);
    }

    return status;

}









