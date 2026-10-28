#include "../include/STD_TYPES.h"

#include "../include/GPIO_Int.h"
#include "../include/GPIO_Private.h"


static volatile GPIO_t*GPIO[TOTAL_PORTS]={GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOH};


static error_t GPIO_staticEnuPortRnage(port_t Cpy_enuPort)
{
    error_t Loc_enustatus=OK;

    if(Cpy_enuPort>=TOTAL_PORTS || Cpy_enuPort<PORTA)
    {
        Loc_enustatus =OUT_OF_RANGE;
    }
    return Loc_enustatus;

}
static error_t GPIO_staticEnuPinRnage(pin_t Cpy_enupin)
{
    error_t Loc_enustatus=OK;

    if(Cpy_enupin>=TOTAL_PINS || Cpy_enupin<PIN0)
    {
        Loc_enustatus =OUT_OF_RANGE;
    }
    return Loc_enustatus;

}

static error_t GPIO_staticEnuModeRnage(mode_t Cpy_enumode)
{
    error_t Loc_enustatus=OK;

    if(Cpy_enumode<INPUT || Cpy_enumode>Analog)
    {
        Loc_enustatus =OUT_OF_RANGE;
    }
    return Loc_enustatus;

}



static error_t GPIO_staticEnuSpeedRange(speed_t Cpy_enuspeed)
{
    error_t Loc_enustatus = OK;

    if (Cpy_enuspeed < Low_Speed || Cpy_enuspeed > VHIGH_Speed)
    {
        Loc_enustatus = OUT_OF_RANGE;
    }

    return Loc_enustatus;
}

static error_t GPIO_staticEnuPullRange(pull_t Cpy_enupull)
{
    error_t Loc_enustatus=OK;

    if (Cpy_enupull<NOPULL || Cpy_enupull>PULLDOWN)
    {
        Loc_enustatus=OUT_OF_RANGE;
    }

    return Loc_enustatus;
}

static error_t GPIO_staticEnuAltRange(alt_fun_t Cpy_enualt)
{
    error_t Loc_enustatus=OK;

    if (Cpy_enualt<AF0 || Cpy_enualt>AF15)
    {
        Loc_enustatus = OUT_OF_RANGE;
    }

    return Loc_enustatus;
}

static error_t GPIO_staticEnuOutRange(out_type_t Cpy_enuout)
{
    error_t Loc_enustatus = OK;

    if (Cpy_enuout<Push_Pull || Cpy_enuout>Open_Drain)
    {
        Loc_enustatus=OUT_OF_RANGE;
    }

    return Loc_enustatus;
}


static error_t GPIO_InitOutPut(const Pin_cfg_t *ref_strCfg)
{
    error_t Loc_enustatus = OK;

    Loc_enustatus=GPIO_enuCfgSpeed(ref_strCfg->port, ref_strCfg->pin, ref_strCfg->speed);

    if(Loc_enustatus==OK)
    {
        Loc_enustatus=GPIO_enuCfgOuTtYPE(ref_strCfg->port, ref_strCfg->pin, ref_strCfg->out);
    }

    if(Loc_enustatus==OK)
    {
        Loc_enustatus=GPIO_enuCfgPull(ref_strCfg->port,ref_strCfg->pin, ref_strCfg->pull);
    }

    return Loc_enustatus;
}

static error_t GPIO_InitInPut(const Pin_cfg_t *ref_strCfg)
{
    error_t Loc_enustatus = OK;

    Loc_enustatus=GPIO_enuCfgPull(ref_strCfg->port,ref_strCfg->pin, ref_strCfg->pull);

    return Loc_enustatus;

}

static error_t GPIO_InitAnalog(const Pin_cfg_t *ref_strCfg)
{
    error_t Loc_enustatus = OK;

    Loc_enustatus=GPIO_enuCfgPull(ref_strCfg->port,ref_strCfg->pin, ref_strCfg->pull);

    return Loc_enustatus;
}


static error_t GPIO_InitAlt_Fun(const Pin_cfg_t *ref_strCfg)
{
    error_t Loc_enustatus = OK;

    Loc_enustatus=GPIO_enuCfgAltFun(ref_strCfg->port,ref_strCfg->pin, ref_strCfg->alt);

    if(Loc_enustatus==OK)
    {
        Loc_enustatus=GPIO_enuCfgSpeed(ref_strCfg->port, ref_strCfg->pin, ref_strCfg->speed);
    }

    if(Loc_enustatus==OK)
    {
        Loc_enustatus=GPIO_enuCfgOuTtYPE(ref_strCfg->port, ref_strCfg->pin, ref_strCfg->out);
    }

    if(Loc_enustatus==OK)
    {
        Loc_enustatus=GPIO_enuCfgPull(ref_strCfg->port,ref_strCfg->pin, ref_strCfg->pull);
    }

    

    return Loc_enustatus;
}



error_t GPIO_enuPinInit(const Pin_cfg_t *ref_strCfg)
{
    error_t Loc_enustatus = OK;

    if (ref_strCfg==NULL)
    {
        Loc_enustatus=NULL_PTR;
    }

    if(Loc_enustatus==OK)
    {
        Loc_enustatus=GPIO_enuCfgMode(ref_strCfg->port, ref_strCfg->pin, ref_strCfg->mode);
    }

    if(Loc_enustatus==OK)
    {
        switch (ref_strCfg->mode) {

            case OUTPUT:
            Loc_enustatus=GPIO_InitOutPut(ref_strCfg);
            break;
            case INPUT:
            Loc_enustatus=GPIO_InitInPut(ref_strCfg);
            break;
            case Analog:
            Loc_enustatus=GPIO_InitAnalog(ref_strCfg);
            break;
            case Alternative_Func:
            Loc_enustatus=GPIO_InitAlt_Fun(ref_strCfg);
            break;
        }
    }

    return Loc_enustatus;
}


error_t GPIO_enumWritePin(port_t Cpy_enuPort,pin_t Cpy_enuPin,value_t Cpy_enuValue)
{
    error_t Loc_enustatus=OK;

    Loc_enustatus=GPIO_staticEnuPortRnage(Cpy_enuPort);

    if(Loc_enustatus==OK)
    {
        Loc_enustatus=GPIO_staticEnuPinRnage(Cpy_enuPin);
    }

    if(Loc_enustatus==OK)
    {
        switch (Cpy_enuValue) {

            case PIN_High:
            GPIO[Cpy_enuPort]->BSRR=(BSRR_WRITE<<Cpy_enuPin);
            break;
            case PIN_Low:
            GPIO[Cpy_enuPort]->BSRR=(BSRR_WRITE<<(Cpy_enuPin+BSRR_SHIFT));
            break;
            default:
            Loc_enustatus=OUT_OF_RANGE;
            break;
        }
    }
    return Loc_enustatus;
}

error_t GPIO_enumReadPin(port_t Cpy_enuPort,pin_t Cpy_enuPin,value_t*ref_enuValue)
{
    error_t Loc_enustatus=OK;

    if(ref_enuValue==NULL)
    {
        Loc_enustatus=NULL_PTR;
    }

    if(Loc_enustatus==OK)
    {
       Loc_enustatus=GPIO_staticEnuPortRnage(Cpy_enuPort); 
    }

    if(Loc_enustatus==OK)
    {
        Loc_enustatus=GPIO_staticEnuPinRnage(Cpy_enuPin);
    }

    if(Loc_enustatus==OK)
    {
        *(ref_enuValue)=GET_BIT(GPIO[Cpy_enuPort]->IDR, Cpy_enuPin);
    }
    return Loc_enustatus;
	
}

error_t GPIO_enumWritePort(port_t Cpy_enuPort,u16 Cpy_u16value)
{
    error_t Loc_enustatus=OK;

    Loc_enustatus=GPIO_staticEnuPortRnage(Cpy_enuPort);

    if(Loc_enustatus==OK)
    {
        GPIO[Cpy_enuPort]->ODR=Cpy_u16value;
    }

    return Loc_enustatus;
}

error_t GPIO_enumReadPort(port_t Cpy_enuPort,u16*ref_u16value)
{
    error_t Loc_enustatus=OK;

    if(ref_u16value==NULL)
    {
        Loc_enustatus=NULL_PTR;
    }

    if(Loc_enustatus==OK)
    {
        Loc_enustatus=GPIO_staticEnuPortRnage(Cpy_enuPort);

    }

    if(Loc_enustatus==OK)
    {
        *(ref_u16value)=GPIO[Cpy_enuPort]->IDR;
    }
    return Loc_enustatus;
}

error_t GPIO_enuCfgSpeed(port_t Cpy_enuPort,pin_t Cpy_enuPin,speed_t Cpy_enuSpeed)
{

    error_t Loc_enustatus=OK;

    Loc_enustatus=GPIO_staticEnuPortRnage(Cpy_enuPort);

    if(Loc_enustatus==OK)
    {
        Loc_enustatus=GPIO_staticEnuPinRnage(Cpy_enuPin);
    }
    if(Loc_enustatus==OK)
    {
        Loc_enustatus=GPIO_staticEnuSpeedRange(Cpy_enuSpeed);
    }

    if(Loc_enustatus==OK)
    {

        GPIO[Cpy_enuPort]->OSPEEDER &= ~(SPEED_MASK<<Cpy_enuPin*SPEED_PIN_SHIFT);

        GPIO[Cpy_enuPort]->OSPEEDER |= (Cpy_enuSpeed<<Cpy_enuPin*SPEED_PIN_SHIFT);

    }

    return Loc_enustatus;
}

error_t GPIO_enuCfgPull(port_t Cpy_enuPort,pin_t Cpy_enuPin,pull_t Cpy_enuPull)
{
    error_t Loc_enustatus=OK;

    Loc_enustatus=GPIO_staticEnuPortRnage(Cpy_enuPort);

    if(Loc_enustatus==OK)
    {
        Loc_enustatus=GPIO_staticEnuPinRnage(Cpy_enuPin);
    }

    if(Loc_enustatus==OK)
    {
        Loc_enustatus=GPIO_staticEnuPullRange(Cpy_enuPull);
    }

    if(Loc_enustatus==OK)
    {
        GPIO[Cpy_enuPort]->PUPDR &= ~(PULL_MASK<<Cpy_enuPin*PULL_PIN_SHIFT);

        GPIO[Cpy_enuPort]->PUPDR |= (Cpy_enuPull<<Cpy_enuPin*PULL_PIN_SHIFT);

    }
    return Loc_enustatus;

}

error_t GPIO_enuCfgMode(port_t Cpy_enuPort,pin_t Cpy_enuPin,mode_t Cpy_enuMode)
{
    error_t Loc_enustatus=OK;

    Loc_enustatus=GPIO_staticEnuPortRnage(Cpy_enuPort);

    if(Loc_enustatus==OK)
    {
        Loc_enustatus=GPIO_staticEnuPinRnage(Cpy_enuPin);
    }

    if(Loc_enustatus==OK)
    {
        Loc_enustatus=GPIO_staticEnuModeRnage(Cpy_enuMode);
    }

    if(Loc_enustatus==OK)
    {
        GPIO[Cpy_enuPort]->MODER &= ~(MODE_MASK<<Cpy_enuPin*MODE_PIN_SHIFT);

        GPIO[Cpy_enuPort]->MODER |= (Cpy_enuMode<<Cpy_enuPin*MODE_PIN_SHIFT);

    }
    return Loc_enustatus;

}

error_t GPIO_enuCfgOuTtYPE(port_t Cpy_enuPort,pin_t Cpy_enuPin,out_type_t Cpy_enuOuttype)
{
    error_t Loc_enustatus=OK;

    Loc_enustatus=GPIO_staticEnuPortRnage(Cpy_enuPort);

    if(Loc_enustatus==OK)
    {
        Loc_enustatus=GPIO_staticEnuPinRnage(Cpy_enuPin);
    }

    if(Loc_enustatus==OK)
    {
        Loc_enustatus=GPIO_staticEnuOutRange(Cpy_enuOuttype);
    }

    if(Loc_enustatus==OK)
    {
        GPIO[Cpy_enuPort]->OTYPER &= ~(OUT_TYPE_MASK<<Cpy_enuPin);

        GPIO[Cpy_enuPort]->OTYPER |= (Cpy_enuOuttype<<Cpy_enuPin);

    }
    return Loc_enustatus;
}

error_t GPIO_enuCfgAltFun(port_t Cpy_enuPort,pin_t Cpy_enuPin,alt_fun_t Cpy_enuAltFun)
{
    error_t Loc_enustatus=OK;

    Loc_enustatus=GPIO_staticEnuPortRnage(Cpy_enuPort);

    if(Loc_enustatus==OK)
    {
        Loc_enustatus=GPIO_staticEnuPinRnage(Cpy_enuPin);
    }

    if(Loc_enustatus==OK)
    {
        Loc_enustatus=GPIO_staticEnuAltRange(Cpy_enuAltFun);
    }

    if(Loc_enustatus==OK)
    {
        GPIO[Cpy_enuPort]->AFR[Cpy_enuPin/AFR_DIV ] &= ~(AF_MASK <<(Cpy_enuPin%AFR_DIV)*AF_PIN_SHIFT);

        GPIO[Cpy_enuPort]->AFR[Cpy_enuPin/AFR_DIV ] |= (Cpy_enuAltFun <<(Cpy_enuPin%AFR_DIV)*AF_PIN_SHIFT);
    }
     return Loc_enustatus;
}








