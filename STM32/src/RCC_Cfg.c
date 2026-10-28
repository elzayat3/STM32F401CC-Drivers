

#include "../include/RCC_Int.h"

/*PLL=((Source/M)*N)/P */

/*M from 1MHz to 2MHz */

/*N from 192MHz to 432MHz */

/*P max 84 MHz*/

const PLL_CFG PLL_config={
    .source=HSI_PLL,
    .M=16,     /*Range 2 to 63*/
    .N=336,    /*Range from 192 to 432*/
    .p=PLLP4,  /* PLLP2 ,PLLP4, PLLP6, PLLP8*/
    .Q=7       /*Range from 2 to 15*/
};