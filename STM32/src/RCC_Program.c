#include "../include/STD_TYPES.h"
#include "../include/RCC_Int.h"
#include "../include/RCC_Private.h"

static u32 m_freq=0;

static u32 n_freq=0;

static u32 p_freq=0;

static u32 q_freq=0;

static u32 SourceClock=0;

static u32 SystemFreq=HSI_FREQ;

static u32 AHB_Freq=HSI_FREQ;

static u32 APB1_Freq=HSI_FREQ;

static error_t RCC_PLL_SOURCE_CFG(const PLL_CFG*CFG_PLL)
{
    error_t status =OK;

    if(CFG_PLL==NULL)
    {
        status=NULL_PTR;
    }
    else
    {
        switch(CFG_PLL->source)
        {
            case HSI_PLL:
            CLR_BIT(RCC->PLLCFGR, PLL_SOURCE_BIT);
            SourceClock=HSI_FREQ;
            break;
            case HSE_PLL:
            SET_BIT(RCC->PLLCFGR, PLL_SOURCE_BIT);
            SourceClock=HSE_FREQ;
            break;
            default:
            status=OUT_OF_RANGE;
        }
    }
    return status;
}

static error_t RCC_M_CFG(PLL_CFG*CFG_PLL)
{
    error_t status=OK;
    if(CFG_PLL == NULL)
    {
        status=NULL_PTR;
    }
    else
    {
        if(CFG_PLL->M<=M_config)
        {
            status=OUT_OF_RANGE;
        }
        else
        {
            m_freq=(SourceClock/CFG_PLL->M);
            if(m_freq > M_max || m_freq < M_min)
            {
                status=OUT_OF_RANGE;
            }else{;}
        }
        if(status==OK)
        { 
            RCC->PLLCFGR &=(~(M_MASK));
            RCC->PLLCFGR |=(CFG_PLL->M);

        }else{;}  
    }
    return status;
}
static error_t RCC_N_CFG(PLL_CFG*CFG_PLL)
{
    error_t status=OK;

    if(CFG_PLL == NULL)
    {
        status=NULL_PTR;
    }
    else
    {
        if(CFG_PLL->N>N_config_max || CFG_PLL->N<N_config_min)
        {
            status=OUT_OF_RANGE;
        }
        else
        {
            n_freq=m_freq*CFG_PLL->N;
            if(n_freq>N_max || n_freq<N_min)
            {
                status=OUT_OF_RANGE;
            }
            else
            {
                RCC->PLLCFGR &=(~(N_MASK<<N_BIT));
                RCC->PLLCFGR |=(CFG_PLL->N<<N_BIT);
            }

        }  
    }
    return status;
}

static error_t RCC_P_CFG(PLL_CFG*CFG_PLL)
{
    error_t status=OK;
    if(CFG_PLL == NULL)
    {
        status=NULL_PTR;
    }
    else
    {
        switch (CFG_PLL->p) 
        {
            case PLLP2:
            p_freq=n_freq/DIV2;
            break;
            case PLLP4:
            p_freq=n_freq/DIV4;
            break;
            case PLLP6:
            p_freq=n_freq/DIV6;
            break;
            case PLLP8:
            p_freq=n_freq/DIV8;
            break;
            default:
            status=OUT_OF_RANGE;
        } 
    }
    if(status==OK)
    {
        if(p_freq>MAX_CLK)
        {
            status=OUT_OF_RANGE;
        }
        else
        {
            CLR_2BIT(RCC->PLLCFGR, P_BIT);
            RCC->PLLCFGR |=(CFG_PLL->p<<P_BIT);
        }
        
    }else{;}

    return status;
}

static error_t RCC_Q_CFG(PLL_CFG*CFG_PLL)
{
    error_t status=OK;

    if(CFG_PLL == NULL)
    {
        status=NULL_PTR;
    }
    else
    {
        if(CFG_PLL->Q>Q_config_max || CFG_PLL->Q<Q_config_min)
        {
            status=OUT_OF_RANGE;
        }
        else
        {
            q_freq=n_freq/CFG_PLL->Q;
            if(q_freq>Q_MAX)
            {
                status=OUT_OF_RANGE;
            }
            else
            {
                RCC->PLLCFGR &= (~(Q_MASK<<Q_BIT));
                RCC->PLLCFGR |= (CFG_PLL->Q<<Q_BIT);
            }
            
        }
        
    }
    return status;
}

static error_t RCC_AHB_Freq_CFG(AHB_Prescaler_t prescaler)
{
    error_t status=OK;

    switch(prescaler)
    {
        case SYS:
            AHB_Freq=SystemFreq;
            break;
        case SYS2:
            AHB_Freq=SystemFreq/DIV2;
            break;
        case SYS4:
            AHB_Freq=SystemFreq/DIV4;
            break;
        case SYS8:
            AHB_Freq=SystemFreq/DIV8;
            break;
        case SYS16:
            AHB_Freq=SystemFreq/DIV16;
            break;
        case SYS64:
            AHB_Freq=SystemFreq/DIV64;
            break;
        case SYS128:
            AHB_Freq=SystemFreq/DIV128;
            break;
        case SYS256:
            AHB_Freq=SystemFreq/DIV256;
            break;
        case SYS512:
            AHB_Freq=SystemFreq/DIV512;
            break;
        default:
            status=OUT_OF_RANGE;
            break;
    }

    return status;
}
static error_t RCC_APB1_Freq_CFG(APB_Prescaler_t prescaler)
{
    error_t status=OK;

    u32 freq=0;

    switch(prescaler)
    {
        case AHB:
            freq=AHB_Freq;
            break;
        case AHB2:
            freq=AHB_Freq/DIV2;
            break;
        case AHB4:
            freq=AHB_Freq/DIV4;
            break;
        case AHB8:
            freq=AHB_Freq/DIV8;
            break;
        case AHB16:
            freq=AHB_Freq/DIV16;
            break;
        default:
            status=OUT_OF_RANGE;
            break;
    }

    if((status==OK) && (freq>APB1_MAX_FREQ))
    {
        status=OUT_OF_RANGE;
    }
    else{;}

    if(status == OK)
    {
        APB1_Freq = freq;
    }else{;}

    return status;
}

error_t RCC_SelectSysCLK(Clock_t clock)
{
    error_t status =OK;

    u32 timeout=0;

    u32 requestedFreq=0;

    switch(clock)
    {
        case HSI:
        CLR_2BIT(RCC->CFGR,SWBIT);
        requestedFreq=HSI_FREQ;
        while(((GET_2BIT(RCC->CFGR, SWSBIT))!=HSI)&&(timeout<RCC_TIMEOUT))
        {
            timeout++;
        }
        break;
        case HSE:
        CLR_2BIT(RCC->CFGR,SWBIT);
        SET_BIT(RCC->CFGR, SW0);
        requestedFreq=HSE_FREQ;
        while(((GET_2BIT(RCC->CFGR, SWSBIT))!=HSE)&&(timeout<RCC_TIMEOUT))
        {
            timeout++;
        }
        break;
        case PLL:
        CLR_2BIT(RCC->CFGR,SWBIT);
        SET_BIT(RCC->CFGR, SW1);
        requestedFreq=p_freq;
        while(((GET_2BIT(RCC->CFGR, SWSBIT))!=PLL)&&(timeout<RCC_TIMEOUT))
        {
            timeout++;
        }
        break;
        default:
        status=OUT_OF_RANGE;
    }
    if(timeout>=RCC_TIMEOUT)
    {
        status=TIMEOUT;
    }
    else{;}

    if (status == OK)
    {
        SystemFreq = requestedFreq;
    }
    else{;}

    return status;
}

error_t RCC_Clockcontrol(Clock_t clock,Clock_state_t state)
{
    error_t status =OK;

    int timeout=0;

    switch(clock)
    {
        case HSI:
        if(state==OFF)
        {
            CLR_BIT(RCC->CR,HSI_BIT);
            while(((timeout<RCC_TIMEOUT)&&(GET_BIT(RCC->CR, HSI_READY_BIT)!=OFF)))
            {
                timeout++;
            }
        }
        else if(state==ON)
        {
            SET_BIT(RCC->CR,HSI_BIT);

            while(((timeout<RCC_TIMEOUT)&&(GET_BIT(RCC->CR, HSI_READY_BIT)!=ON)))
            {
                timeout++;
            }
        }
        else
        {
            status=OUT_OF_RANGE;
        }
        break;
        case HSE:
        if(state==OFF)
        {
            CLR_BIT(RCC->CR,HSE_BIT);
             while(((timeout<RCC_TIMEOUT)&&(GET_BIT(RCC->CR, HSE_READY_BIT)!=OFF)))
            {
                timeout++;
            }
        }
        else if(state==ON)
        {
            SET_BIT(RCC->CR,HSE_BIT);

            while(((timeout<RCC_TIMEOUT)&&(GET_BIT(RCC->CR, HSE_READY_BIT)!=ON)))
            {
                timeout++;
            }
        }
        else
        {
            status=OUT_OF_RANGE;
        }
        break;
        case PLL:
        if(state==OFF)
        {
            CLR_BIT(RCC->CR,PLL_BIT);
            while(((timeout<RCC_TIMEOUT)&&(GET_BIT(RCC->CR, PLL_READY_BIT)!=OFF)))
            {
                timeout++;
            }

        }
        else if(state==ON)
        {
            SET_BIT(RCC->CR,PLL_BIT);
            while(((timeout<RCC_TIMEOUT)&&(GET_BIT(RCC->CR, PLL_READY_BIT)!=ON)))
            {
                timeout++;
            }

        }
        else
        {
            status=OUT_OF_RANGE;
        }
        break;
        default:
        status=OUT_OF_RANGE;
    }

    if(timeout>=RCC_TIMEOUT)
    {
        status=TIMEOUT;
    }
    else{;}

    return status;

}

error_t RCC_PLL_CFG(PLL_CFG*CFG_PLL)
{
    error_t status =OK;

    if(CFG_PLL == NULL)
    {
        status=NULL_PTR;
    }
    else{;}

    if(status==OK)
    {
        if(GET_BIT(RCC->CR,PLL_BIT))
        {
            status=NOK;
        }
        else{;}
    }else{;}

    if(status==OK)
    {
        status=RCC_PLL_SOURCE_CFG(CFG_PLL);
    }else{;}
        
    if(status==OK)
    {
        status=RCC_M_CFG(CFG_PLL);
    }else{;}

    if(status==OK)
    {
        status=RCC_N_CFG(CFG_PLL);
            
    }else{;}

    if(status==OK)
    {
        status=RCC_P_CFG(CFG_PLL);
    }else{;}

    if(status==OK)
    {
        status=RCC_Q_CFG(CFG_PLL);
        
    }else{;}
    
    return status;
}

error_t RCC_APB2_Prescaler(APB_Prescaler_t prescaler)
{
    error_t status=OK;
    if(prescaler>=AHB && prescaler<=AHB16)
    {
        RCC->CFGR &= (~(APB_PRE_MASK<<APB2_PRE_BIT));
        RCC->CFGR |= (prescaler<<APB2_PRE_BIT);
    }
    else
    {
        status=OUT_OF_RANGE;
    }

    return status;

}

error_t RCC_APB1_Prescaler(APB_Prescaler_t prescaler)
{
    error_t status=OK;
    if(prescaler>=AHB && prescaler<=AHB16)
    {
        status=RCC_APB1_Freq_CFG(prescaler);
        if(status==OK)
        {
            RCC->CFGR &= (~(APB_PRE_MASK<<APB1_PRE_BIT));
            RCC->CFGR |= (prescaler<<APB1_PRE_BIT);
        }
        else{;}
    }
    else
    {
        status=OUT_OF_RANGE;
    }

    return status;
}

error_t RCC_AHB_Prescaler(AHB_Prescaler_t prescaler)
{

    error_t status=OK;
    if(prescaler>=SYS && prescaler<=SYS512)
    {
        RCC->CFGR &= (~(AHB_PRE_MASK<<AHB_PRE_BIT));
        RCC->CFGR |= (prescaler<<AHB_PRE_BIT);

        status = RCC_AHB_Freq_CFG(prescaler);
    }
    else
    {
        status=OUT_OF_RANGE;
    }
    return  status;
}


error_t RCC_AHB1_Control(AHB1_t peripheral ,Clock_state_t state)
{
    error_t status=OK;

    if((AHB1_CHECK & (1<<peripheral))!=0)
    {
        switch (state)
        {
            case ON:
            SET_BIT(RCC->AHB1ENR, peripheral);
            break;
            case OFF:
            CLR_BIT(RCC->AHB1ENR, peripheral);
            break;
            default:
            status=OUT_OF_RANGE;
            break;
        }
    }
    else
    {
       status=OUT_OF_RANGE; 
    }
    return status;
}

error_t RCC_AHB2_Control(AHB2_t peripheral ,Clock_state_t state)
{
    error_t status=OK;

    if((AHB2_CHECK & (1<<peripheral))!=0)
    {
        switch (state)
        {
            case ON:
            SET_BIT(RCC->AHB2ENR, peripheral);
            break;
            case OFF:
            CLR_BIT(RCC->AHB2ENR, peripheral);
            break;
            default:
            status=OUT_OF_RANGE;
            break;
        }
    }
    else
    {
       status=OUT_OF_RANGE; 
    }
    return status;
}

error_t RCC_APB1_Control(APB1_t peripheral ,Clock_state_t state)
{
    error_t status=OK;

    if((APB1_CHECK & (1<<peripheral))!=0)
    {
        switch (state)
        {
            case ON:
            SET_BIT(RCC->APB1ENR, peripheral);
            break;
            case OFF:
            CLR_BIT(RCC->APB1ENR, peripheral);
            break;
            default:
            status=OUT_OF_RANGE;
            break;
        }
    }
    else
    {
       status=OUT_OF_RANGE; 
    }
    return status;
}

error_t RCC_APB2_Control(APB2_t peripheral ,Clock_state_t state)
{
    error_t status=OK;

    if((APB2_CHECK & (1<<peripheral))!=0)
    {
        switch (state)
        {
            case ON:
            SET_BIT(RCC->APB2ENR, peripheral);
            break;
            case OFF:
            CLR_BIT(RCC->APB2ENR, peripheral);
            break;
            default:
            status=OUT_OF_RANGE;
            break;
        }
    }
    else
    {
       status=OUT_OF_RANGE; 
    }
    return status;
}

u32 RCC_GetsystenClk_Freq(void)
{
    return SystemFreq;
}

Clock_t RCC_GetsystenClk(void)
{
    return (Clock_t)GET_2BIT(RCC->CFGR, SWSBIT);
}




