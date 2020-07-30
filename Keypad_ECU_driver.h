/*
 * Keypad_ECU_driver.h
 *
 * Created: 23/07/2020 03:05:57 ص
 *  Author: ahmed
 */ 


#ifndef KEYPAD_ECU_DRIVER_H_
#define KEYPAD_ECU_DRIVER_H_

#include "GPIO.h"
#include "Data_Type.h"

#define NOTPRESSED 0xFF

void Keypad_vInit(u_int8 port);

u_int8 Keypad_u8Check_Press(u_int8 port);

#endif /* KEYPAD_ECU_DRIVER_H_ */