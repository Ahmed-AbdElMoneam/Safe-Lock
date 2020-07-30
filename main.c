/*
 * Safe Lock.c
 *
 * Created: 29/07/2020 12:44:03 م
 * Author : ahmed
 */ 

/*************************************************************
**************************************************************
			The user should choose between Real Keypad
			& Proteus Keypad in (Keypad_u8Check_Press)
			 function in Keypad_ECU_driver.c file.
**************************************************************
*************************************************************/

#include <avr/io.h>
#include <util/delay.h>

#include "LCD_ECU_driver.h"
#include "LED_ECU_driver.h"
#include "Keypad_ECU_driver.h"

#define F_CPU 8000000UL

/***EEPROM Password Addresses***/
#define EEPROM_PASSWORD_LOCATION1  0x01
#define EEPROM_PASSWORD_LOCATION2  0x02
#define EEPROM_PASSWORD_LOCATION3  0x03
#define EEPROM_PASSWORD_LOCATION4  0x04
#define STATUS                     0x08
/*******************************/
#define TRIES  3

u_int8 arr_password[4];

int main(void)
{
    /* Replace with your application code */
	u_int8 val = NOTPRESSED;
	u_int8 tries = TRIES;
	u_int8 hash_password = 420;
	OBJ x;
	u_int8 a,b,c,d;
	u_int8 flag = 0;
	/****Drivers Initialization****/
	Keypad_vInit('A');
	LCD_vGet_Config(&x, EIGHT_BIT, HIGH_NIBBLE, 'D', 'B', 0, 'B', 1, 'B', 2);
	LCD_vInit();
	LED_vInit('C', 0);
	LED_vInit('C', 7);
	/*****************************/
	/*The code which will be executed when user sets the password 
	for the first time. The password 4 bits will be stored in EEPROM.*/
	if(EEPROM_u8Read(STATUS) == 0xFF){
		LCD_vSend_String("Set Password:");
		LCD_vMove_Cursor(2,1);
		do{
			val = Keypad_u8Check_Press('A');
		}while(val == NOTPRESSED);
		_delay_ms(500);
		LCD_vSend_Char(val);
		_delay_ms(2000);
		LCD_vMove_Cursor(2,1);
		LCD_vSend_Char('*');
		_delay_ms(500);
		val ^= hash_password;
		EEPROM_vWrite(EEPROM_PASSWORD_LOCATION1, val);
		val = NOTPRESSED;
		do{
			val = Keypad_u8Check_Press('A');
		}while(val == NOTPRESSED);
		_delay_ms(500);
		LCD_vSend_Char(val);
		_delay_ms(2000);
		LCD_vMove_Cursor(2,2);
		LCD_vSend_Char('*');
		_delay_ms(500);
		val ^= hash_password;
		EEPROM_vWrite(EEPROM_PASSWORD_LOCATION2, val);
		val = NOTPRESSED;
		do{
			val = Keypad_u8Check_Press('A');
		}while(val == NOTPRESSED);
		_delay_ms(500);
		LCD_vSend_Char(val);
		_delay_ms(2000);
		LCD_vMove_Cursor(2,3);
		LCD_vSend_Char('*');
		_delay_ms(500);
		val ^= hash_password;
		EEPROM_vWrite(EEPROM_PASSWORD_LOCATION3, val);
		val = NOTPRESSED;
		do{
			val = Keypad_u8Check_Press('A');
		}while(val == NOTPRESSED);
		_delay_ms(500);
		LCD_vSend_Char(val);
		_delay_ms(2000);
		LCD_vMove_Cursor(2,4);
		LCD_vSend_Char('*');
		_delay_ms(500);
		val ^= hash_password;
		EEPROM_vWrite(EEPROM_PASSWORD_LOCATION4, val);
		val = NOTPRESSED;
		//Status will be changed.
		EEPROM_vWrite(STATUS, 0x00);
	}
	/************************************************************/
	/*This is the code which will be executed after setting the password.
	and it enables the user to enter his password to open the safe.*/
	while(flag == 0){
		arr_password[0] = arr_password[1] = arr_password[2] = arr_password[3] = NOTPRESSED;
		LCD_vClear_Screen();
		LCD_vSend_String("Enter Password:");
		LCD_vMove_Cursor(2,1);
		do{
			arr_password[0] = Keypad_u8Check_Press('A');
		}while(arr_password[0] == NOTPRESSED);
		_delay_ms(500);
		LCD_vSend_Char(arr_password[0]);
		_delay_ms(2000);
		LCD_vMove_Cursor(2,1);
		LCD_vSend_Char('*');
		_delay_ms(500);
		do{
			arr_password[1] = Keypad_u8Check_Press('A');
		}while(arr_password[1] == NOTPRESSED);
		_delay_ms(500);
		LCD_vSend_Char(arr_password[1]);
		_delay_ms(2000);
		LCD_vMove_Cursor(2,2);
		LCD_vSend_Char('*');
		_delay_ms(500);
		do{
			arr_password[2] = Keypad_u8Check_Press('A');
		}while(arr_password[2] == NOTPRESSED);
		_delay_ms(500);
		LCD_vSend_Char(arr_password[2]);
		_delay_ms(2000);
		LCD_vMove_Cursor(2,3);
		LCD_vSend_Char('*');
		_delay_ms(500);
		do{
			arr_password[3] = Keypad_u8Check_Press('A');
		}while(arr_password[3] == NOTPRESSED);
		_delay_ms(500);
		LCD_vSend_Char(arr_password[3]);
		_delay_ms(2000);
		LCD_vMove_Cursor(2,4);
		LCD_vSend_Char('*');
		_delay_ms(500);
		//Now, It is Encryption time.
		//The password entered by the user will be encrypted in order to 
		//prevent any hacking to the EEPROM values.
		a = EEPROM_u8Read(EEPROM_PASSWORD_LOCATION1);
		a ^= hash_password;
		b = EEPROM_u8Read(EEPROM_PASSWORD_LOCATION2);
		b ^= hash_password;
		c = EEPROM_u8Read(EEPROM_PASSWORD_LOCATION3);
		c ^= hash_password;
		d = EEPROM_u8Read(EEPROM_PASSWORD_LOCATION4);
		d ^= hash_password;
		/**************************************************************/
		//Comparison between the stored password bits in EEPROM &
		//the entered values using the keypad.
		if(a == arr_password[0] && b == arr_password[1] && c == arr_password[2] && d == arr_password[3]){
			LCD_vClear_Screen();
			LCD_vSend_String("Right Password");
			LCD_vMove_Cursor(2,1);
			LCD_vSend_String("Safe is Unlocked");
			LED_vOn('C', 7);
			flag = 1;
		}
		else{
			tries -= 1;
			if(tries > 0){
				LCD_vClear_Screen();
				LCD_vSend_String("Wrong Password");
				LCD_vMove_Cursor(2, 1);
				LCD_vSend_String("Tries left=");
				LCD_vSend_Number(tries);
				LED_vOn('C', 0);
				_delay_ms(5000);
				LED_vOff('C', 0);
				_delay_ms(5000);
			}
			else{
				LCD_vClear_Screen();
				LCD_vSend_String("Wrong Password");
				LCD_vMove_Cursor(2, 1);
				LCD_vSend_String("Tries left=");
				LCD_vSend_Number(tries);
				LED_vOn('C', 0);
				_delay_ms(5000);
				LCD_vClear_Screen();
				LCD_vSend_String("Safe is Closed");
				_delay_ms(5000);
				break;
			}
		}
		/*************************************************/
	}
	/**********************************************************/
    while (1) 
    {
    }
}

