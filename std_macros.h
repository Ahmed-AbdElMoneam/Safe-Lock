/*
 * std_macros.h
 *
 * Created: 28/06/2020 01:22:49 م
 *  Author: ahmed
 */ 


#ifndef STD_MACROS_H_
#define STD_MACROS_H_

#define SET_BIT(reg,bit) reg|=(1<<bit)

#define CLR_BIT(reg,bit) reg&=(~(1<<bit))

#define TOG_BIT(reg,bit) reg^=(1<<bit)

#define READ_BIT(reg,bit) ((reg&(1<<bit))>>bit)

#endif /* STD_MACROS_H_ */