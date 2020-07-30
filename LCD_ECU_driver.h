/*
 * LCD_ECU_driver.h
 *
 * Created: 22/07/2020 07:30:46 ص
 *  Author: ahmed
 */ 


#ifndef LCD_ECU_DRIVER_H_
#define LCD_ECU_DRIVER_H_

#include "GPIO.h"
#include "Data_Type.h"
#include "std_macros.h"
#include <util/delay.h>

#define F_CPU 8000000UL

#define LCD_4Bit_2Lines  0x28
#define LCD_8Bit_2Lines  0x38

/*LCD Commands*/

#define LCD_MOVE_DISP_RIGHT        0x1C
#define LCD_MOVE_DISP_LEFT         0x18
#define LCD_MOVE_CURSOR_RIGHT      0x14
#define LCD_MOVE_CURSOR_LEFT       0x10
#define LCD_DISP_OFF_CURSOR_OFF    0x08
#define LCD_DISP_ON_CURSOR_ON      0x0E
#define LCD_DISP_ON_CURSOR_BLINK   0x0F
#define LCD_ENTRY_MODE             0x06
#define LCD_ENTRY_DEC              0x04
#define LCD_ENTRY_DEC_SHIFT        0x05
#define LCD_ENTRY_INC              0x06
#define LCD_ENTRY_INC_SHIFT        0x07
#define LCD_BEGIN_AT_FIRST_ROW     0x80
#define LCD_BEGIN_AT_SECOND_ROW    0xC0
#define LCD_CLEAR_SCREEN           0x01
#define LCD_RETURN_HOME            0x02

/************************/

#define FOUR_BIT    0
#define EIGHT_BIT   1

#define HIGH_NIBBLE 1
#define LOW_NIBBLE  0

typedef struct{
	u_int8 Mode;
	u_int8 Nibble;
	u_int8 LCD_Port;
	u_int8 RS_Port;
	u_int8 RS_Pin;
	u_int8 RW_Port;
	u_int8 RW_Pin;
	u_int8 EN_Port;
	u_int8 EN_Pin;
	}OBJ;
	
void LCD_vGet_Config(OBJ *ptr, u_int8 mode, u_int8 nibble, u_int8 port, u_int8 rs_port, u_int8 rs_pin, u_int8 rw_port, u_int8 rw_pin, u_int8 en_port, u_int8 en_pin);

void LCD_vInit();

void LCD_vSend_Cmd(u_int8 cmd);

static void LCD_vSend_Falling_Edge();

void LCD_vSend_Char(u_int8 data);

void LCD_vSend_String(u_int8 *ptr);

void LCD_vMove_Cursor(u_int8 row, u_int8 position);

void LCD_vClear_Screen();

void LCD_vSend_Number(u_int32 number);

void LCD_vSend_Real_Number(float64 number);
#endif /* LCD_ECU_DRIVER_H_ */