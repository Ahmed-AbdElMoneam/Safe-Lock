/*
 * LED_ECU_driver.c
 *
 * Created: 06/07/2020 11:40:33 ص
 *  Author: ahmed
 */ 

#include "LED_ECU_driver.h"
#define High 1

void LED_vInit(u_int8 portnum, u_int8 pinnum){
	GPIO_vSETPIN_DDR(portnum,pinnum,1);
}

void LED_vOn(u_int8 portnum, u_int8 pinnum){
	GPIO_vWRITEPIN(portnum,pinnum,1);
}

void LED_vOff(u_int8 portnum, u_int8 pinnum){
	GPIO_vWRITEPIN(portnum,pinnum,0);
}

void LED_vTog(u_int8 portnum, u_int8 pinnum){
	u_int8 x = 4;
	x = GPIO_u8READPIN(portnum,pinnum);
	if(x == High){
		LED_vOff(portnum,pinnum);
	}
	else{
		LED_vOn(portnum,pinnum);
	}
}