/*
 * Internal_EEPROM_MCAL.h
 *
 * Created: 15/07/2020 06:57:05 ص
 *  Author: ahmed
 */ 


#ifndef INTERNAL_EEPROM_MCAL_H_
#define INTERNAL_EEPROM_MCAL_H_

#include "Data_Type.h"
#include "std_macros.h"
#include "Register.h"

void EEPROM_vWrite(u_int16 address, u_int8 val);

u_int8 EEPROM_u8Read(u_int16 address);



#endif /* INTERNAL_EEPROM_MCAL_H_ */