
#include "../../../lib/STD_TYPES.h"

#include "../../../include/HAL/HLED/HLED_Int.h"

#include "../../../include/MCAL/GPIO/GPIO_Int.h"

#include "../../../include/MCAL/RCC/RCC_Int.h"


extern const HLED_Cfg_t HLED_CFG[HLED_TOTAL_LEDS];




static const AHB1_t HLED_enuPortClock[TOTAL_PORTS] =
{
    [PORTA] = RCC_GPIOA,
    [PORTB] = RCC_GPIOB,
    [PORTC] = RCC_GPIOC,
    [PORTD] = RCC_GPIOD,
    [PORTE] = RCC_GPIOE,
    [PORTH] = RCC_GPIOH
};



error_t HLED_enuInit(void)
{
    error_t Loc_enuStatus=OK;

    u8 Loc_u8ClockEnabled[TOTAL_PORTS]={0};
    u8 Loc_u8Led;

    Pin_cfg_t Loc_strPinCfg;

    for (Loc_u8Led=LED0;(Loc_u8Led<HLED_TOTAL_LEDS) && (Loc_enuStatus==OK);Loc_u8Led++)
    {
        const HLED_Cfg_t *Loc_pstrCfg=&HLED_CFG[Loc_u8Led];

        if ((Loc_pstrCfg->port<PORTA) || (Loc_pstrCfg->port>=TOTAL_PORTS))
        {
            Loc_enuStatus=OUT_OF_RANGE;
        }

        if (Loc_enuStatus==OK)
        {
            if (Loc_u8ClockEnabled[Loc_pstrCfg->port]==0U)
            {
                Loc_enuStatus=RCC_AHB1_Control(HLED_enuPortClock[Loc_pstrCfg->port],ON);

                if (Loc_enuStatus==OK)
                {
                    Loc_u8ClockEnabled[Loc_pstrCfg->port]=1U;
                }
            }
        }

        if (Loc_enuStatus==OK)
        {
            Loc_strPinCfg.port  =Loc_pstrCfg->port;
            Loc_strPinCfg.pin   =Loc_pstrCfg->pin;
            Loc_strPinCfg.mode  =OUTPUT;
            Loc_strPinCfg.speed =Loc_pstrCfg->speed;
            Loc_strPinCfg.pull  =NOPULL;
            Loc_strPinCfg.alt   =AF0;
            Loc_strPinCfg.out   =Loc_pstrCfg->outtype;

            Loc_enuStatus=GPIO_enumWritePin(Loc_pstrCfg->port,Loc_pstrCfg->pin,(Loc_pstrCfg->active == PIN_High) ? PIN_Low : PIN_High);
        }
        if (Loc_enuStatus==OK)
        {
            Loc_enuStatus=GPIO_enuPinInit(&Loc_strPinCfg);
        }
    }

    return Loc_enuStatus;
}



error_t HLED_enuTurnOn(Led_t Cpy_enuLed)
{
    error_t Loc_enuStatus=OK;

    if ((Cpy_enuLed<LED0) || Cpy_enuLed>=HLED_TOTAL_LEDS)
    {
        Loc_enuStatus=OUT_OF_RANGE;
    }
    else
    {
        Loc_enuStatus=GPIO_enumWritePin(HLED_CFG[Cpy_enuLed].port,HLED_CFG[Cpy_enuLed].pin,HLED_CFG[Cpy_enuLed].active);
    }

    return Loc_enuStatus;
}



error_t HLED_enuTurnOff(Led_t Cpy_enuLed)
{
    error_t Loc_enuStatus=OK;

    if ((Cpy_enuLed<LED0) || Cpy_enuLed>=HLED_TOTAL_LEDS)
    {
        Loc_enuStatus=OUT_OF_RANGE;
    }
    else
    {
        Loc_enuStatus=GPIO_enumWritePin(HLED_CFG[Cpy_enuLed].port,HLED_CFG[Cpy_enuLed].pin,(value_t)(HLED_CFG[Cpy_enuLed].active^1U));
    }

    return Loc_enuStatus;
}


error_t HLED_enuToggle(Led_t Cpy_enuLed)
{
    error_t Loc_enuStatus=OK;

    if ((Cpy_enuLed<LED0) || (Cpy_enuLed>=HLED_TOTAL_LEDS))
    {
        Loc_enuStatus=OUT_OF_RANGE;
    }
    else
    {
        Loc_enuStatus = GPIO_enumTogglePin( HLED_CFG[Cpy_enuLed].port,HLED_CFG[Cpy_enuLed].pin);
    }

    return Loc_enuStatus;
}
