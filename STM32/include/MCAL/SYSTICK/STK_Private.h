#ifndef STK_PRIVATE
#define STK_PRIVATE

#include "../../../lib/STD_TYPES.h"

#define MSTK_BASE_ADRESS (0xE000E010)

typedef struct
{
	u32 CTRL;
	u32 LOAD;
	u32 VAL;
	u32 CALIB;
}MSTK_t;

#define STK ((volatile MSTK_t*)MSTK_BASE_ADRESS)


typedef enum
{
	STK_AHB8=0,
	STK_AHB
}stk_pre_t;


#define STK_ENABLE_BIT       0


#define STK_PRE_BIT          2

#define MAX_TICKS            0X00FFFFFF

#define STK_COUNTFLAG        16

#define STK_TICKINT_BIT      1


#endif /* STK_PRIVATE */
