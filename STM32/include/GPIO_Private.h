#ifndef GPIO_PRIVATE
#define GPIO_PRIVATE

#include "../include/STD_TYPES.h"

#define GPIOA_BASE_ADDRESS (0x40020000)
#define GPIOB_BASE_ADDRESS (0x40020400)
#define GPIOC_BASE_ADDRESS (0x40020800)
#define GPIOD_BASE_ADDRESS (0x40020C00)
#define GPIOE_BASE_ADDRESS (0x40021000)
#define GPIOH_BASE_ADDRESS (0x40021C00)


typedef struct
{
u32 MODER;
u32 OTYPER;
u32 OSPEEDER;
u32 PUPDR;
u32 IDR;
u32 ODR;
u32 BSRR;
u32 LCKR;
u32 AFR[2];
}GPIO_t;

#define GPIOA  ((volatile GPIO_t*)GPIOA_BASE_ADDRESS)
#define GPIOB  ((volatile GPIO_t*)GPIOB_BASE_ADDRESS)
#define GPIOC  ((volatile GPIO_t*)GPIOC_BASE_ADDRESS)
#define GPIOD  ((volatile GPIO_t*)GPIOD_BASE_ADDRESS)
#define GPIOE  ((volatile GPIO_t*)GPIOE_BASE_ADDRESS)
#define GPIOH  ((volatile GPIO_t*)GPIOH_BASE_ADDRESS)


#define  BSRR_SHIFT          16UL  


#define  SPEED_MASK          0x3UL

#define  SPEED_PIN_SHIFT      2UL

#define  PULL_MASK          0x3UL

#define  PULL_PIN_SHIFT      2UL


#define  MODE_MASK          0x3UL

#define  MODE_PIN_SHIFT      2UL

#define  OUT_TYPE_MASK       1UL

#define  BSRR_WRITE            1UL


#define  AFR_DIV               8UL

#define  AF_MASK               0xFUL

#define  AF_PIN_SHIFT           4UL


#endif /* GPIO_PRIVATE */
