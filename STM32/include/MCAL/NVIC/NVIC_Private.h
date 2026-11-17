

#ifndef MNVIC_PRIVATE_H_
#define MNVIC_PRIVATE_H_

#include "../../../lib/STD_TYPES.h"

#define NVIC_BASE_ADRESS (0xE000E100)

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
	u8 IPR[240];
	u32 Reseved5[644];
	u32 STIR;
}NVIC_t;




#define NVIC ((volatile NVIC_t*)NVIC_BASE_ADRESS)

#define NVIC_DIV  32



#define SCB_AIRCR  (*(volatile u32*)(0xE000ED0C))


#endif /* MNVIC_PRIVATE_H_ */
