#ifndef _MLX90614_H
#define _MLX90614_H


#define MLXSCL 0
#define MLXSDA 1
#define MLXPORTNAME A

#define mlx_addy 0x5A

int Setup90614();
float Read90614();

#endif

