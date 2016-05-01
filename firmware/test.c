#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include "avr_print.h"
#include "mcp23008.h"
#include "mlx90614.h"
#include <stdio.h>

void delay_ms(uint32_t time) {
  uint32_t i;
  for (i = 0; i < time; i++) {
    _delay_ms(1);
  }
}

#define NOOP asm volatile("nop" ::)

static void setup_clock( void )
{
	/*Examine Page 33*/

	CLKPR = 0x80;	/*Setup CLKPCE to be receptive*/
	CLKPR = 0x00;	/*No scalar*/
}


//Value = 0..f, 0x10 bit indicates period.
//
//  -1-
// 7   2
//  -4-
// 6   3
//  -5-  0
uint8_t vals_norev[17] = {
	0b11101110,  //0
	0b00001100,  //1
	0b01110110,  //2
	0b00111110,  //3
	0b10011100,  //4
	0b10111010,  //5
	0b11111000,  //6
	0b00001110,  //7
	0b11111110,  //8
	0b10011110,  //9
	0b11011110,  //A
	0b11111000,  //B
	0b01110000,  //C
	0b01111100,  //D
	0b11110010,  //E
	0b11010010,  //F
	0b00000000,  //Nothing	
};


//
//  -1-
// 2   7
//  -4-
// 3   6
//  -5-  0
uint8_t vals[17] = {
	0b11101110,  //0
	0b11000000,  //1
	0b10111010,  //2
	0b11110010,  //3
	0b11010100,  //4
	0b01110110,  //5
	0b01111110,  //6
	0b11000010,  //7
	0b11111110,  //8
	0b11010110,  //9
	0b11011110,  //A
	0b01111100,  //B
	0b00111000,  //C
	0b11111000,  //D
	0b00111110,  //E
	0b00011110,  //F
	0b00000000,  // Nothing
};
void UpdateDigit( int digit, int value )
{
	uint8_t val = vals[value];
	SetMCPReg( 0x20|digit, 0x00, 0x00 );
	SetMCPReg( 0x20|digit, 0x09, ~(val | ((value&0x10)?0x01:0x00)) );
}


int main( void )
{
	int r;
	setup_clock();
	
	setup_spi();

	UpdateDigit( 2, 8 );
	UpdateDigit( 1, 8 );
	UpdateDigit( 0, 8 );
//#define TEST

	r = Setup90614();
#ifdef TEST
	printf( "SETUP RESPONDED: %d\n", r );
#endif

	uint16_t add = 0;

	while(1)
	{
#ifdef TEST
		add++;
		printf( "%d\n", add );
#else
		float f = Read90614()*9.0/5.0 + 32.0;
		printf( "%d\n", add );

		add = f;
#endif
		UpdateDigit( 2, (add%10) );
		UpdateDigit( 1, ((add/10)%10) );
		UpdateDigit( 0, (add/100>0)?((add/100)%10):16 );
		_delay_ms(1);
	}

	return 0;
} 
