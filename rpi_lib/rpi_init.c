#include "rpi.h"
#define ARM_AUX_CONTROL_SMP   (1 << 6)

#define ARM_CONTROL_BRANCH_PREDICTION      (1 << 11)
#define ARM_CONTROL_L1_INSTRUCTION_CACHE   (1 << 12)

void rpi_init(void){
	uint32_t controlRegister;
	uint32_t nAuxControl;
	uint32_t nControl;
	
	#ifdef RASPI_2
	asm volatile ("mrc p15, 0, %0, c1, c0,  1" : "=r" (nAuxControl));
	nAuxControl |= ARM_AUX_CONTROL_SMP;
	asm volatile ("mcr p15, 0, %0, c1, c0,  1" : : "r" (nAuxControl));   // SMP bit must be set according to ARM TRM


	asm volatile ("mrc p15, 0, %0, c1, c0,  0" : "=r" (nControl));
	nControl |= ARM_CONTROL_BRANCH_PREDICTION | ARM_CONTROL_L1_INSTRUCTION_CACHE;
	asm volatile ("mcr p15, 0, %0, c1, c0,  0" : : "r" (nControl) : "memory");
	#endif
	
	// bssのクリア
	clearBss();

	// GPIOをすべてINPUT_PULLUPに設定
	init_gpio();

	// 割り込み不許可
	disable_all_IRQ();

	// ベクタテーブルセット
	set_vector_table();

	// システムタイマーを初期化
	init_syst();

}
