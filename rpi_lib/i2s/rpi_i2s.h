#ifndef RPILIB_I2S_H
#define RPILIB_I2S_H

// include
#include <stdint.h>
#include "../rpi_type.h"
#include "../peripherals/rpi_peripherals.h"
#include "../gpio/rpi_gpio.h"


//CS_A Register
#define I2S_STBY	25
#define I2S_SYNC	24
#define I2S_RXSEX	23
#define I2S_RXF	22
#define I2S_TXE	21
#define I2S_RXD	20
#define I2S_TXD	19
#define I2S_CS_A_RXR	18
#define I2S_CS_A_TXW	17
#define I2S_CS_A_RXERR	16
#define I2S_CS_A_TXERR	15
#define I2S_RXSYNC	14
#define I2S_TXSYNC	13
#define I2S_DMAEN	9
#define I2S_RXTHR	7	//2bits
#define I2S_TXTHR	5	//2bits
#define I2S_RXCLR	4
#define I2S_TXCLR	3
#define I2S_TXON	2
#define I2S_RXON	1
#define I2S_EN	0

//MODE_A Register
#define I2S_CLK_DIS	28
#define I2S_PDMN	27
#define I2S_PDME	26
#define I2S_FRXP	25
#define I2S_FTXP	24
#define I2S_CLKM	23
#define I2S_CLKI	22
#define I2S_FSM	21
#define I2S_FSI	20
#define I2S_FLEN	10	//10bits
#define I2S_FSLEN	0	//10bits

//RXC_A and TXC_A Register
#define I2S_CH1WEX	31
#define I2S_CH1EN	30
#define I2S_CH1POS	20	//10bits
#define I2S_CH1WID	16	//4bits
#define I2S_CH2WEX	15
#define I2S_CH2EN	14
#define I2S_CH2POS	4	//10bits
#define I2S_CH2WID	0	//4bits

//DREQ_A Register
#define I2S_TX_PANIC	24	//7bits
#define I2S_RX_PANIC	16	//7bits
#define I2S_TX	8	//7bits
#define I2S_RX	0	//7bits

//INTEN_A and INTSTC_A Register
#define I2S_INT_RXERR	3
#define I2S_INT_TXERR	2
#define I2S_INT_RXR	1
#define I2S_INT_TXW	0

//GRAY Register
#define I2S_GRAY_RXFIFOLEVEL	16
#define I2S_GRAY_FLUSHED	10
#define I2S_GRAY_RXLEVEL	4
#define I2S_GRAY_FLUSH	2
#define I2S_GRAY_CLR	1
#define I2S_GRAY_EN	0

// functions
uint32_t I2S_txCanWrite(void);
uint32_t I2S_rxCanRead(void);
void I2S_Write(int16_t left,int16_t right);
uint32_t I2S_Read(void);
void I2S_Init(void);
void I2S_deInit(void);

#endif
