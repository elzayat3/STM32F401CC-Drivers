#ifndef NVIC_PRIVATE_H_
#define NVIC_PRIVATE_H_

#include "../../../lib/STD_TYPES.h"

#define NVIC_BASE_ADDRESS       (0xE000E100UL)

typedef struct
{
    u32 ISER[8];
    u32 Reserved0[24];
    u32 ICER[8];
    u32 Reserved1[24];
    u32 ISPR[8];
    u32 Reserved2[24];
    u32 ICPR[8];
    u32 Reserved3[24];
    u32 IABR[8];
    u32 Reserved4[56];
    u8  IPR[240];
    u32 Reserved5[644];
    u32 STIR;
} NVIC_t;

#define NVIC                    ((volatile NVIC_t *)NVIC_BASE_ADDRESS)
#define NVIC_DIV                (32U)


#define NVIC_PRIORITY_BITS      (4U)
#define NVIC_PRIORITY_SHIFT     (8U - NVIC_PRIORITY_BITS)
#define NVIC_PRIORITY_MAX       ((1U << NVIC_PRIORITY_BITS) - 1U)

#define SCB_AIRCR_ADDRESS       (0xE000ED0CUL)
#define SCB_AIRCR               (*(volatile u32 *)SCB_AIRCR_ADDRESS)
#define SCB_AIRCR_VECTKEY       (0x5FAUL << 16U)
#define SCB_AIRCR_PRIGROUP_BIT  (8U)
#define SCB_AIRCR_PRIGROUP_MASK (0x7UL << SCB_AIRCR_PRIGROUP_BIT)

#define NVIC_STIR_INTID_MASK    0x1FFUL

#endif /* NVIC_PRIVATE_H_ */
