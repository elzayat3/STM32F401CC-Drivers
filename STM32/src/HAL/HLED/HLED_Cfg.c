

#include "../../../Include/MCAL/GPIO/GPIO_Int.h"

#include "../../../Include/HAL/HLED/HLED_Int.h"

#include "../../../Include/HAL/HLED/HLED_Cfg.h"





const HLED_Cfg_t HLED_CFG[HLED_TOTAL_LEDS] =
{
    [LED0] = {
        .port    = PORTA,
        .pin     = PIN0,
        .speed   = Low_Speed,
        .outtype = Push_Pull,
        .active  = PIN_High
    },

    [LED1] = {
        .port    = PORTA,
        .pin     = PIN1,
        .speed   = Low_Speed,
        .outtype = Push_Pull,
        .active  = PIN_High
    }
};