#ifndef STK_INT
#define STK_INT


#include "../../../lib/STD_TYPES.h"

#include "STK_Private.h"

error_t STK_Init(void);

void STK_Start(void);

void STK_Stop(void);

error_t STK_SetCallback(PTF Copy_pfnCallback);

error_t STK_NotifyONnMS(u32 Copy_u32TimeMs);




#endif /* STK_INT */
