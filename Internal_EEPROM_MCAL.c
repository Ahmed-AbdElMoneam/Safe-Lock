/*
 * Internal_EEPROM_MCAL.c
 *
 * Created: 15/07/2020 06:57:36 ص
 *  Author: ahmed
 */ 

#include "Internal_EEPROM_MCAL.h"

void EEPROM_vWrite(u_int16 address, u_int8 val){
	XEEARL = (u_int8)address;
	XEEARH = (u_int8)(address>>8);
	XEEDR = val;
	SET_BIT(XEECR, EEMWE);
	SET_BIT(XEECR, EEWE);
	while(READ_BIT(XEECR, EEWE) == 1);
}

u_int8 EEPROM_u8Read(u_int16 address){
	XEEARL = (u_int8)address;
	XEEARH = (u_int8)(address>>8);
	SET_BIT(XEECR, EERE);
	return XEEDR;
}
