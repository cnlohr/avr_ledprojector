#ifndef _MCP23008_H
#define _MCP23008_H

#include <stdint.h>

#define MCPSCL 0
#define MCPSDA 1
#define MCPPORTNAME A

//Returns 0 on success.
uint8_t SetMCPReg( uint8_t mcp_addy, uint8_t reg, uint8_t value );

//Returns gotten value.
uint8_t GetMCPReg( uint8_t mcp_addy, uint8_t reg );

#endif
