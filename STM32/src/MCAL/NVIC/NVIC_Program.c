#include "../../../lib/STD_TYPES.h"
#include "../../../include/MCAL/NVIC/NVIC_Int.h"
#include "../../../include/MCAL/NVIC/NVIC_Private.h"


static error_t NVIC_ValidateIRQ(NVIC_IRQ_t IRQn)
{
    error_t status=OUT_OF_RANGE;

    switch(IRQn)
    {
        case IRQ_0:
        case IRQ_1:
        case IRQ_2:
        case IRQ_3:
        case IRQ_4:
        case IRQ_5:
        case IRQ_6:
        case IRQ_7:
        case IRQ_8:
        case IRQ_9:
        case IRQ_10:
        case IRQ_11:
        case IRQ_12:
        case IRQ_13:
        case IRQ_14:
        case IRQ_15:
        case IRQ_16:
        case IRQ_17:
        case IRQ_18:
        case IRQ_23:
        case IRQ_24:
        case IRQ_25:
        case IRQ_26:
        case IRQ_27:
        case IRQ_28:
        case IRQ_29:
        case IRQ_30:
        case IRQ_31:
        case IRQ_32:
        case IRQ_33:
        case IRQ_34:
        case IRQ_35:
        case IRQ_36:
        case IRQ_37:
        case IRQ_38:
        case IRQ_40:
        case IRQ_41:
        case IRQ_42:
        case IRQ_47:
        case IRQ_49:
        case IRQ_50:
        case IRQ_51:
        case IRQ_56:
        case IRQ_57:
        case IRQ_58:
        case IRQ_59:
        case IRQ_60:
        case IRQ_67:
        case IRQ_68:
        case IRQ_69:
        case IRQ_70:
        case IRQ_71:
        case IRQ_72:
        case IRQ_73:
        case IRQ_81:
        case IRQ_84:
            status = OK;
            break;

        default:
            status=OUT_OF_RANGE;
            break;
    }

    return status;
}

static void NVIC_GetPriorityBits(u32 *GroupBits, u32 *SubBits)
{
    u32 priorityGroup=(SCB_AIRCR >> SCB_AIRCR_PRIGROUP_BIT)&0x7UL;

    *GroupBits=7UL-priorityGroup;

    if(*GroupBits>NVIC_PRIORITY_BITS)
    {
        *GroupBits=NVIC_PRIORITY_BITS;
    }

    *SubBits=NVIC_PRIORITY_BITS-*GroupBits;
}

error_t NVIC_EnableIRQ(NVIC_IRQ_t IRQn)
{
    error_t status=NVIC_ValidateIRQ(IRQn);

    if(status==OK)
    {
        u32 reg=(u32)IRQn/NVIC_DIV;
        u32 bit=(u32)IRQn%NVIC_DIV;

        NVIC->ISER[reg]=(1UL<<bit);
    }
    return status;
}

error_t NVIC_DisableIRQ(NVIC_IRQ_t IRQn)
{
    error_t status=NVIC_ValidateIRQ(IRQn);

    if(status==OK)
    {
        u32 reg=(u32)IRQn/NVIC_DIV;
        u32 bit=(u32)IRQn%NVIC_DIV;

        NVIC->ICER[reg]=(1UL<<bit);
    }

    return status;
}

error_t NVIC_SetPendingIRQ(NVIC_IRQ_t IRQn)
{
    error_t status=NVIC_ValidateIRQ(IRQn);

    if(status==OK)
    {
        u32 reg=(u32)IRQn/NVIC_DIV;
        u32 bit=(u32)IRQn%NVIC_DIV;

        NVIC->ISPR[reg]=(1UL<<bit);
    }

    return status;
}

error_t NVIC_ClearPendingIRQ(NVIC_IRQ_t IRQn)
{
    error_t status=NVIC_ValidateIRQ(IRQn);

    if(status==OK)
    {
        u32 reg=(u32)IRQn/NVIC_DIV;
        u32 bit=(u32)IRQn%NVIC_DIV;

        NVIC->ICPR[reg]=(1UL<<bit);
    }

    return status;
}

error_t NVIC_GetPendingIRQ(NVIC_IRQ_t IRQn, u8 *value)
{
    error_t status=OK;

    if(value==NULL)
    {
        status=NULL_PTR;
    }
    else
    {
        status=NVIC_ValidateIRQ(IRQn);
    }

    if(status==OK)
    {
        u32 reg=(u32)IRQn/NVIC_DIV;
        u32 bit=(u32)IRQn%NVIC_DIV;

        *value=(u8)((NVIC->ISPR[reg]>>bit)&1UL);
    }

    return status;
}

error_t NVIC_SetPriority(NVIC_IRQ_t IRQn,u8 GroupPriority,u8 SubPriority)
{
    error_t status=NVIC_ValidateIRQ(IRQn);

    u32 GroupBits=0;
    u32 SubBits=0;

    u32 MaxGroup=0;
    u32 MaxSub=0;

    u32 priority=0;

    if(status==OK)
    {
        NVIC_GetPriorityBits(&GroupBits, &SubBits);

        MaxGroup=(1UL<<GroupBits)-1UL;

        MaxSub=(1UL<<SubBits)-1UL;

        if((GroupPriority>MaxGroup) ||(SubPriority>MaxSub))
        {
            status=OUT_OF_RANGE;
        }
        else
        {
            priority=((u32)GroupPriority<<SubBits)|SubPriority;

            NVIC->IPR[(u32)IRQn]=(u8)(priority<<NVIC_PRIORITY_SHIFT);
        }
    }

    return status;
}

error_t NVIC_GetPriority(NVIC_IRQ_t IRQn,u8*GroupPriority,u8*SubPriority)
{
    error_t status=OK;

    u32 GroupBits=0;
    u32 SubBits=0;
    u32 priority=0;
    u32 SubMask=0;

    if((GroupPriority==NULL) || (SubPriority==NULL))
    {
        status=NULL_PTR;
    }
    else
    {
        status=NVIC_ValidateIRQ(IRQn);

        if(status==OK)
        {
            NVIC_GetPriorityBits(&GroupBits, &SubBits);

            priority=(NVIC->IPR[(u32)IRQn]>>NVIC_PRIORITY_SHIFT)&0x0FUL;

            SubMask=(1UL<<SubBits)-1UL;

            *SubPriority=(u8)(priority&SubMask);

            *GroupPriority=(u8)(priority>>SubBits);
        }
    }

    return status;
}

error_t NVIC_SetPriorityGrouping(NVIC_Group_t group)
{
    error_t status=OK;

    if((group<Group16Sub0) || (group>Group0Sub16))
    {
        status=OUT_OF_RANGE;
    }
    else
    {
        u32 aircr=SCB_AIRCR;

        aircr &= ~((0xFFFFUL << 16U) | SCB_AIRCR_PRIGROUP_MASK);
        aircr |= SCB_AIRCR_VECTKEY;
        aircr |= ((u32)group << SCB_AIRCR_PRIGROUP_BIT);

        SCB_AIRCR = aircr;
    }

    return status;
}

error_t NVIC_TriggerSoftwareIRQ(NVIC_IRQ_t IRQn)
{
    error_t status=NVIC_ValidateIRQ(IRQn);

    if(status==OK)
    {
        NVIC->STIR=((u32)IRQn&NVIC_STIR_INTID_MASK);
    }

    return status;
}
