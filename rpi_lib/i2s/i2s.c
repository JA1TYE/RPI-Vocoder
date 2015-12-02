#include "rpi_i2s.h"

#define PI_VER 0 //0:Raspberry Pi A/B 1:Raspberry Pi A+/B+/Zero
#define DAC_TYPE 1 //0:PCM510x 1:TLV320AIC23B(AIC23B performed as a master)

//for TLV320AIC23B
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

#if DAC_TYPE == 0
	//Set Clock
	*CM_PCMCTL = 0x5a000621;//SRC -> OSC,KILL
	//19.2M/(48k * 64fs) = 6.25
	//23-12 Integer part
	//11-10 Fractional part
	*CM_PCMDIV = 0x5a000000 | (6 << 12) | (1 << 10);
	*CM_PCMCTL = 0x5a000611;//Enabling 3-stage MASH fractional divider	

#elif DAC_TYPE == 1
	//Set Clock
	*CM_PCMCTL = 0x5a000021;//SRC -> OSC,KILL
	//19.2MHz/1 = 9.6MHz
	//23-12 Integer part
	//11-10 Fractional part
	*CM_PCMDIV = 0x5a000000 | (1 << 12);
	*CM_PCMCTL = 0x5a000011;
#else
#error you should define appropriate DAC_TYPE
#endif

#if PI_VER == 0
	//Set Pin Functions(for Raspberry Pi A/B)
	//GPIO28(PCM_CLK) & 29(PCM_FS) -> ALT2
	*GPFSEL2 &= ~((7 << (8 * 3))|(7 << (9 * 3)));
	*GPFSEL2 |=  ((6 << (8 * 3))|(6 << (9 * 3)));

	//GPIO30(PCM_DIN) & 31(PCM_DOUT) -> ALT2
	*GPFSEL3 &= ~((7 << (1 * 3))|(7 << (0 * 3)));
	*GPFSEL3 |=  ((6 << (1 * 3))|(6 << (0 * 3)));

#elif PI_VER == 1
	//Set Pin Functions(for Raspberry Pi A+/B+/Zero)
	//GPIO18(PCM_CLK) & 19(PCM_FS) -> ALT0
	*GPFSEL1 &= ~((7 << (8 * 3))|(7 << (9 * 3)));
	*GPFSEL1 |=  ((4 << (8 * 3))|(4 << (9 * 3)));

	//GPIO20(PCM_DIN) & 21(PCM_DOUT) -> ALT0
	*GPFSEL2 &= ~((7 << (1 * 3))|(7 << (0 * 3)));
	*GPFSEL2 |=  ((4 << (1 * 3))|(4 << (0 * 3)));
#else
#error you should define appropriate PI_VER
#endif

#if DAC_TYPE == 0
	//Set the MODE_A Reg.
	*I2S_MODE_A |= (1 << I2S_FTXP)|((64 - 1) << I2S_FLEN)|(32 << I2S_FSLEN)|(1 << I2S_CLKI);

	//Enable the I2S peripheral
	*I2S_CS_A |= (1 << I2S_EN);	
	
	//Set the TXC_A Reg.
	*I2S_TXC_A = 	(1 << I2S_CH1EN)|(1  << I2S_CH1POS)|(8 << I2S_CH1WID)|
			(1 << I2S_CH2EN)|(33 << I2S_CH2POS)|(8 << I2S_CH2WID);

	//Assert the TXCLR and RXCLR
	*I2S_CS_A |= (1 << I2S_TXCLR)|(1 << I2S_SYNC);
	//Wait 2 PCM_CLK
	while(*I2S_CS_A & (1 << I2S_SYNC));

	//Set TXFIFO Threshold
	*I2S_CS_A |= (3 << I2S_TXTHR);

#elif DAC_TYPE == 1
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
#else
#error you should define appropriate DAC_TYPE
#endif

	//Fill the TX FIFO
	for(i = 0;i < 32;i++){
		I2S_Write(0,0);
	}

	//Enable the I2S peripheral
	*I2S_CS_A |= (1 << I2S_EN);	

	//Clear the Error
	*I2S_CS_A |= ((1 << I2S_CS_A_TXERR)|(1 << I2S_CS_A_RXERR));

#if DAC_TYPE == 0
	//Start transmission
	*I2S_CS_A |= ((1 << I2S_TXON));

	while(*I2S_CS_A & (1 << I2S_TXSYNC) == 0);
#elif DAC_TYPE == 1
	//Start transmission and receive
	*I2S_CS_A |= ((1 << I2S_TXON)|(1 << I2S_RXON));

	while(*I2S_CS_A & (1 << I2S_TXSYNC) == 0);
	while(*I2S_CS_A & (1 << I2S_RXSYNC) == 0);
#endif
}

void I2S_deInit(void){
#if DAC_TYPE == 0
	//End transmission
	*I2S_CS_A &= ~(1 << I2S_TXON);
#elif DAC_TYPE == 1
	//End transmission
	*I2S_CS_A &= ~((1 << I2S_TXON)|(1 << I2S_RXON));
#endif

}

