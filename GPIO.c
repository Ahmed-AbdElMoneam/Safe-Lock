/*
 * GPIO.c
 *
 * Created: 28/06/2020 01:15:43 م
 *  Author: ahmed
 */ 
#include "GPIO.h"
#define OUTPUT 1
#define INPUT 0
#define HIGH 1
#define LOW 0

void GPIO_vSETPIN_DDR(u_int8 portnum, u_int8 pinnum, u_int8 dir){
	switch (portnum){
		case 'A' :
		case 'a' :
			if(dir == OUTPUT){
				SET_BIT(XDDRA,pinnum);
			}
			else{
				CLR_BIT(XDDRA,pinnum);
			}
		break;
		case 'B':
		case 'b':
			if(dir == OUTPUT){
				SET_BIT(XDDRB,pinnum);
			}
			else{
				CLR_BIT(XDDRB,pinnum);
			}
		break;
		case 'C':
		case 'c':
			if(dir == OUTPUT){
				SET_BIT(XDDRC,pinnum);
			}
			else{
				CLR_BIT(XDDRC,pinnum);
			}
		break;
		case 'D':
		case 'd':
			if(dir == OUTPUT){
				SET_BIT(XDDRD,pinnum);
			}
			else{
				CLR_BIT(XDDRD,pinnum);
			}
		break;
	}
}

void GPIO_vSETPORT_DDR(u_int8 portnum, u_int8 dir){
	switch (portnum){
		case 'A' :
		case 'a' :
			XDDRA = dir;
		break;
		
		case 'B' :
		case 'b' :
			XDDRB = dir;
		break;
		
		case 'C' :
		case 'c' :
			XDDRC = dir;
		break;
		
		case 'D' :
		case 'd' :
			XDDRD = dir;
		break;
	}
}

void GPIO_vWRITEPIN(u_int8 portnum, u_int8 pinnum, u_int8 val){
	switch (portnum){
		case 'A' :
		case 'a' :
			if(val == HIGH){
				SET_BIT(XPORTA,pinnum);
			}
			else{
				CLR_BIT(XPORTA,pinnum);
			}
	    break;
		case 'B' :
		case 'b' :
			if(val == HIGH){
				SET_BIT(XPORTB,pinnum);
			}
			else{
				CLR_BIT(XPORTB,pinnum);
			}
		break;
		case 'C' :
		case 'c' :
			if(val == HIGH){
				SET_BIT(XPORTC,pinnum);
			}
			else{
				CLR_BIT(XPORTC,pinnum);
			}
		break;
		case 'D' :
		case 'd' :
			if(val == HIGH){
				SET_BIT(XPORTD,pinnum);
			}
			else{
				CLR_BIT(XPORTD,pinnum);
			}
		break;
	}
}

void GPIO_vWRITEPORT(u_int8 portnum, u_int8 val){
	switch (portnum){
		case 'A' :
		case 'a' :
			XPORTA = val;
		break;
		
		case 'B' :
		case 'b' :
			XPORTB = val;
		break;
		
		case 'C' :
		case 'c' :
			XPORTC = val;
		break;
		
		case 'D' :
		case 'd' :
			XPORTD = val;
		break;
	}
}

u_int8 GPIO_u8READPIN(u_int8 portnum, u_int8 pinnum){
	u_int8 ret = 1;
	switch (portnum){
		case 'A' :
		case 'a' :
			ret=READ_BIT(XPINA,pinnum);
		break;
		
		case 'B' :
		case 'b' :
			ret=READ_BIT(XPINB,pinnum);
		break;
		
		case 'C' :
		case 'c' :
			ret=READ_BIT(XPINC,pinnum);
		break;
		
		case 'D' :
		case 'd' :
			ret=READ_BIT(XPIND,pinnum);
		break;
	}
	return ret;
}

u_int8 GPIO_u8READPORT(u_int8 portnum){
	u_int8 ret = 2;
	switch (portnum){
		case 'A' :
		case 'a' :
			ret=XPINA;
		break;
		
		case 'B' :
		case 'b' :
			ret=XPINB;
		break;
		
		case 'C' :
		case 'c' :
			ret=XPINC;
		break;
		
		case 'D' :
		case 'd' :
			ret=XPIND;
		break;
	}
	return ret;
}

void GPIO_vInternal_pullupON(u_int8 portnum, u_int8 pinnum){
	GPIO_vWRITEPIN(portnum,pinnum,1);
}

void GPIO_vInternal_pullupOFF(u_int8 portnum, u_int8 pinnum){
	GPIO_vWRITEPIN(portnum,pinnum,0);
}

void GPIO_vLowNibble_Set_DDR(u_int8 portnum, u_int8 dir){
	GPIO_vSETPIN_DDR(portnum,0,dir);
	GPIO_vSETPIN_DDR(portnum,1,dir);
	GPIO_vSETPIN_DDR(portnum,2,dir);
	GPIO_vSETPIN_DDR(portnum,3,dir);
}

void GPIO_vLowNibble_write(u_int8 portnum, u_int8 val){
	val &= 0x0f;
	switch(portnum){
		case 'A' :
		case 'a' :
			XPORTA &= 0xf0;
			XPORTA |= val;
		break;
		case 'B' :
		case 'b' :
			XPORTB &= 0xf0;
			XPORTB |= val;
		break;
		case 'C' :
		case 'c' :
			XPORTC &= 0xf0;
			XPORTC |= val;
		break;
		case 'D' :
		case 'd' :
			XPORTD &= 0xf0;
			XPORTD |= val;
		break;
	}
}

void GPIO_vHighNibble_Set_DDR(u_int8 portnum, u_int8 dir){
	GPIO_vSETPIN_DDR(portnum,4,dir);
	GPIO_vSETPIN_DDR(portnum,5,dir);
	GPIO_vSETPIN_DDR(portnum,6,dir);
	GPIO_vSETPIN_DDR(portnum,7,dir);
}

void GPIO_vHighNibble_write(u_int8 portnum, u_int8 val){
	val &= 0xf0;
	switch(portnum){
		case 'A' :
		case 'a' :
			XPORTA &= 0x0f;
			XPORTA |= val;
		break;
		case 'B' :
		case 'b' :
			XPORTB &= 0x0f;
			XPORTB |= val;
		break;
		case 'C' :
		case 'c' :
			XPORTC &= 0x0f;
			XPORTC |= val;
		break;
		case 'D' :
		case 'd' :
			XPORTD &= 0x0f;
			XPORTD |= val;
		break;
	}
}


