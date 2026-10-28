#ifndef RCC_INT
#define RCC_INT



#include "../include/STD_TYPES.h"


typedef enum 
{
    HSI,
    HSE,
    PLL
   
}Clock_t;


typedef enum
{
    OFF,
    ON
}Clock_state_t;

typedef enum
{
    HSI_PLL,
    HSE_PLL
}PLL_CFG_t;

typedef enum
{
    PLLP2,
    PLLP4,
    PLLP6,
    PLLP8
    
}PLLP_t;


typedef struct 
{
    PLL_CFG_t source;
    PLLP_t p;
    u16 Q;
    u16 N;
    u8 M;
}PLL_CFG;

typedef enum 
{
    AHB=3,
    AHB2,
    AHB4,
    AHB8,
    AHB16
    
}APB_Prescaler_t;


typedef enum 
{
    SYS=7,
    SYS2,
    SYS4,
    SYS8,
    SYS16,
    SYS64,
    SYS128,
    SYS256,
    SYS512
}AHB_Prescaler_t;


typedef enum 
{
    RCC_GPIOA=0,
    RCC_GPIOB,
    RCC_GPIOC,
    RCC_GPIOD,
    RCC_GPIOE,
    RCC_GPIOH=7,
    RCC_CRC=12,
    RCC_DMA1=21,
    RCC_DMA2=22
}AHB1_t;

typedef enum
{
    RCC_OTGFS=7
}AHB2_t;


typedef enum
{
    RCC_TIM2=0,
    RCC_TIM3=1,
    RCC_TIM4=2,
    RCC_TIM5=3,
    RCC_WWDG=11,
    RCC_SPI2=14,
    RCC_SPI3=15,
    RCC_USART2=17,
    RCC_I2C1=21,
    RCC_I2C2=22,
    RCC_I2C3=23,
    RCC_PWR=28
}APB1_t;


typedef enum
{
    RCC_TIM1=0,
    RCC_USART1=4,
    RCC_USART6=5,
    RCC_ADC1=8,
    RCC_SDIO=11,
    RCC_SPI1=12,
    RCC_SPI4=13,
    RCC_SYSCFG=14,
    RCC_TIM9=16,
    RCC_TIM10=17,
    RCC_TIM11=18
}APB2_t;




error_t RCC_SelectSysCLK(Clock_t clock);

error_t RCC_Clockcontrol(Clock_t clock,Clock_state_t state);

error_t RCC_PLL_CFG(PLL_CFG*CFG_PLL);

error_t RCC_APB2_Prescaler(APB_Prescaler_t prescaler);

error_t RCC_APB1_Prescaler(APB_Prescaler_t prescaler);

error_t RCC_AHB_Prescaler(AHB_Prescaler_t prescaler);

error_t RCC_AHB1_Control(AHB1_t peripheral ,Clock_state_t state);

error_t RCC_AHB2_Control(AHB2_t peripheral ,Clock_state_t state);

error_t RCC_APB1_Control(APB1_t peripheral ,Clock_state_t state);

error_t RCC_APB2_Control(APB2_t peripheral ,Clock_state_t state);

u32 RCC_GetsystenClk_Freq(void);

Clock_t RCC_GetsystenClk(void);



#endif /* RCC_INT */
