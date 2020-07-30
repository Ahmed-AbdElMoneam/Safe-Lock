/*
 * LED_ECU_driver.h
 *
 * Created: 06/07/2020 11:40:04 ص
 *  Author: ahmed
 */ 


#ifndef LED_ECU_DRIVER_H_
#define LED_ECU_DRIVER_H_

#include "GPIO.h"
#include "Data_Type.h"

/*
	return: void
	argument: portnum as unsigned char and pinnum as unsigned char
*/

void LED_vInit(u_int8 portnum, u_int8 pinnum);
void LED_vOn(u_int8 portnum, u_int8 pinnum);
void LED_vOff(u_int8 portnum, u_int8 pinnum);
void LED_vTog(u_int8 portnum, u_int8 pinnum);

#endif /* LED_ECU_DRIVER_H_ */