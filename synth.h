#ifndef SYNTH_H
#define SYNTH_H

#define EPS 1e-20
#define NOTE_OFFSET 24
#define CONST_0_95 0x3CCCCCCC

enum waveFormType{WF_SAW,WF_TRI,WF_PWM,WF_SIN,WF_NOISE,WF_UD};
enum egState{EG_WAIT,EG_ATTACK,EG_DECAY,EG_SUSTAIN,EG_RELEASE};
enum selectVCF{VCF_LPF,VCF_HPF,VCF_BPF};
enum EGselect{EG_VCA = 0,EG_VCA2 = 1,EG_VCF = 2};
enum VCOselect{SEL_VCO1 = 0,SEL_VCO2 = 1};

struct synthStruct{
	enum egState EGs[3];
	//filter coeffs
	int32_t lpOut;
	int32_t hpOut;
	int32_t bpOut;
	int32_t d1;
	int32_t d2;
	//VCO config
	uint8_t note;
	uint8_t velocity;
	uint64_t acc[2];
	//EG config
	int32_t egVal[3];
};

//Entire control parameter
struct egParam{
	int32_t AR;//table lookup
	int32_t DR;//table lookup
	int32_t SL;//table lookup
	int32_t RR;//table lookup
	int32_t INTEN;
	int32_t VEL;
	int32_t KTrack;
};

struct vcfParam{
	int32_t reso;
	int32_t cutoff;
	enum selectVCF filterType;
};

struct vcoParam{
	int coarseTune;//semitone
	int32_t fineTune;
	uint16_t pulseWidth;//0-512
	int32_t deTune;//0-1
	int32_t tLevel;
	int isSync;//0,1
	int32_t isRingMod;//0-1
	int32_t isFM;//0-1
	enum waveFormType wForm;
};

struct modParam{
	int32_t pitchBend;
	int32_t pitchSensitivity;
	int32_t modWheel;
	int32_t pressure;
};

struct lfoParam{
	uint32_t lfoSpeed;
	int32_t lfoInten;
};

//extern:actual definition are in main.c
extern struct egParam egP[3];
extern struct vcfParam fltP[1];
extern struct vcoParam vcoP[2];
extern struct modParam modP[1];
extern struct synthStruct tone[16];


#endif
