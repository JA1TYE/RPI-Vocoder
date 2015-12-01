#include "rpi_i2c.h"
#include "../delay/rpi_delay.h"

void I2C_Write(uint8_t addr,uint8_t caddr,uint16_t data){
	
	if((data & 0x0100) != 0){
		caddr = caddr << 1;
		caddr = caddr | 1;
	}
	else{
		caddr = caddr << 1;
	}
	
	data = data & 0xff;	

	//clear status register	
	*BSC1_S |= ((1 << CLKT)|(1 << ERR)|(1 << DONE));

	//set slave address
	*BSC1_A = addr;

	//Set read
	*BSC1_C &= ~(1 << READ);

	//Clear FIFO
	*BSC1_C |= (1 <<CLEAR);

	//Set data length(for now,fixed to 2)
	*BSC1_DLEN = 2; 

	//Set data to fifo
	*BSC1_FIFO = caddr;
	*BSC1_FIFO = data;
	
	//Start to send
	*BSC1_C |= ((1 << I2CEN)|(1 << ST));

	//polling
	while(*BSC1_S & (1 << DONE));
	delay(10);
}

void I2C_Init(void){
	//GPIO Function Select
	//GPIO2 and GPIO3 -> FUNCTION0
	*GPFSEL0 &= ~((7 << (2 * 3))|(7 << (3 * 3)));
	*GPFSEL0 |=  ((4 << (2 * 3))|(4 << (3 * 3)));
	
	*BSC1_DIV = 0;

	//I2C enable and clear fifo
	*BSC1_C |= (1 << CLEAR);
}

void I2C_deInit(void){
	//I2C enable and clear fifo
	*BSC1_C &= ~(1 << I2CEN);
}
