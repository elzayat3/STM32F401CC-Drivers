#ifndef STD_TYPES
#define STD_TYPES

typedef signed char 	     s8;
typedef signed short  	     s16;
typedef signed long 	     s32;
typedef unsigned char 		 u8;
typedef unsigned short int   u16;
typedef unsigned long int 	 u32;


#define NULL   ((void*)0)


#define SET_BIT(REG,BIT) (REG|=(1UL<<(BIT)))
#define CLR_BIT(REG,BIT) (REG&=(~(1UL<<(BIT))))
#define TOG_BIT(REG,BIT) (REG^=(1UL<<(BIT)))
#define GET_BIT(REG,BIT) (((REG>>(BIT))&1UL))


#define SET_2BIT(REG,BASEBIT)  (REG|=(0X03UL<<BASEBIT))  
#define CLR_2BIT(REG,BASEBIT)  (REG&=(~(0X03UL<<BASEBIT)))
#define TOG_2BIT(REG,BASEBIT)  (REG^=(0x03UL<<BASEBIT))
#define GET_2BIT(REG,BASEBIT)  (((REG>>BASEBIT)&0x03UL))






typedef void(*PTF)(void);


typedef enum
{
	OK,
	NOK,
	NULL_PTR,
	OUT_OF_RANGE,
	IN_PROGRESS,
	FULL,
	EMPTY,
	TIMEOUT
}error_t;


#endif /* STD_TYPES_H */

