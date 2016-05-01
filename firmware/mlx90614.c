#include <avr/io.h>
#include <util/delay.h>
#include "mlx90614.h"
#include "avr_print.h"

#define DSDA MLXSDA
#define DSCL MLXSCL
#define DPORTNAME MLXPORTNAME
#define I2CNEEDGETBYTE
#define I2CSPEEDBASE 1.0
#define I2CPREFIX ML
#include "static_i2c.h"

int Get90614( uint8_t reg, uint8_t * valo )
{
	int r;
/*	MLSendStart();
	if( MLSendByte( (mlx_addy << 1) | 0 ) ) { r = -1; goto quit; }
	if( MLSendByte( reg ) ) { r = -2; goto quit; }
	MLSendStop();

	SendStart();
	if( MLSendByte( (mlx_addy << 1) | 1 ) ) { r = -3; goto quit; }
	valo[0] = MLGetByte(0);
	valo[1] = MLGetByte(0);
	valo[2] = MLGetByte(1);
	MLSendStop();*/

	MLSendStart();
	if( MLSendByte( (mlx_addy << 1) | 0 ) )
	{
		r = -1;
		goto quit;
	}
	if( MLSendByte( reg ) )
	{
		r = -2;
		goto quit;
	}
	MLSendRS();
//	MLSendStop();
//	MLSendStart();
	if( MLSendByte( (mlx_addy << 1) | 1 ) )
	{
		r = -3;
		goto quit;
	}
	valo[0] = MLGetByte(0);
	valo[1] = MLGetByte(0);
	valo[2] = MLGetByte(1);
	MLSendStop();


	return 0;
quit:
	MLSendStop();
	return r;
}



int Setup90614()
{
	MLConfigI2C();
}

float Read90614()
{
	int r;
	uint8_t dat[3];
	r = Get90614(0x00 | 0x07, &dat[0]);
	if( r ) return (0.0/0.0);
/*	sendchr(0);
	sendchr(':');
	sendhex2(r);
	sendchr('-');
	sendhex2(dat[0]);
	sendhex2(dat[1]);
	sendhex2(dat[2]);
	sendchr('\n');*/
	uint16_t re = (dat[1]<<8)|dat[0];
	float rr = re * 0.02;
	rr -= 273.15;
	return rr;
}


