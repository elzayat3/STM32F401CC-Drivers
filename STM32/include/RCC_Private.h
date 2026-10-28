#ifndef RCC_PRIVATE
#define RCC_PRIVATE

#include "../include/STD_TYPES.h"

#define RCC_BASE_ADRESS (0x40023800)

typedef struct
{
 u32 CR;
 u32 PLLCFGR;
 u32 CFGR;
 u32 CIR;
 u32 AHB1RSTR;
 u32 AHB2RSTR;
 u32 Reserved1[2];
 u32 APB1RSTR;
 u32 APB2RSTR;
 u32 Reserved2[2]; 
 u32 AHB1ENR;
 u32 AHB2ENR;
 u32 Reserved3[2];
 u32 APB1ENR;
 u32 APB2ENR;
 u32 Reserved4[2];
 u32 AHB1LPENR;
 u32 AHB2LPENR;
 u32 Reserved5[2];
 u32 APB1LPENR;
 u32 APB2LPENR;
 u32 Reserved6[2];
 u32 BDCR;
 u32 CSR;
 u32 Reserved7[2];
 u32 SSCGR;
 u32 PLLI2SCFGR;
 u32 Reserved8;
 u32 DCKCFGR;
}RCC_t;

#define RCC    ((volatile RCC_t*)RCC_BASE_ADRESS)


#define   RCC_TIMEOUT    10000

#define   TWOBITS        0x03

#define   SWBIT          0

#define   SWSBIT         2

#define   SW0            0

#define   SW1            1


#define   HSI_BIT        0

#define   HSI_READY_BIT  1

#define   HSE_BIT        16

#define   HSE_READY_BIT  17

#define   PLL_BIT        24

#define   PLL_READY_BIT  25

#define   PLL_SOURCE_BIT 22

#define   HSI_FREQ         16000000UL

#define   HSE_FREQ         25000000UL

#define   M_max            2000000UL

#define   M_min            1000000UL

#define M_config           1

#define N_config_max       432

#define N_config_min       192

#define N_max            432000000UL

#define N_min            192000000UL

#define M_MASK           0X3F

#define N_MASK           0X1FF    

#define N_BIT            6

#define MAX_CLK          84000000

#define P_BIT            16

#define Q_MASK           0Xf

#define Q_BIT            24


#define Q_config_max     15

#define Q_config_min     2

#define Q_MAX            48000000



#define DIV2              2
#define DIV4              4
#define DIV6              6
#define DIV8              8
#define DIV16             16
#define DIV64             64
#define DIV128            128
#define DIV256            256
#define DIV512            512


#define APB2_PRE_BIT      13

#define APB1_PRE_BIT      10

#define APB_PRE_MASK      0x7

#define AHB_PRE_BIT       4

#define AHB_PRE_MASK      0xF

#define APB1_MAX_FREQ    42000000


#define AHB1_CHECK       0x0060109F

#define AHB2_CHECK       0x00000080

#define APB1_CHECK       0x10E2C80F

#define APB2_CHECK       0x00077931









#endif /* RCC_PRIVATE_H */
