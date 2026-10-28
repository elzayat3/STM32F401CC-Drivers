#ifndef GPIO_INT
#define GPIO_INT


#include "../include/STD_TYPES.h" 

typedef enum 
{
    PORTA,
    PORTB,
    PORTC,
    PORTD,
    PORTE,
    PORTH,
    TOTAL_PORTS

}port_t;

typedef enum
{
	PIN0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15,
	TOTAL_PINS
}pin_t;

typedef enum
{
	INPUT,
	OUTPUT,
	Alternative_Func,
	Analog
}mode_t;

typedef enum
{
	Push_Pull,
	Open_Drain
}out_type_t;

typedef enum
{
	Low_Speed,
	Med_Speed,
	High_Speed,
	VHIGH_Speed
}speed_t;

typedef enum
{
	PIN_Low=0,
	PIN_High
}value_t;

typedef enum
{
	NOPULL,
	PULLUP,
	PULLDOWN
}pull_t;

typedef enum
{
	AF0,
	AF1,
	AF2,
	AF3,
	AF4,
	AF5,
	AF6,
	AF7,
	AF8,
	AF9,
	AF10,
	AF11,
	AF12,
	AF13,
	AF14,
	AF15
}alt_fun_t;


typedef struct
{
	port_t port;
	pin_t pin;
	mode_t mode;
	speed_t speed;
	pull_t pull;
	alt_fun_t alt;
	out_type_t out;
	
}Pin_cfg_t;

error_t GPIO_enuPinInit(const Pin_cfg_t*ref_strCfg);

error_t GPIO_enumWritePin(port_t Cpy_enuPort,pin_t Cpy_enuPin,value_t Cpy_enuValue);

error_t GPIO_enumReadPin(port_t Cpy_enuPort,pin_t Cpy_enuPin,value_t*ref_enuValue);

error_t GPIO_enumWritePort(port_t Cpy_enuPort,u16 Cpy_u16value);

error_t GPIO_enumReadPort(port_t Cpy_enuPort,u16*ref_u16value);


error_t GPIO_enuCfgSpeed(port_t Cpy_enuPort,pin_t Cpy_enuPin,speed_t Cpy_enuSpeed);

error_t GPIO_enuCfgPull(port_t Cpy_enuPort,pin_t Cpy_enuPin,pull_t Cpy_enuPull);

error_t GPIO_enuCfgMode(port_t Cpy_enuPort,pin_t Cpy_enuPin,mode_t Cpy_enuMode);

error_t GPIO_enuCfgOuTtYPE(port_t Cpy_enuPort,pin_t Cpy_enuPin,out_type_t Cpy_enuOuttype);

error_t GPIO_enuCfgAltFun(port_t Cpy_enuPort,pin_t Cpy_enuPin,alt_fun_t Cpy_enuAltFun);




#endif /* GPIO_INT */
