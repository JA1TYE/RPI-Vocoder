#ifndef RPILIB_PERIPHERALS_H
#define RPILIB_PERIPHERALS_H
 
#include "../rpi_type.h"

#ifdef RASPI_2
#define PHY_PERI_ADDR(x) (0x3f000000 + (x))
#endif

#ifndef RASPI_2 
#define PHY_PERI_ADDR(x) (0x20000000 + (x))
#endif

// GPIO Peripheral
#define GPIO_BASE	(0x00200000)
#define GPFSEL0		((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x00))
#define GPFSEL1		((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x04))
#define GPFSEL2		((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x08))
#define GPFSEL3		((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x0c))
#define GPFSEL4		((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x10))
#define GPFSEL5		((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x14))
#define GPSET0		((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x1c))
#define GPSET1		((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x20))
#define GPCLR0		((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x28))
#define GPCLR1		((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x2c))
#define GPLEV0		((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x34))
#define GPLEV1		((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x38))
// for GPFSEL mask
// use AND mask
#define GPFSEL_MASK_IN(n)	(~(vu32_t)(0x07 << ((n % 10) * 3)))
// use OR mask
#define GPFSEL_MASK_OUT(n)	(0x01 << ((n % 10) * 3))
#define GPFSEL_MASK_ALT0(n)	(0x04 << ((n % 10) * 3))
#define GPFSEL_MASK_ALT1(n)	(0x05 << ((n % 10) * 3))
#define GPFSEL_MASK_ALT2(n)	(0x06 << ((n % 10) * 3))
#define GPFSEL_MASK_ALT3(n)	(0x07 << ((n % 10) * 3))
#define GPFSEL_MASK_ALT4(n)	(0x03 << ((n % 10) * 3))
#define GPFSEL_MASK_ALT5(n)	(0x02 << ((n % 10) * 3))
// GPIO PULLUP/DOWN
#define GPPUD 		((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x94))
#define GPPUDCLK0	((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x98))
#define GPPUDCLK1	((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x98))


// SystemTimer Peripheral
#define SYST_BASE	(0x00003000)
#define SYST_CS		((vu32_t *)PHY_PERI_ADDR(SYST_BASE + 0x00))
#define SYST_CLO	((vu32_t *)PHY_PERI_ADDR(SYST_BASE + 0x04))
#define SYST_CHI	((vu32_t *)PHY_PERI_ADDR(SYST_BASE + 0x08))
#define SYST_C0		((vu32_t *)PHY_PERI_ADDR(SYST_BASE + 0x0c))
#define SYST_C1		((vu32_t *)PHY_PERI_ADDR(SYST_BASE + 0x10))
#define SYST_C2		((vu32_t *)PHY_PERI_ADDR(SYST_BASE + 0x14))
#define SYST_C3		((vu32_t *)PHY_PERI_ADDR(SYST_BASE + 0x18))


// UART peripheral
#define UART0_BASE		0x00201000
#define UART0_DR		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x00))
#define UART0_RSRECR	((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x04))
#define UART0_FR		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x18))
// #define UART0_ILPR		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x20)) // not use
#define UART0_IBRD		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x24))
#define UART0_FBRD		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x28))
#define UART0_LCRH		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x2c))
#define UART0_CR		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x30))
#define UART0_IFLS		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x34))
#define UART0_IMSC		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x38))
#define UART0_RIS		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x3c))
#define UART0_MIS		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x40))
#define UART0_ICR		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x44))
#define UART0_DMACR		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x48))
#define UART0_ITCR		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x80))
#define UART0_ITIP		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x84))
#define UART0_ITOP		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x88))
#define UART0_TDR		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x8c))


// SPI0 peripheral
#define SPI0_BASE		(0x00204000)
#define SPI0_CS			((vu32_t *)PHY_PERI_ADDR(SPI0_BASE + 0x00))
#define SPI0_FIFO		((vu32_t *)PHY_PERI_ADDR(SPI0_BASE + 0x04))
#define SPI0_CLK		((vu32_t *)PHY_PERI_ADDR(SPI0_BASE + 0x08))
#define SPI0_DLEN		((vu32_t *)PHY_PERI_ADDR(SPI0_BASE + 0x0C))
#define SPI0_LTOH		((vu32_t *)PHY_PERI_ADDR(SPI0_BASE + 0x10))
#define SPI0_DC			((vu32_t *)PHY_PERI_ADDR(SPI0_BASE + 0x14))

// I2C(BSC1) peripheral
#define BSC1_BASE	(0x00804000)
#define BSC1_C		((vu32_t *)PHY_PERI_ADDR(BSC1_BASE + 0x00))
#define BSC1_S		((vu32_t *)PHY_PERI_ADDR(BSC1_BASE + 0x04))
#define BSC1_DLEN	((vu32_t *)PHY_PERI_ADDR(BSC1_BASE + 0x08))
#define BSC1_A		((vu32_t *)PHY_PERI_ADDR(BSC1_BASE + 0x0C))
#define BSC1_FIFO	((vu32_t *)PHY_PERI_ADDR(BSC1_BASE + 0x10))
#define BSC1_DIV	((vu32_t *)PHY_PERI_ADDR(BSC1_BASE + 0x14))
#define BSC1_DEL	((vu32_t *)PHY_PERI_ADDR(BSC1_BASE + 0x18))
#define BSC1_CLKT	((vu32_t *)PHY_PERI_ADDR(BSC1_BASE + 0x1C))


// Timer(ARM side) peripheral
#define TIMER_BASE			(0x0000B000)
#define TIMER_LOAD			((vu32_t *)PHY_PERI_ADDR(TIMER_BASE + 0x400))
#define TIMER_VALUE			((vu32_t *)PHY_PERI_ADDR(TIMER_BASE + 0x404))
#define TIMER_CONTROL		((vu32_t *)PHY_PERI_ADDR(TIMER_BASE + 0x408))
#define TIMER_IRQ_CLR		((vu32_t *)PHY_PERI_ADDR(TIMER_BASE + 0x40C))
#define TIMER_RAWIRQ		((vu32_t *)PHY_PERI_ADDR(TIMER_BASE + 0x410))
#define TIMER_MASKEDIRQ		((vu32_t *)PHY_PERI_ADDR(TIMER_BASE + 0x414))
#define TIMER_RELOAD		((vu32_t *)PHY_PERI_ADDR(TIMER_BASE + 0x418))
#define TIMER_PREDIVIDER	((vu32_t *)PHY_PERI_ADDR(TIMER_BASE + 0x41C))
#define TIMER_FREECOUNTER	((vu32_t *)PHY_PERI_ADDR(TIMER_BASE + 0x420))

// I2S peripheral
#define I2S_BASE			(0x00203000)
#define I2S_CS_A			((vu32_t *)PHY_PERI_ADDR(I2S_BASE + 0x00))
#define I2S_FIFO_A			((vu32_t *)PHY_PERI_ADDR(I2S_BASE + 0x04))
#define I2S_MODE_A			((vu32_t *)PHY_PERI_ADDR(I2S_BASE + 0x08))
#define I2S_RXC_A			((vu32_t *)PHY_PERI_ADDR(I2S_BASE + 0x0C))
#define I2S_TXC_A			((vu32_t *)PHY_PERI_ADDR(I2S_BASE + 0x10))
#define I2S_DREQ_A			((vu32_t *)PHY_PERI_ADDR(I2S_BASE + 0x14))
#define I2S_INTEN_A			((vu32_t *)PHY_PERI_ADDR(I2S_BASE + 0x18))
#define I2S_INTSTC_A			((vu32_t *)PHY_PERI_ADDR(I2S_BASE + 0x1C))
#define I2S_GRAY			((vu32_t *)PHY_PERI_ADDR(I2S_BASE + 0x20))

//Clock Management
#define CM_BASE			(0x00101000)
#define CM_GP0CTL			((vu32_t *)PHY_PERI_ADDR(CM_BASE + 0x70))
#define CM_GP0DIV			((vu32_t *)PHY_PERI_ADDR(CM_BASE + 0x74))
#define CM_GP1CTL			((vu32_t *)PHY_PERI_ADDR(CM_BASE + 0x78))
#define CM_GP1DIV			((vu32_t *)PHY_PERI_ADDR(CM_BASE + 0x7C))
#define CM_PCMCTL			((vu32_t *)PHY_PERI_ADDR(CM_BASE + 0x98))
#define CM_PCMDIV			((vu32_t *)PHY_PERI_ADDR(CM_BASE + 0x9C))
#define CM_PASSWD			0x5a000000

//PLL Registers(?)
#define A2W_BASE			(0x00102000)


// Interrupt
#define INTERRUPT_BASE					(0x0000B000)
#define INTERRUPT_IRQ_BASIC_PENDING		((vu32_t *)PHY_PERI_ADDR(INTERRUPT_BASE + 0x200))
#define INTERRUPT_IRQ_PENDING1			((vu32_t *)PHY_PERI_ADDR(INTERRUPT_BASE + 0x204))
#define INTERRUPT_IRQ_PENDING2			((vu32_t *)PHY_PERI_ADDR(INTERRUPT_BASE + 0x208))
#define INTERRUPT_FIQ_CTRL				((vu32_t *)PHY_PERI_ADDR(INTERRUPT_BASE + 0x20C))
#define INTERRUPT_ENABLE_IRQS1			((vu32_t *)PHY_PERI_ADDR(INTERRUPT_BASE + 0x210))
#define INTERRUPT_ENABLE_IRQS2			((vu32_t *)PHY_PERI_ADDR(INTERRUPT_BASE + 0x214))
#define INTERRUPT_ENABLE_BASIC_IRQS		((vu32_t *)PHY_PERI_ADDR(INTERRUPT_BASE + 0x218))
#define INTERRUPT_DISABLE_IRQS1			((vu32_t *)PHY_PERI_ADDR(INTERRUPT_BASE + 0x21C))
#define INTERRUPT_DISABLE_IRQS2			((vu32_t *)PHY_PERI_ADDR(INTERRUPT_BASE + 0x220))
#define INTERRUPT_DISABLE_BASIC_IRQS	((vu32_t *)PHY_PERI_ADDR(INTERRUPT_BASE + 0x224))


#endif
