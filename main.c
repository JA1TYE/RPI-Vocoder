#include "rpi_lib/rpi.h"
#include <stdio.h>
#include <stdint.h>

#define LON() *GPSET0 |= 1 << 17
#define LOFF() *GPCLR0 |= 1 << 17

#define ACT_ON() *GPCLR0 |= 1 << 16
#define ACT_OFF() *GPSET0 |= 1 << 16

typedef struct{
	float L;
	float B;
	float H;
	float D1;
	float D2;
	float F;
} filter_t;

//Carrier 1st stage
filter_t C_1st[10];
filter_t C_2nd[10];
filter_t M_1st[10];
filter_t M_2nd[10];

float L[40];
float B[40];
float H[40];
float D1[40];
float D2[40];
float F[40];

float F_1st[10] = {
	0.029834,
	0.042838,
	0.061871,
	0.092789,
	0.13912,
	0.203403,
	0.297251,
	0.42514,
	0.608986,
	0.895253
};

float F_2nd[10] = {
	0.036142,
	0.051894,
	0.074949,
	0.11239,
	0.168474,
	0.246214,
	0.35948,
	0.513192,
	0.732231,
	1.066177
};

float MixLevel[10] = {
	1.0,1.0,1.0,1.0,0.823529,
	0.682927,0.56,0.56,0.56,0.56
};

float Env[10] = {0.0};
float Eg = 0.986755; 

float Q_1st = 0.145095;
float Q_2nd = 0.146385;

//prototype definition
void initAIC23B(void){
	I2C_Init();

	
	//Whole Reset
	I2C_Write(0x1A,0x0F,0x00);
	delay(10);
	
	//set Line inpput Left channel volume
	I2C_Write(0x1A,0x00,0x17);
	//set Line inpput Right channel volume
	I2C_Write(0x1A,0x01,0x17);
	//bypass disable
	I2C_Write(0x1A,0x04,0x12);
	//De-emphasis  disable
	I2C_Write(0x1A,0x05,0x00);
	//Line and ADC enable
	I2C_Write(0x1A,0x06,0x02);
	//Format set
	I2C_Write(0x1A,0x07,0x4E);
	//Set sample rate
	I2C_Write(0x1A,0x08,0x00);
	//Activate
	I2C_Write(0x1A,0x09,0x01);
}

inline float s_fabs(float a){
	if(a < 0.0)return (a * -1.0);
	else return a;
}

void vocoder_init(void){
	int i;	
	for(i = 0;i < 40;i++){
		L[i] = 0.0;
		B[i] = 0.0;
		H[i] = 0.0;
		if(i < 10 || (i > 19 && i < 30))F[i] = F_1st[i % 10];
		else F[i] = F_2nd[i % 10];
	}
	for(i = 0;i < 10;i++){
		Env[i] = 0.0;	
	}
}

inline float vocoder(float car,float mod){
	int i;

	for(i = 0;i < 10;i++){
		//Carrier 1st stage
		L[i] = L[i] + F[i] * B[i];
		H[i] = car - L[i] - Q_1st * B[i];
		B[i] = F[i] * H[i] + B[i];
		
		//Carrier 2nd stage
		L[i + 10] = L[i + 10] + F[i + 10] * B[i + 10];
		H[i + 10] = B[i] - L[i + 10] - Q_2nd * B[i + 10];
		B[i + 10] = F[i + 10] * H[i + 10] + B[i + 10];

		//Modulator 1st stage
		L[i + 20] = L[i + 20] + F[i + 20] * B[i + 20];
		H[i + 20] = mod - L[i + 20] - Q_1st * B[i + 20];
		B[i + 20] = F[i + 20] * H[i + 20] + B[i + 20];	

		//Modulator 2nd stage
		L[i + 30] = L[i + 30] + F[i + 30] * B[i + 30];;
		H[i + 30] = B[i + 20] - L[i + 30] - Q_2nd * B[i + 30];
		B[i + 30] = F[i + 30] * H[i + 30] + B[i + 30];

		//Envelope stage
		Env[i] *= Eg;
		Env[i] += (1 - Eg)*s_fabs(B[i + 30]);

	}

	float acc = 0.0;
	for(i = 0;i < 10;i++){
		acc += MixLevel[i] * Env[i] * B[i + 10];
	}
	
	return acc;
}

void hangup_handler(){
	while(1){
		ACT_ON();
		delay(100);
		ACT_OFF();
		delay(100);
	}
}

void dabort_handler(){
	while(1){
		ACT_ON();
		delay(1000);
		ACT_OFF();
		delay(1000);
	}	
}

int main(void){
	uint32_t i = 0;
	uint32_t t = 0;
	uint32_t l; 
	volatile int16_t car;
	volatile int16_t mod;	
	float res;
	float i_scale;
	int16_t res_i;
	rpi_init();

	delay(100);
	i_scale = 1.0/32768.0;
	disable_all_IRQ();
	
	*GPFSEL1 |= (1 << (6 * 3)) | (1 << (7 * 3));

	//Initialize I2S
	initAIC23B();
	vocoder_init();	
	
	delay(100);
	
	I2S_Init();


	while(1){
		if(I2S_rxCanRead() > 0){
			i = I2S_Read();
			car = (i >> 16)& 0xffff; 
			mod = i & 0xffff;					
		}
		if(I2S_txCanWrite() > 0){
			t += 768;
			res = vocoder((float)car*i_scale,(float)mod*i_scale);
			res = (res * 16384.0);
			if(res > 32767.0)res_i = 32767;
			else if(res < -32768.0)res_i = -32768;
			else res_i = (int16_t)res;			
			I2S_Write(res_i,res_i);
		}		
	}
	
	return 0;
}
