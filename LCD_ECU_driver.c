/*
 * LCD_ECU_driver.c
 *
 * Created: 22/07/2020 07:31:02 ص
 *  Author: ahmed
 */ 
#include "LCD_ECU_driver.h"

OBJ *ip;
void LCD_vGet_Config(OBJ *ptr, u_int8 mode, u_int8 nibble, u_int8 port, u_int8 rs_port, u_int8 rs_pin, u_int8 rw_port, u_int8 rw_pin, u_int8 en_port, u_int8 en_pin){
	ip = ptr;
	ip ->Mode = mode;
	ip ->Nibble = nibble;
	ip ->LCD_Port = port;
	ip ->RS_Port = rs_port;
	ip ->RS_Pin = rs_pin;
	ip ->RW_Port = rw_port;
	ip ->RW_Pin = rw_pin;
	ip ->EN_Port = en_port;
	ip ->EN_Pin = en_pin;
}

void LCD_vInit(){
	if(ip != 0){
		_delay_ms(200);
		GPIO_vSETPIN_DDR(ip ->RS_Port, ip ->RS_Pin, 1);
		GPIO_vSETPIN_DDR(ip ->RW_Port, ip ->RW_Pin, 1);
		GPIO_vSETPIN_DDR(ip ->EN_Port, ip ->EN_Pin, 1);
		if(ip -> Mode == EIGHT_BIT){
			GPIO_vSETPORT_DDR(ip ->LCD_Port, 0xFF);
			GPIO_vWRITEPIN(ip ->RW_Port, ip ->RW_Pin, 0);
			_delay_ms(15);
			LCD_vSend_Cmd(LCD_8Bit_2Lines);
			_delay_ms(1);
			LCD_vSend_Cmd(LCD_DISP_ON_CURSOR_ON);
			_delay_ms(1);
			LCD_vSend_Cmd(LCD_CLEAR_SCREEN);
			_delay_ms(10);
			LCD_vSend_Cmd(LCD_ENTRY_MODE);
			_delay_ms(1);
		}
		else{
			if(ip ->Nibble == HIGH_NIBBLE){
				GPIO_vHighNibble_Set_DDR(ip ->LCD_Port, 1);
				GPIO_vWRITEPIN(ip ->RW_Port, ip ->RW_Pin, 0);
				_delay_ms(15);
				LCD_vSend_Cmd(LCD_8Bit_2Lines);
				_delay_ms(1);
				LCD_vSend_Cmd(LCD_DISP_ON_CURSOR_ON);
				_delay_ms(1);
				LCD_vSend_Cmd(LCD_CLEAR_SCREEN);
				_delay_ms(10);
				LCD_vSend_Cmd(LCD_ENTRY_MODE);
				_delay_ms(1);
			}
			else{
				GPIO_vLowNibble_Set_DDR(ip ->LCD_Port, 1);
				GPIO_vWRITEPIN(ip ->RW_Port, ip ->RW_Pin, 0);
				_delay_ms(15);
				LCD_vSend_Cmd(LCD_8Bit_2Lines);
				_delay_ms(1);
				LCD_vSend_Cmd(LCD_DISP_ON_CURSOR_ON);
				_delay_ms(1);
				LCD_vSend_Cmd(LCD_CLEAR_SCREEN);
				_delay_ms(10);
				LCD_vSend_Cmd(LCD_ENTRY_MODE);
				_delay_ms(1);
			}
		}
	}
}

void LCD_vSend_Cmd(u_int8 cmd){
	if(ip ->Mode == EIGHT_BIT){
		GPIO_vWRITEPORT(ip ->LCD_Port, cmd);
		GPIO_vWRITEPIN(ip -> RS_Port, ip -> RS_Pin, 0);
		LCD_vSend_Falling_Edge();
	}
	else{
		if(ip -> Nibble == HIGH_NIBBLE){
			GPIO_vHighNibble_write(ip -> LCD_Port, cmd>>4);
			GPIO_vWRITEPIN(ip -> RS_Port, ip -> RS_Pin, 0);
			LCD_vSend_Falling_Edge();
			GPIO_vHighNibble_write(ip -> LCD_Port, cmd);
			GPIO_vWRITEPIN(ip -> RS_Port, ip -> RS_Pin, 0);
			LCD_vSend_Falling_Edge();
			_delay_ms(1);
		}
		else{
			GPIO_vLowNibble_write(ip -> LCD_Port, cmd>>4);
			GPIO_vWRITEPIN(ip -> RS_Port, ip -> RS_Pin, 0);
			LCD_vSend_Falling_Edge();
			GPIO_vLowNibble_write(ip -> LCD_Port, cmd);
			GPIO_vWRITEPIN(ip -> RS_Port, ip -> RS_Pin, 0);
			LCD_vSend_Falling_Edge();
			_delay_ms(1);
		}
	}
}

static void LCD_vSend_Falling_Edge(){
	GPIO_vWRITEPIN(ip ->EN_Port, ip -> EN_Pin, 1);
	_delay_ms(2);
	GPIO_vWRITEPIN(ip ->EN_Port, ip -> EN_Pin, 0);
}

void LCD_vSend_Char(u_int8 data){
	if(ip -> Mode == EIGHT_BIT){
		GPIO_vWRITEPORT(ip -> LCD_Port, data);
		GPIO_vWRITEPIN(ip -> RS_Port, ip -> RS_Pin, 1);
		LCD_vSend_Falling_Edge();
		_delay_ms(1);
	}
	else{
		if(ip -> Nibble == HIGH_NIBBLE){
			GPIO_vHighNibble_write(ip -> LCD_Port, data>>4);
			GPIO_vWRITEPIN(ip -> RS_Port, ip -> RS_Pin, 1);
			LCD_vSend_Falling_Edge();
			GPIO_vHighNibble_write(ip -> LCD_Port, data);
			GPIO_vWRITEPIN(ip -> RS_Port, ip -> RS_Pin, 1);
			LCD_vSend_Falling_Edge();
			_delay_ms(1);
		}
		else{
			GPIO_vLowNibble_write(ip -> LCD_Port, data>>4);
			GPIO_vWRITEPIN(ip -> RS_Port, ip -> RS_Pin, 1);
			LCD_vSend_Falling_Edge();
			GPIO_vLowNibble_write(ip -> LCD_Port, data);
			GPIO_vWRITEPIN(ip -> RS_Port, ip -> RS_Pin, 1);
			LCD_vSend_Falling_Edge();
			_delay_ms(1);
		}
	}
}

void LCD_vSend_String(u_int8 *ptr){
	while((*ptr) != '\0'){
		LCD_vSend_Char(*ptr);
		ptr++;
	}
}

void LCD_vMove_Cursor(u_int8 row, u_int8 position){
	u_int8 data;
	if(row > 3 || row < 1 || position > 16 || position < 1){
		data = 0x80;
	}
	else if(1 == row){
		data = 0x80 + (position - 1);
	}
	else if(2 == row){
		data = 0xC0 + (position - 1);
	}
	LCD_vSend_Cmd(data);
	_delay_ms(1);
}

void LCD_vClear_Screen(){
	LCD_vSend_Cmd(LCD_CLEAR_SCREEN);
	_delay_ms(100);
}

void LCD_vSend_Number(u_int32 number){
	u_int8 str[7];
	sprintf(str, "%d", number);
	LCD_vSend_String(str);
}

void LCD_vSend_Real_Number(float64 number){
	u_int8 str[16];
	u_int8 *tmpsign = (number < 0) ? "-" : "";
	float32 tmpval = (number < 0) ? -number : number;
	s_int32 tmpint1 = tmpval;
	float32 tmpfrac = tmpval - tmpint1;
	s_int32 tmpint2 = tmpfrac * 10000;
	sprintf(str, "%s%d%0.4d", tmpsign,tmpint1,tmpint2);
	LCD_vSend_String(str);
}