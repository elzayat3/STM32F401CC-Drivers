int main()
{
    volatile u8  x=0;

    value_t pin0=PIN_Low;

    value_t pin1=PIN_Low;

    value_t pin2=PIN_Low;

    if(RCC_AHB1_Control(RCC_GPIOA, ON)==OK)
    {

    }

    if(RCC_AHB1_Control(RCC_GPIOB, ON)==OK)
    {
      
    }
    if(GPIO_enuPinInit(&cfga1)==OK)
    {
    
    }
    if(GPIO_enuPinInit(&cfga2)==OK)
    {
        
    }
    if(GPIO_enuPinInit(&cfga3)==OK)
    {
        
    }
    if(GPIO_enuPinInit(&cfga4)==OK)
    {
        
    }
    if(GPIO_enuPinInit(&cfga5)==OK)
    {
        
    }
    if(GPIO_enuPinInit(&cfga6)==OK)
    {
        
    }
    if(GPIO_enuPinInit(&cfga7)==OK)
    {
        
    }
    if(GPIO_enuPinInit(&cfgb0)==OK)
    {
        
    }
    if(GPIO_enuPinInit(&cfgb1)==OK)
    {
        
    }
    if(GPIO_enuPinInit(&cfgb2)==OK)
    {
        
    }
    GPIO_enumWritePort(PORTA, 0);
    
    while(1)
    {
        if(GPIO_enumReadPin(PORTB,PIN0,&pin0)==OK)
        {
            if(pin0==PIN_High)
            {
                CLR_BIT(x, 0);
            }
            else
            {
                SET_BIT(x,0);
                
            }
        }
        if(GPIO_enumReadPin(PORTB,PIN1,&pin1)==OK)
        {
            if(pin1==PIN_High)
            {
                CLR_BIT(x, 1);
            }
            else
            {
                SET_BIT(x,1);
                
            }
        }
        if(GPIO_enumReadPin(PORTB,PIN3,&pin2)==OK)
        {
            if(pin2==PIN_High)
            {
                CLR_BIT(x, 2);
            }
            else
            {
                SET_BIT(x,2);
                
            }
        }
        GPIO_enumWritePort(PORTA, 0);

        for(int i=1;i<=x;i++)
        {
            GPIO_enumWritePin(PORTA,i,PIN_High);
        }


    }



}