/*
 * GPIO.h
 *
 * Created: 28/06/2020 01:15:04 م
 *  Author: ahmed
 */ 


#ifndef GPIO_H_
#define GPIO_H_

#include "Data_Type.h"
#include "Register.h"
#include "std_macros.h"

void GPIO_vSETPIN_DDR(u_int8 portnum, u_int8 pinnum, u_int8 dir);
void GPIO_vSETPORT_DDR(u_int8 portnum, u_int8 dir);

void GPIO_vWRITEPIN(u_int8 portnum, u_int8 pinnum, u_int8 val);
void GPIO_vWRITEPORT(u_int8 portnum, u_int8 val);

u_int8 GPIO_u8READPIN(u_int8 portnum, u_int8 pinnum);
u_int8 GPIO_u8READPORT(u_int8 portnum);

void GPIO_vInternal_pullupON(u_int8 portnum, u_int8 pinnum);
void GPIO_vInternal_pullupOFF(u_int8 portnum, u_int8 pinnum);

void GPIO_vLowNibble_Set_DDR(u_int8 portnum, u_int8 dir);
void GPIO_vLowNibble_write(u_int8 portnum, u_int8 val);

void GPIO_vHighNibble_Set_DDR(u_int8 portnum, u_int8 dir);
void GPIO_vHighNibble_write(u_int8 portnum, u_int8 val);


#endif /* GPIO_H_ */