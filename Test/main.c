/*
 * Keypad.c
 *
 * Created: 12-12-2019 09:37:10
 * Author : thom8865
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#define delay 50
#include <util/delay.h>
#include <stdio.h>
#include "stdio_setup.h"
#include <string.h>

void Init(void);
int ColumnScan(void);
int ReadRows(void);
void DecodeKeypad(int,int);

int main(void)
{
	UartInit();
	
	Init();
	int Column;
	int Row;
	
    while (1) 
    {
		Column = ColumnScan();
		_delay_ms(delay);
		Row = ReadRows();
		DecodeKeypad(Column, Row);
		//_delay_ms(1000);
		
    }
}

void Init()
{
	DDRC &= ~(1 << DDC4 | 1 << DDC5 | 1 << DDC6 | 1 << DDC7); // Sætter row lines til input
	DDRC |= (1 << DDC0) | (1 << DDC1) | (1 << DDC2) | (1 << DDC3); // Sætter column lines til output
	PORTC |= (1 << PC4) | (1 << PC5) | (1 << PC6) | (1 << PC7); // Enabler pull up på input (rows)
	PORTC |= (1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3); // Sætter outport porte til logisk 1
}

int ColumnScan()
{
	static int columnCounter = 1;
	PORTC |= (1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3); //Sætter output pins til logisk 1
	
	if (columnCounter == 1)
	{
		PORTC &= ~(1 << PC0); //Sætter bit til logisk 0
		columnCounter++;
		return 1;
	}
	else if (columnCounter == 2)
	{
		PORTC &= ~(1 << PC1);
		columnCounter++;
		return 2;
	}
	else if (columnCounter == 3)
	{
		PORTC &= ~(1 << PC2);
		columnCounter++;
		return 3;
	}
	else if (columnCounter == 4)
	{
		PORTC &= ~(1 << PC3);
		columnCounter = 1;
		return 4;
	}
	
    return 0;
}

int ReadRows()
{
	
	
	if (~PINC & (1 << PC7)) 
	{
		_delay_ms(10);
		if (~PINC & (1 << PC7))
		{
			return 5;
		}
	}
	
	if (~PINC & (1 << PC6))
	{
		_delay_ms(10);
		if (~PINC & (1 << PC6))
		{
			return 6;
		}
	}
	
	if (~PINC & (1 << PC5))
	{
		_delay_ms(10);
		if (~PINC & (1 << PC5))
		{
			return 7;
		}
	}
	
	if (~PINC & (1 << PC4))
	{
		_delay_ms(10);
		if (~PINC & (1 << PC4))
		{
			return 8;
		}
	}
	
	return 0;

}

void DecodeKeypad(int column, int row)
{
	int key = column * 10 + row;
	
	//Kolonnerne har numrene 1, 2, 3, 4 fra højre, og rækkerne har numrene 5 ,6 ,7 ,8 fra bunden
	//Key'en er en sammensætning af kolonne tallet og række tallet. eks kolonne 1 og række 7 giver key 17.
	
	switch (key)
	{
		case 48:
		printf("Du trykkede på tasten \"1\"\r\n");
		break;
		case 47:
		printf("Du trykkede på tasten \"4\"\r\n");
		break;
		case 46:
		printf("Du trykkede på tasten \"7\"\r\n");
		break;
		case 45:
		printf("Du trykkede på tasten \"*\"\r\n");
		break;
		case 38:
		printf("Du trykkede på tasten \"2\"\r\n");
		break;
		case 37:
		printf("Du trykkede på tasten \"5\"\r\n");
		break;
		case 36:
		printf("Du trykkede på tasten \"8\"\r\n");
		break;
		case 35:
		printf("Du trykkede på tasten \"0\"\r\n");
		break;
		case 28:
		printf("Du trykkede på tasten \"3\"\r\n");
		break;
		case 27:
		printf("Du trykkede på tasten \"6\"\r\n");
		break;
		case 26:
		printf("Du trykkede på tasten \"9\"\r\n");
		break;
		case 25:
		printf("Du trykkede på tasten \"#\"\r\n");
		break;
		case 18:
		printf("Du trykkede på tasten \"A\"\r\n");
		break;
		case 17:
		printf("Du trykkede på tasten \"B\"\r\n");
		break;
		case 16:
		printf("Du trykkede på tasten \"C\"\r\n");
		break;
		case 15:
		printf("Du trykkede på tasten \"D\"\r\n");
		break;
		default:
		/* Your code here */
		break;
	}
}