#include <avr/io.h>
#include <util/delay.h>
#include "mcp23008.h"

#define DSDA MCPSDA
#define DSCL MCPSCL
#define DPORTNAME MCPPORTNAME
#define I2CNEEDGETBYTE
#define I2CSPEEDBASE 2
#include "static_i2c.h"

//Returns 0 on success.
uint8_t SetMCPReg( uint8_t mcp_addy, uint8_t reg, uint8_t value )
{
	ConfigI2C();

	SendStart();
	if( SendByte( (mcp_addy << 1) | 0 ) ) goto quit;
	if( SendByte( reg ) ) goto quit;
	if( SendByte( value ) ) goto quit;
	SendStop();
/*
	SendStart();
	SendByte( (mcp_addy << 1) | 0 );
	SendByte( reg );
	SendByte( value );
	SendStop();*/
	return 0;
quit:
	SendStop();
	return 1;
}

//Returns gotten value.
uint8_t GetMCPReg( uint8_t mcp_addy, uint8_t reg )
{
	ConfigI2C();
}

