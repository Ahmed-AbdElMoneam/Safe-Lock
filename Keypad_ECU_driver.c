/*
 * Keypad_ECU_driver.c
 *
 * Created: 23/07/2020 03:06:18 ص
 *  Author: ahmed
 */ 

#include "Keypad_ECU_driver.h"

void Keypad_vInit(u_int8 port){
	GPIO_vSETPORT_DDR(port, 0x0F);
	GPIO_vInternal_pullupON(port, 4);
	GPIO_vInternal_pullupON(port, 5);
	GPIO_vInternal_pullupON(port, 6);
	GPIO_vInternal_pullupON(port, 7);
}

u_int8 Keypad_u8Check_Press(u_int8 port){
	u_int8 arr[4][4] = {{'1','2','3','A'}, {'4','5','6','B'}, {'7','8','9','C'},{'*','0','#','D'}}; //Real Keypad.
	//u_int8 arr[4][4] = {{'7','8','9','/'}, {'4','5','6','*'}, {'1','2','3','-'},{'A','0','=','+'}}; //Proteus Keypad.
	u_int8 row, column, x;
	u_int8 return_val = NOTPRESSED;
	for(row = 0; row < 4; row++){
		GPIO_vWRITEPIN(port, 0, 1);
		GPIO_vWRITEPIN(port, 1, 1);
		GPIO_vWRITEPIN(port, 2, 1);
		GPIO_vWRITEPIN(port, 3, 1);
		GPIO_vWRITEPIN(port, row, 0);
		for(column = 0; column < 4; column++){
			x = GPIO_u8READPIN(port, (column + 4));
			if(0 == x){
				return_val = arr[row][column];
				break;
			}
		}
		if(0 == x){
			break;
		}
	}
	return return_val;
}