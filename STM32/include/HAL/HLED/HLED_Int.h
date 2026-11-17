#ifndef HLED_INT
#define HLED_INT

#include "../../MCAL/GPIO/GPIO_Int.h"

#include "HLED_Cfg.h"


typedef enum
{
    HLED_OFF = 0,
    HLED_ON  = 1
} HLED_State_t;

typedef struct
{
    port_t     port;
    pin_t      pin;
    speed_t    speed;
    out_type_t outtype;
    value_t    active;  
} HLED_Cfg_t;

error_t HLED_enuInit(void);

error_t HLED_enuTurnOn(Led_t Cpy_enuLed);
error_t HLED_enuTurnOff(Led_t Cpy_enuLed);
error_t HLED_enuToggle(Led_t Cpy_enuLed);


#endif /* HLED_INT */
