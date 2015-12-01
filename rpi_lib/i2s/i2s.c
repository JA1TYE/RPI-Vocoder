#include "rpi_i2s.h"

//37.5kHz設定になっている

uint32_t I2S_txCanWrite(void){
	return (((*I2S_CS_A) & (1 << I2S_CS_A_TXW)) == 0)?0:1;
}

uint32_t I2S_rxCanRead(void){
	return (((*I2S_CS_A) & (1 << I2S_CS_A_RXR)) == 0)?0:1;
}

void I2S_Write(int16_t left,int16_t right){
	*I2S_FIFO_A = (left << 16)|(right & 0xffff);
}

uint32_t I2S_Read(void){
	uint32_t res;
	res = *I2S_FIFO_A;
	return res;
}
void I2S_Init(void){
	int i = 0;

	//Set Clock
	*CM_PCMCTL = 0x5a000021;//SRC -> OSC,KILL
	//19.2MHz/(37.5k * 64fs) = 8
	//23-12 Integer part
	//11-10 Fractional part
	*CM_PCMDIV = 0x5a000000 | (1 << 12);
	*CM_PCMCTL = 0x5a000011;

	//Set Pin Functions
	//GPIO28 & 29 -> ALT2
	*GPFSEL2 &= ~((7 << (8 * 3))|(7 << (9 * 3)));
	*GPFSEL2 |=  ((6 << (8 * 3))|(6 << (9 * 3)));

	//GPIO31 & 30 -> ALT2
	*GPFSEL3 &= ~((7 << (1 * 3))|(7 << (0 * 3)));
	*GPFSEL3 |=  ((6 << (1 * 3))|(6 << (0 * 3)));
	
	//クロックの設定
	//19.2M/(48k * 256fs) = 1.5625 = 1 + 0.5 + 0.0625
	//11bit目:0.5,10bit目:0.25,9bit目:0.125,8bit目:0.0625
	//PLLA is not working
	//PLLC is 1GHz
	//PLLD is 500MHz
	//PLLHDMI is 216MHz
	//216MHz / 12.288MHz = 17.578125
	//Frac. part = 0.578125
	//Frac. part length is 12bit
	//So Frac. part Reg. value is 0.578125 * 4096 = 2368
	*CM_GP0CTL = 0x5a000021;
	while((*CM_GP0CTL & (1 << 7)) != 0);
	*CM_GP0DIV = 0x5a000000 | (2<< 12);
	*CM_GP0CTL = 0x5a000011;

	*GPPUD = 0x00000000;
	*GPPUDCLK0 = 1 << 4;
	for(i=0;i<150;i++){
		// nop
		asm("mov r0,r0");
	}
	*GPPUDCLK0 = 0;

	//Set the MODE_A Reg.
	*I2S_MODE_A |= (1 << I2S_FTXP)|(1 << I2S_FRXP)|((64 - 1) << I2S_FLEN)|(32 << I2S_FSLEN)|
			(1 << I2S_CLKM)|(1 << I2S_FSM)|(1 << I2S_CLKI);

	//Enable the I2S peripheral
	*I2S_CS_A |= (1 << I2S_EN);	
	
	//Set the TXC_A Reg.
	*I2S_TXC_A = 	(1 << I2S_CH1EN)|(1  << I2S_CH1POS)|(8 << I2S_CH1WID)|
			(1 << I2S_CH2EN)|(33 << I2S_CH2POS)|(8 << I2S_CH2WID);

	//Set the RXC_A Reg.
	*I2S_RXC_A = 	(1 << I2S_CH1EN)|(1  << I2S_CH1POS)|(8 << I2S_CH1WID)|
			(1 << I2S_CH2EN)|(33 << I2S_CH2POS)|(8 << I2S_CH2WID);

	//Assert the TXCLR and RXCLR
	*I2S_CS_A |= ((1 << I2S_TXCLR)|(1 << I2S_SYNC)|(1 << I2S_RXCLR));
	//Wait 2 PCM_CLK
	while(*I2S_CS_A & (1 << I2S_SYNC));

	//Set TXFIFO Threshold
	*I2S_CS_A |= (3 << I2S_TXTHR);
	
	//Set RXFIFO Threshold
	*I2S_CS_A |= (3 << I2S_RXTHR);

	//Fill the TX FIFO
	for(i = 0;i < 32;i++){
		I2S_Write(0,0);
	}

	//Enable the I2S peripheral
	*I2S_CS_A |= (1 << I2S_EN);	

	//Clear the Error
	*I2S_CS_A |= ((1 << I2S_CS_A_TXERR)|(1 << I2S_CS_A_RXERR));
	
	//Start transmission
	*I2S_CS_A |= ((1 << I2S_TXON)|(1 << I2S_RXON));

	while(*I2S_CS_A & (1 << I2S_TXSYNC) == 0);
	while(*I2S_CS_A & (1 << I2S_RXSYNC) == 0);
}

void I2S_deInit(void){
	//End transmission
	*I2S_CS_A &= ~(1 << I2S_TXON);
}

