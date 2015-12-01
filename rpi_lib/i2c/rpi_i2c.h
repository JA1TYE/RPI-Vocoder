#ifndef RPILIB_I2C_H
#define RPILIB_I2C_H

// include
#include <stdint.h>
#include "../rpi_type.h"
#include "../peripherals/rpi_peripherals.h"

//C register definition
#define I2CEN	15
#define INTR	10
#define INTT	9
#define INTD	8
#define ST	7
#define CLEAR 4 //2bits
#define READ	0

//S　register definition
#define CLKT	9
#define ERR	8
#define RXF	7
#define TXE	6
#define RXD	5
#define TXD	4
#define RXR	3
#define TXW	2
#define DONE	1
#define TA	0

//DLEN register definition
#define DLEN	0 //16bits

//A register definition
#define ADDR	0 //7bits

//FIFO register definition	
#define DATA	0 //8bits

//DIV register definition
#define CDIV	0 //16bits

//DEL register definition
#define FEDL	16 //16bits
#define REDL	0 //16bits

//CLKT register definition
#define TOUT	0 //15bits

// functions
void I2C_Write(uint8_t addr,uint8_t caddr,uint16_t data);
void I2S_Init(void);
void I2S_deInit(void);

#endif
