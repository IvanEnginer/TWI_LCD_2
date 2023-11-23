#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "TWI.h"
#include "LCD_I2C.h"

int NewState,OldState,vol,upState,dowState;
char buf[10];

ISR(TIMER2_COMP_vect)
{
	NewState=PINA&0b00000011;
	if (NewState!=OldState)
	{
		switch(OldState)
		{
			case 2:
			{
				if(NewState == 3) upState++;
				if(NewState == 0)dowState++;
				break;
			}
			case 0:
			{
				if(NewState == 2) upState++;
				if(NewState == 1) dowState++;
				break;
			}
			case 1:
			{
				if(NewState == 0) upState++;
				if(NewState == 3) dowState++;
				break;
			}
			case 3:
			{
				if(NewState == 1) upState++;
				if(NewState == 2) dowState++;
				break;
			}
		}
		OldState=NewState;
	}
		if (upState >= 4)
		{
			vol++;
			upState = 0;
					switch(vol)
					{
						case 0:{sprintf(buf,"Test 1");//переводим в строку
							lcd_clear();//переводим курсор
							lcd_putstring(buf);//рисуем строку
						break;}
						case 1:{sprintf(buf,"Test 2");//переводим в строку
							lcd_clear();//переводим курсор
							lcd_putstring(buf);
						break;}
						case 2:{sprintf(buf,"Test 3");//переводим в строку
							lcd_clear();//переводим курсор
							lcd_putstring(buf);
						break;}
						case 3:{sprintf(buf,"Test 4");//переводим в строку
							lcd_clear();//переводим курсор
							lcd_putstring(buf);
						break;}
					}
			
		}
		if (dowState >= 4)
		{
			vol--;
			dowState = 0;
					switch(vol)
					{
						case 3:{sprintf(buf,"Test 1");//переводим в строку
							lcd_clear();//переводим курсор
							lcd_putstring(buf);//рисуем строку
						break;}
						case 2:{sprintf(buf,"Test 2");//переводим в строку
							lcd_clear();//переводим курсор
							lcd_putstring(buf);
						break;}
						case 1:{sprintf(buf,"Test 3");//переводим в строку
							lcd_clear();//переводим курсор
							lcd_putstring(buf);
						break;}
						case 0:{sprintf(buf,"Test 4");//переводим в строку
							lcd_clear();//переводим курсор
							lcd_putstring(buf);
						break;}
					}
		}
				if (vol == 4)
				{
					vol=0;
				}
				if (vol < 0)
				{
					vol=0;
				}
				
}

int main(void)
{
	I2C_Init();//инициализация модуля
	lcd_init();//инициализация LCD
	lcd_clear();//очистка LCD и перевод курсора в 0.0
	PORTA=0x03;
	DDRA=0x00;
	PORTB=0x00;
	DDRB=0xFF;
	ASSR=0x00;
	TCCR2=0x0F;
	TCNT2=0x00;
	OCR2=0xC3;
	TIMSK=0x80;
	sei();
	while(1)
	{		
	}
}